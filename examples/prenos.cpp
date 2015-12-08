#include <simlite.h>

Facility Linka(1, "Prenosova linka");
Histogram hist("Doba v systemu", 100, 1600, 15);

class Packet : public Transaction {
    double time; // Time of entering system
    int priority;

public:
    Packet(int _priority) {
        priority = _priority;
        time = Time_t;
        SeizeNIC();
    }

    // Queue up to network-interface-controller with given priority
    void SeizeNIC() {
        Seize(Linka, DoAfter(WaitInLine), 1, priority);
    }

    void WaitInLine() {
        // Transmission of data + data validation delay
        ActivateAfter(Uniform(150, 250) + 5, DoAfter(DecideIfTransmissionSuccessful));
    }

    void DecideIfTransmissionSuccessful() {
        if (Uniform(0.0, 1.0)<=0.01) {
            // 1% error, retry if incorrect data received

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

class PacketGenerator : public Transaction {
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
    PacketGenerator generator;
    Run();
    Linka.Output();
    hist.Output();
}

