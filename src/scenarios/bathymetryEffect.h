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
		if (pos <= (m_size*4/10) || pos >= (m_size*6/10) )
			return 5 - getBathymetry(pos);
		return 10 - getBathymetry(pos);
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
		if(pos == 0)
			return getBathymetry(1);
		if(pos == (m_size + 1))
			return getBathymetry(m_size);
		if(pos <= (m_size / 2))	
			return ((-1*(-1 - (20.f - 20.f * pos / (m_size *0.5) )))-21);
		return ((-1*(-1 - (10.f - 10.f * (m_size-pos) / (m_size * 0.5))))-21);
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
