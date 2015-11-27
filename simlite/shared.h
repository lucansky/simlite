#ifndef SIMLITE_SHARED_H
#define SIMLITE_SHARED_H

//#include <typeinfo>
#include <iostream>
#include <string>
#include <functional>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
using namespace std;
#define DEBUG true

//TODO
inline double Exp(double mean) {return mean;}
typedef std::function<void(void)> PtrMethod;

extern double Time_t;

#define DoAfter(method_name) [=](void) { (method_name)(); }

#endif //SIMLITE_SHARED_H
