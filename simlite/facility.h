#include "shared.h"

#ifndef SIMLITE_FACILITY_H
#define SIMLITE_FACILITY_H

#include "process.h"

class FacilityQuItem {
public:
	unsigned int priority;
	Process *p;
	double waitStart;
	int itemSize;

	FacilityQuItem(Process *p, int itemSize, unsigned int priority)
	{
		this->p = p;
		this->priority = priority;
		this->itemSize = itemSize;
		this->waitStart = Time_t;
	}
};

bool operator<(const FacilityQuItem a, const FacilityQuItem b);


typedef struct {
	double durationTime;
	int itemsIn;
} HistogramQu;

class Facility {
private:
	double eventStart;
	int itemsIn;
	unsigned int capacity;

	unsigned int maxQuComming;
	std::priority_queue<FacilityQuItem> quComming;  // waiting to seize

	// + for store
	unsigned int maxQuOutgoing;
	std::priority_queue<FacilityQuItem> quOutgoing; // waiting to release


	// output
	string name;
	std::vector<HistogramQu> histogramQu;
	std::vector<double> duration_in_quComming;
	std::vector<double> duration_in_quOutgoing;
public:
	Facility( unsigned int capacity = 1, string name = "No name");
	void seize(Process &p, unsigned int itemSize, unsigned int priority);
	void release(Process &p, unsigned int itemSize, unsigned int priority);
	void SetItemsIn(int ModifyItemsIn);
	void Output();
};


#endif //SIMLITE_FACILITY_H
