#include "process.h"

void Process::Seize(Facility &f) {
    f.seize(*this);
}
