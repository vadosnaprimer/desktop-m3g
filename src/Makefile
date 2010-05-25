SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = libm3g.so
CXX = g++
CXXFLAGS = -Wall -g -shared -fPIC -Wno-deprecated -fno-strict-aliasing
LD = g++
LDFLAGS = -shared -lGL -lGLU -lpng -ljpeg
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
Appearance.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Appearance.o: /usr/include/GL/glu.h Appearance.hpp Object3D.hpp m3gdef.hpp
Appearance.o: m3ginternal.hpp Object.hpp CompositingMode.hpp Fog.hpp
Appearance.o: Material.hpp PolygonMode.hpp Texture2D.hpp Transformable.hpp
Appearance.o: Quaternion.hpp Transform.hpp Matrix.hpp Exception.hpp
Appearance.o: RenderState.hpp
Background.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Background.o: /usr/include/GL/glu.h Background.hpp Object3D.hpp m3gdef.hpp
Background.o: m3ginternal.hpp Object.hpp Image2D.hpp Exception.hpp
Background.o: AnimationTrack.hpp AnimationController.hpp KeyframeSequence.hpp
Background.o: Keyframe.hpp RenderState.hpp
Camera.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Camera.o: /usr/include/GL/glu.h Camera.hpp Node.hpp Transformable.hpp
Camera.o: Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp Quaternion.hpp
Camera.o: Transform.hpp Matrix.hpp Vector.hpp AnimationTrack.hpp
Camera.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Camera.o: Exception.hpp RenderState.hpp
CompositingMode.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
CompositingMode.o: /usr/include/GL/glu.h CompositingMode.hpp Object3D.hpp
CompositingMode.o: m3gdef.hpp m3ginternal.hpp Object.hpp Exception.hpp
CompositingMode.o: RenderState.hpp
Exception.o: Exception.hpp
Fog.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Fog.o: /usr/include/GL/glu.h Fog.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
Fog.o: Object.hpp Exception.hpp AnimationTrack.hpp AnimationController.hpp
Fog.o: KeyframeSequence.hpp Keyframe.hpp RenderState.hpp
Graphics3D.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Graphics3D.o: /usr/include/GL/glu.h Graphics3D.hpp Object.hpp World.hpp
Graphics3D.o: Group.hpp Node.hpp Transformable.hpp Object3D.hpp m3gdef.hpp
Graphics3D.o: m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Graphics3D.o: Image2D.hpp Loader.hpp Camera.hpp RenderState.hpp Exception.hpp
Group.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Group.o: /usr/include/GL/glu.h Group.hpp Node.hpp Transformable.hpp
Group.o: Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp Quaternion.hpp
Group.o: Transform.hpp Matrix.hpp RayIntersection.hpp Vector.hpp
Group.o: Exception.hpp World.hpp Camera.hpp Mesh.hpp
Image2D.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Image2D.o: /usr/include/GL/glu.h Image2D.hpp Object3D.hpp m3gdef.hpp
Image2D.o: m3ginternal.hpp Object.hpp Exception.hpp RenderState.hpp
Image2D.o: /usr/include/png.h /usr/include/zlib.h /usr/include/zconf.h
Image2D.o: /usr/include/zlibdefs.h /usr/include/sys/types.h
Image2D.o: /usr/include/features.h /usr/include/sys/cdefs.h
Image2D.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Image2D.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
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
Image2D.o: /usr/include/string.h
IndexBuffer.o: IndexBuffer.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
IndexBuffer.o: Object.hpp Exception.hpp
Intersect.o: Intersect.hpp Vector.hpp Exception.hpp m3ginternal.hpp
Keyframe.o: Keyframe.hpp Quaternion.hpp Exception.hpp
KeyframeSequence.o: KeyframeSequence.hpp Object3D.hpp m3gdef.hpp
KeyframeSequence.o: m3ginternal.hpp Object.hpp Keyframe.hpp Exception.hpp
KeyframeSequence.o: Quaternion.hpp
Light.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Light.o: /usr/include/GL/glu.h Light.hpp Node.hpp Transformable.hpp
Light.o: Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp Quaternion.hpp
Light.o: Transform.hpp Matrix.hpp Exception.hpp AnimationTrack.hpp
Light.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Light.o: RenderState.hpp
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
Loader.o: /usr/include/string.h /usr/include/jpeglib.h /usr/include/jconfig.h
Loader.o: /usr/include/jmorecfg.h m3g.hpp m3gdef.hpp Graphics3D.hpp
Loader.o: Object.hpp Object3D.hpp m3ginternal.hpp AnimationController.hpp
Loader.o: AnimationTrack.hpp Appearance.hpp Background.hpp
Loader.o: CompositingMode.hpp Fog.hpp Image2D.hpp IndexBuffer.hpp
Loader.o: TriangleStripArray.hpp KeyframeSequence.hpp Keyframe.hpp
Loader.o: Material.hpp PolygonMode.hpp Transformable.hpp Quaternion.hpp
Loader.o: Transform.hpp Matrix.hpp Node.hpp Camera.hpp Group.hpp World.hpp
Loader.o: Light.hpp Mesh.hpp MorphingMesh.hpp SkinnedMesh.hpp BoneIndex.hpp
Loader.o: Sprite3D.hpp Texture2D.hpp VertexArray.hpp VertexBuffer.hpp
Loader.o: RayIntersection.hpp Vector.hpp Loader.hpp Exception.hpp
Loader.o: RenderState.hpp /usr/include/stdlib.h /usr/include/alloca.h
Material.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Material.o: /usr/include/GL/glu.h Material.hpp Object3D.hpp m3gdef.hpp
Material.o: m3ginternal.hpp Object.hpp Exception.hpp AnimationTrack.hpp
Material.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Material.o: RenderState.hpp
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
PolygonMode.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
PolygonMode.o: /usr/include/GL/glu.h PolygonMode.hpp Object3D.hpp m3gdef.hpp
PolygonMode.o: m3ginternal.hpp Object.hpp Exception.hpp RenderState.hpp
Quaternion.o: Quaternion.hpp Exception.hpp m3ginternal.hpp Vector.hpp
Quaternion.o: Matrix.hpp
RayIntersection.o: RayIntersection.hpp Object.hpp Vector.hpp Exception.hpp
RayIntersection.o: VertexBuffer.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
RayIntersection.o: VertexArray.hpp Mesh.hpp Node.hpp Transformable.hpp
RayIntersection.o: Quaternion.hpp Transform.hpp Matrix.hpp Sprite3D.hpp
SkinnedMesh.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
SkinnedMesh.o: /usr/include/GL/glu.h SkinnedMesh.hpp Mesh.hpp Node.hpp
SkinnedMesh.o: Transformable.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
SkinnedMesh.o: Object.hpp Quaternion.hpp Transform.hpp Matrix.hpp
SkinnedMesh.o: BoneIndex.hpp VertexBuffer.hpp IndexBuffer.hpp VertexArray.hpp
SkinnedMesh.o: Vector.hpp Exception.hpp World.hpp Group.hpp
Sprite3D.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Sprite3D.o: /usr/include/GL/glu.h Sprite3D.hpp Node.hpp Transformable.hpp
Sprite3D.o: Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp Quaternion.hpp
Sprite3D.o: Transform.hpp Matrix.hpp Appearance.hpp Image2D.hpp Exception.hpp
Sprite3D.o: Graphics3D.hpp Vector.hpp AnimationTrack.hpp
Sprite3D.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Sprite3D.o: RenderState.hpp
Texture2D.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Texture2D.o: /usr/include/GL/glu.h Texture2D.hpp Transformable.hpp
Texture2D.o: Object3D.hpp m3gdef.hpp m3ginternal.hpp Object.hpp
Texture2D.o: Quaternion.hpp Transform.hpp Matrix.hpp Image2D.hpp
Texture2D.o: Exception.hpp AnimationTrack.hpp AnimationController.hpp
Texture2D.o: KeyframeSequence.hpp Keyframe.hpp RenderState.hpp
Transform.o: Transform.hpp Matrix.hpp Object.hpp Vector.hpp Exception.hpp
Transform.o: Quaternion.hpp
Transformable.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Transformable.o: /usr/include/GL/glu.h Transformable.hpp Object3D.hpp
Transformable.o: m3gdef.hpp m3ginternal.hpp Object.hpp Quaternion.hpp
Transformable.o: Transform.hpp Matrix.hpp Exception.hpp AnimationTrack.hpp
Transformable.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
TriangleStripArray.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
TriangleStripArray.o: /usr/include/GL/glu.h TriangleStripArray.hpp
TriangleStripArray.o: IndexBuffer.hpp Object3D.hpp m3gdef.hpp m3ginternal.hpp
TriangleStripArray.o: Object.hpp Exception.hpp RenderState.hpp
Vector.o: Vector.hpp Exception.hpp m3ginternal.hpp
VertexArray.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
VertexArray.o: /usr/include/GL/glu.h VertexArray.hpp Object3D.hpp m3gdef.hpp
VertexArray.o: m3ginternal.hpp Object.hpp Exception.hpp Vector.hpp
VertexArray.o: BoneIndex.hpp Matrix.hpp
VertexBuffer.o: m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
VertexBuffer.o: /usr/include/GL/glu.h VertexBuffer.hpp Object3D.hpp
VertexBuffer.o: m3gdef.hpp m3ginternal.hpp Object.hpp VertexArray.hpp
VertexBuffer.o: AnimationTrack.hpp AnimationController.hpp
VertexBuffer.o: KeyframeSequence.hpp Keyframe.hpp Exception.hpp
VertexBuffer.o: RenderState.hpp
World.o: World.hpp Group.hpp Node.hpp Transformable.hpp Object3D.hpp
World.o: m3gdef.hpp m3ginternal.hpp Object.hpp Quaternion.hpp Transform.hpp
World.o: Matrix.hpp Camera.hpp Background.hpp Light.hpp Exception.hpp
World.o: RenderState.hpp
m3ginternal.o: m3ginternal.hpp m3gdef.hpp
