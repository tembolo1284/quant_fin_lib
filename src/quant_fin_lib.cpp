#include "pricing/black_scholes.h"
#include "pricing/binomial_tree.h"
#include "pricing/monte_carlo.h"
#include "risk/var.h"
#include "risk/greeks.h"
#include "yield_curve/interpolation.h"
#include <vector>

// Expose Black-Scholes function
QF_API double qf_black_scholes_price(double spot, double strike, double rate, double time, double volatility, int is_call) {
    return black_scholes_price(spot, strike, rate, time, volatility, is_call != 0);
}

// Expose Binomial Tree function
QF_API double qf_binomial_tree_price(double spot, double strike, double rate, double time, double volatility, int steps, int is_call) {
    return binomial_tree_price(spot, strike, rate, time, volatility, is_call != 0, steps);
}

// Expose Monte Carlo function
QF_API double qf_monte_carlo_price(double spot, double strike, double rate, double time, double volatility, int num_simulations, int is_call) {
    // Default number of steps for Monte Carlo simulation
    const int DEFAULT_NUM_STEPS = 252;  // One year of trading days
    return monte_carlo_price(spot, strike, rate, time, volatility, is_call != 0, num_simulations, DEFAULT_NUM_STEPS);
}

// Expose Parametric Value-at-Risk function
QF_API double qf_parametric_var(double mean, double std_dev, double confidence_level) {
    return parametric_var(mean, std_dev, confidence_level);
}

// Expose Historical Value-at-Risk function
QF_API double qf_historical_var(const double* returns, size_t size, double confidence_level) {
    std::vector<double> returns_vec(returns, returns + size);
    return historical_var(returns_vec, confidence_level);
}

// Expose Linear Interpolation function
QF_API double qf_linear_interpolation(const double* x, const double* y, size_t size, double target) {
    std::vector<double> x_vec(x, x + size);
    std::vector<double> y_vec(y, y + size);
    return linear_interpolation(x_vec, y_vec, target);
}

// Expose Greeks functions
QF_API double qf_delta(double spot, double strike, double rate, double time, double volatility, int is_call) {
    return delta(spot, strike, rate, time, volatility, is_call != 0);
}

QF_API double qf_gamma(double spot, double strike, double rate, double time, double volatility) {
    return gamma(spot, strike, rate, time, volatility);
}

QF_API double qf_vega(double spot, double strike, double rate, double time, double volatility) {
    return vega(spot, strike, rate, time, volatility);
}

QF_API double qf_theta(double spot, double strike, double rate, double time, double volatility, int is_call) {
    return theta(spot, strike, rate, time, volatility, is_call != 0);
}

QF_API double qf_rho(double spot, double strike, double rate, double time, double volatility, int is_call) {
    return rho(spot, strike, rate, time, volatility, is_call != 0);
}
