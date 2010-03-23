SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = libm3gparser.so
CXX = g++
CXXFLAGS = -Wall -g -shared -fPIC -std=c++0x -Wno-deprecated
LD = g++
LDFLAGS = -shared


all: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $(TARGET)
	@echo done.

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c

depend:
	makedepend -- $(CXXFLAGS) -- $(SRCS)

clean:
	rm -rf *.o *.so *.a *~ 
	@echo done.

# DO NOT DELETE

M3GParser.o: /usr/include/string.h /usr/include/features.h
M3GParser.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
M3GParser.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
M3GParser.o: M3GParser.hpp /usr/include/stdint.h /usr/include/bits/wchar.h
M3GParser.o: Section.hpp parse-AnimationController.hpp
M3GParser.o: ../AnimationController.hpp ../Object3D.hpp
M3GParser.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
M3GParser.o: /usr/include/GL/gl.h ../m3gdef.hpp ../m3ginternal.hpp
M3GParser.o: parse-AnimationTrack.hpp ../AnimationTrack.hpp
M3GParser.o: parse-Appearance.hpp ../Appearance.hpp parse-Background.hpp
M3GParser.o: ../Background.hpp parse-Camera.hpp ../Camera.hpp ../Node.hpp
M3GParser.o: ../Transformable.hpp ../Quaternion.hpp ../Transform.hpp
M3GParser.o: ../Matrix.hpp parse-Group.hpp ../Group.hpp parse-Image2D.hpp
M3GParser.o: ../Image2D.hpp parse-KeyframeSequence.hpp
M3GParser.o: ../KeyframeSequence.hpp ../Keyframe.hpp parse-Light.hpp
M3GParser.o: ../Light.hpp parse-Material.hpp ../Material.hpp parse-Mesh.hpp
M3GParser.o: ../Mesh.hpp parse-PolygonMode.hpp ../PolygonMode.hpp
M3GParser.o: parse-Texture2D.hpp ../Texture2D.hpp
M3GParser.o: parse-TriangleStripArray.hpp ../TriangleStripArray.hpp
M3GParser.o: /usr/include/unittest++/UnitTest++.h
M3GParser.o: /usr/include/unittest++/Config.h /usr/include/unittest++/Test.h
M3GParser.o: /usr/include/unittest++/TestDetails.h
M3GParser.o: /usr/include/unittest++/TestList.h
M3GParser.o: /usr/include/unittest++/TestSuite.h
M3GParser.o: /usr/include/unittest++/TestResults.h
M3GParser.o: /usr/include/unittest++/TestMacros.h
M3GParser.o: /usr/include/unittest++/Posix/SignalTranslator.h
M3GParser.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h
M3GParser.o: /usr/include/bits/sigset.h /usr/include/signal.h
M3GParser.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
M3GParser.o: /usr/include/bits/signum.h /usr/include/time.h
M3GParser.o: /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h
M3GParser.o: /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h
M3GParser.o: /usr/include/bits/pthreadtypes.h /usr/include/bits/sigthread.h
M3GParser.o: /usr/include/unittest++/CheckMacros.h
M3GParser.o: /usr/include/unittest++/Checks.h
M3GParser.o: /usr/include/unittest++/MemoryOutStream.h
M3GParser.o: /usr/include/unittest++/AssertException.h
M3GParser.o: /usr/include/unittest++/TestRunner.h
M3GParser.o: /usr/include/unittest++/TimeConstraint.h
M3GParser.o: /usr/include/unittest++/TimeHelpers.h
M3GParser.o: /usr/include/unittest++/Posix/TimeHelpers.h
M3GParser.o: /usr/include/sys/time.h /usr/include/bits/time.h
M3GParser.o: /usr/include/sys/select.h /usr/include/bits/select.h
M3GParser.o: ../IndexBuffer.hpp parse-World.hpp ../World.hpp ../Group.hpp
M3GParser.o: parse-VertexArray.hpp ../VertexArray.hpp parse-VertexBuffer.hpp
M3GParser.o: ../VertexBuffer.hpp ../m3gdef.hpp ../m3ginternal.hpp
Section.o: adler32.hpp /usr/include/stdint.h /usr/include/features.h
Section.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
Section.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
Section.o: /usr/include/bits/wchar.h Section.hpp /usr/include/stdlib.h
Section.o: /usr/include/sys/types.h /usr/include/bits/types.h
Section.o: /usr/include/bits/typesizes.h /usr/include/time.h
Section.o: /usr/include/endian.h /usr/include/bits/endian.h
Section.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
Section.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
Section.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
Section.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
parse-AnimationController.o: ../AnimationController.hpp ../Object3D.hpp
parse-AnimationController.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-AnimationController.o: /usr/include/GL/gl.h ../m3gdef.hpp
parse-AnimationController.o: ../m3ginternal.hpp parse-Object3D.hpp
parse-AnimationController.o: ../Object3D.hpp
parse-AnimationTracker.o: ../AnimationController.hpp ../Object3D.hpp
parse-AnimationTracker.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-AnimationTracker.o: /usr/include/GL/gl.h ../m3gdef.hpp
parse-AnimationTracker.o: ../m3ginternal.hpp ../AnimationTrack.hpp
parse-AnimationTracker.o: ../KeyframeSequence.hpp ../Keyframe.hpp
parse-AnimationTracker.o: parse-Object3D.hpp ../Object3D.hpp
parse-Appearance.o: ../AnimationTrack.hpp ../Object3D.hpp
parse-Appearance.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-Appearance.o: /usr/include/GL/gl.h ../m3gdef.hpp ../m3ginternal.hpp
parse-Appearance.o: ../Appearance.hpp ../Fog.hpp ../KeyframeSequence.hpp
parse-Appearance.o: ../Keyframe.hpp ../AnimationController.hpp
parse-Appearance.o: ../CompositingMode.hpp ../PolygonMode.hpp
parse-Appearance.o: ../Texture2D.hpp ../Transformable.hpp ../Quaternion.hpp
parse-Appearance.o: ../Transform.hpp ../Matrix.hpp ../Material.hpp
parse-Appearance.o: parse-Object3D.hpp ../Object3D.hpp
parse-Background.o: ../Background.hpp ../Object3D.hpp /usr/include/GL/glew.h
parse-Background.o: /usr/include/GL/glu.h /usr/include/GL/gl.h ../m3gdef.hpp
parse-Background.o: ../m3ginternal.hpp ../Image2D.hpp parse-Background.hpp
parse-Background.o: parse-Object3D.hpp ../Object3D.hpp
parse-Camera.o: ../Camera.hpp ../Node.hpp ../Transformable.hpp
parse-Camera.o: ../Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-Camera.o: /usr/include/GL/gl.h ../m3gdef.hpp ../m3ginternal.hpp
parse-Camera.o: ../Quaternion.hpp ../Transform.hpp ../Matrix.hpp
parse-Camera.o: ../Transform.hpp parse-Node.hpp ../Node.hpp
parse-CompositingMode.o: ../CompositingMode.hpp ../Object3D.hpp
parse-CompositingMode.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-CompositingMode.o: /usr/include/GL/gl.h ../m3gdef.hpp
parse-CompositingMode.o: ../m3ginternal.hpp
parse-Fog.o: ../Fog.hpp ../Object3D.hpp /usr/include/GL/glew.h
parse-Fog.o: /usr/include/GL/glu.h /usr/include/GL/gl.h ../m3gdef.hpp
parse-Fog.o: ../m3ginternal.hpp
parse-Group.o: ../Group.hpp ../Node.hpp ../Transformable.hpp ../Object3D.hpp
parse-Group.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-Group.o: /usr/include/GL/gl.h ../m3gdef.hpp ../m3ginternal.hpp
parse-Group.o: ../Quaternion.hpp ../Transform.hpp ../Matrix.hpp
parse-Group.o: parse-Node.hpp ../Node.hpp
parse-Image2D.o: ../Image2D.hpp ../Object3D.hpp /usr/include/GL/glew.h
parse-Image2D.o: /usr/include/GL/glu.h /usr/include/GL/gl.h ../m3gdef.hpp
parse-Image2D.o: ../m3ginternal.hpp parse-Object3D.hpp ../Object3D.hpp
parse-IndexBuffer.o: ../IndexBuffer.hpp /usr/include/GL/glew.h
parse-IndexBuffer.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
parse-IndexBuffer.o: ../Object3D.hpp ../m3gdef.hpp ../m3ginternal.hpp
parse-IndexBuffer.o: parse-Object3D.hpp ../Object3D.hpp
parse-KeyframeSequence.o: ../KeyframeSequence.hpp ../Object3D.hpp
parse-KeyframeSequence.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-KeyframeSequence.o: /usr/include/GL/gl.h ../m3gdef.hpp
parse-KeyframeSequence.o: ../m3ginternal.hpp ../Keyframe.hpp
parse-KeyframeSequence.o: parse-Object3D.hpp ../Object3D.hpp
parse-Light.o: ../Light.hpp ../Node.hpp ../Transformable.hpp ../Object3D.hpp
parse-Light.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-Light.o: /usr/include/GL/gl.h ../m3gdef.hpp ../m3ginternal.hpp
parse-Light.o: ../Quaternion.hpp ../Transform.hpp ../Matrix.hpp
parse-Light.o: parse-Node.hpp ../Node.hpp
parse-Material.o: ../Material.hpp ../Object3D.hpp /usr/include/GL/glew.h
parse-Material.o: /usr/include/GL/glu.h /usr/include/GL/gl.h ../m3gdef.hpp
parse-Material.o: ../m3ginternal.hpp parse-Object3D.hpp ../Object3D.hpp
parse-Mesh.o: ../VertexBuffer.hpp /usr/include/GL/glew.h
parse-Mesh.o: /usr/include/GL/glu.h /usr/include/GL/gl.h ../Object3D.hpp
parse-Mesh.o: ../m3gdef.hpp ../m3ginternal.hpp ../Mesh.hpp ../Node.hpp
parse-Mesh.o: ../Transformable.hpp ../Quaternion.hpp ../Transform.hpp
parse-Mesh.o: ../Matrix.hpp ../IndexBuffer.hpp ../Appearance.hpp
parse-Mesh.o: parse-Node.hpp ../Node.hpp
parse-MorphingMesh.o: ../MorphingMesh.hpp ../Mesh.hpp ../Node.hpp
parse-MorphingMesh.o: ../Transformable.hpp ../Object3D.hpp
parse-MorphingMesh.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-MorphingMesh.o: /usr/include/GL/gl.h ../m3gdef.hpp ../m3ginternal.hpp
parse-MorphingMesh.o: ../Quaternion.hpp ../Transform.hpp ../Matrix.hpp
parse-Node.o: ../Node.hpp parse-Transformable.hpp ../Transformable.hpp
parse-Node.o: ../Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-Node.o: /usr/include/GL/gl.h ../m3gdef.hpp ../m3ginternal.hpp
parse-Node.o: ../Quaternion.hpp ../Transform.hpp ../Matrix.hpp parse-Node.hpp
parse-Object3D.o: parse-Object3D.hpp ../Object3D.hpp ../AnimationTrack.hpp
parse-Object3D.o: ../Object3D.hpp /usr/include/GL/glew.h
parse-Object3D.o: /usr/include/GL/glu.h /usr/include/GL/gl.h ../m3gdef.hpp
parse-Object3D.o: ../m3ginternal.hpp
parse-PolygonMode.o: ../PolygonMode.hpp ../Object3D.hpp
parse-PolygonMode.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-PolygonMode.o: /usr/include/GL/gl.h ../m3gdef.hpp ../m3ginternal.hpp
parse-PolygonMode.o: parse-Object3D.hpp ../Object3D.hpp
parse-RayIntersection.o: ../Object3D.hpp ../RayIntersection.hpp
parse-SkinnedMesh.o: ../SkinnedMesh.hpp ../Mesh.hpp ../Node.hpp
parse-SkinnedMesh.o: ../Transformable.hpp ../Object3D.hpp
parse-SkinnedMesh.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-SkinnedMesh.o: /usr/include/GL/gl.h ../m3gdef.hpp ../m3ginternal.hpp
parse-SkinnedMesh.o: ../Quaternion.hpp ../Transform.hpp ../Matrix.hpp
parse-Sprite.o: ../Sprite3D.hpp ../Node.hpp ../Transformable.hpp
parse-Sprite.o: ../Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-Sprite.o: /usr/include/GL/gl.h ../m3gdef.hpp ../m3ginternal.hpp
parse-Sprite.o: ../Quaternion.hpp ../Transform.hpp ../Matrix.hpp
parse-Texture2D.o: ../Texture2D.hpp /usr/include/GL/glew.h
parse-Texture2D.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
parse-Texture2D.o: ../Transformable.hpp ../Object3D.hpp ../m3gdef.hpp
parse-Texture2D.o: ../m3ginternal.hpp ../Quaternion.hpp ../Transform.hpp
parse-Texture2D.o: ../Matrix.hpp ../Image2D.hpp parse-Transformable.hpp
parse-Texture2D.o: ../Transformable.hpp
parse-Transform.o: ../Object3D.hpp ../Transform.hpp
parse-Transformable.o: parse-Object3D.hpp ../Object3D.hpp
parse-Transformable.o: parse-Transformable.hpp ../Transformable.hpp
parse-Transformable.o: ../Object3D.hpp /usr/include/GL/glew.h
parse-Transformable.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
parse-Transformable.o: ../m3gdef.hpp ../m3ginternal.hpp ../Quaternion.hpp
parse-Transformable.o: ../Transform.hpp ../Matrix.hpp
parse-TriangleStripArray.o: ../TriangleStripArray.hpp
parse-TriangleStripArray.o: /usr/include/unittest++/UnitTest++.h
parse-TriangleStripArray.o: /usr/include/unittest++/Config.h
parse-TriangleStripArray.o: /usr/include/unittest++/Test.h
parse-TriangleStripArray.o: /usr/include/unittest++/TestDetails.h
parse-TriangleStripArray.o: /usr/include/unittest++/TestList.h
parse-TriangleStripArray.o: /usr/include/unittest++/TestSuite.h
parse-TriangleStripArray.o: /usr/include/unittest++/TestResults.h
parse-TriangleStripArray.o: /usr/include/unittest++/TestMacros.h
parse-TriangleStripArray.o: /usr/include/unittest++/Posix/SignalTranslator.h
parse-TriangleStripArray.o: /usr/include/setjmp.h /usr/include/features.h
parse-TriangleStripArray.o: /usr/include/sys/cdefs.h
parse-TriangleStripArray.o: /usr/include/bits/wordsize.h
parse-TriangleStripArray.o: /usr/include/gnu/stubs.h
parse-TriangleStripArray.o: /usr/include/gnu/stubs-64.h
parse-TriangleStripArray.o: /usr/include/bits/setjmp.h
parse-TriangleStripArray.o: /usr/include/bits/sigset.h /usr/include/signal.h
parse-TriangleStripArray.o: /usr/include/bits/types.h
parse-TriangleStripArray.o: /usr/include/bits/typesizes.h
parse-TriangleStripArray.o: /usr/include/bits/signum.h /usr/include/time.h
parse-TriangleStripArray.o: /usr/include/bits/siginfo.h
parse-TriangleStripArray.o: /usr/include/bits/sigaction.h
parse-TriangleStripArray.o: /usr/include/bits/sigcontext.h
parse-TriangleStripArray.o: /usr/include/bits/sigstack.h
parse-TriangleStripArray.o: /usr/include/bits/pthreadtypes.h
parse-TriangleStripArray.o: /usr/include/bits/sigthread.h
parse-TriangleStripArray.o: /usr/include/unittest++/CheckMacros.h
parse-TriangleStripArray.o: /usr/include/unittest++/Checks.h
parse-TriangleStripArray.o: /usr/include/unittest++/MemoryOutStream.h
parse-TriangleStripArray.o: /usr/include/unittest++/AssertException.h
parse-TriangleStripArray.o: /usr/include/unittest++/TestRunner.h
parse-TriangleStripArray.o: /usr/include/unittest++/TimeConstraint.h
parse-TriangleStripArray.o: /usr/include/unittest++/TimeHelpers.h
parse-TriangleStripArray.o: /usr/include/unittest++/Posix/TimeHelpers.h
parse-TriangleStripArray.o: /usr/include/sys/time.h /usr/include/bits/time.h
parse-TriangleStripArray.o: /usr/include/sys/select.h
parse-TriangleStripArray.o: /usr/include/bits/select.h ../IndexBuffer.hpp
parse-TriangleStripArray.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-TriangleStripArray.o: /usr/include/GL/gl.h ../Object3D.hpp
parse-TriangleStripArray.o: ../m3gdef.hpp ../m3ginternal.hpp
parse-TriangleStripArray.o: parse-IndexBuffer.hpp ../IndexBuffer.hpp
parse-VertexArray.o: ../VertexArray.hpp /usr/include/GL/glew.h
parse-VertexArray.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
parse-VertexArray.o: ../Object3D.hpp ../m3gdef.hpp ../m3ginternal.hpp
parse-VertexArray.o: parse-Object3D.hpp ../Object3D.hpp
parse-VertexBuffer.o: ../VertexBuffer.hpp /usr/include/GL/glew.h
parse-VertexBuffer.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
parse-VertexBuffer.o: ../Object3D.hpp ../m3gdef.hpp ../m3ginternal.hpp
parse-VertexBuffer.o: ../VertexArray.hpp parse-Object3D.hpp ../Object3D.hpp
parse-World.o: ../World.hpp ../Group.hpp ../Group.hpp ../Node.hpp
parse-World.o: ../Transformable.hpp ../Object3D.hpp /usr/include/GL/glew.h
parse-World.o: /usr/include/GL/glu.h /usr/include/GL/gl.h ../m3gdef.hpp
parse-World.o: ../m3ginternal.hpp ../Quaternion.hpp ../Transform.hpp
parse-World.o: ../Matrix.hpp ../Camera.hpp ../Background.hpp parse-Group.hpp
