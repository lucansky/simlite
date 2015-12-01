#include "rng.h"

RNG rng;

RNG::RNG() {
    twister = new std::mt19937(rd());
}

RNG::~RNG() {
    delete twister;
}

// NOTE: Reinitializing std::xxxx_distribution for every call is fine, as long as MT is used same.
// Source: https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful
// at time 30:02

double Uniform(double low, double high) {
    std::uniform_real_distribution<double> dist(low, high);
    return dist(rng.getMT());
}

int UniformInt(int low, int high) {
    std::uniform_int_distribution<int> dist(low, high);
    return dist(rng.getMT());
}

double Exp(double mean) {
    std::exponential_distribution<> dist(mean);
    return dist(rng.getMT());
}

double Normal(double mean, double stddev) {
    std::normal_distribution<> normal_dist(mean, stddev);
    return normal_dist(rng.getMT());
}
