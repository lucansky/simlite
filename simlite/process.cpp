#include "process.h"

#include "event.h"
#include "calendar.h"

void Process::Seize(Facility &f, PtrMethod nextMethod, unsigned int itemSize) {
    ptrMethod = nextMethod;
    f.seize(*this, itemSize);
}

void Process::ActivateNext() {
    (ptrMethod)();
}

void Process::Release(Facility &f, PtrMethod nextMethod, unsigned int itemSize) {
	//if (DEBUG)
	  //  std::cout << "V case " << Time_t << " " << name << " uvolnil process\n";
    ptrMethod = nextMethod;
    f.release(*this, itemSize);
}

void Process::ActivateAfter(double interval, PtrMethod nextMethod)
{
    ptrMethod = nextMethod;
    calendar.add(Event(Time_t + interval, 1, this));
}