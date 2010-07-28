SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = a.out
CXX = g++
CXXFLAGS = -Wall -g -Wno-deprecated -I../../src
LD = g++
LDFLAGS = -L../../src
LIBS = -lm3g -lglut -lGL -lz


all: $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $(TARGET)
	@echo done.

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c

depend:
	makedepend -- $(CXXFLAGS) -- $(SRCS)

clean:
	rm -rf *.o *.so *.a *~ 
	@echo done.


# DO NOT DELETE

main.o: ../../src/m3g.hpp ../../src/m3gdef.hpp ../../src/Graphics3D.hpp
main.o: ../../src/Object.hpp ../../src/Object3D.hpp ../../src/m3ginternal.hpp
main.o: ../../src/AnimationController.hpp ../../src/AnimationTrack.hpp
main.o: ../../src/Appearance.hpp ../../src/Background.hpp
main.o: ../../src/CompositingMode.hpp ../../src/Fog.hpp ../../src/Image2D.hpp
main.o: ../../src/IndexBuffer.hpp ../../src/TriangleStripArray.hpp
main.o: ../../src/KeyframeSequence.hpp ../../src/Keyframe.hpp
main.o: ../../src/Material.hpp ../../src/PolygonMode.hpp
main.o: ../../src/Transformable.hpp ../../src/Quaternion.hpp
main.o: ../../src/Transform.hpp ../../src/Matrix.hpp ../../src/Node.hpp
main.o: ../../src/Camera.hpp ../../src/Group.hpp ../../src/World.hpp
main.o: ../../src/Light.hpp ../../src/Mesh.hpp ../../src/MorphingMesh.hpp
main.o: ../../src/SkinnedMesh.hpp ../../src/BoneIndex.hpp
main.o: ../../src/Sprite3D.hpp ../../src/Texture2D.hpp
main.o: ../../src/VertexArray.hpp ../../src/VertexBuffer.hpp
main.o: ../../src/RayIntersection.hpp ../../src/Vector.hpp
main.o: ../../src/Loader.hpp ../../src/M3GReader.hpp
main.o: ../../src/InMemoryStream.hpp ../../src/M3GStruct.hpp
main.o: ../../src/Exception.hpp ../../src/RenderState.hpp
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
