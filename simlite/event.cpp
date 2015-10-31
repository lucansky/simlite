#include "event.h"

Event::Event(double _at, int _priority, Process *_process) {
	id = id_autoincrement++;

	at = _at;
	priority = _priority;
	process = _process;
}

int Event::id_autoincrement = 0;

bool operator<(const Event &a, const Event &b) {
	if (a.at == b.at)
		if(a.priority == b.priority)
			return a.id > b.id;
		else
			return a.priority < b.priority;
	else
		return a.at > b.at;
}