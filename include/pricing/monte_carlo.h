#ifndef QUANT_FIN_MONTE_CARLO_H
#define QUANT_FIN_MONTE_CARLO_H

double monte_carlo_price(double spot, double strike, double rate, double time, 
                        double volatility, bool is_call, int num_simulations, int num_steps);

#endif // QUANT_FIN_MONTE_CARLO_H
