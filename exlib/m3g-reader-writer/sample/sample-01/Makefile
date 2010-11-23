SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = a.out
CXX = g++
CXXFLAGS = -Wall -g -Wno-deprecated -I../../src
LD = g++
LDFLAGS = -L../../src
LIBS = -lM3GReaderWriter -lz 


all: $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $(TARGET)
	@echo done.

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c

depend:
	makedepend -- $(CXXFLAGS) -- $(SRCS)

clean:
	rm -rf *.o *.so *.a *~ $(TARGET)
	@echo done.


# DO NOT DELETE

main.o: /usr/include/GL/glut.h /usr/include/GL/freeglut_std.h
main.o: /usr/include/GL/gl.h /usr/include/GL/glext.h /usr/include/inttypes.h
main.o: /usr/include/features.h /usr/include/bits/predefs.h
main.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
main.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
main.o: /usr/include/stdint.h /usr/include/bits/wchar.h /usr/include/GL/glu.h
main.o: /usr/include/stdlib.h /usr/include/sys/types.h
main.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
main.o: /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h
main.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
main.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
main.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
main.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
