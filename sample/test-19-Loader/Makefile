SRCS     = $(wildcard *.cpp)
OBJS     = $(SRCS:.cpp=.o)
TARGET   = a.out
CXX      = g++
CXXFLAGS = -Wall -O3  -Wno-deprecated -I../../bin/include
LD       = g++
LDFLAGS  = -L../../bin/lib
LIBS     = -lm3g -lglut


all: $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $(TARGET)
	@echo done.

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c

depend:
	makedepend -- $(CXXFLAGS) -- $(SRCS)

clean:
	rm -rf *.o *.so *.a *~ *.ppm $(TARGET)
	@echo done.


