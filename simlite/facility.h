#include "shared.h"

#ifndef SIMLITE_FACILITY_H
#define SIMLITE_FACILITY_H

#include "process.h"

typedef struct {
	Process *p;
	double waitStart;
	unsigned int itemSize;
} FacilityQuItem;

typedef struct {
	double durationTime;
	unsigned int itemsIn;
} HistogramQu;

class Facility {
private:
	double eventStart;
	unsigned int itemsIn;
	unsigned int capacity;

	unsigned int maxQuComming;
	std::queue<FacilityQuItem> quComming;  // waiting to seize

	// + for store
	unsigned int maxQuOutgoing;
	std::queue<FacilityQuItem> quOutgoing; // waiting to release


	// output
	std::vector<HistogramQu> histogramQu;
	std::vector<double> duration_in_quComming;
	std::vector<double> duration_in_quOutgoing;
public:
	void Output();
	Facility(unsigned int capacity = 1);
	void seize(Process &p, unsigned int itemSize = 1);
	void release(Process &p, unsigned int itemSize = 1);
};

#endif //SIMLITE_FACILITY_H
