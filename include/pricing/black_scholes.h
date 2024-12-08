#ifndef BLACK_SCHOLES_H_INCLUDED
#define BLACK_SCHOLES_H_INCLUDED

#include <cmath>

// Declare the norm_cdf function (helper function)
double norm_cdf(double x);

// Declare the Black-Scholes pricing function
double black_scholes_price(double spot, double strike, double rate, double time, double volatility, int is_call);

#endif // BLACK_SCHOLES_H_INCLUDED

