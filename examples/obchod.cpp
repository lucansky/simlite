#include <simlite.h>

Facility pokladna;

class Zakaznik : Process {
    int state = 0;

public:

    void Behavior() {
        switch(state) {
            case 0:
                Seize(pokladna);

                break;
            case 1:
                ActivateAfter(Exp(3));

                break;
            case 2:
                Release(pokladna);
                break;
        }
        state++;
    }

};

int main() {
    Calendar calendar;
    calendar.add(Event(0, 1, NULL));
    calendar.add(Event(2, 1, NULL));
    calendar.add(Event(2, 2, NULL));
    calendar.add(Event(2, 3, (Process*)1));
    calendar.add(Event(2, 3, (Process*)2));
    calendar.add(Event(2, 3, (Process*)3));
    calendar.add(Event(2, 3, (Process*)4));
    calendar.add(Event(1, 1, NULL));

    calendar.dump();
    return 0;

}
