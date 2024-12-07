#include <cmath>

// Delta
double delta(double spot, double strike, double rate, double time, double volatility, int is_call) {
    double d1 = (std::log(spot / strike) + (rate + 0.5 * volatility * volatility) * time) / (volatility * std::sqrt(time));
    return is_call ? std::exp(-rate * time) * d1 : std::exp(-rate * time) * (d1 - 1);
}

// Gamma
double gamma(double spot, double strike, double rate, double time, double volatility) {
    double d1 = (std::log(spot / strike) + (rate + 0.5 * volatility * volatility) * time) / (volatility * std::sqrt(time));
    return std::exp(-rate * time) / (spot * volatility * std::sqrt(time)) * d1;
}

// Vega
double vega(double spot, double strike, double rate, double time, double volatility) {
    double d1 = (std::log(spot / strike) + (rate + 0.5 * volatility * volatility) * time) / (volatility * std::sqrt(time));
    return spot * std::exp(-rate * time) * std::sqrt(time) * d1;
}

// Theta
double theta(double spot, double strike, double rate, double time, double volatility, int is_call) {
    double d1 = (std::log(spot / strike) + (rate + 0.5 * volatility * volatility) * time) / (volatility * std::sqrt(time));
    double d2 = d1 - volatility * std::sqrt(time);
    double term1 = -spot * std::exp(-rate * time) * d1 * volatility / (2 * std::sqrt(time));
    double term2 = rate * strike * std::exp(-rate * time) * d2;
    return is_call ? term1 - term2 : term1 + term2;
}

// Rho
double rho(double spot, double strike, double rate, double time, double volatility, int is_call) {
    double d2 = (std::log(spot / strike) + (rate - 0.5 * volatility * volatility) * time) / (volatility * std::sqrt(time));
    return is_call ? time * strike * std::exp(-rate * time) * d2 : -time * strike * std::exp(-rate * time) * d2;
}

