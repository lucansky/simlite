#include <simlite.h>

#define DoAfter(piece_of_code) [=](void) { piece_of_code; }

Facility pokladna;
double Time_t = 0;

class Zakaznik : public Process {
public:
    Zakaznik() { PokladnaSeize(); }

    void PokladnaSeize();
    void PokladnaRun();
    void PokladnaRelease();
    void End();

};

void Zakaznik::PokladnaSeize()
{
    // Zakaznik sa snazi obsadit pokladnu
    Seize(pokladna, DoAfter(PokladnaRun()));
}

void Zakaznik::PokladnaRun()
{
    // Zakaznikovi sa podarilo uspesne obsadit pokladnu
    // Zostava vo facility po nejaku dobu
    std::cout << "V case " << Time_t << " " << name << " obsadil pokladnu na 15 min\n";
    ActivateAfter(15, [=](void) { this->PokladnaRelease(); }); // uvolnim zariadenie po 15 jednotkach casu
}

void Zakaznik::PokladnaRelease()
{
    // Skoncila obsluha pokladnou, zakaznik ide von
    Release(pokladna, [=](void) { this->End(); });
}

void Zakaznik::End()
{
    // Zakaznik ide von zo systemu
    std::cout << "V case " << Time_t << " " << name << " skoncil\n";
}

int main() {

    Zakaznik zak1;

    while(!calendar.Empty())
        calendar.CallNext();
    pokladna.Output();
}
