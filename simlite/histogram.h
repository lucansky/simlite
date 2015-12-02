#include "shared.h"

#ifndef SIMLITE_HISTOGRAM_H
#define SIMLITE_HISTOGRAM_H

class Histogram {
    std::vector<int> interval_counts;

    std::string name;
    double min;
    double max;
    int total_count;
    int values_lower_than_limit;
    int values_higher_than_limit;

public:
    Histogram(std::string _name, double _min, double _max, int interval_count = 40);
    int interval_count(); // Derived from size of interval_counts
    double step();

    void mark(double value);
    void Output();
};

#endif //SIMLITE_HISTOGRAM_H
