/**
 *  SIMLite - simple discrete simulation core
 *  Authors:
 *     Adam Lucansky <xlucan01@stud.fit.vutbr.cz>
 *     Tomas Kello <xkello00@stud.fit.vutbr.cz>
 */

#ifndef SIMLITE_SHARED_H
#define SIMLITE_SHARED_H

#include <iostream>
#include <string>
#include <functional>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <assert.h>
#include <iomanip>        // std::setprecision
using namespace std;
#define DEBUG false

typedef std::function<void(void)> PtrMethod;

extern double Time_t;
extern double Time_tStart;

#define DoAfter(method_name) [=](void) { (method_name)(); }

#endif //SIMLITE_SHARED_H
