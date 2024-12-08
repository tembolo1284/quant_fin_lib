from quant_fin import *

def main():
    # Test option pricing
    spot = 100
    strike = 100
    rate = 0.05
    time = 1
    vol = 0.2
    is_call = 1
    
    print(f"Option Pricing Models:")
    print(f"Black-Scholes: {black_scholes_price(spot, strike, rate, time, vol, is_call):.4f}")
    print(f"Binomial Tree: {binomial_tree_price(spot, strike, rate, time, vol, 100, is_call):.4f}")
    print(f"Monte Carlo: {monte_carlo_price(spot, strike, rate, time, vol, 10000, is_call):.4f}\n")

    # Test VaR calculations
    returns = [-0.02, 0.01, -0.015, 0.005, -0.01]
    confidence = 0.95
    print(f"Risk Metrics:")
    print(f"Historical VaR: {historical_var(returns, confidence):.4f}")
    print(f"Parametric VaR: {parametric_var(0.001, 0.02, confidence):.4f}\n")

    # Test Greeks
    print(f"Option Greeks:")
    print(f"Delta: {delta(spot, strike, rate, time, vol, is_call):.4f}")
    print(f"Gamma: {gamma(spot, strike, rate, time, vol):.4f}")
    print(f"Vega: {vega(spot, strike, rate, time, vol):.4f}")
    print(f"Theta: {theta(spot, strike, rate, time, vol, is_call):.4f}")
    print(f"Rho: {rho(spot, strike, rate, time, vol, is_call):.4f}\n")

if __name__ == "__main__":
    main()
