CXX=g++
CXXFLAGS=-std=c++11 -g
LDFLAGS=-I./simlite

SRCS=$(wildcard simlite/*.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

run: all

all: simlite.a examples

clean:
	rm -f simlite.a simlite/*.o

examples: obchod sklad

#$(BIN): $(OBJS) simlite.a
#	$(CXX) $(LDFLAGS) -o $(BIN) $(BIN).o simlite.a $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

simlite.a: $(filter-out $(BIN).o, $(OBJS))
	ar -rcs $@ $(filter-out $(BIN).o, $(OBJS))

obchod: simlite.a examples/obchod.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) examples/obchod.cpp -o examples/obchod simlite.a

sklad: simlite.a examples/sklad.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) examples/sklad.cpp -o examples/sklad simlite.a

histogram: simlite.a unit_tests/histogram.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) unit_tests/histogram.cpp -o unit_tests/histogram simlite.a

random: simlite.a unit_tests/random.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) unit_tests/random.cpp -o unit_tests/random simlite.a


pack:
	-rm *.zip || true
	zip -r 01_xlucan01_xkello00.zip examples/ simlite/ Makefile README.md

include .depend

