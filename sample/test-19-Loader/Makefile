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

main.o: ../../src/m3g.hpp ../../src/m3gdef.hpp ../../src/Graphics3D.hpp
main.o: ../../src/Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
main.o: /usr/include/GL/gl.h ../../src/m3ginternal.hpp
main.o: ../../src/AnimationController.hpp ../../src/AnimationTrack.hpp
main.o: ../../src/Appearance.hpp ../../src/Background.hpp
main.o: ../../src/CompositingMode.hpp ../../src/Fog.hpp ../../src/Image2D.hpp
main.o: ../../src/IndexBuffer.hpp ../../src/TriangleStripArray.hpp
main.o: /usr/include/unittest++/UnitTest++.h /usr/include/unittest++/Config.h
main.o: /usr/include/unittest++/Test.h /usr/include/unittest++/TestDetails.h
main.o: /usr/include/unittest++/TestList.h
main.o: /usr/include/unittest++/TestSuite.h
main.o: /usr/include/unittest++/TestResults.h
main.o: /usr/include/unittest++/TestMacros.h
main.o: /usr/include/unittest++/Posix/SignalTranslator.h
main.o: /usr/include/setjmp.h /usr/include/features.h
main.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
main.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
main.o: /usr/include/bits/setjmp.h /usr/include/bits/sigset.h
main.o: /usr/include/signal.h /usr/include/bits/types.h
main.o: /usr/include/bits/typesizes.h /usr/include/bits/signum.h
main.o: /usr/include/time.h /usr/include/bits/siginfo.h
main.o: /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h
main.o: /usr/include/bits/sigstack.h /usr/include/bits/pthreadtypes.h
main.o: /usr/include/bits/sigthread.h /usr/include/unittest++/CheckMacros.h
main.o: /usr/include/unittest++/Checks.h
main.o: /usr/include/unittest++/MemoryOutStream.h
main.o: /usr/include/unittest++/AssertException.h
main.o: /usr/include/unittest++/TestRunner.h
main.o: /usr/include/unittest++/TimeConstraint.h
main.o: /usr/include/unittest++/TimeHelpers.h
main.o: /usr/include/unittest++/Posix/TimeHelpers.h /usr/include/sys/time.h
main.o: /usr/include/bits/time.h /usr/include/sys/select.h
main.o: /usr/include/bits/select.h ../../src/KeyframeSequence.hpp
main.o: ../../src/Keyframe.hpp ../../src/Material.hpp
main.o: ../../src/PolygonMode.hpp ../../src/Transformable.hpp
main.o: ../../src/Quaternion.hpp ../../src/Transform.hpp ../../src/Matrix.hpp
main.o: ../../src/Node.hpp ../../src/Camera.hpp ../../src/Group.hpp
main.o: ../../src/World.hpp ../../src/Light.hpp ../../src/Mesh.hpp
main.o: ../../src/MorphingMesh.hpp ../../src/SkinnedMesh.hpp
main.o: ../../src/Sprite3D.hpp ../../src/Texture2D.hpp
main.o: ../../src/VertexArray.hpp ../../src/VertexBuffer.hpp
main.o: ../../src/RayIntersection.hpp ../../src/Loader.hpp
main.o: ../../src/Exception.hpp /usr/include/GL/glut.h
main.o: /usr/include/GL/freeglut_std.h
