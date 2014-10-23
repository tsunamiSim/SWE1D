/**
* This file defines the class to simulate a shock-shock problem.
* It implements the scenarioBase class.
*/

#ifndef SCENARIOS_SHOK_H_
#define SCENARIOS_SHOCK_H_

#include "./../types.h"
#include "./../tools/logger.h"

using namespace tools;

namespace scenarios
{

/**
* This class offers the setup for a shock-shock scenario.
* The water walls are located at the outer sides (facing inwards) with a distance of one quarter of the whole amount of cells to the edges
*/
class Shock : public scenarioBase
{

private:
	unsigned int left, right;
public:
	/**
	* Constructor for the scenario
	*
	* @param size The amount of cells which are simulated
	*/
	Shock(unsigned int size)
		: scenarioBase(size),
		left(size/4),
		right(3*size/4)
	{
		Logger::logger << "size: " << m_size << ", left: " << left << ", right: " << right << std::endl;
	}

	/**
	* Returns the initial height at a given cell
	*
	* @param pos The index of the cell
	*
	* @return The height of the specified cell
	*/
	unsigned int getHeight(unsigned int pos)
	{
		if (pos <= left)
			return 15;
		if (pos >= right)
			return 15;
		return 10;
	}
	
	/**
	* Returns the initial momentum at a given cell
	*	
	* @param pos The index of the cell
	*
	* @return The momentum at the specified cell
	*/
	T getMomentum(unsigned int pos)
	{
		T u = 2.0;
		if (pos <= left)
			return getHeight(pos) * u;
		if (pos >= right)
			return getHeight(pos) * u * -1;
		return 0;
	}
};

}

#endif
