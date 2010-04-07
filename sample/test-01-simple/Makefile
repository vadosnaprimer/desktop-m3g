SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = a.out
CXX = g++
CXXFLAGS = -Wall -g  -std=c++0x -I/usr/local/include/m3g
LD = g++
LDFLAGS = -L/usr/local/lib
LIBS = -lm3g  -lglut -lGLEW -lGL


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
main.o: /usr/local/include/m3g/Keyframe.hpp
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
main.o: /usr/include/GL/freeglut_std.h
