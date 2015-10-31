#include "facility.h"

Facility::Facility() {
	empty = true;
}
void Facility::seize(Process &p) {
	if(empty)
		p.Behavior();
}
void Facility::release(Process &p) {
	if(!qu.empty())
		qu.pop().Behavior;
	else
		empty = true;
	p.Behavior;
}
