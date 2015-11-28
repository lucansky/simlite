#include "../simlite/simlite.h"

Facility sklad(12);

class Vyroba : public Process {
public:
    Vyroba() {
        skladSeize(); // Pociatocna metoda ktora sa naplanuje po vytvoreni Vyrobka
    }

    // Vyroba sa snazi obsadit pokladnu
    void skladSeize() {
        Seize(sklad, DoAfter(End), 5);
    }

    // Vyroba ide von zo systemu
    void End() {
        std::cout << "\033[1;34m V case " << Time_t << " skoncila vyroba\033[0m\n";
    }

};

class Odvoz : public Process {
public:
    Odvoz() {
        skladSeize(); // Pociatocna metoda ktora sa naplanuje po vytvoreni Vyrobka
    }

    // Odvoz sa snazi obsadit pokladnu
    void skladSeize() {
        Release(sklad, DoAfter(End), 7);
    }

    // Odvoz ide von zo systemu
    void End() {
        std::cout << "\033[1;32m V case " << Time_t << " skoncil Odvoz\033[0m\n";
    }

};



// ............................................................ generator.h ...................
class Generator : public Process{
private:
    double (*delayFunc)(double);
    double funcArg;
public:
    //virtual void Behavior(); // potrebne aby tuto metodu definoval uzivatel
    void Behavior();
    Generator(double (*delayFunc)(double), double funcArg);
    void Run();
};
// ............................................................ END generator.h ...................


// priklad ako definovat Behavior generatora. Toto by mal definovat uzivatel
void Generator::Behavior() {
    new Vyroba;
    new Odvoz;
}


// ............................................................ generator.cpp ...................
void Generator::Run() {
    Behavior();
    ActivateAfter(delayFunc(funcArg), DoAfter(Run)); // uvolnim zariadenie po 15 jednotkach casu
}

Generator::Generator(double (*delayFunc)(double), double funcArg) {
    this->delayFunc = delayFunc;
    this->funcArg = funcArg;
    Run();
}
// ............................................................ END generator.cpp ...................

class InitSklad : public Process {
public:
    InitSklad() {
        skladSeize(); // Pociatocna metoda ktora sa naplanuje po vytvoreni Vyrobka
    }

    // InitSklad sa snazi obsadit pokladnu
    void skladSeize() {
        Seize(sklad, DoAfter(End), 10);
    }

    // InitSklad ide von zo systemu
    void End() {
    }

};


int main() {
    new InitSklad;
    Init(0, 80);
    new Generator(Exp, 10);
    Run();

    sklad.Output();
}
