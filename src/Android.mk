LOCAL_PATH := $(call my-dir)

# libm3g.so用
include $(CLEAR_VARS)
LOCAL_MODULE    := libm3g
LOCAL_SRC_FILES :=                      \
AnimationController.cpp  Group.cpp             M3GStruct.cpp     PolygonMode.cpp         Vector.cpp             \
AnimationTrack.cpp       Image2D.cpp           M3GWriter.cpp     Quaternion.cpp          VertexArray.cpp        \
Appearance.cpp           IndexBuffer.cpp       Material.cpp      RayIntersection.cpp     VertexBuffer.cpp       \
Background.cpp           Intersect.cpp         Matrix.cpp        SkinnedMesh.cpp         World.cpp              \
Camera.cpp               Keyframe.cpp          Mesh.cpp          Sprite3D.cpp            m3ginternal.cpp        \
CompositingMode.cpp      KeyframeSequence.cpp  MorphingMesh.cpp  Texture2D.cpp           stb_image_reader.cpp   \
Exception.cpp            Light.cpp             Node.cpp          Transform.cpp           stb_image_writer.cpp   \
Fog.cpp                  Loader.cpp            Object.cpp        Transformable.cpp                              \
Graphics3D.cpp           M3GReader.cpp         Object3D.cpp      TriangleStripArray.cpp
LOCAL_CPPFLAGS         := -fexceptions -frtti
LOCAL_LDLIBS           := -lGLESv1_CM -llog -lz
LOCAL_STATIC_LIBRARIES := 
LOCAL_C_INCLUDES       := ./include ./jni/external/include
include $(BUILD_SHARED_LIBRARY)


