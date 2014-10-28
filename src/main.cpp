/**
 * @file
 *  This file is part of SWE1D
 *
 *  SWE1D is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SWE1D is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with SWE1D.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Diese Datei ist Teil von SWE1D.
 *
 *  SWE1D ist Freie Software: Sie koennen es unter den Bedingungen
 *  der GNU General Public License, wie von der Free Software Foundation,
 *  Version 3 der Lizenz oder (nach Ihrer Option) jeder spaeteren
 *  veroeffentlichten Version, weiterverbreiten und/oder modifizieren.
 *
 *  SWE1D wird in der Hoffnung, dass es nuetzlich sein wird, aber
 *  OHNE JEDE GEWAEHELEISTUNG, bereitgestellt; sogar ohne die implizite
 *  Gewaehrleistung der MARKTFAEHIGKEIT oder EIGNUNG FUER EINEN BESTIMMTEN
 *  ZWECK. Siehe die GNU General Public License fuer weitere Details.
 *
 *  Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 *  Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
 * 
 * @copyright 2013 Technische Universitaet Muenchen
 * @author Sebastian Rettenberger <rettenbs@in.tum.de>
 */

#include "types.h"
#include "WavePropagation.h"
#include "writer/ConsoleWriter.h"
#include "writer/VtkWriter.h"
#include "tools/args.h"

#include <cstring>


int main(int argc, char** argv)
{
	// Parse command line parameters
	tools::Args args(argc, argv);

	// Allocate memory
	// Water height
	T *h = new T[args.size()+2];
	// Momentum
	T *hu = new T[args.size()+2];
	// Bathymetry
	T *b = new T[args.size()+2];
	// Scenario	
	scenarios::scenarioBase* scenario;

	// Initialize scenario
	switch(args.scenario()){
	case 1:	
		scenario = new scenarios::Shock(args.size());
		break;
	case 2:
		scenario = new scenarios::Rare(args.size());
		break;
	default:		
		scenario = new scenarios::DamBreak(args.size());
		break;
	}

	// Initialize water height and momentum
	for (unsigned int i = 0; i < args.size()+2; i++)
		{
		h[i] = scenario->getHeight(i);
		
		hu[i] = scenario->getMomentum(i);

		b[i] = scenario-> getBathymetry(i);
		}

	// Create a writer that is responsible printing out values	
	
//	writer::ConsoleWriter writer;	
	writer::VtkWriter writer("results/swe1d", scenario->getCellSize());

	// Helper class computing the wave propagation
	WavePropagation wavePropagation(h, hu, b, args.size(), scenario->getCellSize());

	// Write initial data
	tools::Logger::logger.info("Initial data");

	// Current time of simulation
	T t = 0;
	
	// Collission-time for DamBreak simulation
	T collission_time = 0;

	writer.write(t, h, hu, b, args.size());

	for (unsigned int i = 0; i < args.timeSteps(); i++) {
		// Do one time step
		tools::Logger::logger << "Computing timestep " << i
				<< " at time " << t << std::endl;

		// Update boundaries
		wavePropagation.setOutflowBoundaryConditions();

		// Compute numerical flux on each edge
		T maxTimeStep = wavePropagation.computeNumericalFluxes();

		// Update unknowns from net updates
		wavePropagation.updateUnknowns(maxTimeStep);

		// Update time
		t += maxTimeStep;

		// Write new values
		writer.write(t, h, hu, b, args.size());
		
		// Save collission-time and stop Simulation if index of scenario is 3
		if((args.scenario() == 3 || args.scenario() == 0 ) 
			&& h[args.size() * 29000/30000] != scenario->getHeight(args.size() * 29000/30000)
			&& !collission_time)
		{					
			collission_time = t;
			if(args.scenario() == 3)
				i = args.timeSteps();
		}
	}
	
	// Print collission-time if DamBreak is used and a collission was detected
	if((args.scenario() == 3 || args.scenario() == 0 ) && collission_time)		
		tools::Logger::logger << "Water reached the village after " << collission_time << " secounds!" << std::endl;

	// Free allocated memory
	delete [] h;
	delete [] hu;
	delete scenario;

	return 0;
}
