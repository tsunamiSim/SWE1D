#ifndef SCENARIOS_RARE_H_
#define SCENARIOS_RARE_H_

#include "./../types.h"

namespace scenarios
{

class Rare : public scenarioBase 
{
public:
	Rare(unsigned int size)
		: scenarioBase(size)
	{
	}

	unsigned int getHeight(unsigned int pos)
	{
		if (pos <= 3*m_size/7)
			return 10;
		if (pos >= 4*m_size/7)
			return 10;
		return 15;
	}

	T getCellSize()
	{
		return 1000.f / m_size;
	}
};

}

#endif
