#ifndef SCENARIOS_RARE_H_
#define SCENARIOS_RARE_H_

#include "./../types.h"

namespace scenarios
{

class Rare : public scenarioBase 
{
private:
	unsigned int left, right;
public:
	/**
	* Constructor for the scenario
	*
	* @param size The amount of cells which are simulated
	*/
	Rare(unsigned int size)
		: scenarioBase(size),
		left(2*size/5),
		right(3*size/5)
	{
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
			return 10;
		if (pos >= right)
			return 10;
		return 15;
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
		T u = 2;
		if(pos <= left)
			return getHeight(pos) * u * -1;
		if(pos >= right)
			return getHeight(pos) * u;
		return 0;
	}
};

}

#endif
