SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = a.out
CXX = g++
CXXFLAGS = -Wall -g  -I../../src
LD = g++
LDFLAGS = -L../../src
LIBS = -lm3g  -lglut -lGLEW -lGL -lpng


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
main.o: /usr/local/include/m3g/m3g.hpp /usr/local/include/m3g/m3gexcept.hpp
main.o: /usr/local/include/m3g/m3gdef.hpp
main.o: /usr/local/include/m3g/Graphics3D.hpp
main.o: /usr/local/include/m3g/Object3D.hpp /usr/include/GL/glew.h
main.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
main.o: /usr/local/include/m3g/m3ginternal.hpp
main.o: /usr/local/include/m3g/AnimationController.hpp
main.o: /usr/local/include/m3g/ActiveInterval.hpp
main.o: /usr/local/include/m3g/AnimationTrack.hpp
main.o: /usr/local/include/m3g/Appearance.hpp
main.o: /usr/local/include/m3g/Background.hpp
main.o: /usr/local/include/m3g/CompositingMode.hpp
main.o: /usr/local/include/m3g/Fog.hpp /usr/local/include/m3g/Image2D.hpp
main.o: /usr/local/include/m3g/IndexBuffer.hpp
main.o: /usr/local/include/m3g/TriangleStripArray.hpp
main.o: /usr/local/include/m3g/KeyframeSequence.hpp
main.o: /usr/local/include/m3g/Material.hpp
main.o: /usr/local/include/m3g/PolygonMode.hpp
main.o: /usr/local/include/m3g/Transformable.hpp
main.o: /usr/local/include/m3g/Quaternion.hpp
main.o: /usr/local/include/m3g/Transform.hpp
main.o: /usr/local/include/m3g/Matrix.hpp /usr/local/include/m3g/Node.hpp
main.o: /usr/local/include/m3g/Camera.hpp
main.o: /usr/local/include/m3g/Projection.hpp
main.o: /usr/local/include/m3g/Group.hpp /usr/local/include/m3g/World.hpp
main.o: /usr/local/include/m3g/Light.hpp /usr/local/include/m3g/Mesh.hpp
main.o: /usr/local/include/m3g/MorphingMesh.hpp
main.o: /usr/local/include/m3g/SkinnedMesh.hpp
main.o: /usr/local/include/m3g/Sprite3D.hpp
main.o: /usr/local/include/m3g/Texture2D.hpp
main.o: /usr/local/include/m3g/TextureCoord2D.hpp
main.o: /usr/local/include/m3g/VertexArray.hpp
main.o: /usr/local/include/m3g/VertexBuffer.hpp
main.o: /usr/local/include/m3g/RayIntersection.hpp /usr/include/GL/glut.h
main.o: /usr/include/GL/freeglut_std.h libpng.hpp data.hpp
