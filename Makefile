
#all:
#

CXX=g++
CXXFLAGS=-std=c++11
LDFLAGS=-I./simlite

SRCS=$(wildcard simlite/*.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

all: simlite.a examples

#$(BIN): $(OBJS) simlite.a
#	$(CXX) $(LDFLAGS) -o $(BIN) $(BIN).o simlite.a $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) -MM $^>>./.depend;

simlite.a: $(filter-out $(BIN).o, $(OBJS))
	ar -rcs $@ $(filter-out $(BIN).o, $(OBJS))

obchod: simlite.a examples/obchod.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) examples/obchod.cpp -o examples/obchod simlite.a $(LDLIBS)

include .depend

