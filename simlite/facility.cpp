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

void Facility::seize(Process &p, unsigned int itemSize) {
	if (capacity - itemsIn >= itemSize && quComming.empty())
	{
		// save for Output
			histogramQu.push_back(HistogramQu{ Time_t - eventStart, itemsIn });
			eventStart = Time_t;
		// End save for Output

		itemsIn += itemSize;
		//duration_in_quComming.push(0);
		p.ActivateNext();

		// ak prisli zasoby tak zavolaj dalsieho do skladu na zobratie
		if (quOutgoing.front().itemSize <= itemsIn && !quOutgoing.empty())
		{
			// duration_in_quOutgoing.push_back( ........ );
			itemsIn -= quOutgoing.front().itemSize;
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
		// save for Output
			histogramQu.push_back(HistogramQu{ Time_t - eventStart, itemsIn });
			eventStart = Time_t;
		// End save for Output

		//duration_in_quOutgoing.push_back(0);
		itemsIn -= itemSize;
		p.ActivateNext();

		// ak sa uvolnilo tak zavolaj dalsieho do skladu na vlozenie
		if (quComming.front().itemSize <= capacity - itemsIn && !quComming.empty())
		{
			// duration_in_quComming.push( ........ );
			itemsIn += quComming.front().itemSize;
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
	{
		cout << "\n\033[1;31mFacility has " << itemsIn << " items!!\n";
		if (!quComming.empty())
			cout << "And have " << quComming.size() << " records in quComming\n";
		if (!quOutgoing.empty())
			cout << "And have " << quOutgoing.size() << " records in quOutgoing\n";
		cout <<"\033[0m\n";
	}
	cout << "Max queue: In " << maxQuComming
	   << "\n          Out " << maxQuOutgoing << "\n";

	// imcomming queue
	double sum=0; int count=0;
	while (!duration_in_quComming.empty())
	{
		count++;
		sum += duration_in_quComming.front();
		duration_in_quComming.pop_back();
	}
	if (count == 0)
		cout << "Noone was in incomming queue\n";
	else
		cout << "Average time in incomming queue: " << sum / count << "\n";

	// imcomming queue
	sum=0; count=0;
	while (!duration_in_quOutgoing.empty())
	{
		count++;
		sum += duration_in_quOutgoing.front();
		duration_in_quOutgoing.pop_back();
	}
	if (count == 0)
		cout << "No one was in outgoing queue\n";
	else
		cout << "Average time in outgoing queue: " << sum / count << "\n";

	if (capacity >= 1) // TODO asi netreba
	{
		sum = 0; count = 0;
		if (histogramQu.empty())
			cout << "No one enter facility\n";
		else
		{
			unsigned int duration_of_empty = 0;
			while (!histogramQu.empty())
			{
				if (histogramQu.front().itemsIn == 0)
					duration_of_empty += histogramQu.front().durationTime;
				else
				{
					sum += histogramQu.front().durationTime * histogramQu.front().itemsIn;
				}
				histogramQu.pop_back();
			}
			cout << "Average usage of facility: " << sum /(Time_tStart - Time_t) << "\n";
			cout << "Facility free: " << duration_of_empty << " -- " << duration_of_empty /(Time_tStart - Time_t) << "% \n"; // v percentach
		}

	}
}
