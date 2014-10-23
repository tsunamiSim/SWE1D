#ifndef SCENARIOS_SCHOK_H_
#define SCENARIOS_SCHOCK_H_

#include "./../types.h"

namespace scenarios
{

class Schock
{
private:
	const unsigned int m_size;

public:
	Schock(unsigned int size)
		: m_size(size)
	{
	}

	unsigned int getHeight(unsigned int pos)
	{
		if (pos <= 3*m_size/7)
			return 15;
		if (pos >= 4*m_size/7)
			return 15;
		return 10;
	}

	T getCellSize()
	{
		return 1000.f / m_size;
	}
};

}

#endif
