#include "shared.h"

#ifndef SIMLITE_CALENDAR_H
#define SIMLITE_CALENDAR_H

#define HIGH_PRIORITY 99

#include "event.h"

void Init(double timeStart, double timeTo);
void Run();

class Calendar {
public:
	void add(Event event);
	bool Empty();
	void dump();
	void CallNext();
private:
	std::priority_queue<Event> events;
};

extern Calendar calendar;

#endif //SIMLITE_CALENDAR_H
