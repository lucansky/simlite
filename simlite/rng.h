/**
 *  SIMLite - simple discrete simulation core
 *  Authors:
 *     Adam Lucansky <xlucan01@stud.fit.vutbr.cz>
 *     Tomas Kello <xkello00@stud.fit.vutbr.cz>
 */

#include "shared.h"

#ifndef SIMLITE_RNG_H
#define SIMLITE_RNG_H

#include <random>

class RNG {
    std::random_device rd;

    // Mersene-Twister black box with states
    std::mt19937 *twister;
public:

    // Initializes and seeds MT from random_device.
    RNG();

    // Deletes MT
    ~RNG();

    // MT getter
    std::mt19937 & getMT() {
        return *twister;
    }
};

// Singleton with MT initialized, do not change.
extern RNG rng;

// Uniform generator in range [0.0..1.0]
double Random();

// WARNING: Uniform generator has both ends INCLUSIVE.
// Uniform distribution, [low, high]
double Uniform(double low, double high);
int UniformInt(int low, int high);

// Exponential distribution
double Exp(double mean);

// Normal (Gauss) distribution
double Normal(double mean, double stddev);

#endif