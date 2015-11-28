#include "process.h"

#include "event.h"
#include "calendar.h"

void Process::Seize(Facility &f, PtrMethod nextMethod) {
    ptrMethod = nextMethod;
    f.seize(*this);
}

void Process::ActivateNext() {
    (ptrMethod)();
}

void Process::Release(Facility &f, PtrMethod nextMethod) {
	if (DEBUG)
	    std::cout << "V case " << Time_t << " " << name << " uvolnil pokladnu\n";
    ptrMethod = nextMethod;
    f.release(*this);
    ActivateNext();
}

void Process::ActivateAfter(double interval, PtrMethod nextMethod)
{
    ptrMethod = nextMethod;
    calendar.add(Event(Time_t + interval, 1, this));
}