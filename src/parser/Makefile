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
M3GParser.o: Section.hpp parse-Appearance.hpp ../Appearance.hpp
M3GParser.o: ../Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
M3GParser.o: /usr/include/GL/gl.h ../m3gdef.hpp ../m3ginternal.hpp
M3GParser.o: parse-Background.hpp ../Background.hpp parse-Camera.hpp
M3GParser.o: ../Camera.hpp ../Node.hpp ../Transformable.hpp ../Quaternion.hpp
M3GParser.o: ../Transform.hpp ../Matrix.hpp ../Projection.hpp parse-Group.hpp
M3GParser.o: ../Group.hpp parse-Light.hpp ../Light.hpp parse-Material.hpp
M3GParser.o: ../Material.hpp parse-Mesh.hpp ../Mesh.hpp parse-PolygonMode.hpp
M3GParser.o: ../PolygonMode.hpp parse-TriangleStripArray.hpp
M3GParser.o: ../TriangleStripArray.hpp ../IndexBuffer.hpp parse-World.hpp
M3GParser.o: ../World.hpp ../Group.hpp parse-VertexArray.hpp
M3GParser.o: ../VertexArray.hpp parse-VertexBuffer.hpp ../VertexBuffer.hpp
M3GParser.o: ../m3gdef.hpp ../m3ginternal.hpp ../m3gexcept.hpp
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
parse-AnimationController.o: ../m3ginternal.hpp ../ActiveInterval.hpp
parse-AnimationTracker.o: ../AnimationTrack.hpp ../Object3D.hpp
parse-AnimationTracker.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-AnimationTracker.o: /usr/include/GL/gl.h ../m3gdef.hpp
parse-AnimationTracker.o: ../m3ginternal.hpp ../KeyframeSequence.hpp
parse-AnimationTracker.o: ../AnimationController.hpp ../ActiveInterval.hpp
parse-Appearance.o: ../AnimationTrack.hpp ../Object3D.hpp
parse-Appearance.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-Appearance.o: /usr/include/GL/gl.h ../m3gdef.hpp ../m3ginternal.hpp
parse-Appearance.o: ../Appearance.hpp ../Fog.hpp ../KeyframeSequence.hpp
parse-Appearance.o: ../AnimationController.hpp ../ActiveInterval.hpp
parse-Appearance.o: ../CompositingMode.hpp ../PolygonMode.hpp
parse-Appearance.o: ../Texture2D.hpp ../Transformable.hpp ../Quaternion.hpp
parse-Appearance.o: ../Transform.hpp ../Matrix.hpp ../TextureCoord2D.hpp
parse-Appearance.o: ../Material.hpp parse-Object3D.hpp ../Object3D.hpp
parse-Background.o: ../Background.hpp ../Object3D.hpp /usr/include/GL/glew.h
parse-Background.o: /usr/include/GL/glu.h /usr/include/GL/gl.h ../m3gdef.hpp
parse-Background.o: ../m3ginternal.hpp ../Image2D.hpp ../m3gexcept.hpp
parse-Background.o: parse-Background.hpp parse-Object3D.hpp ../Object3D.hpp
parse-Camera.o: ../Camera.hpp ../Node.hpp ../Transformable.hpp
parse-Camera.o: ../Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-Camera.o: /usr/include/GL/gl.h ../m3gdef.hpp ../m3ginternal.hpp
parse-Camera.o: ../Quaternion.hpp ../Transform.hpp ../Matrix.hpp
parse-Camera.o: ../Projection.hpp ../Transform.hpp ../m3gexcept.hpp
parse-Camera.o: parse-Node.hpp ../Node.hpp
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
parse-Image2D.o: ../m3ginternal.hpp
parse-IndexBuffer.o: ../IndexBuffer.hpp /usr/include/GL/glew.h
parse-IndexBuffer.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
parse-IndexBuffer.o: ../Object3D.hpp ../m3gdef.hpp ../m3ginternal.hpp
parse-IndexBuffer.o: parse-Object3D.hpp ../Object3D.hpp
parse-Keyframeequence.o: ../KeyframeSequence.hpp ../Object3D.hpp
parse-Keyframeequence.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-Keyframeequence.o: /usr/include/GL/gl.h ../m3gdef.hpp
parse-Keyframeequence.o: ../m3ginternal.hpp
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
parse-Node.o: ../m3gexcept.hpp
parse-Object3D.o: parse-Object3D.hpp ../Object3D.hpp ../AnimationTrack.hpp
parse-Object3D.o: ../Object3D.hpp /usr/include/GL/glew.h
parse-Object3D.o: /usr/include/GL/glu.h /usr/include/GL/gl.h ../m3gdef.hpp
parse-Object3D.o: ../m3ginternal.hpp ../m3gexcept.hpp
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
parse-Texture2D.o: ../Matrix.hpp ../TextureCoord2D.hpp
parse-Transform.o: ../Object3D.hpp ../Transform.hpp
parse-Transformable.o: parse-Object3D.hpp ../Object3D.hpp
parse-Transformable.o: parse-Transformable.hpp ../Transformable.hpp
parse-Transformable.o: ../Object3D.hpp /usr/include/GL/glew.h
parse-Transformable.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
parse-Transformable.o: ../m3gdef.hpp ../m3ginternal.hpp ../Quaternion.hpp
parse-Transformable.o: ../Transform.hpp ../Matrix.hpp ../m3gexcept.hpp
parse-TriangleStripArray.o: ../TriangleStripArray.hpp ../IndexBuffer.hpp
parse-TriangleStripArray.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
parse-TriangleStripArray.o: /usr/include/GL/gl.h ../Object3D.hpp
parse-TriangleStripArray.o: ../m3gdef.hpp ../m3ginternal.hpp ../m3gexcept.hpp
parse-TriangleStripArray.o: parse-IndexBuffer.hpp ../IndexBuffer.hpp
parse-VertexArray.o: ../VertexArray.hpp /usr/include/GL/glew.h
parse-VertexArray.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
parse-VertexArray.o: ../Object3D.hpp ../m3gdef.hpp ../m3ginternal.hpp
parse-VertexArray.o: parse-Object3D.hpp ../Object3D.hpp ../m3gexcept.hpp
parse-VertexBuffer.o: ../VertexBuffer.hpp /usr/include/GL/glew.h
parse-VertexBuffer.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
parse-VertexBuffer.o: ../Object3D.hpp ../m3gdef.hpp ../m3ginternal.hpp
parse-VertexBuffer.o: ../VertexArray.hpp parse-Object3D.hpp ../Object3D.hpp
parse-World.o: ../World.hpp ../Group.hpp ../Group.hpp ../Node.hpp
parse-World.o: ../Transformable.hpp ../Object3D.hpp /usr/include/GL/glew.h
parse-World.o: /usr/include/GL/glu.h /usr/include/GL/gl.h ../m3gdef.hpp
parse-World.o: ../m3ginternal.hpp ../Quaternion.hpp ../Transform.hpp
parse-World.o: ../Matrix.hpp ../Camera.hpp ../Projection.hpp
parse-World.o: ../Background.hpp parse-Group.hpp
