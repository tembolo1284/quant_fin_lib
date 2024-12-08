#ifndef GREEKS_H
#define GREEKS_H

double delta(double spot, double strike, double rate, double time, double volatility, int is_call);
double gamma(double spot, double strike, double rate, double time, double volatility);
double vega(double spot, double strike, double rate, double time, double volatility);
double theta(double spot, double strike, double rate, double time, double volatility, int is_call);
double rho(double spot, double strike, double rate, double time, double volatility, int is_call);

#endif
