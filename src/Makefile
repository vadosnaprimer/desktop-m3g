SRCS     = $(wildcard *.cpp)
OBJS     = $(SRCS:.cpp=.o)
TARGET   = libm3g.so
CXX      = g++
CXXFLAGS = -Wall -g -I. -shared -fPIC -fno-strict-aliasing
LD       = g++
LDFLAGS  = -shared -L. 
LIBS     = -lGL -lGLU -lpng -ljpeg


all: $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $(TARGET)
	@echo done.

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c

install: $(TARGET)
	install -c -m 0755 $(TARGET) /usr/lib
	mkdir -p /usr/include/m3g
	cp *.hpp /usr/include/m3g

depend:
	makedepend -- $(CXXFLAGS) -- $(SRCS)

clean:
	rm -rf *.o *.so *~ 
	@echo done.


# DO NOT DELETE

AnimationController.o: m3g/AnimationController.hpp m3g/Object3D.hpp
AnimationController.o: m3g/m3gdef.hpp m3g/m3ginternal.hpp m3g/Object.hpp
AnimationController.o: m3g/Exception.hpp
AnimationTrack.o: m3g/AnimationTrack.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
AnimationTrack.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/KeyframeSequence.hpp
AnimationTrack.o: m3g/Keyframe.hpp m3g/AnimationController.hpp
AnimationTrack.o: m3g/Exception.hpp
Appearance.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Appearance.o: /usr/include/inttypes.h /usr/include/features.h
Appearance.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Appearance.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Appearance.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Appearance.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
Appearance.o: m3g/Appearance.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
Appearance.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/CompositingMode.hpp
Appearance.o: m3g/Fog.hpp m3g/Material.hpp m3g/PolygonMode.hpp
Appearance.o: m3g/Texture2D.hpp m3g/Transformable.hpp m3g/Quaternion.hpp
Appearance.o: m3g/Transform.hpp m3g/Matrix.hpp m3g/Exception.hpp
Appearance.o: m3g/RenderState.hpp
Background.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Background.o: /usr/include/inttypes.h /usr/include/features.h
Background.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Background.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Background.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Background.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
Background.o: m3g/Background.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
Background.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/Image2D.hpp
Background.o: m3g/Exception.hpp m3g/AnimationTrack.hpp
Background.o: m3g/AnimationController.hpp m3g/KeyframeSequence.hpp
Background.o: m3g/Keyframe.hpp m3g/RenderState.hpp
Camera.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Camera.o: /usr/include/inttypes.h /usr/include/features.h
Camera.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Camera.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Camera.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Camera.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h m3g/Camera.hpp
Camera.o: m3g/Node.hpp m3g/Transformable.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
Camera.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/Quaternion.hpp
Camera.o: m3g/Transform.hpp m3g/Matrix.hpp m3g/Vector.hpp
Camera.o: m3g/AnimationTrack.hpp m3g/AnimationController.hpp
Camera.o: m3g/KeyframeSequence.hpp m3g/Keyframe.hpp m3g/Exception.hpp
Camera.o: m3g/RenderState.hpp
CompositingMode.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h
CompositingMode.o: /usr/include/GL/glext.h /usr/include/inttypes.h
CompositingMode.o: /usr/include/features.h /usr/include/bits/predefs.h
CompositingMode.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
CompositingMode.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
CompositingMode.o: /usr/include/stdint.h /usr/include/bits/wchar.h
CompositingMode.o: /usr/include/GL/glu.h m3g/CompositingMode.hpp
CompositingMode.o: m3g/Object3D.hpp m3g/m3gdef.hpp m3g/m3ginternal.hpp
CompositingMode.o: m3g/Object.hpp m3g/Exception.hpp m3g/RenderState.hpp
Exception.o: m3g/Exception.hpp
Fog.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Fog.o: /usr/include/inttypes.h /usr/include/features.h
Fog.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Fog.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Fog.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Fog.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h m3g/Fog.hpp
Fog.o: m3g/Object3D.hpp m3g/m3gdef.hpp m3g/m3ginternal.hpp m3g/Object.hpp
Fog.o: m3g/Exception.hpp m3g/AnimationTrack.hpp m3g/AnimationController.hpp
Fog.o: m3g/KeyframeSequence.hpp m3g/Keyframe.hpp m3g/RenderState.hpp
Graphics3D.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Graphics3D.o: /usr/include/inttypes.h /usr/include/features.h
Graphics3D.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Graphics3D.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Graphics3D.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Graphics3D.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
Graphics3D.o: m3g/Graphics3D.hpp m3g/Object.hpp m3g/World.hpp m3g/Group.hpp
Graphics3D.o: m3g/Node.hpp m3g/Transformable.hpp m3g/Object3D.hpp
Graphics3D.o: m3g/m3gdef.hpp m3g/m3ginternal.hpp m3g/Quaternion.hpp
Graphics3D.o: m3g/Transform.hpp m3g/Matrix.hpp m3g/Image2D.hpp m3g/Loader.hpp
Graphics3D.o: m3g/M3GReader.hpp m3g/InMemoryStream.hpp m3g/M3GStruct.hpp
Graphics3D.o: m3g/m3g.hpp m3g/AnimationController.hpp m3g/AnimationTrack.hpp
Graphics3D.o: m3g/Appearance.hpp m3g/Background.hpp m3g/CompositingMode.hpp
Graphics3D.o: m3g/Fog.hpp m3g/IndexBuffer.hpp m3g/TriangleStripArray.hpp
Graphics3D.o: m3g/KeyframeSequence.hpp m3g/Keyframe.hpp m3g/Material.hpp
Graphics3D.o: m3g/PolygonMode.hpp m3g/Camera.hpp m3g/Light.hpp m3g/Mesh.hpp
Graphics3D.o: m3g/MorphingMesh.hpp m3g/SkinnedMesh.hpp m3g/BoneWeight.hpp
Graphics3D.o: m3g/Sprite3D.hpp m3g/Texture2D.hpp m3g/VertexArray.hpp
Graphics3D.o: m3g/VertexBuffer.hpp m3g/RayIntersection.hpp m3g/Vector.hpp
Graphics3D.o: m3g/Exception.hpp m3g/RenderState.hpp
Group.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Group.o: /usr/include/inttypes.h /usr/include/features.h
Group.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Group.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Group.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Group.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h m3g/Group.hpp
Group.o: m3g/Node.hpp m3g/Transformable.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
Group.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/Quaternion.hpp
Group.o: m3g/Transform.hpp m3g/Matrix.hpp m3g/RayIntersection.hpp
Group.o: m3g/Vector.hpp m3g/Exception.hpp m3g/World.hpp m3g/Camera.hpp
Group.o: m3g/Mesh.hpp m3g/Sprite3D.hpp
Image2D.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Image2D.o: /usr/include/inttypes.h /usr/include/features.h
Image2D.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Image2D.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Image2D.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Image2D.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h m3g/Image2D.hpp
Image2D.o: m3g/Object3D.hpp m3g/m3gdef.hpp m3g/m3ginternal.hpp m3g/Object.hpp
Image2D.o: m3g/Exception.hpp m3g/RenderState.hpp /usr/include/png.h
Image2D.o: /usr/include/zlib.h /usr/include/zconf.h /usr/include/zlibdefs.h
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
InMemoryStream.o: m3g/InMemoryStream.hpp
IndexBuffer.o: m3g/IndexBuffer.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
IndexBuffer.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/Exception.hpp
Intersect.o: m3g/Intersect.hpp m3g/Vector.hpp m3g/Exception.hpp
Intersect.o: m3g/m3ginternal.hpp
Keyframe.o: m3g/Keyframe.hpp m3g/Quaternion.hpp m3g/Exception.hpp
KeyframeSequence.o: m3g/KeyframeSequence.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
KeyframeSequence.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/Keyframe.hpp
KeyframeSequence.o: m3g/Exception.hpp m3g/Quaternion.hpp
Light.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Light.o: /usr/include/inttypes.h /usr/include/features.h
Light.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Light.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Light.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Light.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h m3g/Light.hpp
Light.o: m3g/Node.hpp m3g/Transformable.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
Light.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/Quaternion.hpp
Light.o: m3g/Transform.hpp m3g/Matrix.hpp m3g/Exception.hpp
Light.o: m3g/AnimationTrack.hpp m3g/AnimationController.hpp
Light.o: m3g/KeyframeSequence.hpp m3g/Keyframe.hpp m3g/RenderState.hpp
Loader.o: m3g/m3g.hpp m3g/m3gdef.hpp m3g/Graphics3D.hpp m3g/Object.hpp
Loader.o: m3g/Object3D.hpp m3g/m3ginternal.hpp m3g/AnimationController.hpp
Loader.o: m3g/AnimationTrack.hpp m3g/Appearance.hpp m3g/Background.hpp
Loader.o: m3g/CompositingMode.hpp m3g/Fog.hpp m3g/Image2D.hpp
Loader.o: m3g/IndexBuffer.hpp m3g/TriangleStripArray.hpp
Loader.o: m3g/KeyframeSequence.hpp m3g/Keyframe.hpp m3g/Material.hpp
Loader.o: m3g/PolygonMode.hpp m3g/Transformable.hpp m3g/Quaternion.hpp
Loader.o: m3g/Transform.hpp m3g/Matrix.hpp m3g/Node.hpp m3g/Camera.hpp
Loader.o: m3g/Group.hpp m3g/World.hpp m3g/Light.hpp m3g/Mesh.hpp
Loader.o: m3g/MorphingMesh.hpp m3g/SkinnedMesh.hpp m3g/BoneWeight.hpp
Loader.o: m3g/Sprite3D.hpp m3g/Texture2D.hpp m3g/VertexArray.hpp
Loader.o: m3g/VertexBuffer.hpp m3g/RayIntersection.hpp m3g/Vector.hpp
Loader.o: m3g/Loader.hpp m3g/M3GReader.hpp m3g/InMemoryStream.hpp
Loader.o: m3g/M3GStruct.hpp m3g/Exception.hpp m3g/RenderState.hpp
Loader.o: m3g/MemoryReader.hpp /usr/include/png.h /usr/include/zlib.h
Loader.o: /usr/include/zconf.h /usr/include/zlibdefs.h
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
Loader.o: /usr/include/string.h /usr/include/xlocale.h /usr/include/jpeglib.h
Loader.o: /usr/include/jconfig.h /usr/include/jmorecfg.h jpeg_memory_src.hpp
M3GReader.o: m3g/M3GReader.hpp m3g/InMemoryStream.hpp m3g/M3GStruct.hpp
M3GReader.o: /usr/include/zlib.h /usr/include/zconf.h /usr/include/zlibdefs.h
M3GReader.o: /usr/include/sys/types.h /usr/include/features.h
M3GReader.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
M3GReader.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
M3GReader.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
M3GReader.o: /usr/include/bits/typesizes.h /usr/include/time.h
M3GReader.o: /usr/include/endian.h /usr/include/bits/endian.h
M3GReader.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
M3GReader.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
M3GReader.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
M3GReader.o: /usr/include/bits/pthreadtypes.h /usr/include/unistd.h
M3GReader.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
M3GReader.o: /usr/include/getopt.h
M3GStruct.o: m3g/M3GStruct.hpp
M3GWriter.o: m3g/M3GWriter.hpp m3g/OutMemoryStream.hpp m3g/M3GStruct.hpp
M3GWriter.o: /usr/include/zlib.h /usr/include/zconf.h /usr/include/zlibdefs.h
M3GWriter.o: /usr/include/sys/types.h /usr/include/features.h
M3GWriter.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
M3GWriter.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
M3GWriter.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
M3GWriter.o: /usr/include/bits/typesizes.h /usr/include/time.h
M3GWriter.o: /usr/include/endian.h /usr/include/bits/endian.h
M3GWriter.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
M3GWriter.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
M3GWriter.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
M3GWriter.o: /usr/include/bits/pthreadtypes.h /usr/include/unistd.h
M3GWriter.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
M3GWriter.o: /usr/include/getopt.h
Material.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Material.o: /usr/include/inttypes.h /usr/include/features.h
Material.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Material.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Material.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Material.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h m3g/Material.hpp
Material.o: m3g/Object3D.hpp m3g/m3gdef.hpp m3g/m3ginternal.hpp
Material.o: m3g/Object.hpp m3g/Exception.hpp m3g/AnimationTrack.hpp
Material.o: m3g/AnimationController.hpp m3g/KeyframeSequence.hpp
Material.o: m3g/Keyframe.hpp m3g/RenderState.hpp
Matrix.o: m3g/Matrix.hpp m3g/Vector.hpp m3g/Exception.hpp
MemoryReader.o: m3g/MemoryReader.hpp /usr/include/png.h /usr/include/zlib.h
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
Mesh.o: m3g/Mesh.hpp m3g/Node.hpp m3g/Transformable.hpp m3g/Object3D.hpp
Mesh.o: m3g/m3gdef.hpp m3g/m3ginternal.hpp m3g/Object.hpp m3g/Quaternion.hpp
Mesh.o: m3g/Transform.hpp m3g/Matrix.hpp m3g/VertexBuffer.hpp
Mesh.o: m3g/VertexArray.hpp m3g/IndexBuffer.hpp m3g/Appearance.hpp
Mesh.o: m3g/Exception.hpp m3g/RayIntersection.hpp m3g/Vector.hpp
Mesh.o: m3g/RenderState.hpp m3g/Intersect.hpp
MorphingMesh.o: m3g/MorphingMesh.hpp m3g/Mesh.hpp m3g/Node.hpp
MorphingMesh.o: m3g/Transformable.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
MorphingMesh.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/Quaternion.hpp
MorphingMesh.o: m3g/Transform.hpp m3g/Matrix.hpp m3g/VertexBuffer.hpp
MorphingMesh.o: m3g/VertexArray.hpp m3g/IndexBuffer.hpp m3g/Appearance.hpp
MorphingMesh.o: m3g/AnimationTrack.hpp m3g/AnimationController.hpp
MorphingMesh.o: m3g/KeyframeSequence.hpp m3g/Keyframe.hpp m3g/Vector.hpp
MorphingMesh.o: m3g/Exception.hpp
Node.o: m3g/Node.hpp m3g/Transformable.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
Node.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/Quaternion.hpp
Node.o: m3g/Transform.hpp m3g/Matrix.hpp m3g/Exception.hpp
Node.o: m3g/AnimationTrack.hpp m3g/AnimationController.hpp
Node.o: m3g/KeyframeSequence.hpp m3g/Keyframe.hpp m3g/RenderState.hpp
Node.o: m3g/Vector.hpp
Object.o: m3g/Object.hpp
Object3D.o: m3g/Object3D.hpp m3g/m3gdef.hpp m3g/m3ginternal.hpp
Object3D.o: m3g/Object.hpp m3g/AnimationTrack.hpp m3g/Exception.hpp
OutMemoryStream.o: m3g/OutMemoryStream.hpp
PolygonMode.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
PolygonMode.o: /usr/include/inttypes.h /usr/include/features.h
PolygonMode.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
PolygonMode.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
PolygonMode.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
PolygonMode.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
PolygonMode.o: m3g/PolygonMode.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
PolygonMode.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/Exception.hpp
PolygonMode.o: m3g/RenderState.hpp
Quaternion.o: m3g/Quaternion.hpp m3g/Exception.hpp m3g/m3ginternal.hpp
Quaternion.o: m3g/Vector.hpp m3g/Matrix.hpp
RayIntersection.o: m3g/RayIntersection.hpp m3g/Object.hpp m3g/Vector.hpp
RayIntersection.o: m3g/Exception.hpp m3g/VertexBuffer.hpp m3g/Object3D.hpp
RayIntersection.o: m3g/m3gdef.hpp m3g/m3ginternal.hpp m3g/VertexArray.hpp
RayIntersection.o: m3g/Mesh.hpp m3g/Node.hpp m3g/Transformable.hpp
RayIntersection.o: m3g/Quaternion.hpp m3g/Transform.hpp m3g/Matrix.hpp
RayIntersection.o: m3g/Sprite3D.hpp
SkinnedMesh.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
SkinnedMesh.o: /usr/include/inttypes.h /usr/include/features.h
SkinnedMesh.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
SkinnedMesh.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
SkinnedMesh.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
SkinnedMesh.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
SkinnedMesh.o: m3g/SkinnedMesh.hpp m3g/Mesh.hpp m3g/Node.hpp
SkinnedMesh.o: m3g/Transformable.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
SkinnedMesh.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/Quaternion.hpp
SkinnedMesh.o: m3g/Transform.hpp m3g/Matrix.hpp m3g/BoneWeight.hpp
SkinnedMesh.o: m3g/VertexBuffer.hpp m3g/IndexBuffer.hpp m3g/VertexArray.hpp
SkinnedMesh.o: m3g/Vector.hpp m3g/Exception.hpp m3g/World.hpp m3g/Group.hpp
SkinnedMesh.o: m3g/RayIntersection.hpp
Sprite3D.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Sprite3D.o: /usr/include/inttypes.h /usr/include/features.h
Sprite3D.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Sprite3D.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Sprite3D.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Sprite3D.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h m3g/Sprite3D.hpp
Sprite3D.o: m3g/Node.hpp m3g/Transformable.hpp m3g/Object3D.hpp
Sprite3D.o: m3g/m3gdef.hpp m3g/m3ginternal.hpp m3g/Object.hpp
Sprite3D.o: m3g/Quaternion.hpp m3g/Transform.hpp m3g/Matrix.hpp
Sprite3D.o: m3g/Appearance.hpp m3g/Image2D.hpp m3g/Exception.hpp
Sprite3D.o: m3g/Graphics3D.hpp m3g/Vector.hpp m3g/AnimationTrack.hpp
Sprite3D.o: m3g/AnimationController.hpp m3g/KeyframeSequence.hpp
Sprite3D.o: m3g/Keyframe.hpp m3g/RenderState.hpp m3g/CompositingMode.hpp
Sprite3D.o: m3g/Fog.hpp m3g/Intersect.hpp m3g/RayIntersection.hpp
Sprite3D.o: m3g/Camera.hpp
Texture2D.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Texture2D.o: /usr/include/inttypes.h /usr/include/features.h
Texture2D.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Texture2D.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Texture2D.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Texture2D.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
Texture2D.o: m3g/Texture2D.hpp m3g/Transformable.hpp m3g/Object3D.hpp
Texture2D.o: m3g/m3gdef.hpp m3g/m3ginternal.hpp m3g/Object.hpp
Texture2D.o: m3g/Quaternion.hpp m3g/Transform.hpp m3g/Matrix.hpp
Texture2D.o: m3g/Image2D.hpp m3g/Exception.hpp m3g/AnimationTrack.hpp
Texture2D.o: m3g/AnimationController.hpp m3g/KeyframeSequence.hpp
Texture2D.o: m3g/Keyframe.hpp m3g/RenderState.hpp
Transform.o: m3g/Transform.hpp m3g/Matrix.hpp m3g/Object.hpp m3g/Vector.hpp
Transform.o: m3g/Exception.hpp m3g/Quaternion.hpp m3g/VertexArray.hpp
Transform.o: m3g/Object3D.hpp m3g/m3gdef.hpp m3g/m3ginternal.hpp
Transformable.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
Transformable.o: /usr/include/inttypes.h /usr/include/features.h
Transformable.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
Transformable.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
Transformable.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
Transformable.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
Transformable.o: m3g/Transformable.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
Transformable.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/Quaternion.hpp
Transformable.o: m3g/Transform.hpp m3g/Matrix.hpp m3g/Exception.hpp
Transformable.o: m3g/AnimationTrack.hpp m3g/AnimationController.hpp
Transformable.o: m3g/KeyframeSequence.hpp m3g/Keyframe.hpp
TriangleStripArray.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h
TriangleStripArray.o: /usr/include/GL/glext.h /usr/include/inttypes.h
TriangleStripArray.o: /usr/include/features.h /usr/include/bits/predefs.h
TriangleStripArray.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
TriangleStripArray.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
TriangleStripArray.o: /usr/include/stdint.h /usr/include/bits/wchar.h
TriangleStripArray.o: /usr/include/GL/glu.h m3g/TriangleStripArray.hpp
TriangleStripArray.o: m3g/IndexBuffer.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
TriangleStripArray.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/Exception.hpp
TriangleStripArray.o: m3g/RenderState.hpp
Vector.o: m3g/Vector.hpp m3g/Exception.hpp m3g/m3ginternal.hpp
VertexArray.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
VertexArray.o: /usr/include/inttypes.h /usr/include/features.h
VertexArray.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
VertexArray.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
VertexArray.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
VertexArray.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
VertexArray.o: m3g/VertexArray.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
VertexArray.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/Exception.hpp
VertexArray.o: m3g/Vector.hpp /usr/include/m3g/BoneIndex.hpp Matrix.hpp
VertexBuffer.o: m3g/m3g-gl.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
VertexBuffer.o: /usr/include/inttypes.h /usr/include/features.h
VertexBuffer.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
VertexBuffer.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
VertexBuffer.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
VertexBuffer.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
VertexBuffer.o: m3g/VertexBuffer.hpp m3g/Object3D.hpp m3g/m3gdef.hpp
VertexBuffer.o: m3g/m3ginternal.hpp m3g/Object.hpp m3g/VertexArray.hpp
VertexBuffer.o: m3g/AnimationTrack.hpp m3g/AnimationController.hpp
VertexBuffer.o: m3g/KeyframeSequence.hpp m3g/Keyframe.hpp m3g/Exception.hpp
VertexBuffer.o: m3g/RenderState.hpp
World.o: m3g/World.hpp m3g/Group.hpp m3g/Node.hpp m3g/Transformable.hpp
World.o: m3g/Object3D.hpp m3g/m3gdef.hpp m3g/m3ginternal.hpp m3g/Object.hpp
World.o: m3g/Quaternion.hpp m3g/Transform.hpp m3g/Matrix.hpp m3g/Camera.hpp
World.o: m3g/Background.hpp m3g/Light.hpp m3g/Exception.hpp
World.o: m3g/RenderState.hpp
jpeg_memory_src.o: /usr/include/jpeglib.h /usr/include/jconfig.h
jpeg_memory_src.o: /usr/include/jmorecfg.h
m3ginternal.o: m3g/m3ginternal.hpp m3g/m3gdef.hpp
