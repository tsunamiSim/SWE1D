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
#ifndef SUPERCRITICAL_H_
#define SUPERCRITICAL_H_

#include "./../types.h"
#include "scenario.h"
#include <cmath>
#include <iostream>
#include <assert.h>

namespace scenarios
{

class SupercriticalFlow : public scenarioBase
{
private:

public:
	/**
	* Constructor for the scenario
	*
	* @param size The amount of cells which are simulated
	*/
	SupercriticalFlow(unsigned int size)
		: scenarioBase(size)
	{
	}

	/**
       	 * @param pos The index of the cell
	 * 
	 * @return Initial water height at pos
	 */
	T getHeight(unsigned int pos)
	{	
		assert(m_size == 25);
		return -getBathymetry(pos);
	}
	
	/**
	 * @param pos The index of the cell
	 * 
	 * @return Initial Momentum
	 */
	T getMomentum(unsigned int pos)
	{
		return 0.18;
	}

	/**	
	* @param pos The index of the cell
	*
	* @return The bathymetry at the specified cell
	*/
	T getBathymetry(unsigned int pos)
	{
		if(pos <= 12 && pos >= 8)
			return -0.13 - (0.05 * (pos-10.0) * (pos-10.0));
		return -0.33;
	}

	/**
	 * @return Cell size of one cell (= domain size/number of cells)
	 */
	T getCellSize()
	{
		return 1000.f / m_size;
	}

	/**
	* @return Outflow boundary conditions
	*/
	unsigned int hasReflectiveBoundaries()
	{
		return 0;
	}


};

}

#endif /* SUPERCRITICAL_H_ */
