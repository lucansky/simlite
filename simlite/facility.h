#include "shared.h"

#ifndef SIMLITE_FACILITY_H
#define SIMLITE_FACILITY_H

#include "process.h"

typedef struct {
	Process *p;
	double waitStart;
} FacilityQuItem;

class Facility {
private:
	double emptyStart;
	bool empty;
	double duration_of_empty;
	std::queue<FacilityQuItem> qu;
	int maxQu;
	std::vector<double> duration_of_service;
	std::vector<double> duration_in_queue;
public:
	void Output();
	Facility();
	void seize(Process &p);
	void release();
};

#endif //SIMLITE_FACILITY_H
