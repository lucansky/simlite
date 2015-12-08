/**
 *  SIMLite - simple discrete simulation core
 *  Authors:
 *     Adam Lucansky <xlucan01@stud.fit.vutbr.cz>
 *     Tomas Kello <xkello00@stud.fit.vutbr.cz>
 */

#include "shared.h"

#ifndef SIMLITE_EVENT_H
#define SIMLITE_EVENT_H

#include "transaction.h"

class Event {
	static int id_autoincrement;
public:
	int id;

	double at;
	int priority;
	Transaction *transaction;
public:
	Event(double at, int priority, Transaction *transaction);

};

bool operator<(const Event &a, const Event &b);

#endif //SIMLITE_EVENT_H
