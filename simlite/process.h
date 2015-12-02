#include "shared.h"

#ifndef SIMLITE_PROCESS_H
#define SIMLITE_PROCESS_H

class Facility;

class Process {
public:
    PtrMethod ptrMethod;
    string name;
public:
	Process(string name = "No name");

    void Seize(Facility &f, PtrMethod nextMethod, unsigned int itemSize = 1);

    void ActivateAfter(double interval, PtrMethod nextMethod);

    void ActivateNext();

    void Release(Facility &f, PtrMethod nextMethod, unsigned int itemSize = 1);
};

#include "facility.h"

#endif //SIMLITE_PROCESS_H
