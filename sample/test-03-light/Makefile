SRCS     = $(wildcard *.cpp)
OBJS     = $(SRCS:.cpp=.o)
TARGET   = a.out
CXX      = g++
CXXFLAGS = -Wall -g -Wno-deprecated -I../../bin/include
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
	rm -rf *.o *.so *.a *.ppm *~ $(TARGET)
	@echo done.


# DO NOT DELETE

main.o: ../../bin/include/m3g/m3g.hpp ../../bin/include/m3g/m3gdef.hpp
main.o: ../../bin/include/m3g/Graphics3D.hpp ../../bin/include/m3g/Object.hpp
main.o: ../../bin/include/m3g/Object3D.hpp
main.o: ../../bin/include/m3g/m3ginternal.hpp
main.o: ../../bin/include/m3g/AnimationController.hpp
main.o: ../../bin/include/m3g/AnimationTrack.hpp
main.o: ../../bin/include/m3g/Appearance.hpp
main.o: ../../bin/include/m3g/Background.hpp
main.o: ../../bin/include/m3g/CompositingMode.hpp
main.o: ../../bin/include/m3g/Fog.hpp ../../bin/include/m3g/Image2D.hpp
main.o: ../../bin/include/m3g/IndexBuffer.hpp
main.o: ../../bin/include/m3g/TriangleStripArray.hpp
main.o: ../../bin/include/m3g/KeyframeSequence.hpp
main.o: ../../bin/include/m3g/Keyframe.hpp ../../bin/include/m3g/Material.hpp
main.o: ../../bin/include/m3g/PolygonMode.hpp
main.o: ../../bin/include/m3g/Transformable.hpp
main.o: ../../bin/include/m3g/Quaternion.hpp
main.o: ../../bin/include/m3g/Transform.hpp ../../bin/include/m3g/Matrix.hpp
main.o: ../../bin/include/m3g/Node.hpp ../../bin/include/m3g/Camera.hpp
main.o: ../../bin/include/m3g/Group.hpp ../../bin/include/m3g/World.hpp
main.o: ../../bin/include/m3g/Light.hpp ../../bin/include/m3g/Mesh.hpp
main.o: ../../bin/include/m3g/MorphingMesh.hpp
main.o: ../../bin/include/m3g/SkinnedMesh.hpp
main.o: ../../bin/include/m3g/BoneWeight.hpp
main.o: ../../bin/include/m3g/Sprite3D.hpp
main.o: ../../bin/include/m3g/Texture2D.hpp
main.o: ../../bin/include/m3g/VertexArray.hpp
main.o: ../../bin/include/m3g/VertexBuffer.hpp
main.o: ../../bin/include/m3g/RayIntersection.hpp
main.o: ../../bin/include/m3g/Vector.hpp ../../bin/include/m3g/Loader.hpp
main.o: ../../bin/include/m3g/M3GReader.hpp
main.o: ../../bin/include/m3g/InMemoryStream.hpp
main.o: ../../bin/include/m3g/M3GStruct.hpp
main.o: ../../bin/include/m3g/Exception.hpp
main.o: ../../bin/include/m3g/RenderState.hpp /usr/include/GL/glut.h
main.o: /usr/include/GL/freeglut_std.h /usr/include/GL/gl.h
main.o: /usr/include/GL/glext.h /usr/include/inttypes.h
main.o: /usr/include/features.h /usr/include/sys/cdefs.h
main.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
main.o: /usr/include/gnu/stubs-32.h /usr/include/stdint.h
main.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h /usr/include/stdlib.h
main.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
main.o: /usr/include/endian.h /usr/include/bits/endian.h
main.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
main.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
main.o: /usr/include/time.h /usr/include/sys/select.h
main.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
main.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
main.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h data.hpp
