#include "pricing/monte_carlo.h"
#include <random>
#include <cmath>

double monte_carlo_price(double spot, double strike, double rate, double time, 
                        double volatility, bool is_call, int num_simulations, int num_steps) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(0, 1);

    double dt = time / num_steps;
    double drift = (rate - 0.5 * volatility * volatility) * dt;
    double vol_sqrt = volatility * std::sqrt(dt);
    double total_payoff = 0.0;

    for (int i = 0; i < num_simulations; ++i) {
        double path_price = spot;
        
        for (int j = 0; j < num_steps; ++j) {
            path_price *= std::exp(drift + vol_sqrt * d(gen));
        }

        double payoff = is_call ? std::max(path_price - strike, 0.0) 
                               : std::max(strike - path_price, 0.0);
        total_payoff += payoff;
    }

    double mean_payoff = total_payoff / num_simulations;
    return mean_payoff * std::exp(-rate * time);
}
