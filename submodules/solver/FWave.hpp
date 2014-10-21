#include <math.h>
#include <iostream>
#include <assert.h>
#include <cstdlib>

using namespace std;

class FWave
{
private:
	double eigen_coeff1, eigen_coeff2,
	update_r, update_l,
	lamda_roe1, lamda_roe2, 
	delta_f1, delta_f2,
	h_l, hu_l, h_r, hu_r, gravity;



	//flux-function
	void _delta_flux()
	{
	delta_f1 = hu_r - hu_l;
	delta_f2 = hu_r * hu_r + h_r * h_r * gravity * 0.5 - hu_l * hu_l + h_l * h_l * gravity * 0.5;
	//cout << "DELTA_F:" << delta_f1 << "  " << delta_f2 << '\n';
	}

	//(3)
	void _eigenval()
	{
	double u_roe, u_l, u_r, sqrt_hg;
	u_l = hu_l / h_l;
	u_r = hu_r / h_r;
	sqrt_hg = sqrt(gravity * (h_l + h_r) * 0.5 );
	u_roe = (u_l * sqrt(h_l) + u_r * sqrt(h_r) ) / (sqrt(h_l) + sqrt(h_r));
	lamda_roe1 = u_roe - sqrt_hg;
	lamda_roe2 = u_roe + sqrt_hg;
	cout << "LAMDA:" << lamda_roe1 << "  " << lamda_roe2 << '\n';
	}

	//(8)
	void _eigencoeff()
	{
	eigen_coeff1 = lamda_roe1 * delta_f1 - delta_f2;
	eigen_coeff2 = delta_f2 - lamda_roe2 * delta_f1;
	cout << "EIGEN_COEFF:" << eigen_coeff1 << "  " << eigen_coeff2 << '\n';
	}

public:
	FWave()
	{
	gravity = 9.81;
	}

	void computeNetUpdates(double i_h_l, double i_h_r, double i_hu_l, double i_hu_r, double i_b_l, double i_b_r,
			double& o_lamda_l, double& o_lamda_r, double& o_Q_l, double& o_Q_r, double& o_max_ws)
	{
	o_max_ws = 0;
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
	}

};


