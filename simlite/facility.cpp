#include "facility.h"

Facility::Facility(unsigned int capacity) {
	// TODO preco musi byt this-> a nie this. (prekladac pisal chybu)
	assert(capacity > 0);
	this->capacity = capacity;
	itemsIn = 0;
	// save for Output
		eventStart = Time_t;
		maxQuComming  = 0;
		maxQuOutgoing = 0;
	// End save for Output
}

void Facility::SetItemsIn(int ModifyItemsIn)
{
	histogramQu.push_back(HistogramQu{ Time_t - eventStart, itemsIn });
	eventStart = Time_t;
	itemsIn += ModifyItemsIn;
	if (DEBUG)
		cout << "In time: " << Time_t << " are in facaility: " << itemsIn << " items\n";
}

void Facility::seize(Process &p, unsigned int itemSize) {
	if (capacity - itemsIn >= itemSize && quComming.empty())
	{

		SetItemsIn(itemSize);
		duration_in_quComming.push_back(0);
		p.ActivateNext();

		// ak prisli zasoby tak zavolaj dalsieho do skladu na zobratie
		if (quOutgoing.front().itemSize <= itemsIn && !quOutgoing.empty())
		{
			duration_in_quOutgoing.push_back( Time_t - quOutgoing.front().waitStart );
			SetItemsIn(-quOutgoing.front().itemSize);
			quOutgoing.front().p->ActivateNext();
			quOutgoing.pop();
		}
	}
	else
	{
		quComming.push(FacilityQuItem{ &p, Time_t, itemSize });

		// save for Output
			if (maxQuComming < quComming.size())
				maxQuComming = quComming.size();
		// End save for Output
	}
}

void Facility::release(Process &p, unsigned int itemSize) {
	if (quOutgoing.empty() && itemsIn >= itemSize)
	{

		duration_in_quOutgoing.push_back(0);
		SetItemsIn(-itemSize);
		p.ActivateNext();

		// ak sa uvolnilo tak zavolaj dalsieho do skladu na vlozenie
		if (quComming.front().itemSize <= capacity - itemsIn && !quComming.empty())
		{
			double tmp = Time_t - quComming.front().waitStart;
			duration_in_quComming.push_back( tmp );
			SetItemsIn(quComming.front().itemSize);
			quComming.front().p->ActivateNext();
			quComming.pop();
		}
	}
	else
	{
		// must waitng, queue not empty, or not enought itemsIn
		quOutgoing.push(FacilityQuItem{ &p, Time_t, itemSize });

		// save for Output
			if (maxQuOutgoing < quOutgoing.size())
				maxQuOutgoing = quOutgoing.size();
		// End save for Output
	}
}

void Facility::Output() {

	histogramQu.push_back(HistogramQu{ Time_t - eventStart, itemsIn });
	if (itemsIn != 0)
		cout << "\033[1;31mFacility has " << itemsIn << " items!!\033[0m\n";
	if (!quComming.empty())
		cout << "\033[1;31mFacility has " << quComming.size() << " records in quComming\033[0m\n";
	if (!quOutgoing.empty())
		cout << "\033[1;31mFacility has " << quOutgoing.size() << " records in quOutgoing\033[0m\n";

	cout << "Max queue: In " << maxQuComming
	   << "\n          Out " << maxQuOutgoing << "\n";

	// imcomming queue
	double sum=0; int count=0;
	while (!duration_in_quComming.empty())
	{
		count++;
		sum += duration_in_quComming.back();
		duration_in_quComming.pop_back();
	}
	if (count == 0)
		cout << "No one seize facility\n";
	else
		cout << "Average time in incomming queue: " << sum / count << " (without transactions in queue at stop time)\n";

	// imcomming queue
	sum=0; count=0;
	while (!duration_in_quOutgoing.empty())
	{
		count++;
		sum += duration_in_quOutgoing.back();
		duration_in_quOutgoing.pop_back();
	}
	if (count == 0)
		cout << "No one release facility\n";
	else
		cout << "Average time in outgoing queue: " << sum / count << " (without transactions in queue at stop time)\n";

	sum = 0; count = 0;
	if (histogramQu.empty())
		cout << "No one enter facility\n";
	else
	{
		unsigned int duration_of_empty = 0;
		while (!histogramQu.empty())
		{
			if (histogramQu.back().itemsIn == 0)
				duration_of_empty += histogramQu.back().durationTime;
			else
			{
				sum += histogramQu.back().durationTime * histogramQu.back().itemsIn;
			}
			histogramQu.pop_back();
		}
			cout << "Facility used for " << (100* sum /(Time_t - Time_tStart))/capacity << "%\n";
		cout << "Facility was " << 100* duration_of_empty /(Time_t - Time_tStart) << "% of time free\n"; // v percentach
	}
}
