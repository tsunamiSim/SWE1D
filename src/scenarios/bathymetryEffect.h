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
#ifndef BATHYMETRYEFFECT_H_
#define BATHYMETRYEFFECT_H_

#include "./../types.h"
#include "scenario.h"

namespace scenarios
{

class BathymetryEffect : public scenarioBase
{
private:

public:
	/**
	* Constructor for the scenario
	*
	* @param size The amount of cells which are simulated
	*/
	BathymetryEffect(unsigned int size)
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
		if (pos <= (m_size*9/20) || pos >= (m_size*11/20) )
			return -getBathymetry(pos);
		return 5-getBathymetry(pos);
	}
	
	/**
	 * @param pos The index of the cell
	 * 
	 * @return Initial Momentum
	 */
	T getMomentum(unsigned int pos)
	{
		return 0;
	}

	/**	
	* @param pos The index of the cell
	*
	* @return The bathymetry at the specified cell
	*/
	T getBathymetry(unsigned int pos)
	{
		return ( pos * getCellSize() < 300 && pos * getCellSize() > 200 ) ? -5.f: -10.f;
	}

	/**
	 * @return Cell size of one cell (= domain size/number of cells)
	 */
	T getCellSize()
	{
		return 1000.f / m_size;
	}

};

}

#endif /* BATHYMETRYEFFECT_H_ */
