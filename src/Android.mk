LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := libm3g
LOCAL_SRC_FILES := 
LOCAL_LDLIBS    := -llog
	AnimationController.cpp  \
	Graphics3D.cpp           \
	Loader.cpp               \
	PolygonMode.cpp          \
	TriangleStripArray.cpp   \
	AnimationTrack.cpp       \
	Group.cpp                \
	Material.cpp             \
	Quaternion.cpp           \
	Vector.cpp               \
	Appearance.cpp           \
	Image2D.cpp              \
	Matrix.cpp               \
	RayIntersection.cpp      \
	VertexArray.cpp          \
	Background.cpp           \
	IndexBuffer.cpp          \
	Mesh.cpp                 \
	SkinnedMesh.cpp          \
	VertexBuffer.cpp         \
	Camera.cpp               \
	Intersect.cpp            \
	MorphingMesh.cpp         \
	Sprite3D.cpp             \
	World.cpp                \
	CompositingMode.cpp      \
	Keyframe.cpp             \
	Node.cpp                 \
	Texture2D.cpp            \
	m3ginternal.cpp          \
	Exception.cpp            \
	KeyframeSequence.cpp     \
	Object.cpp               \
	Transform.cpp            \
	Fog.cpp                  \
	Light.cpp                \
	Object3D.cpp             \
	Transformable.cpp
LOCAL_CPPFLAGS   := -fexceptions -frtti
LOCAL_LDLIBS     := -lGLESv1_CM
LOCAL_C_INCLUDES := internal/jpeg-helper/src       \
                    internal/m3g-reader-writer/src \
                    internal/png-helper/src        \
                    external/include
include $(BUILD_SHARED_LIBRARY)
