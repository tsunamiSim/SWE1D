#ifndef SCENARIOBASE_H_
#define SCENARIOBASE_H_

#include "./../types.h"
#include <iostream>

namespace scenarios
{
class scenarioBase
{
protected:
	/** Number of cells */
	const unsigned int m_size;

public:
	/**
	* Constructor for the scenario
	*
	* @param size The amount of cells which are simulated
	*/
	scenarioBase(unsigned int size): m_size(size)
	{ }


	/**
	* Returns the initial height at a given cell
	*
	* @param pos The index of the cell
	*
	* @return The height of the specified cell
	*/
	virtual unsigned int getHeight(unsigned int pos)
	{	
		return 15;
	}

	/**
	* Returns the initial momentum at a given cell
	*	
	* @param pos The index of the cell
	*
	* @return The momentum at the specified cell
	*/
	virtual T getMomentum(unsigned int pos)
	{
		return 0;
	}
	
	/**
	* Returns the width of each cell
	*
	* @return Width of one cell
	*/
	virtual T getCellSize()
	{
		return 1000.f / m_size;
	}
	
};
}

#endif /* SCENARIOBASE_H_ */
