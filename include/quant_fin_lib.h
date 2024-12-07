#ifndef QUANT_FIN_LIB_H_INCLUDED
#define QUANT_FIN_LIB_H_INCLUDED

#include <cmath>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef QF_API
#  ifdef _WIN32
#     if defined(QF_BUILD_SHARED)
#         define QF_API __declspec(dllexport)
#     elif !defined(QF_BUILD_STATIC)
#         define QF_API __declspec(dllimport)
#     else
#         define QF_API
#     endif
#  else
#     if __GNUC__ >= 4
#         define QF_API __attribute__((visibility("default")))
#     else
#         define QF_API
#     endif
#  endif
#endif

#define QF_VERSION_MAJOR 1
#define QF_VERSION_MINOR 0
#define QF_VERSION ((QF_VERSION_MAJOR << 16) | QF_VERSION_MINOR)

// Basic API
QF_API unsigned int qf_get_version(void);
QF_API int qf_is_compatible_dll(void);

// API for Black-Scholes pricing
QF_API double qf_black_scholes_price(double spot, double strike, double rate, double time, double volatility, int is_call);

// API for Binomial Tree pricing
double qf_binomial_tree_price(double spot, double strike, double rate, double time, double volatility, int steps, int is_call);

// API for Monte Carlo pricing
double qf_monte_carlo_price(double spot, double strike, double rate, double time, double volatility, int num_simulations, int is_call);

// Risk Management
double qf_historical_var(const double* returns, size_t size, double confidence_level);
double qf_parametric_var(double mean, double std_dev, double confidence_level);

// Yield Curve
double qf_linear_interpolation(const double* x, const double* y, size_t size, double target);

// Greeks

// Delta
double qf_delta(double spot, double strike, double rate, double time, double volatility, int is_call) {
    double d1 = (std::log(spot / strike) + (rate + 0.5 * volatility * volatility) * time) / (volatility * std::sqrt(time));
    return is_call ? std::exp(-rate * time) * d1 : std::exp(-rate * time) * (d1 - 1);
}

// Gamma
double qf_gamma(double spot, double strike, double rate, double time, double volatility) {
    double d1 = (std::log(spot / strike) + (rate + 0.5 * volatility * volatility) * time) / (volatility * std::sqrt(time));
    return std::exp(-rate * time) / (spot * volatility * std::sqrt(time)) * d1;
}

// Vega
double qf_vega(double spot, double strike, double rate, double time, double volatility) {
    double d1 = (std::log(spot / strike) + (rate + 0.5 * volatility * volatility) * time) / (volatility * std::sqrt(time));
    return spot * std::exp(-rate * time) * std::sqrt(time) * d1;
}

// Theta
double qf_theta(double spot, double strike, double rate, double time, double volatility, int is_call) {
    double d1 = (std::log(spot / strike) + (rate + 0.5 * volatility * volatility) * time) / (volatility * std::sqrt(time));
    double d2 = d1 - volatility * std::sqrt(time);
    double term1 = -spot * std::exp(-rate * time) * d1 * volatility / (2 * std::sqrt(time));
    double term2 = rate * strike * std::exp(-rate * time) * d2;
    return is_call ? term1 - term2 : term1 + term2;
}

// Rho
double qf_rho(double spot, double strike, double rate, double time, double volatility, int is_call) {
    double d2 = (std::log(spot / strike) + (rate - 0.5 * volatility * volatility) * time) / (volatility * std::sqrt(time));
    return is_call ? time * strike * std::exp(-rate * time) * d2 : -time * strike * std::exp(-rate * time) * d2;
}


#ifdef __cplusplus
}
#endif

#endif // QUANT_FIN_LIB_H_INCLUDED

