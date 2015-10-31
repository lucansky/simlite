#include "calendar.h"
#include <stdio.h>
void Calendar::add(Event event)
{
	events.push(event);
}

void Calendar::dump()
{
	int size = events.size();
	for (int i = 0; i < size; ++i)
    {
        std::cout<<events.top().at<<" "<<events.top().priority;
        printf(" %p\n", events.top().process);
        events.pop();
    }
}
// bool operator<(const node& a, const node& b) {

//     node temp1=a,temp2=b;
//     if(a.age != b.age)
//         return a.age > b.age;
//     else{
//         return temp1.name.append(temp2.name) > temp2.name.append(temp1.name);
//     }
// }
