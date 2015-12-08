/**
 *  SIMLite - simple discrete simulation core
 *  Authors:
 *     Adam Lucansky <xlucan01@stud.fit.vutbr.cz>
 *     Tomas Kello <xkello00@stud.fit.vutbr.cz>
 */

#include "shared.h"

#ifndef SIMLITE_FACILITY_H
#define SIMLITE_FACILITY_H

#include "transaction.h"

class FacilityQuItem {
public:
	unsigned int priority;
	Transaction *p;
	double waitStart;
	int itemSize;

	FacilityQuItem(Transaction *p, int itemSize, unsigned int priority)
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

	std::priority_queue<FacilityQuItem> quComming;  // waiting to seize

	// + for store
	std::priority_queue<FacilityQuItem> quOutgoing; // waiting to release


	// output
	string name;
	std::vector<HistogramQu> histogramQu;

	unsigned int quCommingMax;
	unsigned int quCommingCount;
	unsigned int commingCount;
	std::vector<double> duration_in_quComming;

	unsigned int quOutgoingMax;
	unsigned int quOutgoingCount;
	unsigned int outgoingCount;
	std::vector<double> duration_in_quOutgoing;
public:
	Facility( unsigned int capacity = 1, string name = "No name");
	void seize(Transaction &p, unsigned int itemSize, unsigned int priority);
	void release(Transaction &p, unsigned int itemSize, unsigned int priority);
	void SetItemsIn(int ModifyItemsIn);
	void Output();
};


#endif //SIMLITE_FACILITY_H
