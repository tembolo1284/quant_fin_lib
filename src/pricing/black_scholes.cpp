#include <cmath>
#include "pricing/black_scholes.h"
#include "quant_fin_lib.h"

double norm_cdf(double x) {
    return 0.5 * (1 + erf(x / sqrt(2)));
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

