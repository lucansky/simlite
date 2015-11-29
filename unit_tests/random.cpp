#include <simlite.h>

#include <random>
#include <iostream>

int main() {
    Histogram h("Exp test", 0, 20);

    for (int i=0; i < 1000000; ++i) {
        double generated_number = Exp(1);
        //std::cout << generated_number << "\n";

        h.mark(generated_number);
    }

    h.Output();
}