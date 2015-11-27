#include "facility.h"

Facility::Facility() {
	// save for Output
		empty = true;
		eventStart = Time_t;
		maxQu = 0;
	// End save for Output
}

void Facility::seize(Process &p) {
	if (empty == true)
	{
		// save for Output
			empty = false;
			duration_of_empty += Time_t - eventStart;
			eventStart = Time_t;
		// End save for Output

		duration_in_queue.push_back(0);
		p.ActivateNext();
	}
	else
	{
		qu.push(FacilityQuItem{ &p, Time_t });

		// save for Output
			if (maxQu < qu.size())
				maxQu = qu.size();
		// End save for Output
	}
}

void Facility::release() {
	duration_of_service.push_back(Time_t - eventStart);
	if (!qu.empty())
	{
		// save for Output
			eventStart = Time_t;
			duration_in_queue.push_back(Time_t - qu.front().waitStart);
		// End save for Output

		qu.front().p->ActivateNext();
		qu.pop();
	}
	else
	{
		// save for Output
			empty = true;
			eventStart = Time_t;
		// End save for Output
	}
}

void Facility::Output() {
	if (empty)
	{
		duration_of_empty += Time_t - eventStart;
	}
	else
	{
		cout << "\n\033[1;31mFacility not empty!!\n";
		if (!qu.empty())
			cout << "And still have " << qu.size() << " Process in queue\n";
		cout <<"\033[0m\n";
	}
	cout << "Maximalna fronta: " << maxQu << "\n";

	double sum=0; int count=0;
	while (!duration_in_queue.empty())
	{
		count++;
		sum += duration_in_queue.back();
		duration_in_queue.pop_back();
	}
	if (count == 0)
		cout << "Vo fronte nebol ziadny zakaznik\n";
	else
		cout << "Priemerna cas vo fronte: " << sum / count << "\n";

	sum = 0; count = 0;
	while (!duration_of_service.empty())
	{
		count++;
		sum += duration_of_service.back();
		duration_of_service.pop_back();
	}
	if (count == 0)
		cout << "Obsluha neobsluzila ziadneho zakaznika\n";
	else
		cout << "Priemerna dlzka obsluhy: " << sum / count << "\n";

	cout << "Zariadenie volne: " << duration_of_empty << "\n";
}
