/**
 *  SIMLite - simple discrete simulation core
 *  Authors:
 *     Adam Lucansky <xlucan01@stud.fit.vutbr.cz>
 *     Tomas Kello <xkello00@stud.fit.vutbr.cz>
 */

#include "facility.h"

Facility::Facility(unsigned int capacity, string name) {
	assert(capacity > 0);
	this->name = name;
	this->capacity = capacity;
	itemsIn = 0;
	// save for Output
		eventStart = Time_t;
		quCommingCount = 0;
		quCommingMax  = 0;
		quOutgoingCount = 0;
		quOutgoingMax = 0;
	// End save for Output
}

void Facility::SetItemsIn(int ModifyItemsIn)
{
	histogramQu.push_back(HistogramQu{ Time_t - eventStart, itemsIn });
	eventStart = Time_t;
	itemsIn += ModifyItemsIn;
	if (DEBUG)
		cout << "In " << this->name << " " << itemsIn << " items (modified with: " << ModifyItemsIn << ")" << "In time: " << Time_t << "\n";
}

void Facility::seize(Transaction &p, unsigned int itemSize, unsigned int priority) {
	commingCount++;
	if (DEBUG)
		std::cout << " vklada/obsadzuje linku " << name << " s " << itemSize << " items" << " v case " << Time_t << "\n";
	if (capacity - itemsIn >= itemSize && quComming.empty())
	{

		SetItemsIn(itemSize);
		duration_in_quComming.push_back(0);
		p.ActivateNext();

		// ak prisli zasoby tak zavolaj dalsieho do skladu na zobratie
		if (!quOutgoing.empty())
			if (quOutgoing.top().itemSize <= itemsIn)
			{
				duration_in_quOutgoing.push_back( Time_t - quOutgoing.top().waitStart);
				SetItemsIn((-1)*quOutgoing.top().itemSize);
				quOutgoing.top().p->ActivateNext();
				quOutgoing.pop();
			}
	}
	else
	{
		quComming.push(FacilityQuItem( &p, itemSize, priority ));

		// save for Output
			quCommingCount++;
			if (quCommingMax < quComming.size())
				quCommingMax = quComming.size();
		// End save for Output
	}
}

void Facility::release(Transaction &p, unsigned int itemSize, unsigned int priority) {
	outgoingCount++;
	if (DEBUG)
		std::cout << " bere/uvolnuje linku " << name << " s " << itemSize << " items" << " v case " << Time_t << "\n";
	if (quOutgoing.empty() && itemsIn >= itemSize)
	{

		duration_in_quOutgoing.push_back(0);
		SetItemsIn((-1)*itemSize);
		p.ActivateNext();

		// ak sa uvolnilo tak zavolaj dalsieho do skladu na vlozenie
		if (!quComming.empty())
			if (quComming.top().itemSize <= capacity - itemsIn)
			{
				double tmp = Time_t - quComming.top().waitStart;
				duration_in_quComming.push_back( tmp );
				SetItemsIn(quComming.top().itemSize);
				quComming.top().p->ActivateNext();
				quComming.pop();
			}
	}
	else
	{
		// must waitng, queue not empty, or not enought itemsIn
		quOutgoing.push(FacilityQuItem( &p, itemSize, priority ));

		// save for Output
			quOutgoingCount++;
			if (quOutgoingMax < quOutgoing.size())
				quOutgoingMax = quOutgoing.size();
		// End save for Output
	}
}

void Facility::Output() {
	cout << "\n\n\033[1;32m--------------- OUTPUT FROM " << this->name << "-----------------\033[0m\n";

	histogramQu.push_back(HistogramQu{ Time_t - eventStart, itemsIn });
	if (itemsIn != 0)
		cout << "\033[1;31mFacility has " << itemsIn << "/" << capacity << " items in!!\033[0m\n";
	if (!quComming.empty())
		cout << "\033[1;31mFacility has " << quComming.size() << " records in quComming\033[0m\n";
	if (!quOutgoing.empty())
		cout << "\033[1;31mFacility has " << quOutgoing.size() << " records in quOutgoing\033[0m\n";

	cout << "Incoming  " << commingCount << " in queue " << quCommingCount << " max queue " << quCommingMax << "\n";
	cout << "Outcoming " << outgoingCount << " in queue " << quOutgoingCount << " max queue " << quOutgoingMax << "\n";

	// imcomming queue
	double sum=0, minTime=0, maxTime=0; int count=0, countFree = 0;
	bool isFirst = true;
	while (!duration_in_quComming.empty())
	{
		if (duration_in_quComming.back() != 0)
		{
			count++;
			sum += duration_in_quComming.back();

			if (duration_in_quComming.back() > maxTime)
				maxTime = duration_in_quComming.back();
			if (isFirst)
			{
				isFirst = false;
				minTime = duration_in_quComming.back();
			}
			if (duration_in_quComming.back() < minTime)
				minTime = duration_in_quComming.back();
		}
		else
			countFree++;
		duration_in_quComming.pop_back();
	}
	if (count == 0 && countFree == 0)
		cout << "No one seize facility\n";
	else
	{
		cout << "\nINCOMING\n";
		if (count == 0)
		{
			cout << "No one was waiting in qu\n";
			cout << "Items entered " << countFree << "\n";
		}
		else
		{
			cout << "Average waiting time: " << sum / (count + countFree) << " (without transactions in queue at stop time)\n";
			cout << "Items without waiting: " << countFree << "\n";
			cout << "Items with    waiting: " << count << "\n";
			cout << "Minimal time in qu:   " << minTime << "\n";
			cout << "Maximal time in qu:   " << maxTime << "\n";
			cout << "Avarage time in qu:   " << sum / count << "\n";
		}
	}

	// outgoing queue
	sum=0; count=0; countFree = 0; minTime=0; maxTime=0; isFirst = true;
	while (!duration_in_quOutgoing.empty())
	{
		if (duration_in_quOutgoing.back() != 0)
		{
			count++;
			sum += duration_in_quOutgoing.back();

			if (duration_in_quOutgoing.back() > maxTime)
				maxTime = duration_in_quOutgoing.back();
			if (isFirst)
			{
				isFirst = false;
				minTime = duration_in_quOutgoing.back();
			}
			if (duration_in_quOutgoing.back() < minTime)
				minTime = duration_in_quOutgoing.back();
		}
		else
			countFree++;
		duration_in_quOutgoing.pop_back();
	}
	if (count == 0)
		cout << "No one release facility\n";
	else
	{
		cout << "\nOUTGOING\n";
		if (count == 0)
		{
			cout << "No one was waiting in qu\n";
			cout << "Items entered " << countFree << "\n";
		}
		else
		{
			cout << "Average waiting time: " << sum / (count + countFree) << " (without transactions in queue at stop time)\n";
			cout << "Items without waiting: " << countFree << "\n";
			cout << "Items with    waiting: " << count << "\n";
			cout << "Minimal time in qu:   " << minTime << "\n";
			cout << "Maximal time in qu:   " << maxTime << "\n";
			cout << "Avarage time in qu:   " << sum / count << "\n";
		}
	}

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
				count += histogramQu.back().durationTime;
			}
			histogramQu.pop_back();
		}
		cout << "Facility used capacity " << sum /(Time_t - Time_tStart) << "\n";
		cout << "Facility was " << 100* duration_of_empty /(Time_t - Time_tStart) << "% of time free\n"; // v percentach
	}
}

bool operator<(const FacilityQuItem a, const FacilityQuItem b)
{
	return a.priority < b.priority;
}
