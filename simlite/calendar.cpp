#include "calendar.h"

// TODO: Put somewhere else
Calendar calendar;
double Time_t = 0;
double Time_tStart = 0;

void Init(double timeStart, double timeTo)
{
    // invalid time
    if (timeStart > timeTo || timeStart < 0)
    {
        fprintf(stderr, "Invalid time range set\n");
        exit(-1);
    }
    Time_t = timeStart;
    Time_tStart = timeStart;
    calendar.add(Event(timeTo, HIGH_PRIORITY, NULL));
}
void Run()
{
    while(!calendar.Empty())
        calendar.CallNext();
    if (DEBUG)
        std::cout << "\n" << "simulation ended in time: " << Time_t << "\n\n";
}

bool Calendar::Empty()
{
    return events.size() == 0;
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

        // if end of simulation
        if (events.top().process == NULL)
        {
            // remove all elements from queue
            events = std::priority_queue<Event>();
            return;
        }
        events.top().process->ActivateNext();
        events.pop();
    }
}