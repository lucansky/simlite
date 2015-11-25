#include "shared.h"

#ifndef SIMLITE_EVENT_H
#define SIMLITE_EVENT_H

#include "process.h"

class Event {
	//TODO pridat do kalendara miesto eventu
	static int id_autoincrement;
public:
	int id;

	double at;
	int priority;
	Process *process;
public:
	Event(double at, int priority, Process *process);

};

bool operator<(const Event &a, const Event &b);

#endif //SIMLITE_EVENT_H
