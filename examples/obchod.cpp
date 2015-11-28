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


// ............................................................ generator.h ...................
//class Generator : public Process{
//private:
//    double (*delayFunc)(double);
//    double funcArg;
//public:
//    //virtual void Behavior(); // potrebne aby tuto metodu definoval uzivatel
//    void Behavior();
//    Generator(double (*delayFunc)(double), double funcArg);
//    void Run();
//};
//// ............................................................ END generator.h ...................
//
//
//// priklad ako definovat Behavior generatora. Toto by mal definovat uzivatel
//void Generator::Behavior() {
//    new Zakaznik;
//}
//
//
//// ............................................................ generator.cpp ...................
//void Generator::Run() {
//    Behavior();
//    ActivateAfter(delayFunc(funcArg), DoAfter(Run)); // spusti generator znovu za
//    //ActivateAfter(20, DoAfter(Run)); // spusti generator znovu za
//}
//
//Generator::Generator(double (*delayFunc)(double), double funcArg) {
//    this->delayFunc = delayFunc;
//    this->funcArg = funcArg;
//    ActivateAfter(delayFunc(0), DoAfter(Run)); // spusti generator znovu za
//    //Run();
//}
// ............................................................ END generator.cpp ...................


int main() {
    Init(0, 100);
    new Generator();
    Run();

    pokladna.Output();
}
