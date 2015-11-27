#include "shared.h"

#ifndef SIMLITE_STORE_H
#define SIMLITE_STORE_H

#include "process.h"

typedef struct {
    Process *p;
    double waitStart;
} StoreQuItem;

class Store {
private:
    double eventStart;
    bool empty;
    double duration_of_empty;
    std::queue<StoreQuItem> qu;
    int maxQu;
    std::vector<double> duration_of_service;
    std::vector<double> duration_in_queue;
public:
    void Output();
    Store();
    void seize(Process &p);
    void release();
};

#endif //SIMLITE_STORE_H
