import pytest
from python_bindings.quant_fin import *
import math

def test_black_scholes_call():
    price = black_scholes_price(100, 100, 0.05, 1, 0.2, 1)
    assert abs(price - 10.45) < 0.01

def test_black_scholes_put():
    price = black_scholes_price(100, 100, 0.05, 1, 0.2, 0)
    assert abs(price - 5.57) < 0.01

def test_binomial_tree():
    price = binomial_tree_price(100, 100, 0.05, 1, 0.2, 1, 100)
    assert abs(price - 10.45) < 0.1

def test_monte_carlo():
    price = monte_carlo_price(100, 100, 0.05, 1, 0.2, 10000, 1)
    assert abs(price - 10.45) < 0.5

def test_historical_var():
    returns = [-0.02, 0.01, -0.015, 0.005, -0.01]
    var = historical_var(returns, 0.95)
    assert var < 0

def test_parametric_var():
    var = parametric_var(0.001, 0.02, 0.95)
    assert var < 0

def test_linear_interpolation():
    x = [1.0, 2.0, 3.0]
    y = [10.0, 20.0, 30.0]
    interp = linear_interpolation(x, y, 1.5)
    assert abs(interp - 15.0) < 0.01

def test_delta():
    delta_val = delta(100, 100, 0.05, 1, 0.2, 1)
    assert 0 < delta_val < 1

def test_gamma():
    gamma_val = gamma(100, 100, 0.05, 1, 0.2)
    assert gamma_val > 0

def test_vega():
    vega_val = vega(100, 100, 0.05, 1, 0.2)
    assert vega_val > 0

def test_theta():
    theta_val = theta(100, 100, 0.05, 1, 0.2, 1)
    assert theta_val < 0

def test_rho():
    rho_val = rho(100, 100, 0.05, 1, 0.2, 1)
    assert rho_val > 0
