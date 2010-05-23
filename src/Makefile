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

AnimationController.o: AnimationController.hpp Object3D.hpp m3gdef.hpp
AnimationController.o: m3ginternal.hpp Object.hpp
AnimationTrack.o: AnimationTrack.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
AnimationTrack.o: Object.hpp KeyframeSequence.hpp Keyframe.hpp
AnimationTrack.o: AnimationController.hpp Exception.hpp
Appearance.o: Appearance.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
Appearance.o: Object.hpp CompositingMode.hpp Fog.hpp Material.hpp
Appearance.o: PolygonMode.hpp Texture2D.hpp Transformable.hpp Quaternion.hpp
Appearance.o: Transform.hpp Matrix.hpp Exception.hpp RenderState.hpp
Background.o: Background.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
Background.o: Object.hpp Image2D.hpp Exception.hpp AnimationTrack.hpp
Background.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Background.o: RenderState.hpp
Camera.o: Camera.hpp Node.hpp Transformable.hpp Object3D.hpp m3gdef.hpp
Camera.o: m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Camera.o: Vector.hpp AnimationTrack.hpp AnimationController.hpp
Camera.o: KeyframeSequence.hpp Keyframe.hpp Exception.hpp RenderState.hpp
CompositingMode.o: CompositingMode.hpp Object3D.hpp m3gdef.hpp
CompositingMode.o: m3ginternal.hpp Object.hpp Exception.hpp RenderState.hpp
Exception.o: Exception.hpp
Fog.o: Fog.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp
Fog.o: Exception.hpp AnimationTrack.hpp AnimationController.hpp
Fog.o: KeyframeSequence.hpp Keyframe.hpp RenderState.hpp
Graphics3D.o: Graphics3D.hpp Object.hpp World.hpp Group.hpp Node.hpp
Graphics3D.o: Transformable.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
Graphics3D.o: Quaternion.hpp Transform.hpp Matrix.hpp Camera.hpp Graphics.hpp
Graphics3D.o: Light.hpp Exception.hpp RenderState.hpp Loader.hpp
Group.o: Group.hpp Node.hpp Transformable.hpp Object3D.hpp m3gdef.hpp
Group.o: m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Group.o: RayIntersection.hpp Vector.hpp Exception.hpp World.hpp Camera.hpp
Group.o: Mesh.hpp
Image2D.o: Image2D.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp
Image2D.o: Exception.hpp
IndexBuffer.o: IndexBuffer.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
IndexBuffer.o: Object.hpp Exception.hpp
Intersect.o: Intersect.hpp Vector.hpp Exception.hpp m3ginternal.hpp
Keyframe.o: Keyframe.hpp Quaternion.hpp Exception.hpp
KeyframeSequence.o: KeyframeSequence.hpp Object3D.hpp m3gdef.hpp
KeyframeSequence.o: m3ginternal.hpp Object.hpp Keyframe.hpp Exception.hpp
KeyframeSequence.o: Quaternion.hpp
Light.o: Light.hpp Node.hpp Transformable.hpp Object3D.hpp m3gdef.hpp
Light.o: m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Light.o: Exception.hpp AnimationTrack.hpp AnimationController.hpp
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
Loader.o: Object3D.hpp m3ginternal.hpp AnimationController.hpp
Loader.o: AnimationTrack.hpp Appearance.hpp Background.hpp
Loader.o: CompositingMode.hpp Fog.hpp Image2D.hpp IndexBuffer.hpp
Loader.o: TriangleStripArray.hpp KeyframeSequence.hpp Keyframe.hpp
Loader.o: Material.hpp PolygonMode.hpp Transformable.hpp Quaternion.hpp
Loader.o: Transform.hpp Matrix.hpp Node.hpp Camera.hpp Group.hpp World.hpp
Loader.o: Light.hpp Mesh.hpp MorphingMesh.hpp SkinnedMesh.hpp BoneIndex.hpp
Loader.o: Sprite3D.hpp Texture2D.hpp VertexArray.hpp VertexBuffer.hpp
Loader.o: RayIntersection.hpp Vector.hpp Loader.hpp Exception.hpp
Loader.o: RenderState.hpp /usr/include/stdlib.h /usr/include/alloca.h
Material.o: Material.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp
Material.o: Exception.hpp AnimationTrack.hpp AnimationController.hpp
Material.o: KeyframeSequence.hpp Keyframe.hpp RenderState.hpp
Matrix.o: Matrix.hpp Vector.hpp Exception.hpp
Mesh.o: Mesh.hpp Node.hpp Transformable.hpp Object3D.hpp m3gdef.hpp
Mesh.o: m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Mesh.o: VertexBuffer.hpp VertexArray.hpp IndexBuffer.hpp Appearance.hpp
Mesh.o: Exception.hpp RayIntersection.hpp Vector.hpp RenderState.hpp
Mesh.o: Intersect.hpp
MorphingMesh.o: MorphingMesh.hpp Mesh.hpp Node.hpp Transformable.hpp
MorphingMesh.o: Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp
MorphingMesh.o: Quaternion.hpp Transform.hpp Matrix.hpp VertexBuffer.hpp
MorphingMesh.o: VertexArray.hpp IndexBuffer.hpp Appearance.hpp
MorphingMesh.o: AnimationTrack.hpp AnimationController.hpp
MorphingMesh.o: KeyframeSequence.hpp Keyframe.hpp Vector.hpp Exception.hpp
Node.o: Node.hpp Transformable.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
Node.o: Object.hpp Quaternion.hpp Transform.hpp Matrix.hpp Exception.hpp
Node.o: AnimationTrack.hpp AnimationController.hpp KeyframeSequence.hpp
Node.o: Keyframe.hpp RenderState.hpp Vector.hpp
Object.o: Object.hpp
Object3D.o: Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp
Object3D.o: AnimationTrack.hpp Exception.hpp
PolygonMode.o: PolygonMode.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
PolygonMode.o: Object.hpp Exception.hpp RenderState.hpp
Quaternion.o: Quaternion.hpp Exception.hpp m3ginternal.hpp Vector.hpp
Quaternion.o: Matrix.hpp
RayIntersection.o: RayIntersection.hpp Object.hpp Vector.hpp Exception.hpp
RayIntersection.o: VertexBuffer.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
RayIntersection.o: VertexArray.hpp Mesh.hpp Node.hpp Transformable.hpp
RayIntersection.o: Quaternion.hpp Transform.hpp Matrix.hpp Sprite3D.hpp
RenderState.o: RenderState.hpp
SkinnedMesh.o: SkinnedMesh.hpp Mesh.hpp Node.hpp Transformable.hpp
SkinnedMesh.o: Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp
SkinnedMesh.o: Quaternion.hpp Transform.hpp Matrix.hpp BoneIndex.hpp
SkinnedMesh.o: VertexBuffer.hpp IndexBuffer.hpp VertexArray.hpp Vector.hpp
SkinnedMesh.o: Exception.hpp World.hpp Group.hpp
Sprite3D.o: Sprite3D.hpp Node.hpp Transformable.hpp Object3D.hpp m3gdef.hpp
Sprite3D.o: m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp
Sprite3D.o: Matrix.hpp Appearance.hpp Image2D.hpp Exception.hpp
Sprite3D.o: Graphics3D.hpp Vector.hpp AnimationTrack.hpp
Sprite3D.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Sprite3D.o: RenderState.hpp
Texture2D.o: Texture2D.hpp Transformable.hpp Object3D.hpp m3gdef.hpp
Texture2D.o: m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp
Texture2D.o: Matrix.hpp Image2D.hpp Exception.hpp AnimationTrack.hpp
Texture2D.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Texture2D.o: RenderState.hpp
Transform.o: Transform.hpp Matrix.hpp Object.hpp Vector.hpp Exception.hpp
Transform.o: Quaternion.hpp
Transformable.o: Transformable.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
Transformable.o: Object.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Transformable.o: Exception.hpp AnimationTrack.hpp AnimationController.hpp
Transformable.o: KeyframeSequence.hpp Keyframe.hpp
TriangleStripArray.o: TriangleStripArray.hpp IndexBuffer.hpp Object3D.hpp
TriangleStripArray.o: m3gdef.hpp m3ginternal.hpp Object.hpp Exception.hpp
TriangleStripArray.o: RenderState.hpp
Vector.o: Vector.hpp Exception.hpp m3ginternal.hpp
VertexArray.o: VertexArray.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
VertexArray.o: Object.hpp Exception.hpp Vector.hpp BoneIndex.hpp Matrix.hpp
VertexBuffer.o: VertexBuffer.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
VertexBuffer.o: Object.hpp VertexArray.hpp AnimationTrack.hpp
VertexBuffer.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
VertexBuffer.o: Exception.hpp RenderState.hpp
World.o: World.hpp Group.hpp Node.hpp Transformable.hpp Object3D.hpp
World.o: m3gdef.hpp m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp
World.o: Matrix.hpp Camera.hpp Background.hpp Light.hpp Exception.hpp
World.o: RenderState.hpp
m3ginternal.o: m3ginternal.hpp m3gdef.hpp
