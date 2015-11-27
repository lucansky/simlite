#include "facility.h"

Facility::Facility() {
	empty = true;
	emptyStart = Time_t;
	maxQu = 0;
}

void Facility::seize(Process &p) {
	if (empty == true)
	{
		duration_of_empty += Time_t - emptyStart;
		duration_in_queue.push_back(0);
		p.ActivateNext();
		empty = false;
	}
	else
	{
		qu.push(FacilityQuItem{ &p, Time_t });
		if (maxQu < qu.size())
			maxQu = qu.size();
	}
}
void Facility::release() {
	duration_of_service.push_back(Time_t - emptyStart);
	if (!qu.empty())
	{
		qu.front().p->ActivateNext();
		duration_in_queue.push_back(Time_t - qu.front().waitStart);
		emptyStart = Time_t;
		qu.pop();
	}
	else
	{
		empty = true;
		emptyStart = Time_t;
	}
}
void Facility::Output() {
	if (empty)
	{
		duration_of_empty += Time_t - emptyStart;
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