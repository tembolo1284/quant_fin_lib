#include <cmath>
#include <vector>
#include "pricing/monte_carlo.h"

// Binomial Tree Pricing Model
double binomial_tree_price(double spot, double strike, double rate, double time, double volatility, int steps, int is_call) {
    double dt = time / steps;
    double discount = std::exp(-rate * dt);
    double up = std::exp(volatility * std::sqrt(dt));
    double down = 1.0 / up;
    double probability = (std::exp(rate * dt) - down) / (up - down);

    // Initialize the option prices at maturity
    std::vector<double> prices(steps + 1);
    for (int i = 0; i <= steps; ++i) {
        double stock_price = spot * std::pow(up, steps - i) * std::pow(down, i);
        prices[i] = is_call
                        ? std::max(stock_price - strike, 0.0)
                        : std::max(strike - stock_price, 0.0);
    }

    // Backward induction to calculate option price
    for (int step = steps - 1; step >= 0; --step) {
        for (int i = 0; i <= step; ++i) {
            prices[i] = discount * (probability * prices[i] + (1 - probability) * prices[i + 1]);
        }
    }

    return prices[0];
}

