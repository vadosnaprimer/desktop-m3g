SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = libm3g.so
CXX = g++
CXXFLAGS = -Wall -g -shared -fPIC
LD = g++
LDFLAGS = -shared
LIBS = 


all: $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $(TARGET)
	@echo done.

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c

install: $(TARGET)
	cp $(TARGET) /usr/local/lib
#	mkdir /usr/local/include/m3g
	cp *.hpp /usr/local/include/m3g

depend:
	makedepend -- $(CXXFLAGS) -- $(SRCS)

clean:
	rm -rf *.o *.so *.a *~ 
	@echo done.


# DO NOT DELETE

AnimationController.o: AnimationController.hpp Object3D.hpp
AnimationController.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
AnimationController.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp
AnimationTrack.o: AnimationTrack.hpp Object3D.hpp /usr/include/GL/glew.h
AnimationTrack.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
AnimationTrack.o: m3ginternal.hpp KeyframeSequence.hpp Keyframe.hpp
AnimationTrack.o: AnimationController.hpp Exception.hpp
Appearance.o: Appearance.hpp Object3D.hpp /usr/include/GL/glew.h
Appearance.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Appearance.o: m3ginternal.hpp CompositingMode.hpp Fog.hpp Material.hpp
Appearance.o: PolygonMode.hpp Texture2D.hpp Transformable.hpp Quaternion.hpp
Appearance.o: Transform.hpp Matrix.hpp Exception.hpp
Background.o: Background.hpp Object3D.hpp /usr/include/GL/glew.h
Background.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Background.o: m3ginternal.hpp Image2D.hpp Exception.hpp AnimationTrack.hpp
Background.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Bone.o: Bone.hpp Matrix.hpp Group.hpp Node.hpp Transformable.hpp Object3D.hpp
Bone.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Bone.o: m3gdef.hpp m3ginternal.hpp Quaternion.hpp Transform.hpp Exception.hpp
Camera.o: Camera.hpp Node.hpp Transformable.hpp Object3D.hpp
Camera.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Camera.o: m3gdef.hpp m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Camera.o: Vector.hpp AnimationTrack.hpp AnimationController.hpp
Camera.o: KeyframeSequence.hpp Keyframe.hpp Exception.hpp
CompositingMode.o: CompositingMode.hpp Object3D.hpp /usr/include/GL/glew.h
CompositingMode.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
CompositingMode.o: m3ginternal.hpp Exception.hpp
Exception.o: Exception.hpp
Fog.o: Fog.hpp Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
Fog.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp Exception.hpp
Fog.o: AnimationTrack.hpp AnimationController.hpp KeyframeSequence.hpp
Fog.o: Keyframe.hpp
Graphics3D.o: Graphics3D.hpp World.hpp Group.hpp Node.hpp Transformable.hpp
Graphics3D.o: Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
Graphics3D.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp Quaternion.hpp
Graphics3D.o: Transform.hpp Matrix.hpp Camera.hpp Graphics.hpp Light.hpp
Graphics3D.o: Exception.hpp Property.hpp
Group.o: Group.hpp Node.hpp Transformable.hpp Object3D.hpp
Group.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Group.o: m3gdef.hpp m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Group.o: RayIntersection.hpp Sprite3D.hpp Exception.hpp
Image2D.o: Image2D.hpp Object3D.hpp /usr/include/GL/glew.h
Image2D.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Image2D.o: m3ginternal.hpp Exception.hpp
IndexBuffer.o: IndexBuffer.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
IndexBuffer.o: /usr/include/GL/gl.h Object3D.hpp m3gdef.hpp m3ginternal.hpp
IndexBuffer.o: Exception.hpp
Keyframe.o: Keyframe.hpp Quaternion.hpp Exception.hpp
KeyframeSequence.o: KeyframeSequence.hpp Object3D.hpp /usr/include/GL/glew.h
KeyframeSequence.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
KeyframeSequence.o: m3ginternal.hpp Keyframe.hpp Exception.hpp Quaternion.hpp
Light.o: Light.hpp Node.hpp Transformable.hpp Object3D.hpp
Light.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Light.o: m3gdef.hpp m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Light.o: Exception.hpp AnimationTrack.hpp AnimationController.hpp
Light.o: KeyframeSequence.hpp Keyframe.hpp
Loader.o: m3g.hpp m3gdef.hpp Graphics3D.hpp Object3D.hpp
Loader.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Loader.o: m3ginternal.hpp AnimationController.hpp AnimationTrack.hpp
Loader.o: Appearance.hpp Background.hpp CompositingMode.hpp Fog.hpp
Loader.o: Image2D.hpp IndexBuffer.hpp TriangleStripArray.hpp
Loader.o: /usr/include/unittest++/UnitTest++.h
Loader.o: /usr/include/unittest++/Config.h /usr/include/unittest++/Test.h
Loader.o: /usr/include/unittest++/TestDetails.h
Loader.o: /usr/include/unittest++/TestList.h
Loader.o: /usr/include/unittest++/TestSuite.h
Loader.o: /usr/include/unittest++/TestResults.h
Loader.o: /usr/include/unittest++/TestMacros.h
Loader.o: /usr/include/unittest++/Posix/SignalTranslator.h
Loader.o: /usr/include/setjmp.h /usr/include/features.h
Loader.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
Loader.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
Loader.o: /usr/include/bits/setjmp.h /usr/include/bits/sigset.h
Loader.o: /usr/include/signal.h /usr/include/bits/types.h
Loader.o: /usr/include/bits/typesizes.h /usr/include/bits/signum.h
Loader.o: /usr/include/time.h /usr/include/bits/siginfo.h
Loader.o: /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h
Loader.o: /usr/include/bits/sigstack.h /usr/include/bits/pthreadtypes.h
Loader.o: /usr/include/bits/sigthread.h /usr/include/unittest++/CheckMacros.h
Loader.o: /usr/include/unittest++/Checks.h
Loader.o: /usr/include/unittest++/MemoryOutStream.h
Loader.o: /usr/include/unittest++/AssertException.h
Loader.o: /usr/include/unittest++/TestRunner.h
Loader.o: /usr/include/unittest++/TimeConstraint.h
Loader.o: /usr/include/unittest++/TimeHelpers.h
Loader.o: /usr/include/unittest++/Posix/TimeHelpers.h /usr/include/sys/time.h
Loader.o: /usr/include/bits/time.h /usr/include/sys/select.h
Loader.o: /usr/include/bits/select.h KeyframeSequence.hpp Keyframe.hpp
Loader.o: Material.hpp PolygonMode.hpp Transformable.hpp Quaternion.hpp
Loader.o: Transform.hpp Matrix.hpp Node.hpp Camera.hpp Group.hpp World.hpp
Loader.o: Light.hpp Mesh.hpp MorphingMesh.hpp SkinnedMesh.hpp Sprite3D.hpp
Loader.o: Texture2D.hpp VertexArray.hpp VertexBuffer.hpp RayIntersection.hpp
Loader.o: Loader.hpp Exception.hpp /usr/include/stdlib.h
Loader.o: /usr/include/sys/types.h /usr/include/endian.h
Loader.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
Loader.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
Material.o: Material.hpp Object3D.hpp /usr/include/GL/glew.h
Material.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Material.o: m3ginternal.hpp Exception.hpp AnimationTrack.hpp
Material.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Matrix.o: Matrix.hpp Vector.hpp Exception.hpp
Mesh.o: Mesh.hpp Node.hpp Transformable.hpp Object3D.hpp
Mesh.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Mesh.o: m3gdef.hpp m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Mesh.o: VertexBuffer.hpp VertexArray.hpp IndexBuffer.hpp Appearance.hpp
Mesh.o: Exception.hpp
MorphingMesh.o: MorphingMesh.hpp Mesh.hpp Node.hpp Transformable.hpp
MorphingMesh.o: Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
MorphingMesh.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp
MorphingMesh.o: Quaternion.hpp Transform.hpp Matrix.hpp VertexBuffer.hpp
MorphingMesh.o: IndexBuffer.hpp Appearance.hpp
Node.o: Node.hpp Transformable.hpp Object3D.hpp /usr/include/GL/glew.h
Node.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp
Node.o: Quaternion.hpp Transform.hpp Matrix.hpp Exception.hpp
Node.o: AnimationTrack.hpp AnimationController.hpp KeyframeSequence.hpp
Node.o: Keyframe.hpp
Object3D.o: Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
Object3D.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp
Object3D.o: AnimationTrack.hpp Exception.hpp
PolygonMode.o: PolygonMode.hpp Object3D.hpp /usr/include/GL/glew.h
PolygonMode.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
PolygonMode.o: m3ginternal.hpp Exception.hpp
Property.o: Property.hpp Exception.hpp
Quaternion.o: Quaternion.hpp Exception.hpp m3ginternal.hpp
RayIntersection.o: RayIntersection.hpp Node.hpp Transformable.hpp
RayIntersection.o: Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
RayIntersection.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp
RayIntersection.o: Quaternion.hpp Transform.hpp Matrix.hpp
SkinnedMesh.o: SkinnedMesh.hpp Mesh.hpp Node.hpp Transformable.hpp
SkinnedMesh.o: Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
SkinnedMesh.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp Quaternion.hpp
SkinnedMesh.o: Transform.hpp Matrix.hpp VertexBuffer.hpp IndexBuffer.hpp
SkinnedMesh.o: VertexArray.hpp Bone.hpp Exception.hpp Group.hpp
Sprite3D.o: Sprite3D.hpp Node.hpp Transformable.hpp Object3D.hpp
Sprite3D.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Sprite3D.o: m3gdef.hpp m3ginternal.hpp Quaternion.hpp Transform.hpp
Sprite3D.o: Matrix.hpp Appearance.hpp Image2D.hpp Exception.hpp
Sprite3D.o: Graphics3D.hpp Vector.hpp AnimationTrack.hpp
Sprite3D.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Texture2D.o: Texture2D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
Texture2D.o: /usr/include/GL/gl.h Transformable.hpp Object3D.hpp m3gdef.hpp
Texture2D.o: m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Texture2D.o: Image2D.hpp Exception.hpp AnimationTrack.hpp
Texture2D.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Transform.o: Transform.hpp Matrix.hpp Vector.hpp Exception.hpp Quaternion.hpp
Transformable.o: Transformable.hpp Object3D.hpp /usr/include/GL/glew.h
Transformable.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Transformable.o: m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Transformable.o: Exception.hpp AnimationTrack.hpp AnimationController.hpp
Transformable.o: KeyframeSequence.hpp Keyframe.hpp
TriangleStripArray.o: TriangleStripArray.hpp
TriangleStripArray.o: /usr/include/unittest++/UnitTest++.h
TriangleStripArray.o: /usr/include/unittest++/Config.h
TriangleStripArray.o: /usr/include/unittest++/Test.h
TriangleStripArray.o: /usr/include/unittest++/TestDetails.h
TriangleStripArray.o: /usr/include/unittest++/TestList.h
TriangleStripArray.o: /usr/include/unittest++/TestSuite.h
TriangleStripArray.o: /usr/include/unittest++/TestResults.h
TriangleStripArray.o: /usr/include/unittest++/TestMacros.h
TriangleStripArray.o: /usr/include/unittest++/Posix/SignalTranslator.h
TriangleStripArray.o: /usr/include/setjmp.h /usr/include/features.h
TriangleStripArray.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
TriangleStripArray.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
TriangleStripArray.o: /usr/include/bits/setjmp.h /usr/include/bits/sigset.h
TriangleStripArray.o: /usr/include/signal.h /usr/include/bits/types.h
TriangleStripArray.o: /usr/include/bits/typesizes.h
TriangleStripArray.o: /usr/include/bits/signum.h /usr/include/time.h
TriangleStripArray.o: /usr/include/bits/siginfo.h
TriangleStripArray.o: /usr/include/bits/sigaction.h
TriangleStripArray.o: /usr/include/bits/sigcontext.h
TriangleStripArray.o: /usr/include/bits/sigstack.h
TriangleStripArray.o: /usr/include/bits/pthreadtypes.h
TriangleStripArray.o: /usr/include/bits/sigthread.h
TriangleStripArray.o: /usr/include/unittest++/CheckMacros.h
TriangleStripArray.o: /usr/include/unittest++/Checks.h
TriangleStripArray.o: /usr/include/unittest++/MemoryOutStream.h
TriangleStripArray.o: /usr/include/unittest++/AssertException.h
TriangleStripArray.o: /usr/include/unittest++/TestRunner.h
TriangleStripArray.o: /usr/include/unittest++/TimeConstraint.h
TriangleStripArray.o: /usr/include/unittest++/TimeHelpers.h
TriangleStripArray.o: /usr/include/unittest++/Posix/TimeHelpers.h
TriangleStripArray.o: /usr/include/sys/time.h /usr/include/bits/time.h
TriangleStripArray.o: /usr/include/sys/select.h /usr/include/bits/select.h
TriangleStripArray.o: IndexBuffer.hpp /usr/include/GL/glew.h
TriangleStripArray.o: /usr/include/GL/glu.h /usr/include/GL/gl.h Object3D.hpp
TriangleStripArray.o: m3gdef.hpp m3ginternal.hpp Exception.hpp
Vector.o: Vector.hpp Exception.hpp
VertexArray.o: VertexArray.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
VertexArray.o: /usr/include/GL/gl.h Object3D.hpp m3gdef.hpp m3ginternal.hpp
VertexArray.o: Exception.hpp
VertexBuffer.o: VertexBuffer.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
VertexBuffer.o: /usr/include/GL/gl.h Object3D.hpp m3gdef.hpp m3ginternal.hpp
VertexBuffer.o: VertexArray.hpp AnimationTrack.hpp AnimationController.hpp
VertexBuffer.o: KeyframeSequence.hpp Keyframe.hpp Exception.hpp
World.o: World.hpp Group.hpp Node.hpp Transformable.hpp Object3D.hpp
World.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
World.o: m3gdef.hpp m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
World.o: Camera.hpp Background.hpp Light.hpp Exception.hpp
m3ginternal.o: m3ginternal.hpp m3gdef.hpp
