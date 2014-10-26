#include <cxxtest/TestSuite.h>
#include "./../src/solvers/FWave.hpp"

class FWaveTest : public CxxTest::TestSuite
{
private:
	float h_l;
	float hu_l;
	float h_r;
	float hu_r; 
	float speed;	
	unsigned int testrange;	
	solver::FWave<float> *m_solver;

public:
	/**
	 * Tests 10000 steady states 
	 */
	void test_steady_states(void)
	{
	testrange = 100;
	m_solver = new solver::FWave<float>();

	for(unsigned int i = 1; i < testrange; i++)
		{
		for(unsigned int j = 0; i < testrange; i++)
			{	
			m_solver->computeNetUpdates(i, i, j, j, 0.0f, 0.0f, hu_l, hu_r, h_l, h_r, speed);
			TS_ASSERT_EQUALS(hu_l,hu_r);
			TS_ASSERT_EQUALS(h_l,h_r);
			TS_ASSERT(!h_l);
			TS_ASSERT(!h_r);
			TS_ASSERT(!hu_l);
			TS_ASSERT(!hu_r);
			}	
		}
	}

	/**
	 * Tests correctness for [Lambda1 < 0 && Lambda 2 < 0] and [Lambda1 > 0 && Lambda 2 > 0]
	 */
	void test_both_lamda_pos_neg(void)
	{		
	testrange = 100;
	m_solver = new solver::FWave<float>();

	for(unsigned int i = 1; i < testrange; i++)
		{
		for(unsigned int j = 1; i < testrange; i++)
			{	
				for(unsigned int k = 1; k < testrange; i++)
				{	
				m_solver->computeNetUpdates(i, i, j, k, 0.0f, 0.0f, hu_l, hu_r, h_l, h_r, speed);
			
				TS_ASSERT((!hu_l && !h_l) || (hu_r && h_r));
				}	
			
			}	
		}
	}



};
