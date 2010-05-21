SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = libm3g.so
CXX = g++
CXXFLAGS = -Wall -g -shared -fPIC -Wno-deprecated -fno-strict-aliasing
LD = g++
LDFLAGS = -shared -lpng
LIBS = 


all: $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $(TARGET)
	@echo done.

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c

install: $(TARGET)
	/usr/bin/install -c -m 0755 $(TARGET) /usr/lib
	mkdir -p /usr/include/m3g
	cp *.hpp /usr/include/m3g

depend:
	makedepend -- $(CXXFLAGS) -- $(SRCS)

clean:
	rm -rf *.o *.so *.a *~ 
	@echo done.


# DO NOT DELETE

AnimationController.o: AnimationController.hpp Object3D.hpp
AnimationController.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
AnimationController.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp
AnimationController.o: Object.hpp
AnimationTrack.o: AnimationTrack.hpp Object3D.hpp /usr/include/GL/glew.h
AnimationTrack.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
AnimationTrack.o: m3ginternal.hpp Object.hpp KeyframeSequence.hpp
AnimationTrack.o: Keyframe.hpp AnimationController.hpp Exception.hpp
Appearance.o: Appearance.hpp Object3D.hpp /usr/include/GL/glew.h
Appearance.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Appearance.o: m3ginternal.hpp Object.hpp CompositingMode.hpp Fog.hpp
Appearance.o: Material.hpp PolygonMode.hpp Texture2D.hpp Transformable.hpp
Appearance.o: Quaternion.hpp Transform.hpp Matrix.hpp Exception.hpp
Appearance.o: RenderState.hpp
Background.o: Background.hpp Object3D.hpp /usr/include/GL/glew.h
Background.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Background.o: m3ginternal.hpp Object.hpp Image2D.hpp Exception.hpp
Background.o: AnimationTrack.hpp AnimationController.hpp KeyframeSequence.hpp
Background.o: Keyframe.hpp RenderState.hpp
Camera.o: Camera.hpp Node.hpp Transformable.hpp Object3D.hpp
Camera.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Camera.o: m3gdef.hpp m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp
Camera.o: Matrix.hpp Vector.hpp AnimationTrack.hpp AnimationController.hpp
Camera.o: KeyframeSequence.hpp Keyframe.hpp Exception.hpp RenderState.hpp
CompositingMode.o: CompositingMode.hpp Object3D.hpp /usr/include/GL/glew.h
CompositingMode.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
CompositingMode.o: m3ginternal.hpp Object.hpp Exception.hpp RenderState.hpp
Exception.o: Exception.hpp
Fog.o: Fog.hpp Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
Fog.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp Object.hpp
Fog.o: Exception.hpp AnimationTrack.hpp AnimationController.hpp
Fog.o: KeyframeSequence.hpp Keyframe.hpp RenderState.hpp
Graphics3D.o: Graphics3D.hpp Object.hpp World.hpp Group.hpp Node.hpp
Graphics3D.o: Transformable.hpp Object3D.hpp /usr/include/GL/glew.h
Graphics3D.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Graphics3D.o: m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Graphics3D.o: Camera.hpp Graphics.hpp Light.hpp Exception.hpp RenderState.hpp
Graphics3D.o: Loader.hpp
Group.o: Group.hpp Node.hpp Transformable.hpp Object3D.hpp
Group.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Group.o: m3gdef.hpp m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp
Group.o: Matrix.hpp RayIntersection.hpp Vector.hpp Exception.hpp World.hpp
Group.o: Camera.hpp Mesh.hpp
Image2D.o: Image2D.hpp Object3D.hpp /usr/include/GL/glew.h
Image2D.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Image2D.o: m3ginternal.hpp Object.hpp Exception.hpp
IndexBuffer.o: IndexBuffer.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
IndexBuffer.o: /usr/include/GL/gl.h Object3D.hpp m3gdef.hpp m3ginternal.hpp
IndexBuffer.o: Object.hpp Exception.hpp
Intersect.o: Intersect.hpp Vector.hpp Exception.hpp m3ginternal.hpp
Keyframe.o: Keyframe.hpp Quaternion.hpp Exception.hpp
KeyframeSequence.o: KeyframeSequence.hpp Object3D.hpp /usr/include/GL/glew.h
KeyframeSequence.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
KeyframeSequence.o: m3ginternal.hpp Object.hpp Keyframe.hpp Exception.hpp
KeyframeSequence.o: Quaternion.hpp
Light.o: Light.hpp Node.hpp Transformable.hpp Object3D.hpp
Light.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Light.o: m3gdef.hpp m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp
Light.o: Matrix.hpp Exception.hpp AnimationTrack.hpp AnimationController.hpp
Light.o: KeyframeSequence.hpp Keyframe.hpp RenderState.hpp
Loader.o: /usr/include/zlib.h /usr/include/zconf.h /usr/include/zlibdefs.h
Loader.o: /usr/include/sys/types.h /usr/include/features.h
Loader.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
Loader.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
Loader.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
Loader.o: /usr/include/time.h /usr/include/endian.h
Loader.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
Loader.o: /usr/include/sys/select.h /usr/include/bits/select.h
Loader.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
Loader.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
Loader.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
Loader.o: /usr/include/bits/confname.h /usr/include/getopt.h
Loader.o: /usr/include/png.h /usr/include/pngconf.h /usr/include/stdio.h
Loader.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
Loader.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Loader.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h
Loader.o: /usr/include/string.h m3g.hpp m3gdef.hpp Graphics3D.hpp Object.hpp
Loader.o: Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
Loader.o: /usr/include/GL/gl.h m3ginternal.hpp AnimationController.hpp
Loader.o: AnimationTrack.hpp Appearance.hpp Background.hpp
Loader.o: CompositingMode.hpp Fog.hpp Image2D.hpp IndexBuffer.hpp
Loader.o: TriangleStripArray.hpp KeyframeSequence.hpp Keyframe.hpp
Loader.o: Material.hpp PolygonMode.hpp Transformable.hpp Quaternion.hpp
Loader.o: Transform.hpp Matrix.hpp Node.hpp Camera.hpp Group.hpp World.hpp
Loader.o: Light.hpp Mesh.hpp MorphingMesh.hpp SkinnedMesh.hpp BoneIndex.hpp
Loader.o: Sprite3D.hpp Texture2D.hpp VertexArray.hpp VertexBuffer.hpp
Loader.o: RayIntersection.hpp Vector.hpp Loader.hpp Exception.hpp
Loader.o: RenderState.hpp /usr/include/stdlib.h /usr/include/alloca.h
Material.o: Material.hpp Object3D.hpp /usr/include/GL/glew.h
Material.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Material.o: m3ginternal.hpp Object.hpp Exception.hpp AnimationTrack.hpp
Material.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Material.o: RenderState.hpp
Matrix.o: Matrix.hpp Vector.hpp Exception.hpp
Mesh.o: Mesh.hpp Node.hpp Transformable.hpp Object3D.hpp
Mesh.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Mesh.o: m3gdef.hpp m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp
Mesh.o: Matrix.hpp VertexBuffer.hpp VertexArray.hpp IndexBuffer.hpp
Mesh.o: Appearance.hpp Exception.hpp RayIntersection.hpp Vector.hpp
Mesh.o: RenderState.hpp Intersect.hpp
MorphingMesh.o: MorphingMesh.hpp Mesh.hpp Node.hpp Transformable.hpp
MorphingMesh.o: Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
MorphingMesh.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp Object.hpp
MorphingMesh.o: Quaternion.hpp Transform.hpp Matrix.hpp VertexBuffer.hpp
MorphingMesh.o: VertexArray.hpp IndexBuffer.hpp Appearance.hpp
MorphingMesh.o: AnimationTrack.hpp AnimationController.hpp
MorphingMesh.o: KeyframeSequence.hpp Keyframe.hpp Vector.hpp Exception.hpp
Node.o: Node.hpp Transformable.hpp Object3D.hpp /usr/include/GL/glew.h
Node.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp
Node.o: Object.hpp Quaternion.hpp Transform.hpp Matrix.hpp Exception.hpp
Node.o: AnimationTrack.hpp AnimationController.hpp KeyframeSequence.hpp
Node.o: Keyframe.hpp RenderState.hpp Vector.hpp
Object.o: Object.hpp
Object3D.o: Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
Object3D.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp Object.hpp
Object3D.o: AnimationTrack.hpp Exception.hpp
PolygonMode.o: PolygonMode.hpp Object3D.hpp /usr/include/GL/glew.h
PolygonMode.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
PolygonMode.o: m3ginternal.hpp Object.hpp Exception.hpp RenderState.hpp
Quaternion.o: Quaternion.hpp Exception.hpp m3ginternal.hpp Vector.hpp
Quaternion.o: Matrix.hpp
RayIntersection.o: RayIntersection.hpp Object.hpp Vector.hpp Exception.hpp
RayIntersection.o: VertexBuffer.hpp /usr/include/GL/glew.h
RayIntersection.o: /usr/include/GL/glu.h /usr/include/GL/gl.h Object3D.hpp
RayIntersection.o: m3gdef.hpp m3ginternal.hpp VertexArray.hpp Mesh.hpp
RayIntersection.o: Node.hpp Transformable.hpp Quaternion.hpp Transform.hpp
RayIntersection.o: Matrix.hpp Sprite3D.hpp
RenderState.o: RenderState.hpp
SkinnedMesh.o: SkinnedMesh.hpp Mesh.hpp Node.hpp Transformable.hpp
SkinnedMesh.o: Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
SkinnedMesh.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp Object.hpp
SkinnedMesh.o: Quaternion.hpp Transform.hpp Matrix.hpp BoneIndex.hpp
SkinnedMesh.o: VertexBuffer.hpp IndexBuffer.hpp VertexArray.hpp Vector.hpp
SkinnedMesh.o: Exception.hpp World.hpp Group.hpp
Sprite3D.o: Sprite3D.hpp Node.hpp Transformable.hpp Object3D.hpp
Sprite3D.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Sprite3D.o: m3gdef.hpp m3ginternal.hpp Object.hpp Quaternion.hpp
Sprite3D.o: Transform.hpp Matrix.hpp Appearance.hpp Image2D.hpp Exception.hpp
Sprite3D.o: Graphics3D.hpp Vector.hpp AnimationTrack.hpp
Sprite3D.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Sprite3D.o: RenderState.hpp
Texture2D.o: Texture2D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
Texture2D.o: /usr/include/GL/gl.h Transformable.hpp Object3D.hpp m3gdef.hpp
Texture2D.o: m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp
Texture2D.o: Matrix.hpp Image2D.hpp Exception.hpp AnimationTrack.hpp
Texture2D.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Texture2D.o: RenderState.hpp
Transform.o: Transform.hpp Matrix.hpp Object.hpp Vector.hpp Exception.hpp
Transform.o: Quaternion.hpp
Transformable.o: Transformable.hpp Object3D.hpp /usr/include/GL/glew.h
Transformable.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Transformable.o: m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp
Transformable.o: Matrix.hpp Exception.hpp AnimationTrack.hpp
Transformable.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
TriangleStripArray.o: TriangleStripArray.hpp IndexBuffer.hpp
TriangleStripArray.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
TriangleStripArray.o: /usr/include/GL/gl.h Object3D.hpp m3gdef.hpp
TriangleStripArray.o: m3ginternal.hpp Object.hpp Exception.hpp
TriangleStripArray.o: RenderState.hpp
Vector.o: Vector.hpp Exception.hpp m3ginternal.hpp
VertexArray.o: VertexArray.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
VertexArray.o: /usr/include/GL/gl.h Object3D.hpp m3gdef.hpp m3ginternal.hpp
VertexArray.o: Object.hpp Exception.hpp Vector.hpp BoneIndex.hpp Matrix.hpp
VertexBuffer.o: VertexBuffer.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
VertexBuffer.o: /usr/include/GL/gl.h Object3D.hpp m3gdef.hpp m3ginternal.hpp
VertexBuffer.o: Object.hpp VertexArray.hpp AnimationTrack.hpp
VertexBuffer.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
VertexBuffer.o: Exception.hpp RenderState.hpp
World.o: World.hpp Group.hpp Node.hpp Transformable.hpp Object3D.hpp
World.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
World.o: m3gdef.hpp m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp
World.o: Matrix.hpp Camera.hpp Background.hpp Light.hpp Exception.hpp
World.o: RenderState.hpp
m3ginternal.o: m3ginternal.hpp m3gdef.hpp
