#include "calendar.h"

// TODO: Put somewhere else
Calendar calendar;
double Time_t = 0;

bool Calendar::Empty()
{
    return events.size()==0?true:false;
}
void Calendar::add(Event event)
{
    events.push(event);
}

void Calendar::dump()
{
    int size = events.size();
    for (int i = 0; i < size; ++i)
    {
        std::cout << events.top().at << " " << events.top().priority;
        printf(" %p\n", events.top().process);
        events.pop();
    }
}
void Calendar::CallNext()
{
    if (events.size() > 0)
    {
        Time_t = events.top().at;
        events.top().process->ActivateNext();
        events.pop();
    }
}