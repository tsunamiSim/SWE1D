#ifndef SCENARIOS_SHOK_H_
#define SCENARIOS_SHOCK_H_

#include "./../types.h"

namespace scenarios
{

class Shock : public scenarioBase
{
public:
	Shock(unsigned int size)
		: scenarioBase(size)
	{
	}

	unsigned int getHeight(unsigned int pos)
	{
		if (pos <= m_size/2 - 2)
			return 15;
		if (pos >= m_size/2 + 2)
			return 14;
		return 10;
	}

	T getCellSize()
	{
		return 1000.f / m_size;
	}
};

}

#endif
