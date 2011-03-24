LOCAL_PATH := $(call my-dir)

# libpng.a用
include $(CLEAR_VARS)
LOCAL_MODULE    := prebuild-libpng
LOCAL_SRC_FILES := external/lib/libpng.a
include $(PREBUILT_STATIC_LIBRARY)

# libm3g-reader-writer.a用
include $(CLEAR_VARS)
LOCAL_MODULE    := prebuild-libm3g-reader-writer
LOCAL_SRC_FILES := external/lib/libm3g-reader-writer.a
include $(PREBUILT_STATIC_LIBRARY)

# libm3g.so用
include $(CLEAR_VARS)
LOCAL_MODULE    := libm3g
LOCAL_SRC_FILES :=                      \
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
	png-helper.cpp           \
               jpeg-helper.cpp          \
	Transformable.cpp
LOCAL_CPPFLAGS         := -fexceptions -frtti
LOCAL_LDLIBS           := -lGLESv1_CM -llog -lz
LOCAL_STATIC_LIBRARIES := prebuild-libm3g-reader-writer \
                          prebuild-libpng
LOCAL_C_INCLUDES       := ./include ./jni/external/include
include $(BUILD_SHARED_LIBRARY)


