#include <simlite.h>
#define MAX_FLIAS 20
const int p_krav = 100;

Facility flasky(MAX_FLIAS, "flasky"); // vyrobene flasky cakajuce na nalozenie
Facility dojicky(3, "Dojicky");
Facility rampa(1, "Nakladaci rampa");

Histogram nalozeni("Jak dlouho ceka auto na nalozeni", 30, 330, 15); // Jak dlouho ceka auto na nalozeni

// proces kravy
class Krava : public Transaction {
public:
    Krava() {
        Pasenie();
    }

    void Pasenie() {
        ActivateAfter(Exp(15*60), DoAfter(ChodDojit));
    }

    void ChodDojit() {
        Seize(dojicky, DoAfter(Dojenie));
    }

    void Dojenie() {
        if (Random() <= 0.1)
        {
            ActivateAfter(Exp(15), DoAfter(NaplnFlasu));
        }
        else
        {
            ActivateAfter(Exp(8), DoAfter(NaplnFlasu));
        }
    }

    void NaplnFlasu(){
        Seize(flasky, DoAfter(SkonciDojenie));
    }

    void SkonciDojenie() {
        Release(dojicky, DoAfter(Pasenie));
    }
} ;

// proces auta nakladajiciho a odvazejiciho konvice
class Auto : public Transaction {
private:
    unsigned int KonviceVAute;
    double Time;
public:
    int odvezenych = 0;
    Auto() {
        ObsadRampu();
    }

    void ObsadRampu() {
        KonviceVAute = 0;
        Seize(rampa, DoAfter(ZaznamenajCas));
    }

    void ZaznamenajCas() {
        Time = Time_t;
        NalozKonvice();
    }

    void NalozKonvice() {
		if (DEBUG)
	        cout << "Pripraveny na nalzoenie v case " << Time_t << "\n";
        Release(flasky, DoAfter(NakladanieKonvice));
    }
    void NakladanieKonvice() {
		if (DEBUG)
	        cout << KonviceVAute+1 << " konvice v aute\n";
        if (++KonviceVAute == 20)
            ActivateAfter(Uniform(1,2), DoAfter(UvolniRampu));
        else
            ActivateAfter(Uniform(1,2), DoAfter(NalozKonvice));
    }

    void UvolniRampu() {
        nalozeni.mark(Time_t-Time);
        Release(rampa, DoAfter(OdvezKonvice));
    }
    void OdvezKonvice() {
        odvezenych++;
        ActivateAfter(60, DoAfter(ObsadRampu));
    }
};

int main() {
    Init(0,200*60*10); // 200 hodin casovy ramec
    //Init(0,2000);

    // vygenerovat 100 krav do systemu (zustavaji tam)
    for (int i=0; i<p_krav; i++)
        new Krava;

    // dve auta do systemu
    Auto vehicles[2];

    Run();

    rampa.Output();
    dojicky.Output();
    flasky.Output();
    nalozeni.Output();
    cout << "\033[1;32m--------------- ODVEZENYCH AUT " << vehicles[0].odvezenych + vehicles[1].odvezenych
            << "-----------------\033[0m\n";
}
