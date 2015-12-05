#include <simlite.h>

Facility Linka(1, "Prenosova linka");
Histogram hist("Doba v systemu", 100, 1600, 15);

class Packet : public Process {
    double time;
    int priority;

public:
    Packet(int _priority) {
        priority = _priority;
        time = Time_t;
        SeizeNIC();
    }

    void SeizeNIC() {
        Seize(Linka, DoAfter(WaitInLine));
    }

    void WaitInLine() {
        ActivateAfter(Uniform(150, 250) + 5, DoAfter(DecideIfTransmissionSuccessful));    // prenos dat a dotaz na uspesnost
    }

    void DecideIfTransmissionSuccessful() {
        if (Uniform(0.0, 1.0)<=0.01) {
            // 1% chyba, opakovani cekani

            WaitInLine();
            return;
        }

        // Transmission successful, leaving line
        Release(Linka, DoAfter(PostTransmission));

        hist.mark(Time_t-time);
    }

    void PostTransmission() {
        delete this;
    }
};

class PacketGenerator : public Process {
public:
    PacketGenerator() {
        Loop();
    }

    void Loop() {
        GenerateSinglePacket();
        ActivateAfter(Exp(250), DoAfter(Loop));
    }

    void GenerateSinglePacket() {
        /*
            20% - vysoka priorita
            40% - stredni
            40% - mala
        */
        double r = Uniform(0.0, 1.0);
        int priority;
        if (r<=0.2)
            priority = 3;
        else if (r>0.2 && r<=0.6)
            priority = 2;
        else
            priority = 1;

        new Packet(priority);
    }

};

int main()
{
    Init(0,1000*1000);
    new PacketGenerator();
    Run();
    Linka.Output();
    hist.Output();
}
