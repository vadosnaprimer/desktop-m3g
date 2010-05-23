SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = a.out
CXX = g++
CXXFLAGS = -Wall -g -Wno-deprecated  -I../../src
LD = g++
LDFLAGS = -L../../src
LIBS = -lm3g  -lglut -lGL -lpng -lz


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
main.o: ../../src/Loader.hpp ../../src/Exception.hpp
main.o: ../../src/RenderState.hpp /usr/include/GL/glut.h
main.o: /usr/include/GL/freeglut_std.h /usr/include/GL/gl.h
main.o: /usr/include/GL/glext.h /usr/include/GL/glu.h
