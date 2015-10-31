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

    return 0;

}
