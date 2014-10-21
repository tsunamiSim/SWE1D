#include <math.h>
#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <cmath>

using namespace std;

namespace solver { 
template <typename T> class FWave
{
private:
	T eigen_coeff1, eigen_coeff2,
	update_r, update_l,
	lamda_roe1, lamda_roe2, 
	delta_f1, delta_f2,
	h_l, hu_l, h_r, hu_r, gravity, lamda_inv;



	//flux-function
	void _delta_flux()
	{
	delta_f1 = hu_r - hu_l;
	delta_f2 = (hu_r * hu_r / h_r + h_r * h_r * gravity * 0.5) - (hu_l * hu_l / h_r + h_l * h_l * gravity * 0.5);
	}

	//(3)
	void _eigenval()
	{
	T u_roe, u_l, u_r, sqrt_hg;
	u_l = hu_l / h_l;
	u_r = hu_r / h_r;
	sqrt_hg = sqrt(gravity * (h_l + h_r) * 0.5 );
	u_roe = (u_l * sqrt(h_l) + u_r * sqrt(h_r) ) / (sqrt(h_l) + sqrt(h_r));
	lamda_roe1 = u_roe - sqrt_hg;
	lamda_roe2 = u_roe + sqrt_hg;
	}

	//(8)
	void _eigencoeff()
	{
	lamda_inv = 1.0 / (lamda_roe2 - lamda_roe1);
	eigen_coeff1 = lamda_inv * (lamda_roe2 * delta_f1 - delta_f2);
	eigen_coeff2 = lamda_inv * (delta_f2 - lamda_roe1 * delta_f1);
	}

public:
	FWave()
	{
	gravity = 9.81;
	}

	void computeNetUpdates(T i_h_l, T i_h_r, T i_hu_l, T i_hu_r, T i_b_l, T i_b_r,
			T& o_lamda_l, T& o_lamda_r, T& o_Q_l, T& o_Q_r, T& o_max_ws)
	{
	h_l = i_h_l;
	h_r = i_h_r;
	hu_l = i_hu_l;
	hu_r = i_hu_r;
	_delta_flux();
	_eigenval();
	_eigencoeff();
	if(lamda_roe1 <= 0 && lamda_roe2 >= 0)
		{
		o_Q_l = (lamda_roe1 * eigen_coeff1);
		o_Q_r = (lamda_roe2 * eigen_coeff2);
		o_lamda_l = (eigen_coeff1);
		o_lamda_r = (eigen_coeff2);
		}
	else if(lamda_roe1 >= 0 && lamda_roe2 <= 0)
		{
		o_Q_r = lamda_roe1 * eigen_coeff1;
		o_Q_l = lamda_roe2 * eigen_coeff2;
		o_lamda_r = eigen_coeff1;
		o_lamda_l = eigen_coeff2;
		}
	else if(lamda_roe1 >= 0 && lamda_roe2 >= 0)
		{
		o_Q_l = 0.0;
		o_Q_r = lamda_roe1 * eigen_coeff1 + lamda_roe2 * eigen_coeff2;
		o_lamda_r = eigen_coeff1 + eigen_coeff2;
		o_lamda_l = 0.0;
		}
	else if(lamda_roe1 <= 0 && lamda_roe2 <= 0)
		{
		o_Q_r = 0.0;
		o_Q_l = lamda_roe1 * eigen_coeff1 + lamda_roe2 * eigen_coeff2;	
		o_lamda_l = eigen_coeff1 + eigen_coeff2;
		o_lamda_r = 0.0;
		}
	//cout << o_lamda_l/o_Q_l << "  " << o_lamda_r/o_Q_l << '\n';
	o_max_ws = max(abs(o_lamda_l), abs(o_lamda_r));
	}

};
}


