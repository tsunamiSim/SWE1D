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

#ifndef TOOLS_ARGS_H_
#define TOOLS_ARGS_H_

#include "logger.h"

#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "./../scenarios/dambreak.h"
#include "./../scenarios/schock.h"
#include "./../scenarios/rare.h"
#include "./../scenarios/bathymetryEffect.h"
#include "./../scenarios/subcriticalFlow.h"
#include "./../scenarios/supercriticalFlow.h"

namespace tools
{

/**
 * Parse command line arguments
 */
class Args
{
private:
	/** Domain size */
	unsigned int m_size;
	/** Number of time steps we want to simulate */
	unsigned int m_timeSteps;
	/** Scenario we want to simulate */
	unsigned int m_scenario;
	
	

public:
	Args(int argc, char** argv)
		: m_size(100),
		  m_timeSteps(100.0),
		  m_scenario(0)
		
	{
		const struct option longOptions[] = {
			{"size", required_argument, 0, 's'},
			{"time", required_argument, 0, 't'},
			{"help", no_argument, 0, 'h'},
			{"scenario", required_argument, 0, 'z'},
			{0, 0, 0, 0}
		};

		int c, optionIndex;
		std::istringstream ss;
		while ((c = getopt_long(argc, argv, "s:t:h:z:",
			longOptions, &optionIndex)) >= 0) {
			switch (c) {
			case 0:
				tools::Logger::logger.error("Could not parse command line arguments");
				break;
			case 's':
				ss.clear();
				ss.str(optarg);
				ss >> m_size;
				std::cout << m_size << std::endl;
				break;
			case 't':
				ss.clear();
				ss.str(optarg);
				ss >> m_timeSteps;
				std::cout << m_timeSteps << std::endl;
				break;
			case 'h':
				printHelpMessage();
				exit(0);
				break;
			case 'z':
				ss.clear();
				ss.str(optarg);
				ss >> m_scenario;
				std::cout << m_scenario << std::endl;
				break;
			case '?':
				printHelpMessage(std::cerr);
				abort();
				break;
			default:
				tools::Logger::logger.error("Could not parse command line arguments");
				break;
			}
		}
	}

	unsigned int size()
	{
		return m_size;
	}

	unsigned int timeSteps()
	{
		return m_timeSteps;
	}

	unsigned int scenario()
	{
		return m_scenario;
	}

private:
	/**
	 * Prints the help message, showing all available options
	 *
	 * @param out The output stream that should be used for
	 *  printing
	 */	
	void printHelpMessage(std::ostream &out = std::cout)
	{
		out << "Usage: SWE1D [OPTIONS...]" << std::endl
			<< "  -s, --size=SIZE              domain size" << std::endl
			<< "  -t, --time=TIME              number of simulated time steps" << std::endl
			<< "  -h, --help                   this help message" << std::endl
			<< "  -z, --scenario=INDEX         index of simulated scenario [0: DamBreak (set by default), 1: Shock, 2: RareRare, 3: 				DamBreak with activated stop-function at villagecollission, 4: BathymetryEffect, 5: SubcriticalFlow (only use with size 25), 6: SupercriticalFLow (only use with size 25)]" 				<< std::endl;
	}
};

} /* namespace tools */
#endif /* TOOLS_ARGS_H_ */
