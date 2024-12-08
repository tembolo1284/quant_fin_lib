#include <gtest/gtest.h>
#include <cmath>
#include "quant_fin_lib.h"

// Utility function for approximate equality
bool approximately_equal(double a, double b, double tolerance = 1e-6) {
    return std::fabs(a - b) < tolerance;
}

// Test Black-Scholes Pricing
TEST(QuantFinTest, BlackScholes) {
    double spot = 100;
    double strike = 100;
    double rate = 0.05;
    double time = 1;
    double volatility = 0.2;

    double call_price = qf_black_scholes_price(spot, strike, rate, time, volatility, 1);
    double put_price = qf_black_scholes_price(spot, strike, rate, time, volatility, 0);

    EXPECT_TRUE(approximately_equal(call_price, 10.4506, 1e-4));
    EXPECT_TRUE(approximately_equal(put_price, 5.5735, 1e-4));
}

// Test Binomial Tree Pricing
TEST(QuantFinTest, BinomialTree) {
    double spot = 100;
    double strike = 100;
    double rate = 0.05;
    double time = 1;
    double volatility = 0.2;
    int steps = 10000;

    double call_price = qf_binomial_tree_price(spot, strike, rate, time, volatility, steps, 1);
    double put_price = qf_binomial_tree_price(spot, strike, rate, time, volatility, steps, 0);

    EXPECT_TRUE(approximately_equal(call_price, 10.4506, 1e-2));
    EXPECT_TRUE(approximately_equal(put_price, 5.5735, 1e-2));
}

// Test Monte Carlo Pricing
TEST(QuantFinTest, MonteCarlo) {
    double spot = 100;
    double strike = 100;
    double rate = 0.05;
    double time = 1;
    double volatility = 0.2;
    int num_simulations = 100000;

    double call_price = qf_monte_carlo_price(spot, strike, rate, time, volatility, num_simulations, 1);

    EXPECT_TRUE(approximately_equal(call_price, 10.4506, 0.5)); // Tolerance due to randomness
}

// Test Value-at-Risk
TEST(QuantFinTest, ValueAtRisk) {
    double returns[] = {-0.02, 0.01, -0.015, 0.005, -0.01};
    size_t size = 5;

    double historical_var = qf_historical_var(returns, size, 0.95);
    double parametric_var = qf_parametric_var(0.001, 0.02, 0.95);

    EXPECT_LT(historical_var, 0); // Historical VaR should be negative
    EXPECT_LT(parametric_var, 0); // Parametric VaR should be negative
}

// Test Greeks
TEST(QuantFinTest, Greeks) {
    double spot = 100;
    double strike = 100;
    double rate = 0.05;
    double time = 1;
    double volatility = 0.2;

    double delta_val = qf_delta(spot, strike, rate, time, volatility, 1);
    double gamma_val = qf_gamma(spot, strike, rate, time, volatility);
    double vega_val = qf_vega(spot, strike, rate, time, volatility);
    double theta_val = qf_theta(spot, strike, rate, time, volatility, 1);
    double rho_val = qf_rho(spot, strike, rate, time, volatility, 1);

    EXPECT_GT(delta_val, 0);
    EXPECT_LT(delta_val, 1);
    EXPECT_GT(gamma_val, 0);
    EXPECT_GT(vega_val, 0);
    EXPECT_LT(theta_val, 0);
    EXPECT_GT(rho_val, 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

