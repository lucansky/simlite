/**
 *  SIMLite - simple discrete simulation core
 *  Authors:
 *     Adam Lucansky <xlucan01@stud.fit.vutbr.cz>
 *     Tomas Kello <xkello00@stud.fit.vutbr.cz>
 */

#include "transaction.h"

#include "event.h"
#include "calendar.h"

Transaction::Transaction(string name)
{
	this->name = name;
}

void Transaction::Seize(Facility &f, PtrMethod nextMethod, unsigned int itemSize, unsigned int priority) {
	if (DEBUG)
		std::cout << "Process " << name;
    ptrMethod = nextMethod;
    f.seize(*this, itemSize, priority);
}

void Transaction::ActivateNext() {
    (ptrMethod)();
}

void Transaction::Release(Facility &f, PtrMethod nextMethod, unsigned int itemSize, unsigned int priority) {
	if (DEBUG)
		std::cout << "Process " << name;
    ptrMethod = nextMethod;
    f.release(*this, itemSize, priority);
}

void Transaction::ActivateAfter(double interval, PtrMethod nextMethod)
{
    ptrMethod = nextMethod;
    calendar.add(Event(Time_t + interval, 1, this));
}
