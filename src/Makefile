SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = libm3g.so
CXX = g++
CXXFLAGS = -Wall -g -shared -fPIC -std=c++0x
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
AnimationTrack.o: AnimationController.hpp m3gexcept.hpp
Appearance.o: Appearance.hpp Object3D.hpp /usr/include/GL/glew.h
Appearance.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Appearance.o: m3ginternal.hpp CompositingMode.hpp Fog.hpp Material.hpp
Appearance.o: PolygonMode.hpp Texture2D.hpp Transformable.hpp Quaternion.hpp
Appearance.o: Transform.hpp Matrix.hpp m3gexcept.hpp
Background.o: Background.hpp Object3D.hpp /usr/include/GL/glew.h
Background.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Background.o: m3ginternal.hpp Image2D.hpp m3gexcept.hpp AnimationTrack.hpp
Background.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Bone.o: Bone.hpp Matrix.hpp Group.hpp Node.hpp Transformable.hpp Object3D.hpp
Bone.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Bone.o: m3gdef.hpp m3ginternal.hpp Quaternion.hpp Transform.hpp m3gexcept.hpp
Camera.o: Camera.hpp Node.hpp Transformable.hpp Object3D.hpp
Camera.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Camera.o: m3gdef.hpp m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Camera.o: Vector.hpp m3gexcept.hpp AnimationTrack.hpp AnimationController.hpp
Camera.o: KeyframeSequence.hpp Keyframe.hpp
CompositingMode.o: CompositingMode.hpp Object3D.hpp /usr/include/GL/glew.h
CompositingMode.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
CompositingMode.o: m3ginternal.hpp m3gexcept.hpp
Fog.o: Fog.hpp Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
Fog.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp m3gexcept.hpp
Fog.o: AnimationTrack.hpp AnimationController.hpp KeyframeSequence.hpp
Fog.o: Keyframe.hpp
Graphics3D.o: Graphics3D.hpp World.hpp Group.hpp Node.hpp Transformable.hpp
Graphics3D.o: Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
Graphics3D.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp Quaternion.hpp
Graphics3D.o: Transform.hpp Matrix.hpp Camera.hpp Graphics.hpp Light.hpp
Graphics3D.o: m3gexcept.hpp
Group.o: Group.hpp Node.hpp Transformable.hpp Object3D.hpp
Group.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Group.o: m3gdef.hpp m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Group.o: RayIntersection.hpp Sprite3D.hpp m3gexcept.hpp
Image2D.o: m3gexcept.hpp Image2D.hpp Object3D.hpp /usr/include/GL/glew.h
Image2D.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Image2D.o: m3ginternal.hpp
IndexBuffer.o: IndexBuffer.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
IndexBuffer.o: /usr/include/GL/gl.h Object3D.hpp m3gdef.hpp m3ginternal.hpp
IndexBuffer.o: m3gexcept.hpp
Keyframe.o: Keyframe.hpp Quaternion.hpp m3gexcept.hpp
KeyframeSequence.o: KeyframeSequence.hpp Object3D.hpp /usr/include/GL/glew.h
KeyframeSequence.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
KeyframeSequence.o: m3ginternal.hpp Keyframe.hpp m3gexcept.hpp Quaternion.hpp
Light.o: Light.hpp Node.hpp Transformable.hpp Object3D.hpp
Light.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Light.o: m3gdef.hpp m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Light.o: m3gexcept.hpp AnimationTrack.hpp AnimationController.hpp
Light.o: KeyframeSequence.hpp Keyframe.hpp
Loader.o: Loader.hpp Object3D.hpp /usr/include/GL/glew.h
Loader.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Loader.o: m3ginternal.hpp
Material.o: Material.hpp Object3D.hpp /usr/include/GL/glew.h
Material.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Material.o: m3ginternal.hpp m3gexcept.hpp AnimationTrack.hpp
Material.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Matrix.o: Matrix.hpp Vector.hpp m3gexcept.hpp
Mesh.o: Mesh.hpp Node.hpp Transformable.hpp Object3D.hpp
Mesh.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Mesh.o: m3gdef.hpp m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Mesh.o: VertexBuffer.hpp VertexArray.hpp IndexBuffer.hpp Appearance.hpp
Mesh.o: m3gexcept.hpp
MorphingMesh.o: MorphingMesh.hpp Mesh.hpp Node.hpp Transformable.hpp
MorphingMesh.o: Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
MorphingMesh.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp
MorphingMesh.o: Quaternion.hpp Transform.hpp Matrix.hpp VertexBuffer.hpp
MorphingMesh.o: IndexBuffer.hpp Appearance.hpp
Node.o: Node.hpp Transformable.hpp Object3D.hpp /usr/include/GL/glew.h
Node.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp
Node.o: Quaternion.hpp Transform.hpp Matrix.hpp m3gexcept.hpp
Node.o: AnimationTrack.hpp AnimationController.hpp KeyframeSequence.hpp
Node.o: Keyframe.hpp
Object3D.o: Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
Object3D.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp
Object3D.o: AnimationTrack.hpp m3gexcept.hpp
PolygonMode.o: PolygonMode.hpp Object3D.hpp /usr/include/GL/glew.h
PolygonMode.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
PolygonMode.o: m3ginternal.hpp m3gexcept.hpp
Quaternion.o: Quaternion.hpp m3gexcept.hpp m3ginternal.hpp
RayIntersection.o: RayIntersection.hpp Node.hpp Transformable.hpp
RayIntersection.o: Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
RayIntersection.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp
RayIntersection.o: Quaternion.hpp Transform.hpp Matrix.hpp
SkinnedMesh.o: SkinnedMesh.hpp Mesh.hpp Node.hpp Transformable.hpp
SkinnedMesh.o: Object3D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
SkinnedMesh.o: /usr/include/GL/gl.h m3gdef.hpp m3ginternal.hpp Quaternion.hpp
SkinnedMesh.o: Transform.hpp Matrix.hpp VertexBuffer.hpp IndexBuffer.hpp
SkinnedMesh.o: VertexArray.hpp Bone.hpp m3gexcept.hpp Group.hpp
Sprite3D.o: Sprite3D.hpp Node.hpp Transformable.hpp Object3D.hpp
Sprite3D.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
Sprite3D.o: m3gdef.hpp m3ginternal.hpp Quaternion.hpp Transform.hpp
Sprite3D.o: Matrix.hpp Appearance.hpp Image2D.hpp m3gexcept.hpp
Sprite3D.o: Graphics3D.hpp Vector.hpp AnimationTrack.hpp
Sprite3D.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Texture2D.o: Texture2D.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
Texture2D.o: /usr/include/GL/gl.h Transformable.hpp Object3D.hpp m3gdef.hpp
Texture2D.o: m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Texture2D.o: Image2D.hpp m3gexcept.hpp AnimationTrack.hpp
Texture2D.o: AnimationController.hpp KeyframeSequence.hpp Keyframe.hpp
Transform.o: Transform.hpp Matrix.hpp Vector.hpp m3gexcept.hpp Quaternion.hpp
Transformable.o: Transformable.hpp Object3D.hpp /usr/include/GL/glew.h
Transformable.o: /usr/include/GL/glu.h /usr/include/GL/gl.h m3gdef.hpp
Transformable.o: m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
Transformable.o: m3gexcept.hpp AnimationTrack.hpp AnimationController.hpp
Transformable.o: KeyframeSequence.hpp Keyframe.hpp
TriangleStripArray.o: TriangleStripArray.hpp IndexBuffer.hpp
TriangleStripArray.o: /usr/include/GL/glew.h /usr/include/GL/glu.h
TriangleStripArray.o: /usr/include/GL/gl.h Object3D.hpp m3gdef.hpp
TriangleStripArray.o: m3ginternal.hpp m3gexcept.hpp
Vector.o: Vector.hpp m3gexcept.hpp
VertexArray.o: VertexArray.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
VertexArray.o: /usr/include/GL/gl.h Object3D.hpp m3gdef.hpp m3ginternal.hpp
VertexArray.o: m3gexcept.hpp
VertexBuffer.o: VertexBuffer.hpp /usr/include/GL/glew.h /usr/include/GL/glu.h
VertexBuffer.o: /usr/include/GL/gl.h Object3D.hpp m3gdef.hpp m3ginternal.hpp
VertexBuffer.o: VertexArray.hpp AnimationTrack.hpp AnimationController.hpp
VertexBuffer.o: KeyframeSequence.hpp Keyframe.hpp m3gexcept.hpp
World.o: World.hpp Group.hpp Node.hpp Transformable.hpp Object3D.hpp
World.o: /usr/include/GL/glew.h /usr/include/GL/glu.h /usr/include/GL/gl.h
World.o: m3gdef.hpp m3ginternal.hpp Quaternion.hpp Transform.hpp Matrix.hpp
World.o: Camera.hpp Background.hpp Light.hpp m3gexcept.hpp
m3ginternal.o: m3ginternal.hpp m3gdef.hpp
