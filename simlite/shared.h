#ifndef SIMLITE_SHARED_H
#define SIMLITE_SHARED_H

//#include <typeinfo>
#include <iostream>
#include <string>
#include <functional>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <assert.h>
#include <iomanip>        // std::setprecision(
using namespace std;
#define DEBUG true

//TODO
inline double Exp(double mean) {return mean;}
inline double Uniform(double min, double max) {return max;}
inline double Normal(double mean, double variance) {return mean;}

typedef std::function<void(void)> PtrMethod;

extern double Time_t;
extern double Time_tStart;

#define DoAfter(method_name) [=](void) { (method_name)(); }

#endif //SIMLITE_SHARED_H
