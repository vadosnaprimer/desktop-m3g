SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = a.out
CXX = g++
CXXFLAGS = -Wall -g -Wno-deprecated -I../../src
LD = g++
LDFLAGS = -L../../src
LIBS = -lm3g  -lglut -lGL -lz 


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

main.o: ../../src/m3g.hpp ../../src/m3g/m3gdef.hpp
main.o: ../../src/m3g/Graphics3D.hpp ../../src/m3g/m3g/Object.hpp
main.o: ../../src/m3g/Object3D.hpp ../../src/m3g/m3g/m3ginternal.hpp
main.o: ../../src/m3g/AnimationController.hpp
main.o: ../../src/m3g/AnimationTrack.hpp ../../src/m3g/Appearance.hpp
main.o: ../../src/m3g/Background.hpp ../../src/m3g/CompositingMode.hpp
main.o: ../../src/m3g/Fog.hpp ../../src/m3g/Image2D.hpp
main.o: ../../src/m3g/IndexBuffer.hpp ../../src/m3g/TriangleStripArray.hpp
main.o: ../../src/m3g/KeyframeSequence.hpp ../../src/m3g/m3g/Keyframe.hpp
main.o: ../../src/m3g/Material.hpp ../../src/m3g/PolygonMode.hpp
main.o: ../../src/m3g/Transformable.hpp ../../src/m3g/m3g/Quaternion.hpp
main.o: ../../src/m3g/m3g/Transform.hpp ../../src/m3g/m3g/m3g/Matrix.hpp
main.o: ../../src/m3g/Node.hpp ../../src/m3g/Camera.hpp
main.o: ../../src/m3g/Group.hpp ../../src/m3g/World.hpp
main.o: ../../src/m3g/Light.hpp ../../src/m3g/Mesh.hpp
main.o: ../../src/m3g/MorphingMesh.hpp ../../src/m3g/SkinnedMesh.hpp
main.o: ../../src/m3g/m3g/BoneWeight.hpp ../../src/m3g/Sprite3D.hpp
main.o: ../../src/m3g/Texture2D.hpp ../../src/m3g/VertexArray.hpp
main.o: ../../src/m3g/VertexBuffer.hpp ../../src/m3g/RayIntersection.hpp
main.o: ../../src/m3g/m3g/Vector.hpp ../../src/m3g/Loader.hpp
main.o: ../../src/m3g/m3g/M3GReader.hpp
main.o: ../../src/m3g/m3g/m3g/InMemoryStream.hpp
main.o: ../../src/m3g/m3g/m3g/M3GStruct.hpp ../../src/m3g/m3g/m3g.hpp
main.o: ../../src/m3g/Exception.hpp ../../src/m3g/RenderState.hpp
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
