#include <cmath>
#include <vector>
#include "pricing/binomial_tree.h"

double binomial_tree_price(double spot, double strike, double rate, double time, double volatility, bool is_call, int steps) {
    // Ensure we have at least 2 steps
    steps = std::max(steps, 2);
    
    double dt = time / steps;
    double u = std::exp(volatility * std::sqrt(dt));
    double d = 1.0 / u;
    double p = (std::exp(rate * dt) - d) / (u - d);
    double discount = std::exp(-rate * dt);

    // Initialize the stock prices at maturity
    std::vector<double> values(steps + 1);
    for (int i = 0; i <= steps; ++i) {
        double stock_price = spot * std::pow(u, steps - i) * std::pow(d, i);
        values[i] = is_call ? 
            std::max(0.0, stock_price - strike) : 
            std::max(0.0, strike - stock_price);
    }

    // Backward induction
    for (int step = steps - 1; step >= 0; --step) {
        for (int i = 0; i <= step; ++i) {
            values[i] = discount * (p * values[i] + (1 - p) * values[i + 1]);
        }
    }

    return values[0];
}
