#ifndef SIMLITE_FACILITY_H
#define SIMLITE_FACILITY_H

class Process;

class Facility {
public:
    void seize(Process &p);
    void release(Process &p);
};

#endif //SIMLITE_FACILITY_H
