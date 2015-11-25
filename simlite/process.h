#include "shared.h"

#ifndef SIMLITE_PROCESS_H
#define SIMLITE_PROCESS_H

class Facility;

class Process {
public:
    PtrMethod ptrMethod;
    string name;
public:
    void Seize(Facility &f, PtrMethod nextMethod);

    void ActivateAfter(double interval, PtrMethod nextMethod);

    void ActivateNext();

    void Release(Facility &f, PtrMethod nextMethod);
};

#include "facility.h"

#endif //SIMLITE_PROCESS_H
