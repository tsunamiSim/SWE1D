#include "./../types.h"

namespace scenarios
{
class scenarioBase
{
protected:
	/** Number of cells */
	const unsigned int m_size;

public:
	scenarioBase(unsigned int size): m_size(size)
	{ }

	virtual unsigned int getHeight(unsigned int pos)
	{
		return 15;
	}

	virtual int getMomentum(unsigned int pos)
	{
		return 0;
	}
	
	virtual T getCellSize()
	{
		return 1000.f / m_size;
	}
};
}