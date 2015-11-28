#include <simlite.h>

int main() {
    Histogram h("Testovaci histogram", 5, 20, 46);

    h.mark(8.1);
    h.mark(8.2);
    h.mark(8.4);
    h.mark(7.9);

    h.Output();
    return 0;
}