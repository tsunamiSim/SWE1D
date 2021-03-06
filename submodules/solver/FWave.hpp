#include <math.h>
#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <cmath>

using namespace std;

namespace solver { 
/**
*	Simple solver used to compute net udates for a given set of height, momentum and bathymetry values
*/
template <typename T> class FWave
{
private:
	T eigen_coeff1, eigen_coeff2,
	update_r, update_l,
	lambda_roe1, lambda_roe2, 
	delta_f1, delta_f2,
	h_l, hu_l, h_r, hu_r, gravity, lambda_inv,
	b_l, b_r;

	// computes the flux-function --> results in delta_f(1/2)
	void _delta_flux()
	{
	delta_f1 = hu_r - hu_l;
	delta_f2 = (hu_r * hu_r / h_r + h_r * h_r * gravity * 0.5) - (hu_l * hu_l / h_r + h_l * h_l * gravity * 0.5);
	}

	// computes the effect of the bathymetry
	void _bathymetry()
	{
	delta_f2 += gravity * (b_r - b_l) * (h_l + h_r) * 0.5; 
	}

	// computes the roe eigenvalues --> results in lamda_roe(1/2)
	void _eigenval()
	{
	T u_roe, u_l, u_r, sqrt_hg;
	u_l = hu_l / h_l;
	u_r = hu_r / h_r;
	sqrt_hg = sqrt(gravity * (h_l + h_r) * 0.5 );
	u_roe = (u_l * sqrt(h_l) + u_r * sqrt(h_r) ) / (sqrt(h_l) + sqrt(h_r));
	lambda_roe1 = u_roe - sqrt_hg;
	lambda_roe2 = u_roe + sqrt_hg;
	}

	// computes the roe eigencoeffizients --> results in eigen_coeff(1/2)
	void _eigencoeff()
	{
	lambda_inv = 1.0 / (lambda_roe2 - lambda_roe1);
	eigen_coeff1 = lambda_inv * (lambda_roe2 * delta_f1 - delta_f2);
	eigen_coeff2 = lambda_inv * (delta_f2 - lambda_roe1 * delta_f1);
	}

public:
	/**
	*	The default constructor just setting gravity
	*/
	FWave()
	{
	gravity = 9.81;
	}


	/**
	*	Computes the next timesteps net updates
	*
	*	@param i_h_l the height on the left cell of the edge
	*	@param i_h_r the height on the right cell of the edge
	*	@param i_hu_l the momentum on the left cell of the edge
	*	@param i_hu_r the momentum on the right cell of the edge
	*	@param i_b_l the bathymetry on the left cell of the edge
	*	@param i_b_r the bathymetry on the right cell of the edge
	*
	*	@param o_h_l output: the height update for the left cell
	*	@param o_h_r output: the height update for the right cell
	*	@param o_hu_l output: the momentum update for the left cell
	*	@param o_hu_r output: the momentum update for the right cell
	*	@param o_max_wd output: the maximum wavespeed (which is the maximum of the left and right wave speed)
	*/
	void computeNetUpdates(T i_h_l, T i_h_r, T i_hu_l, T i_hu_r, T i_b_l, T i_b_r,
			T& o_h_l, T& o_h_r, T& o_hu_l, T& o_hu_r, T& o_max_ws)
	{
	
	assert(i_h_l > 0 || i_h_r > 0);

	h_l = i_h_l;
	h_r = i_h_r;
	hu_l = i_hu_l;
	hu_r = i_hu_r;
	b_l = i_b_l;
	b_r = i_b_r;

	// reflective boundaries at dry-wet-states
	if(h_l == 0) 
	{
		h_l = h_r;
		hu_l = -hu_r;
		b_l = b_r;
	}else if(h_r == 0) 
	{
		h_r = h_l;
		hu_r = -hu_l;
		b_r = b_l;
	}
	assert(h_l != 0 && h_r != 0);

	// compute the FWave-solution 
	_delta_flux();
	_bathymetry();
	_eigenval();
	_eigencoeff();

	// set the output for both waves
	if(lambda_roe1 <= 0 && lambda_roe2 >= 0)
		{
		o_hu_l = (lambda_roe1 * eigen_coeff1);
		o_hu_r = (lambda_roe2 * eigen_coeff2);
		o_h_l = (eigen_coeff1);
		o_h_r = (eigen_coeff2);
		}
	else if(lambda_roe1 >= 0 && lambda_roe2 <= 0)
		{
		o_hu_r = lambda_roe1 * eigen_coeff1;
		o_hu_l = lambda_roe2 * eigen_coeff2;
		o_h_r = eigen_coeff1;
		o_h_l = eigen_coeff2;
		}
	else if(lambda_roe1 >= 0 && lambda_roe2 >= 0)
		{
		o_hu_l = 0.0;
		o_hu_r = lambda_roe1 * eigen_coeff1 + lambda_roe2 * eigen_coeff2;
		o_h_r = eigen_coeff1 + eigen_coeff2;
		o_h_l = 0.0;
		}
	else if(lambda_roe1 <= 0 && lambda_roe2 <= 0)
		{
		o_hu_r = 0.0;
		o_hu_l = lambda_roe1 * eigen_coeff1 + lambda_roe2 * eigen_coeff2;	
		o_h_l = eigen_coeff1 + eigen_coeff2;
		o_h_r = 0.0;
		}
	else{assert(0);}

	// set the maximum wavespeed
	o_max_ws = max(abs(lambda_roe1), abs(lambda_roe2));
	}

};
}


