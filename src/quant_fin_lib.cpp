#include "quant_fin_lib.h"
#include "pricing/black_scholes.h"
#include "pricing/binomial_tree.h"
#include "pricing/monte_carlo.h"
#include "risk/var.h"
#include "risk/greeks.h"
#include "yield_curve/interpolation.h"
#include <vector>

// Version and Compatibility functions
unsigned int qf_get_version(void) {
    return QF_VERSION;
}

int qf_is_compatible_dll(void) {
    return QF_VERSION_MAJOR;
}

// Option Pricing Models
double qf_black_scholes_price(double spot, double strike, double rate, double time, double volatility, int is_call) {
    return black_scholes_price(spot, strike, rate, time, volatility, is_call != 0);
}

double qf_binomial_tree_price(double spot, double strike, double rate, double time, double volatility, int is_call, int steps) {
    return binomial_tree_price(spot, strike, rate, time, volatility, is_call != 0, steps);
}

double qf_monte_carlo_price(double spot, double strike, double rate, double time, double volatility, int num_simulations, int is_call) {
    const int default_steps = 252; // One year of trading days
    return monte_carlo_price(spot, strike, rate, time, volatility, is_call != 0, num_simulations, default_steps);
}

// Risk Management
double qf_historical_var(const double* returns, size_t size, double confidence_level) {
    if (!returns || size == 0) return 0.0;
    std::vector<double> returns_vec(returns, returns + size);
    return historical_var(returns_vec, confidence_level);
}

double qf_parametric_var(double mean, double std_dev, double confidence_level) {
    return parametric_var(mean, std_dev, confidence_level);
}

// Yield Curve Interpolation
double qf_linear_interpolation(const double* x, const double* y, size_t size, double target) {
    if (!x || !y || size == 0) return 0.0;
    std::vector<double> x_vec(x, x + size);
    std::vector<double> y_vec(y, y + size);
    return linear_interpolation(x_vec, y_vec, target);
}

// Greeks
double qf_delta(double spot, double strike, double rate, double time, double volatility, int is_call) {
    return delta(spot, strike, rate, time, volatility, is_call != 0);
}

double qf_gamma(double spot, double strike, double rate, double time, double volatility) {
    return gamma(spot, strike, rate, time, volatility);
}

double qf_vega(double spot, double strike, double rate, double time, double volatility) {
    return vega(spot, strike, rate, time, volatility);
}

double qf_theta(double spot, double strike, double rate, double time, double volatility, int is_call) {
    return theta(spot, strike, rate, time, volatility, is_call != 0);
}

double qf_rho(double spot, double strike, double rate, double time, double volatility, int is_call) {
    return rho(spot, strike, rate, time, volatility, is_call != 0);
}
