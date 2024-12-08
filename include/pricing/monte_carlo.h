#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

double monte_carlo_price(double spot, double strike, double rate, double time, double volatility, int num_simulations, int is_call);

#endif // MONTE_CARLO_H
