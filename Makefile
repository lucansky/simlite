CXX=g++
CXXFLAGS=-std=c++11 -g
LDFLAGS=-I./simlite

SRCS=$(wildcard simlite/*.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

all: simlite.a examples info

run: all
	./examples/kravin
	./examples/prenos

info:
	@echo
	@echo "Run examples with:"
	@echo " ./examples/kravin"
	@echo " ./examples/prenos"

clean:
	rm -f simlite.a simlite/*.o

examples: kravin prenos

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

simlite.a: $(filter-out $(BIN).o, $(OBJS))
	ar -rcs $@ $(filter-out $(BIN).o, $(OBJS))

kravin: simlite.a examples/kravin.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) examples/kravin.cpp -o examples/kravin simlite.a

prenos: simlite.a examples/prenos.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) examples/prenos.cpp -o examples/prenos simlite.a

pack:
	-rm *.zip || true
	cp doc/dokumentace.pdf dokumentace.pdf
	zip -r 01_xlucan01_xkello00.zip examples/kravin.cpp examples/prenos.cpp simlite/*.cpp simlite/*.h Makefile README.md dokumentace.pdf

	rm dokumentace.pdf

include .depend
