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

// Version and Compatibility
QF_API unsigned int qf_get_version(void);
QF_API int qf_is_compatible_dll(void);

// Option Pricing Models
/**
 * Calculate option price using Black-Scholes model
 * @param spot Current price of the underlying asset
 * @param strike Strike price of the option
 * @param rate Risk-free interest rate (as decimal, e.g., 0.05 for 5%)
 * @param time Time to maturity in years
 * @param volatility Annual volatility (as decimal)
 * @param is_call 1 for call option, 0 for put option
 * @return Option price
 */
QF_API double qf_black_scholes_price(double spot, double strike, double rate, 
                                   double time, double volatility, int is_call);

/**
 * Calculate option price using Binomial Tree model
 * @param spot Current price of the underlying asset
 * @param strike Strike price of the option
 * @param rate Risk-free interest rate (as decimal)
 * @param time Time to maturity in years
 * @param volatility Annual volatility (as decimal)
 * @param is_call 1 for call option, 0 for put option
 * @param steps Number of steps in the binomial tree
 * @return Option price
 */
QF_API double qf_binomial_tree_price(double spot, double strike, double rate,
                                   double time, double volatility, int is_call, 
                                   int steps);

/**
 * Calculate option price using Monte Carlo simulation
 * @param spot Current price of the underlying asset
 * @param strike Strike price of the option
 * @param rate Risk-free interest rate (as decimal)
 * @param time Time to maturity in years
 * @param volatility Annual volatility (as decimal)
 * @param num_simulations Number of Monte Carlo simulations
 * @param is_call 1 for call option, 0 for put option
 * @return Option price
 */
QF_API double qf_monte_carlo_price(double spot, double strike, double rate,
                                 double time, double volatility, int num_simulations,
                                 int is_call);

// Risk Management
/**
 * Calculate historical Value at Risk
 * @param returns Array of historical returns
 * @param size Size of the returns array
 * @param confidence_level Confidence level (e.g., 0.95 for 95%)
 * @return Historical VaR value
 */
QF_API double qf_historical_var(const double* returns, size_t size, 
                              double confidence_level);

/**
 * Calculate parametric Value at Risk
 * @param mean Mean of returns
 * @param std_dev Standard deviation of returns
 * @param confidence_level Confidence level (e.g., 0.95 for 95%)
 * @return Parametric VaR value
 */
QF_API double qf_parametric_var(double mean, double std_dev, double confidence_level);

// Yield Curve Interpolation
/**
 * Perform linear interpolation on yield curve points
 * @param x Array of x-values (time points)
 * @param y Array of y-values (yields)
 * @param size Size of the arrays
 * @param target Target x-value for interpolation
 * @return Interpolated y-value
 */
QF_API double qf_linear_interpolation(const double* x, const double* y, 
                                    size_t size, double target);

// Greeks Calculations
/**
 * Calculate Delta (first derivative with respect to spot price)
 */
QF_API double qf_delta(double spot, double strike, double rate, 
                      double time, double volatility, int is_call);

/**
 * Calculate Gamma (second derivative with respect to spot price)
 */
QF_API double qf_gamma(double spot, double strike, double rate, 
                      double time, double volatility);

/**
 * Calculate Vega (derivative with respect to volatility)
 */
QF_API double qf_vega(double spot, double strike, double rate, 
                     double time, double volatility);

/**
 * Calculate Theta (derivative with respect to time)
 */
QF_API double qf_theta(double spot, double strike, double rate, 
                      double time, double volatility, int is_call);

/**
 * Calculate Rho (derivative with respect to interest rate)
 */
QF_API double qf_rho(double spot, double strike, double rate, 
                    double time, double volatility, int is_call);

#ifdef __cplusplus
}
#endif

#endif // QUANT_FIN_LIB_H_INCLUDED
