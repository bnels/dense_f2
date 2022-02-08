CXXFLAGS = -Wall -std=c++17 -Wextra
OUTFLAGS = -O3
PERFFLAGS = -O3 -march=native -fprofile-use
PROFFLAGS = -O3 -march=native -pg -fprofile-generate
DBFLAGS = -g -O0
OPFLAGS = -O3
CXX ?= g++
IFLAGS = -I../include

ifeq ($(CXX),g++)
  OUTFLAGS += -fopenmp
else ifeq ($(CXX),clang++)
  OUTFLAGS += -lomp
else
	OUTFLAGS += -lomp -DMESSAGE='"Compiled with an unknown compiler"'
endif

default: demo.out

%.out: %.cpp
	$(CXX) -o $@ $< $(IFLAGS) $(CXXFLAGS) $(OUTFLAGS)

%.op: %.cpp
	$(CXX) -o $@ $< $(IFLAGS) $(CXXFLAGS) $(OPFLAGS)

%.prof: %.cpp
	$(CXX) -o $@ $< $(IFLAGS) $(CXXFLAGS) $(PROFFLAGS)

%.db: %.cpp
	$(CXX) -o $@ $< $(IFLAGS) $(CXXFLAGS) $(DBFLAGS)

%.perf: %.cpp
	$(CXX) -o $@ $< $(IFLAGS) $(CXXFLAGS) $(PERFFLAGS)

%: %.out %.prof %.db

.PHONY: clean
clean:
	rm -f *.out *.prof 
