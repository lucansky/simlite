/**
 *  SIMLite - simple discrete simulation core
 *  Authors:
 *     Adam Lucansky <xlucan01@stud.fit.vutbr.cz>
 *     Tomas Kello <xkello00@stud.fit.vutbr.cz>
 */

#include "event.h"

int Event::id_autoincrement = 0;

Event::Event(double _at, int _priority, Transaction *_transaction) {
	id = id_autoincrement++;

	at = _at;
	priority = _priority;
	transaction = _transaction;
}

bool operator<(const Event &a, const Event &b) {
	if (a.at == b.at)
		if (a.priority == b.priority)
			return a.id > b.id;
		else
			return a.priority < b.priority;
	else
		return a.at > b.at;
}
