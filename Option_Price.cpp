#include <iostream>
#include <cmath>
#include <random>
using namespace std;

double call_option_price(double S, double K, double r, double sigma, double T, int M) {
    default_random_engine generator;
    normal_distribution<double> distribution(0.0, 1.0);
    double sum = 0.0;
    for (int i = 0; i < M; i++) {
        double Z = distribution(generator);
        double ST = S * exp((r - 0.5 * sigma * sigma) * T + sigma * sqrt(T) * Z);
        double payoff = max(ST - K, 0.0);
        sum += payoff;
    }
    double option_price = exp(-r * T) * sum / M;
    return option_price;
}

double put_option_price(double S, double K, double r, double sigma, double T, int M) {
    default_random_engine generator;
    normal_distribution<double> distribution(0.0, 1.0);
    double sum = 0.0;
    for (int i = 0; i < M; i++) {
        double Z = distribution(generator);
        double ST = S * exp((r - 0.5 * sigma * sigma) * T + sigma * sqrt(T) * Z);
        double payoff = max(K - ST, 0.0);
        sum += payoff;
    }
    double option_price = exp(-r * T) * sum / M;
    return option_price;
}

int main() {
    double S = 100.0;    // stock price
    double K = 110.0;    // strike price
    double r = 0.05;     // risk-free interest rate
    double sigma = 0.2;  // volatility
    double T = 1.0;      // time to maturity
    int M = 100000;      // number of simulations
    double call_price = call_option_price(S, K, r, sigma, T, M);
    double put_price = put_option_price(S, K, r, sigma, T, M);
    cout << "Call option price: " << call_price << endl;
    cout << "Put option price: " << put_price << endl;
    return 0;
}

