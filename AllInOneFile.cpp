
#include <typeinfo>


#include <stdio.h>
#include <iostream>
#include <string>
#include <functional>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
using namespace std;

// .................................................................   SHARED
double Time_t = 0;
class Process;
//class Zakaznik;
typedef std::function<void(void)> PtrMethod;
typedef void(Process::*PtrMethodOld)();

//class Zakaznik;
//typedef void(Zakaznik::*ZakaznikPtrMethod)();


// .................................................................   EVENT
class Event {
	//TODO pridat do kalendara miesto eventu
	static int id_autoincrement;
public:
	int id;

	double at;
	int priority;
	Process *process;
public:
	Event(double at, int priority, Process *process);
};

bool operator<(const Event &a, const Event &b);

Event::Event(double _at, int _priority, Process *_process) {
	id = id_autoincrement++;

	at = _at;
	priority = _priority;
	process = _process;
}

int Event::id_autoincrement = 0;
bool operator<(const Event &a, const Event &b) {
	if (a.at == b.at)
		if (a.priority == b.priority)
			return a.id > b.id;
		else
			return a.priority < b.priority;
	else
		return a.at > b.at;
}
// .................................................................   CALENDAR

class Calendar {
public:
	void add(Event event);
	bool Empty();
	void dump();
	void CallNext();
private:
	std::priority_queue<Event> events;
};
Calendar calendar;

// .................................................................   FACILITY
typedef struct
{
	Process *p;
	double waitStart;
}FacilityQuItem;
class Facility {
private:
	double emptyStart;
	bool empty;
	double duration_of_empty;
	std::queue<FacilityQuItem> qu;
	int maxQu;
	std::vector<double> duration_of_service;
	std::vector<double> duration_in_queue;
public:
	void Output();
	Facility();
	void seize(Process &p);
	void release();
};
Facility pokladna;

// .................................................................   PROCESS
class Process {
public:
	PtrMethod ptrMethod;
	string name;
public:
//	explicit Process();

	void Seize(Facility &f, PtrMethod nextMethod);

	void ActivateAfter(double interval, PtrMethod nextMethod);

	void ActivateNext();

	void Release(Facility &f, PtrMethod nextMethod);
};
//
//Process::Process() {
//	this->Start();
//}

void Process::Seize(Facility &f, PtrMethod nextMethod) {
	ptrMethod = nextMethod;
	f.seize(*this);
}
void Process::ActivateNext() {
	(ptrMethod)();
}
void Process::Release(Facility &f, PtrMethod nextMethod) {
	std::cout << "V case " << Time_t << " " << name << " uvolnil pokladnu\n";
	ptrMethod = nextMethod;
	f.release();
	ActivateNext();
}
void Process::ActivateAfter(double interval, PtrMethod nextMethod)
{
	ptrMethod = nextMethod;
	calendar.add(Event(Time_t + interval, 1, this));
}

//..............................................................................  ZAKAZNIK.cpp
class Zakaznik : public Process {
public:
	using Process::Process;
	void Start();
	void End();
	void PokladnaRelease();
	void PokladnaRun();
	void PokladnaSeize();
};

// Toto treba dat aby definoval uzivatel cez dedenie

void Zakaznik::Start()
{
	this->PokladnaSeize();
}

void Zakaznik::End()
{
	// koniec programu
	std::cout << "V case " << Time_t << " " << name << " skoncil\n";
}
void Zakaznik::PokladnaRelease()
{
	Release(pokladna, [=](void) { this->End();});
}
void Zakaznik::PokladnaRun()
{
	std::cout << "V case " << Time_t << " " << name << " obsadil pokladnu na 15 min\n";
	ActivateAfter(15, [=](void) { this->PokladnaRelease();}); // uvolnim zariadenie po 10s
}
void Zakaznik::PokladnaSeize()
{
	Seize(pokladna, [=](void) { this->PokladnaRun();});
}


//..............................................................................  FACILITY.cpp

Facility::Facility() {
	empty = true;
	emptyStart = Time_t;
	maxQu = 0;
}
void Facility::seize(Process &p) {
	if (empty == true)
	{
		duration_of_empty += Time_t - emptyStart;
		duration_in_queue.push_back(0);
		p.ActivateNext();
		empty = false;
	}
	else
	{
		qu.push(FacilityQuItem{ &p, Time_t });
		if (maxQu < qu.size())
			maxQu = qu.size();
	}
}
void Facility::release() {
	duration_of_service.push_back(Time_t - emptyStart);
	if (!qu.empty())
	{
		qu.front().p->ActivateNext();
		duration_in_queue.push_back(Time_t - qu.front().waitStart);
		emptyStart = Time_t;
		qu.pop();
	}
	else
	{
		empty = true;
		emptyStart = Time_t;
	}
}
void Facility::Output() {
	cout << "Maximalna fronta: " << maxQu << "\n";
	double sum=0;
	int count=0;
	while (!duration_in_queue.empty())
	{
		count++;
		sum += duration_in_queue.back();
		duration_in_queue.pop_back();
	}
	cout << "Priemerna cas vo fronte: " << sum / count << "\n";
	sum = 0;
	count = 0;
	while (!duration_of_service.empty())
	{
		count++;
		sum += duration_of_service.back();
		duration_of_service.pop_back();
	}
	cout << "Priemerna dlzka obsluhy: " << sum / count << "\n";
	cout << "Zariadenie volne: " << duration_of_empty << "\n";
}

//..............................................................................  CALENDAR.cpp

bool Calendar::Empty()
{
	return events.size()==0?true:false;
}
void Calendar::add(Event event)
{
	events.push(event);
}

void Calendar::dump()
{
	int size = events.size();
	for (int i = 0; i < size; ++i)
	{
		std::cout << events.top().at << " " << events.top().priority;
		printf(" %p\n", events.top().process);
		events.pop();
	}
}
void Calendar::CallNext()
{
	if (events.size() > 0)
	{
		Time_t = events.top().at;
		events.top().process->ActivateNext();
		events.pop();
	}
}

// TODO Generator

int main()
{
//	Process pro1;
//	Process pro2;
//	Process pro3;
//	Process pro4;
//	Process pro5;
//	Process pro6;
//	Process pro7;
//
//	// Todo Generator
//	pro1.Start(&Process::PokladnaSeize, "pro1");
//	pro2.Start(&Process::PokladnaSeize, "pro2");
//	pro3.Start(&Process::PokladnaSeize, "pro3");
//	pro4.Start(&Process::PokladnaSeize, "pro4");
//	pro5.Start(&Process::PokladnaSeize, "pro5");
//	pro6.Start(&Process::PokladnaSeize, "pro6");
//	pro7.Start(&Process::PokladnaSeize, "pro7");

	(new Zakaznik)->Start();
//zak1.Start();
//zak1.Start(&Zakaznik::PokladnaSeize, "zak1");

	while(!calendar.Empty())
		calendar.CallNext();
	pokladna.Output();
	//int i;
	//scanf("%d", &i);
	return 0;
}


