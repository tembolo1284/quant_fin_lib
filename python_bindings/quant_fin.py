import os
from cffi import FFI

ffi = FFI()

# Define the C API
ffi.cdef("""
    double qf_black_scholes_price(double spot, double strike, double rate, double time, double volatility, int is_call);
""")

# Locate the shared library
lib_path = os.path.join(os.path.dirname(__file__), "libquant_fin_lib.so")
lib = ffi.dlopen(lib_path)

# Python wrapper for the Black-Scholes function
def black_scholes_price(spot, strike, rate, time, volatility, is_call):
    """
    Calculate the Black-Scholes price.

    :param spot: Spot price of the asset.
    :param strike: Strike price of the option.
    :param rate: Risk-free rate.
    :param time: Time to maturity.
    :param volatility: Volatility of the asset.
    :param is_call: 1 for call option, 0 for put option.
    :return: Option price.
    """
    return lib.qf_black_scholes_price(spot, strike, rate, time, volatility, is_call)

