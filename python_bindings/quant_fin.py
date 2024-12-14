import os
from cffi import FFI

ffi = FFI()

ffi.cdef("""
    double qf_black_scholes_price(double spot, double strike, double rate, double time, double volatility, int is_call);
    double qf_binomial_tree_price(double spot, double strike, double rate, double time, double volatility, int steps, int is_call);
    double qf_monte_carlo_price(double spot, double strike, double rate, double time, double volatility, int num_simulations, int is_call);
    double qf_historical_var(const double* returns, size_t size, double confidence_level);
    double qf_parametric_var(double mean, double std_dev, double confidence_level);
    double qf_linear_interpolation(const double* x, const double* y, size_t size, double target);
    double qf_delta(double spot, double strike, double rate, double time, double volatility, int is_call);
    double qf_gamma(double spot, double strike, double rate, double time, double volatility);
    double qf_vega(double spot, double strike, double rate, double time, double volatility);
    double qf_theta(double spot, double strike, double rate, double time, double volatility, int is_call);
    double qf_rho(double spot, double strike, double rate, double time, double volatility, int is_call);
""")

lib_path = os.path.join(os.path.dirname(__file__), "libquant_fin_lib.so.1.0")
lib = ffi.dlopen(lib_path)

def black_scholes_price(spot, strike, rate, time, volatility, is_call):
    return lib.qf_black_scholes_price(spot, strike, rate, time, volatility, is_call)

def binomial_tree_price(spot, strike, rate, time, volatility, is_call, steps):
    return lib.qf_binomial_tree_price(spot, strike, rate, time, volatility, is_call, steps)

def monte_carlo_price(spot, strike, rate, time, volatility, num_simulations, is_call):
    return lib.qf_monte_carlo_price(spot, strike, rate, time, volatility, num_simulations, is_call)

def historical_var(returns, confidence_level):
    arr = ffi.new("double[]", returns)
    return lib.qf_historical_var(arr, len(returns), confidence_level)

def parametric_var(mean, std_dev, confidence_level):
    return lib.qf_parametric_var(mean, std_dev, confidence_level)

def linear_interpolation(x, y, target):
    x_arr = ffi.new("double[]", x)
    y_arr = ffi.new("double[]", y)
    return lib.qf_linear_interpolation(x_arr, y_arr, len(x), target)

def delta(spot, strike, rate, time, volatility, is_call):
    return lib.qf_delta(spot, strike, rate, time, volatility, is_call)

def gamma(spot, strike, rate, time, volatility):
    return lib.qf_gamma(spot, strike, rate, time, volatility)

def vega(spot, strike, rate, time, volatility):
    return lib.qf_vega(spot, strike, rate, time, volatility)

def theta(spot, strike, rate, time, volatility, is_call):
    return lib.qf_theta(spot, strike, rate, time, volatility, is_call)

def rho(spot, strike, rate, time, volatility, is_call):
    return lib.qf_rho(spot, strike, rate, time, volatility, is_call)
