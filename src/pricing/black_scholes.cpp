#include <cmath>
#include "pricing/black_scholes.h"

double norm_cdf(double x) {
    return 0.5 * (1.0 + erf(x / std::sqrt(2.0)));
}

double black_scholes_price(double spot, double strike, double rate, double time, double volatility, int is_call) {
    double d1 = (std::log(spot / strike) + (rate + 0.5 * volatility * volatility) * time) / (volatility * std::sqrt(time));
    double d2 = d1 - volatility * std::sqrt(time);
    if (is_call) {
        return spot * norm_cdf(d1) - strike * std::exp(-rate * time) * norm_cdf(d2);
    } else {
        return strike * std::exp(-rate * time) * norm_cdf(-d2) - spot * norm_cdf(-d1);
    }
}

