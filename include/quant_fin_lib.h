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
QF_API double qf_binomial_tree_price(double spot, double strike, double rate, double time, double volatility, int steps, int is_call);

// API for Monte Carlo pricing
QF_API double qf_monte_carlo_price(double spot, double strike, double rate, double time, double volatility, int num_simulations, int is_call);

// Risk Management
QF_API double qf_historical_var(const double* returns, size_t size, double confidence_level);
QF_API double qf_parametric_var(double mean, double std_dev, double confidence_level);

// Yield Curve
QF_API double qf_linear_interpolation(const double* x, const double* y, size_t size, double target);

// Greeks

// Delta
QF_API double qf_delta(double spot, double strike, double rate, double time, double volatility, int is_call);

// Gamma
QF_API double qf_gamma(double spot, double strike, double rate, double time, double volatility);

// Vega
QF_API double qf_vega(double spot, double strike, double rate, double time, double volatility);

// Theta
QF_API double qf_theta(double spot, double strike, double rate, double time, double volatility, int is_call);

// Rho
QF_API double qf_rho(double spot, double strike, double rate, double time, double volatility, int is_call);

#ifdef __cplusplus
}
#endif

#endif // QUANT_FIN_LIB_H_INCLUDED

