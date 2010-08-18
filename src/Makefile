SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = libm3g.so
CXX = g++
CXXFLAGS = -Wall -g -shared -fPIC -fno-strict-aliasing
LD = g++
LDFLAGS = -shared -L. -lGL -lGLU -lpng -ljpeg -Wl,-whole-archive -lM3GReaderWriter -Wl,-no-whole-archive
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
	rm -rf *.o *.so *~ 
	@echo done.


# DO NOT DELETE

AnimationController.o: AnimationController.hpp Object3D.hpp m3gdef.hpp
AnimationController.o: m3ginternal.hpp Object.hpp Exception.hpp
AnimationTrack.o: AnimationTrack.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
AnimationTrack.o: Object.hpp KeyframeSequence.hpp Keyframe.hpp
AnimationTrack.o: AnimationController.hpp Exception.hpp
Appearance.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Appearance.o: /usr/include/inttypes.h /usr/include/features.h
Appearance.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Appearance.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Appearance.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Appearance.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h Appearance.hpp
Appearance.o: Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp
Appearance.o: CompositingMode.hpp Fog.hpp Material.hpp PolygonMode.hpp
Appearance.o: Texture2D.hpp Transformable.hpp Quaternion.hpp Transform.hpp
Appearance.o: Matrix.hpp Exception.hpp RenderState.hpp
Background.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Background.o: /usr/include/inttypes.h /usr/include/features.h
Background.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Background.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Background.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Background.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h Background.hpp
Background.o: Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp Image2D.hpp
Background.o: Exception.hpp AnimationTrack.hpp AnimationController.hpp
Background.o: KeyframeSequence.hpp Keyframe.hpp RenderState.hpp
Camera.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Camera.o: /usr/include/inttypes.h /usr/include/features.h
Camera.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Camera.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Camera.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Camera.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h Camera.hpp Node.hpp
Camera.o: Transformable.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
Camera.o: Object.hpp Quaternion.hpp Transform.hpp Matrix.hpp Vector.hpp
Camera.o: AnimationTrack.hpp AnimationController.hpp KeyframeSequence.hpp
Camera.o: Keyframe.hpp Exception.hpp RenderState.hpp
CompositingMode.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
CompositingMode.o: /usr/include/inttypes.h /usr/include/features.h
CompositingMode.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
CompositingMode.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
CompositingMode.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
CompositingMode.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
CompositingMode.o: CompositingMode.hpp Object3D.hpp m3gdef.hpp
CompositingMode.o: m3ginternal.hpp Object.hpp Exception.hpp RenderState.hpp
Exception.o: Exception.hpp
Fog.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Fog.o: /usr/include/inttypes.h /usr/include/features.h
Fog.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Fog.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Fog.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Fog.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h Fog.hpp Object3D.hpp
Fog.o: m3gdef.hpp m3ginternal.hpp Object.hpp Exception.hpp AnimationTrack.hpp
Fog.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Fog.o: RenderState.hpp
Graphics3D.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Graphics3D.o: /usr/include/inttypes.h /usr/include/features.h
Graphics3D.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Graphics3D.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Graphics3D.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Graphics3D.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h Graphics3D.hpp
Graphics3D.o: Object.hpp World.hpp Group.hpp Node.hpp Transformable.hpp
Graphics3D.o: Object3D.hpp m3gdef.hpp m3ginternal.hpp Quaternion.hpp
Graphics3D.o: Transform.hpp Matrix.hpp Image2D.hpp Loader.hpp M3GReader.hpp
Graphics3D.o: InMemoryStream.hpp M3GStruct.hpp m3g.hpp
Graphics3D.o: AnimationController.hpp AnimationTrack.hpp Appearance.hpp
Graphics3D.o: Background.hpp CompositingMode.hpp Fog.hpp IndexBuffer.hpp
Graphics3D.o: TriangleStripArray.hpp KeyframeSequence.hpp Keyframe.hpp
Graphics3D.o: Material.hpp PolygonMode.hpp Camera.hpp Light.hpp Mesh.hpp
Graphics3D.o: MorphingMesh.hpp SkinnedMesh.hpp BoneIndex.hpp Sprite3D.hpp
Graphics3D.o: Texture2D.hpp VertexArray.hpp VertexBuffer.hpp
Graphics3D.o: RayIntersection.hpp Vector.hpp Exception.hpp RenderState.hpp
Group.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Group.o: /usr/include/inttypes.h /usr/include/features.h
Group.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Group.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Group.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Group.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h Group.hpp Node.hpp
Group.o: Transformable.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp
Group.o: Quaternion.hpp Transform.hpp Matrix.hpp RayIntersection.hpp
Group.o: Vector.hpp Exception.hpp World.hpp Camera.hpp Mesh.hpp Sprite3D.hpp
Image2D.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Image2D.o: /usr/include/inttypes.h /usr/include/features.h
Image2D.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Image2D.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Image2D.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Image2D.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h Image2D.hpp
Image2D.o: Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp Exception.hpp
Image2D.o: RenderState.hpp /usr/include/png.h /usr/include/zlib.h
Image2D.o: /usr/include/zconf.h /usr/include/zlibdefs.h
Image2D.o: /usr/include/sys/types.h /usr/include/bits/types.h
Image2D.o: /usr/include/bits/typesizes.h /usr/include/time.h
Image2D.o: /usr/include/endian.h /usr/include/bits/endian.h
Image2D.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
Image2D.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
Image2D.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
Image2D.o: /usr/include/bits/pthreadtypes.h /usr/include/unistd.h
Image2D.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
Image2D.o: /usr/include/getopt.h /usr/include/pngconf.h /usr/include/stdio.h
Image2D.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
Image2D.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Image2D.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h
Image2D.o: /usr/include/string.h /usr/include/xlocale.h
IndexBuffer.o: IndexBuffer.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
IndexBuffer.o: Object.hpp Exception.hpp
Intersect.o: Intersect.hpp Vector.hpp Exception.hpp m3ginternal.hpp
Keyframe.o: Keyframe.hpp Quaternion.hpp Exception.hpp
KeyframeSequence.o: KeyframeSequence.hpp Object3D.hpp m3gdef.hpp
KeyframeSequence.o: m3ginternal.hpp Object.hpp Keyframe.hpp Exception.hpp
KeyframeSequence.o: Quaternion.hpp
Light.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Light.o: /usr/include/inttypes.h /usr/include/features.h
Light.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Light.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Light.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Light.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h Light.hpp Node.hpp
Light.o: Transformable.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp
Light.o: Quaternion.hpp Transform.hpp Matrix.hpp Exception.hpp
Light.o: AnimationTrack.hpp AnimationController.hpp KeyframeSequence.hpp
Light.o: Keyframe.hpp RenderState.hpp
Loader.o: m3g.hpp m3gdef.hpp Graphics3D.hpp Object.hpp Object3D.hpp
Loader.o: m3ginternal.hpp AnimationController.hpp AnimationTrack.hpp
Loader.o: Appearance.hpp Background.hpp CompositingMode.hpp Fog.hpp
Loader.o: Image2D.hpp IndexBuffer.hpp TriangleStripArray.hpp
Loader.o: KeyframeSequence.hpp Keyframe.hpp Material.hpp PolygonMode.hpp
Loader.o: Transformable.hpp Quaternion.hpp Transform.hpp Matrix.hpp Node.hpp
Loader.o: Camera.hpp Group.hpp World.hpp Light.hpp Mesh.hpp MorphingMesh.hpp
Loader.o: SkinnedMesh.hpp BoneIndex.hpp Sprite3D.hpp Texture2D.hpp
Loader.o: VertexArray.hpp VertexBuffer.hpp RayIntersection.hpp Vector.hpp
Loader.o: Loader.hpp M3GReader.hpp InMemoryStream.hpp M3GStruct.hpp
Loader.o: Exception.hpp RenderState.hpp MemoryReader.hpp /usr/include/png.h
Loader.o: /usr/include/zlib.h /usr/include/zconf.h /usr/include/zlibdefs.h
Loader.o: /usr/include/sys/types.h /usr/include/features.h
Loader.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Loader.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Loader.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
Loader.o: /usr/include/bits/typesizes.h /usr/include/time.h
Loader.o: /usr/include/endian.h /usr/include/bits/endian.h
Loader.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
Loader.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
Loader.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
Loader.o: /usr/include/bits/pthreadtypes.h /usr/include/unistd.h
Loader.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
Loader.o: /usr/include/getopt.h /usr/include/pngconf.h /usr/include/stdio.h
Loader.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
Loader.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Loader.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h
Loader.o: /usr/include/string.h /usr/include/xlocale.h
Material.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Material.o: /usr/include/inttypes.h /usr/include/features.h
Material.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Material.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Material.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Material.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h Material.hpp
Material.o: Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp Exception.hpp
Material.o: AnimationTrack.hpp AnimationController.hpp KeyframeSequence.hpp
Material.o: Keyframe.hpp RenderState.hpp
Matrix.o: Matrix.hpp Vector.hpp Exception.hpp
MemoryReader.o: MemoryReader.hpp /usr/include/png.h /usr/include/zlib.h
MemoryReader.o: /usr/include/zconf.h /usr/include/zlibdefs.h
MemoryReader.o: /usr/include/sys/types.h /usr/include/features.h
MemoryReader.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
MemoryReader.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
MemoryReader.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
MemoryReader.o: /usr/include/bits/typesizes.h /usr/include/time.h
MemoryReader.o: /usr/include/endian.h /usr/include/bits/endian.h
MemoryReader.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
MemoryReader.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
MemoryReader.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
MemoryReader.o: /usr/include/bits/pthreadtypes.h /usr/include/unistd.h
MemoryReader.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
MemoryReader.o: /usr/include/getopt.h /usr/include/pngconf.h
MemoryReader.o: /usr/include/stdio.h /usr/include/libio.h
MemoryReader.o: /usr/include/_G_config.h /usr/include/wchar.h
MemoryReader.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
MemoryReader.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h
MemoryReader.o: /usr/include/string.h /usr/include/xlocale.h
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
PolygonMode.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
PolygonMode.o: /usr/include/inttypes.h /usr/include/features.h
PolygonMode.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
PolygonMode.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
PolygonMode.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
PolygonMode.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
PolygonMode.o: PolygonMode.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
PolygonMode.o: Object.hpp Exception.hpp RenderState.hpp
Quaternion.o: Quaternion.hpp Exception.hpp m3ginternal.hpp Vector.hpp
Quaternion.o: Matrix.hpp
RayIntersection.o: RayIntersection.hpp Object.hpp Vector.hpp Exception.hpp
RayIntersection.o: VertexBuffer.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
RayIntersection.o: VertexArray.hpp Mesh.hpp Node.hpp Transformable.hpp
RayIntersection.o: Quaternion.hpp Transform.hpp Matrix.hpp Sprite3D.hpp
SkinnedMesh.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
SkinnedMesh.o: /usr/include/inttypes.h /usr/include/features.h
SkinnedMesh.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
SkinnedMesh.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
SkinnedMesh.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
SkinnedMesh.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
SkinnedMesh.o: SkinnedMesh.hpp Mesh.hpp Node.hpp Transformable.hpp
SkinnedMesh.o: Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp
SkinnedMesh.o: Quaternion.hpp Transform.hpp Matrix.hpp BoneIndex.hpp
SkinnedMesh.o: VertexBuffer.hpp IndexBuffer.hpp VertexArray.hpp Vector.hpp
SkinnedMesh.o: Exception.hpp World.hpp Group.hpp RayIntersection.hpp
Sprite3D.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Sprite3D.o: /usr/include/inttypes.h /usr/include/features.h
Sprite3D.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Sprite3D.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Sprite3D.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Sprite3D.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h Sprite3D.hpp
Sprite3D.o: Node.hpp Transformable.hpp Object3D.hpp m3gdef.hpp
Sprite3D.o: m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp
Sprite3D.o: Matrix.hpp Appearance.hpp Image2D.hpp Exception.hpp
Sprite3D.o: Graphics3D.hpp Vector.hpp AnimationTrack.hpp
Sprite3D.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Sprite3D.o: RenderState.hpp CompositingMode.hpp Fog.hpp Intersect.hpp
Sprite3D.o: RayIntersection.hpp Camera.hpp
Texture2D.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Texture2D.o: /usr/include/inttypes.h /usr/include/features.h
Texture2D.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Texture2D.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Texture2D.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Texture2D.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h Texture2D.hpp
Texture2D.o: Transformable.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
Texture2D.o: Object.hpp Quaternion.hpp Transform.hpp Matrix.hpp Image2D.hpp
Texture2D.o: Exception.hpp AnimationTrack.hpp AnimationController.hpp
Texture2D.o: KeyframeSequence.hpp Keyframe.hpp RenderState.hpp
Transform.o: Transform.hpp Matrix.hpp Object.hpp Vector.hpp Exception.hpp
Transform.o: Quaternion.hpp VertexArray.hpp Object3D.hpp m3gdef.hpp
Transform.o: m3ginternal.hpp
Transformable.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Transformable.o: /usr/include/inttypes.h /usr/include/features.h
Transformable.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Transformable.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Transformable.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Transformable.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
Transformable.o: Transformable.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
Transformable.o: Object.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Transformable.o: Exception.hpp AnimationTrack.hpp AnimationController.hpp
Transformable.o: KeyframeSequence.hpp Keyframe.hpp
TriangleStripArray.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
TriangleStripArray.o: /usr/include/inttypes.h /usr/include/features.h
TriangleStripArray.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
TriangleStripArray.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
TriangleStripArray.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
TriangleStripArray.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
TriangleStripArray.o: TriangleStripArray.hpp IndexBuffer.hpp Object3D.hpp
TriangleStripArray.o: m3gdef.hpp m3ginternal.hpp Object.hpp Exception.hpp
TriangleStripArray.o: RenderState.hpp
Vector.o: Vector.hpp Exception.hpp m3ginternal.hpp
VertexArray.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
VertexArray.o: /usr/include/inttypes.h /usr/include/features.h
VertexArray.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
VertexArray.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
VertexArray.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
VertexArray.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
VertexArray.o: VertexArray.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
VertexArray.o: Object.hpp Exception.hpp Vector.hpp BoneIndex.hpp Matrix.hpp
VertexBuffer.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
VertexBuffer.o: /usr/include/inttypes.h /usr/include/features.h
VertexBuffer.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
VertexBuffer.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
VertexBuffer.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
VertexBuffer.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
VertexBuffer.o: VertexBuffer.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
VertexBuffer.o: Object.hpp VertexArray.hpp AnimationTrack.hpp
VertexBuffer.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
VertexBuffer.o: Exception.hpp RenderState.hpp
World.o: World.hpp Group.hpp Node.hpp Transformable.hpp Object3D.hpp
World.o: m3gdef.hpp m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp
World.o: Matrix.hpp Camera.hpp Background.hpp Light.hpp Exception.hpp
World.o: RenderState.hpp
m3ginternal.o: m3ginternal.hpp m3gdef.hpp
