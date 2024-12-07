#include "quant_fin_lib.h"
#include "pricing/black_scholes.cpp"
#include "pricing/binomial_tree.cpp"
#include "pricing/monte_carlo.cpp"
#include "risk/var.cpp"
#include "risk/greeks.cpp"
#include "yield_curve/interpolation.cpp"

// Expose Black-Scholes function
double qf_black_scholes_price(double spot, double strike, double rate, double time, double volatility, int is_call) {
    return black_scholes_price(spot, strike, rate, time, volatility, is_call);
}

// Expose Binomial Tree function
double qf_binomial_tree_price(double spot, double strike, double rate, double time, double volatility, int steps, int is_call) {
    return binomial_tree_price(spot, strike, rate, time, volatility, steps, is_call);
}

// Expose Monte Carlo function
double qf_monte_carlo_price(double spot, double strike, double rate, double time, double volatility, int num_simulations, int is_call) {
    return monte_carlo_price(spot, strike, rate, time, volatility, num_simulations, is_call);
}

// Expose Parametric Value-at-Risk function
double qf_parametric_var(double mean, double std_dev, double confidence_level) {
    return parametric_var(mean, std_dev, confidence_level);
}

// Expose Linear Interpolation function
double qf_linear_interpolation(const double* x, const double* y, size_t size, double target) {
    std::vector<double> x_vec(x, x + size);
    std::vector<double> y_vec(y, y + size);
    return linear_interpolation(x_vec, y_vec, target);
}

// Expose Delta function
double qf_delta(double spot, double strike, double rate, double time, double volatility, int is_call) {
    return delta(spot, strike, rate, time, volatility, is_call);
}

// Expose Gamma function
double qf_gamma(double spot, double strike, double rate, double time, double volatility) {
    return gamma(spot, strike, rate, time, volatility);
}

// Expose Vega function
double qf_vega(double spot, double strike, double rate, double time, double volatility) {
    return vega(spot, strike, rate, time, volatility);
}

// Expose Theta function
double qf_theta(double spot, double strike, double rate, double time, double volatility, int is_call) {
    return theta(spot, strike, rate, time, volatility, is_call);
}

// Expose Rho function
double qf_rho(double spot, double strike, double rate, double time, double volatility, int is_call) {
    return rho(spot, strike, rate, time, volatility, is_call);
}
