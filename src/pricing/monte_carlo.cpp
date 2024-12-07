#include <cmath>
#include <random>
#include <vector>

// Monte Carlo Pricing Model
double monte_carlo_price(double spot, double strike, double rate, double time, double volatility, int num_simulations, int is_call) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<double> distribution(0.0, 1.0);

    double drift = (rate - 0.5 * volatility * volatility) * time;
    double diffusion = volatility * std::sqrt(time);

    double total_payoff = 0.0;

    for (int i = 0; i < num_simulations; ++i) {
        double random_value = distribution(generator);
        double simulated_price = spot * std::exp(drift + diffusion * random_value);
        double payoff = is_call
                            ? std::max(simulated_price - strike, 0.0)
                            : std::max(strike - simulated_price, 0.0);
        total_payoff += payoff;
    }

    double average_payoff = total_payoff / num_simulations;
    return std::exp(-rate * time) * average_payoff;
}

