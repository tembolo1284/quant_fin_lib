#include "quant_fin_lib.h"
#include <iostream>

int main() {
    // Pricing Models
    double bs_price = qf_black_scholes_price(100, 100, 0.05, 1, 0.2, 1);
    double bt_price = qf_binomial_tree_price(100, 100, 0.05, 1, 0.2, 100, 1);
    double mc_price = qf_monte_carlo_price(100, 100, 0.05, 1, 0.2, 10000, 1);

    // Risk Management
    double returns[] = {-0.02, 0.01, -0.015, 0.005, -0.01};
    double historical_var = qf_historical_var(returns, 5, 0.95);
    double parametric_var = qf_parametric_var(0.001, 0.02, 0.95);

    // Greeks
    double delta_val = qf_delta(100, 100, 0.05, 1, 0.2, 1);
    double gamma_val = qf_gamma(100, 100, 0.05, 1, 0.2);
    double vega_val = qf_vega(100, 100, 0.05, 1, 0.2);
    double theta_val = qf_theta(100, 100, 0.05, 1, 0.2, 1);
    double rho_val = qf_rho(100, 100, 0.05, 1, 0.2, 1);

    std::cout << "Black-Scholes Price: " << bs_price << "\n";
    std::cout << "Binomial Tree Price: " << bt_price << "\n";
    std::cout << "Monte Carlo Price: " << mc_price << "\n";
    std::cout << "Historical VaR: " << historical_var << "\n";
    std::cout << "Parametric VaR: " << parametric_var << "\n";
    std::cout << "Delta: " << delta_val << "\n";
    std::cout << "Gamma: " << gamma_val << "\n";
    std::cout << "Vega: " << vega_val << "\n";
    std::cout << "Theta: " << theta_val << "\n";
    std::cout << "Rho: " << rho_val << "\n";

    return 0;
}

