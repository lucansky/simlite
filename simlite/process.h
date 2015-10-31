#include "shared.h"
#include "facility.h"

#ifndef SIMLITE_PROCESS_H
#define SIMLITE_PROCESS_H

    class Process {
    public:
        virtual void Behavior() = 0;

        void Seize(Facility &f);

        void ActivateAfter(double interval);

        void Release(Facility &f);
    };


#endif //SIMLITE_PROCESS_H
