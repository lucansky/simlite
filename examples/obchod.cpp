#include "../simlite/simlite.h"

Facility pokladna;


class Zakaznik : public Process {
public:
    Zakaznik() {
        PokladnaSeize(); // Pociatocna metoda ktora sa naplanuje po vytvoreni Zakaznika
    }

    // Zakaznik sa snazi obsadit pokladnu
    void PokladnaSeize() {
        Seize(pokladna, DoAfter(PokladnaRun));
    }

    // Zakaznikovi sa podarilo uspesne obsadit pokladnu
    // Zostava vo facility po nejaku dobu
    void PokladnaRun() {

        std::cout << "V case " << Time_t << " " << name << " obsadil pokladnu na 15 min\n";
        ActivateAfter(15, DoAfter(PokladnaRelease)); // uvolnim zariadenie po 15 jednotkach casu
    }

    // Skoncila obsluha pokladnou, zakaznik ide von
    void PokladnaRelease() {
        Release(pokladna, DoAfter(End));
    }

    // Zakaznik ide von zo systemu
    void End() {
        std::cout << "V case " << Time_t << " " << name << " skoncil\n";
    }

};

int main() {
    Zakaznik zak1;
    Zakaznik zak2;
    Zakaznik zak3;

    Init(0, 10);
    Run();

    pokladna.Output();
}
