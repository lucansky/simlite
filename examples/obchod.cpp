#include "../simlite/simlite.h"

Facility pokladna;

class Zakaznik : public Process {
private:
    double ZakaznikTime;
public:
    Zakaznik() {
        PokladnaSeize(); // Pociatocna metoda ktora sa naplanuje po vytvoreni Zakaznika
    }

    // Zakaznik sa snazi obsadit pokladnu
    void PokladnaSeize() {
        Seize(pokladna, DoAfter(PokladnaRun));
        ZakaznikTime = Time_t;
    }

    // Zakaznikovi sa podarilo uspesne obsadit pokladnu
    // Zostava vo facility po nejaku dobu
    void PokladnaRun() {

        std::cout << "Po cakani " << Time_t - ZakaznikTime << " v case " << Time_t << " obsadil pokladnu\n";
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

class Generator : Process {
public:
    Generator() {
        GenerujZakaznika();
    }

    void GenerujZakaznika() {
        new Zakaznik;
        ActivateAfter(15, DoAfter(GenerujZakaznika));
    }
};

int main() {
    Init(0, 100);
    Generator generator;
    Run();

    pokladna.Output();
}
