#include "process.h"

#include "event.h"
#include "calendar.h"

Process::Process(string name)
{
	this->name = name;
}

void Process::Seize(Facility &f, PtrMethod nextMethod, unsigned int itemSize) {
	if (DEBUG)
		std::cout << "Process " << name;
    ptrMethod = nextMethod;
    f.seize(*this, itemSize);
}

void Process::ActivateNext() {
    (ptrMethod)();
}

void Process::Release(Facility &f, PtrMethod nextMethod, unsigned int itemSize) {
	if (DEBUG)
		std::cout << "Process " << name;
    ptrMethod = nextMethod;
    f.release(*this, itemSize);
}

void Process::ActivateAfter(double interval, PtrMethod nextMethod)
{
    ptrMethod = nextMethod;
    calendar.add(Event(Time_t + interval, 1, this));
}