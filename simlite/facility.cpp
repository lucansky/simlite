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
	cout << "Maximalna fronta: " << maxQu << "\n";
	double sum=0;
	int count=0;
	while (!duration_in_queue.empty())
	{
		count++;
		sum += duration_in_queue.back();
		duration_in_queue.pop_back();
	}
	cout << "Priemerna cas vo fronte: " << sum / count << "\n";
	sum = 0;
	count = 0;
	while (!duration_of_service.empty())
	{
		count++;
		sum += duration_of_service.back();
		duration_of_service.pop_back();
	}
	cout << "Priemerna dlzka obsluhy: " << sum / count << "\n";
	cout << "Zariadenie volne: " << duration_of_empty << "\n";
}