CXX=g++
CPPFLAGS=-Isrc
CXXFLAGS=-g -Wall -Wextra
LDFLAGS=-g

SRCS=examples/nbody_gravitation.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: examples

examples: $(OBJS)
	$(CXX) $(LDFLAGS) -o test $(OBJS)

nbody_gravitation.o: nbody_gravitation.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c nbody_gravitation.cpp

clean:
	rm -f $(OBJS)
