SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = a.out
CXX = g++
CXXFLAGS = -Wall -g -Wno-deprecated -I../../src
LD = g++
LDFLAGS = -L../../src
LIBS = -lm3g  -lglut -lGLEW -lGL -lpng -lz


all: $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $(TARGET)
	@echo done.

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c

depend:
	makedepend -- $(CXXFLAGS) -- $(SRCS)

clean:
	rm -rf *.o *.so *.a *~ $(TARGET) *.ppm
	@echo done.


# DO NOT DELETE

libpng.o: /usr/include/png.h /usr/include/zlib.h /usr/include/zconf.h
libpng.o: /usr/include/zlibdefs.h /usr/include/sys/types.h
libpng.o: /usr/include/features.h /usr/include/sys/cdefs.h
libpng.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
libpng.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
libpng.o: /usr/include/bits/typesizes.h /usr/include/time.h
libpng.o: /usr/include/endian.h /usr/include/bits/endian.h
libpng.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
libpng.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
libpng.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
libpng.o: /usr/include/bits/pthreadtypes.h /usr/include/unistd.h
libpng.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
libpng.o: /usr/include/getopt.h /usr/include/pngconf.h /usr/include/stdio.h
libpng.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
libpng.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
libpng.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h
libpng.o: /usr/include/string.h
main.o: /usr/include/GL/glut.h /usr/include/GL/freeglut_std.h
main.o: /usr/include/GL/gl.h /usr/include/GL/glext.h /usr/include/GL/glu.h
main.o: libpng.hpp
