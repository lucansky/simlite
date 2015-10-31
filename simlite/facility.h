#ifndef SIMLITE_FACILITY_H
#define SIMLITE_FACILITY_H

class Process;

class Facility {
private:
	bool empty;
	Facility();
	std::queue<Process*> qu;
	std::vector<double> duration_of_service;
	std::vector<double> duration_in_queue;
public:
    void seize(Process &p);
    void release(Process &p);
};

#endif //SIMLITE_FACILITY_H
