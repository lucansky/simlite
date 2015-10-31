#include "shared.h"
#include "process.h"

#ifndef SIMLITE_CALENDAR_H
#define SIMLITE_CALENDAR_H

#include "event.h"

class Calendar {
public:
	//Calendar();
	void add(Event event);
	void dump();
private:
	std::priority_queue<Event> events;
};


#endif //SIMLITE_CALENDAR_H
