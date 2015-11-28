#include "histogram.h"

Histogram::Histogram(std::string _name, double _min, double _max, int interval_count) :
                    name(_name) , min(_min), max(_max)
{
    interval_counts.resize(interval_count);
}

int Histogram::interval_count() {
    return interval_counts.size();
}

double Histogram::step() {
    return (max - min) / interval_count();
}

void Histogram::mark(double value) {
    if(value >= max || value < min)
        return;

    int index = (value - min) / step();

    interval_counts.at(index)++;
}

void Histogram::Output() {
    std::cout << "=== " << name << " ===\n";

    for (int i = 0; i < interval_count(); ++i) {
        std::cout   << std::fixed
                    << std::setprecision(3)
                    << min + i*step()
                    << "\t\t"
                    << interval_counts[i]
                    << "\n";
    }
}