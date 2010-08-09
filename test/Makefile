SRCS = $(wildcard *.cpp)
#SRCS = test-Appearance.cpp test-main.cpp	
OBJS = $(SRCS:.cpp=.o)
TARGET = a.out
CXX = g++
CXXFLAGS = -Wall -g -Wno-deprecated -I../src -I../lib
LD = g++
LDFLAGS = -L../src -L../lib
LIBS =  -lm3g  -lUnitTest++ -lglut -lGL -lz

all: $(OBJS)
	$(LD)  $(LDFLAGS) $^ $(LIBS) -o $(TARGET)
	@echo done.

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c

depend:
	makedepend -- $(CXXFLAGS) -- $(SRCS)

clean:
	rm -rf *.o *.so *.a *~ *.out log
	@echo done.




# DO NOT DELETE

test-AnimationController.o: /usr/include/unittest++/UnitTest++.h
test-AnimationController.o: /usr/include/unittest++/Config.h
test-AnimationController.o: /usr/include/unittest++/Test.h
test-AnimationController.o: /usr/include/unittest++/TestDetails.h
test-AnimationController.o: /usr/include/unittest++/TestList.h
test-AnimationController.o: /usr/include/unittest++/TestSuite.h
test-AnimationController.o: /usr/include/unittest++/TestResults.h
test-AnimationController.o: /usr/include/unittest++/TestMacros.h
test-AnimationController.o: /usr/include/unittest++/ExecuteTest.h
test-AnimationController.o: /usr/include/unittest++/MemoryOutStream.h
test-AnimationController.o: /usr/include/unittest++/AssertException.h
test-AnimationController.o: /usr/include/unittest++/CurrentTest.h
test-AnimationController.o: /usr/include/unittest++/CheckMacros.h
test-AnimationController.o: /usr/include/unittest++/Checks.h
test-AnimationController.o: /usr/include/unittest++/TestRunner.h
test-AnimationController.o: /usr/include/unittest++/TimeConstraint.h
test-AnimationController.o: /usr/include/unittest++/TimeHelpers.h
test-AnimationController.o: ../src/AnimationTrack.hpp ../src/Object3D.hpp
test-AnimationController.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp
test-AnimationController.o: ../src/Object.hpp ../src/AnimationController.hpp
test-AnimationController.o: ../src/KeyframeSequence.hpp ../src/Keyframe.hpp
test-AnimationTrack.o: /usr/include/unittest++/UnitTest++.h
test-AnimationTrack.o: /usr/include/unittest++/Config.h
test-AnimationTrack.o: /usr/include/unittest++/Test.h
test-AnimationTrack.o: /usr/include/unittest++/TestDetails.h
test-AnimationTrack.o: /usr/include/unittest++/TestList.h
test-AnimationTrack.o: /usr/include/unittest++/TestSuite.h
test-AnimationTrack.o: /usr/include/unittest++/TestResults.h
test-AnimationTrack.o: /usr/include/unittest++/TestMacros.h
test-AnimationTrack.o: /usr/include/unittest++/ExecuteTest.h
test-AnimationTrack.o: /usr/include/unittest++/MemoryOutStream.h
test-AnimationTrack.o: /usr/include/unittest++/AssertException.h
test-AnimationTrack.o: /usr/include/unittest++/CurrentTest.h
test-AnimationTrack.o: /usr/include/unittest++/CheckMacros.h
test-AnimationTrack.o: /usr/include/unittest++/Checks.h
test-AnimationTrack.o: /usr/include/unittest++/TestRunner.h
test-AnimationTrack.o: /usr/include/unittest++/TimeConstraint.h
test-AnimationTrack.o: /usr/include/unittest++/TimeHelpers.h
test-AnimationTrack.o: ../src/AnimationTrack.hpp ../src/Object3D.hpp
test-AnimationTrack.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp
test-AnimationTrack.o: ../src/Object.hpp ../src/AnimationController.hpp
test-AnimationTrack.o: ../src/KeyframeSequence.hpp ../src/Keyframe.hpp
test-Appearance.o: /usr/include/unittest++/UnitTest++.h
test-Appearance.o: /usr/include/unittest++/Config.h
test-Appearance.o: /usr/include/unittest++/Test.h
test-Appearance.o: /usr/include/unittest++/TestDetails.h
test-Appearance.o: /usr/include/unittest++/TestList.h
test-Appearance.o: /usr/include/unittest++/TestSuite.h
test-Appearance.o: /usr/include/unittest++/TestResults.h
test-Appearance.o: /usr/include/unittest++/TestMacros.h
test-Appearance.o: /usr/include/unittest++/ExecuteTest.h
test-Appearance.o: /usr/include/unittest++/MemoryOutStream.h
test-Appearance.o: /usr/include/unittest++/AssertException.h
test-Appearance.o: /usr/include/unittest++/CurrentTest.h
test-Appearance.o: /usr/include/unittest++/CheckMacros.h
test-Appearance.o: /usr/include/unittest++/Checks.h
test-Appearance.o: /usr/include/unittest++/TestRunner.h
test-Appearance.o: /usr/include/unittest++/TimeConstraint.h
test-Appearance.o: /usr/include/unittest++/TimeHelpers.h
test-Appearance.o: ../src/Appearance.hpp ../src/Object3D.hpp
test-Appearance.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp ../src/Object.hpp
test-Appearance.o: ../src/PolygonMode.hpp ../src/CompositingMode.hpp
test-Appearance.o: ../src/Image2D.hpp ../src/Texture2D.hpp
test-Appearance.o: ../src/Transformable.hpp ../src/Quaternion.hpp
test-Appearance.o: ../src/Transform.hpp ../src/Matrix.hpp ../src/Material.hpp
test-Appearance.o: ../src/Fog.hpp
test-Background.o: /usr/include/unittest++/UnitTest++.h
test-Background.o: /usr/include/unittest++/Config.h
test-Background.o: /usr/include/unittest++/Test.h
test-Background.o: /usr/include/unittest++/TestDetails.h
test-Background.o: /usr/include/unittest++/TestList.h
test-Background.o: /usr/include/unittest++/TestSuite.h
test-Background.o: /usr/include/unittest++/TestResults.h
test-Background.o: /usr/include/unittest++/TestMacros.h
test-Background.o: /usr/include/unittest++/ExecuteTest.h
test-Background.o: /usr/include/unittest++/MemoryOutStream.h
test-Background.o: /usr/include/unittest++/AssertException.h
test-Background.o: /usr/include/unittest++/CurrentTest.h
test-Background.o: /usr/include/unittest++/CheckMacros.h
test-Background.o: /usr/include/unittest++/Checks.h
test-Background.o: /usr/include/unittest++/TestRunner.h
test-Background.o: /usr/include/unittest++/TimeConstraint.h
test-Background.o: /usr/include/unittest++/TimeHelpers.h
test-Background.o: ../src/Background.hpp ../src/Object3D.hpp
test-Background.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp ../src/Object.hpp
test-Background.o: ../src/Image2D.hpp
test-Camera.o: /usr/include/unittest++/UnitTest++.h
test-Camera.o: /usr/include/unittest++/Config.h
test-Camera.o: /usr/include/unittest++/Test.h
test-Camera.o: /usr/include/unittest++/TestDetails.h
test-Camera.o: /usr/include/unittest++/TestList.h
test-Camera.o: /usr/include/unittest++/TestSuite.h
test-Camera.o: /usr/include/unittest++/TestResults.h
test-Camera.o: /usr/include/unittest++/TestMacros.h
test-Camera.o: /usr/include/unittest++/ExecuteTest.h
test-Camera.o: /usr/include/unittest++/MemoryOutStream.h
test-Camera.o: /usr/include/unittest++/AssertException.h
test-Camera.o: /usr/include/unittest++/CurrentTest.h
test-Camera.o: /usr/include/unittest++/CheckMacros.h
test-Camera.o: /usr/include/unittest++/Checks.h
test-Camera.o: /usr/include/unittest++/TestRunner.h
test-Camera.o: /usr/include/unittest++/TimeConstraint.h
test-Camera.o: /usr/include/unittest++/TimeHelpers.h ../src/Camera.hpp
test-Camera.o: ../src/Node.hpp ../src/Transformable.hpp ../src/Object3D.hpp
test-Camera.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp ../src/Object.hpp
test-Camera.o: ../src/Quaternion.hpp ../src/Transform.hpp ../src/Matrix.hpp
test-Camera.o: ../src/Group.hpp
test-CompositingMode.o: /usr/include/unittest++/UnitTest++.h
test-CompositingMode.o: /usr/include/unittest++/Config.h
test-CompositingMode.o: /usr/include/unittest++/Test.h
test-CompositingMode.o: /usr/include/unittest++/TestDetails.h
test-CompositingMode.o: /usr/include/unittest++/TestList.h
test-CompositingMode.o: /usr/include/unittest++/TestSuite.h
test-CompositingMode.o: /usr/include/unittest++/TestResults.h
test-CompositingMode.o: /usr/include/unittest++/TestMacros.h
test-CompositingMode.o: /usr/include/unittest++/ExecuteTest.h
test-CompositingMode.o: /usr/include/unittest++/MemoryOutStream.h
test-CompositingMode.o: /usr/include/unittest++/AssertException.h
test-CompositingMode.o: /usr/include/unittest++/CurrentTest.h
test-CompositingMode.o: /usr/include/unittest++/CheckMacros.h
test-CompositingMode.o: /usr/include/unittest++/Checks.h
test-CompositingMode.o: /usr/include/unittest++/TestRunner.h
test-CompositingMode.o: /usr/include/unittest++/TimeConstraint.h
test-CompositingMode.o: /usr/include/unittest++/TimeHelpers.h
test-CompositingMode.o: ../src/CompositingMode.hpp ../src/Object3D.hpp
test-CompositingMode.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp
test-CompositingMode.o: ../src/Object.hpp
test-Exception.o: /usr/include/unittest++/UnitTest++.h
test-Exception.o: /usr/include/unittest++/Config.h
test-Exception.o: /usr/include/unittest++/Test.h
test-Exception.o: /usr/include/unittest++/TestDetails.h
test-Exception.o: /usr/include/unittest++/TestList.h
test-Exception.o: /usr/include/unittest++/TestSuite.h
test-Exception.o: /usr/include/unittest++/TestResults.h
test-Exception.o: /usr/include/unittest++/TestMacros.h
test-Exception.o: /usr/include/unittest++/ExecuteTest.h
test-Exception.o: /usr/include/unittest++/MemoryOutStream.h
test-Exception.o: /usr/include/unittest++/AssertException.h
test-Exception.o: /usr/include/unittest++/CurrentTest.h
test-Exception.o: /usr/include/unittest++/CheckMacros.h
test-Exception.o: /usr/include/unittest++/Checks.h
test-Exception.o: /usr/include/unittest++/TestRunner.h
test-Exception.o: /usr/include/unittest++/TimeConstraint.h
test-Exception.o: /usr/include/unittest++/TimeHelpers.h ../src/Exception.hpp
test-Fog.o: /usr/include/unittest++/UnitTest++.h
test-Fog.o: /usr/include/unittest++/Config.h /usr/include/unittest++/Test.h
test-Fog.o: /usr/include/unittest++/TestDetails.h
test-Fog.o: /usr/include/unittest++/TestList.h
test-Fog.o: /usr/include/unittest++/TestSuite.h
test-Fog.o: /usr/include/unittest++/TestResults.h
test-Fog.o: /usr/include/unittest++/TestMacros.h
test-Fog.o: /usr/include/unittest++/ExecuteTest.h
test-Fog.o: /usr/include/unittest++/MemoryOutStream.h
test-Fog.o: /usr/include/unittest++/AssertException.h
test-Fog.o: /usr/include/unittest++/CurrentTest.h
test-Fog.o: /usr/include/unittest++/CheckMacros.h
test-Fog.o: /usr/include/unittest++/Checks.h
test-Fog.o: /usr/include/unittest++/TestRunner.h
test-Fog.o: /usr/include/unittest++/TimeConstraint.h
test-Fog.o: /usr/include/unittest++/TimeHelpers.h ../src/Fog.hpp
test-Fog.o: ../src/Object3D.hpp ../src/m3gdef.hpp ../src/m3ginternal.hpp
test-Fog.o: ../src/Object.hpp
test-Group.o: /usr/include/unittest++/UnitTest++.h
test-Group.o: /usr/include/unittest++/Config.h /usr/include/unittest++/Test.h
test-Group.o: /usr/include/unittest++/TestDetails.h
test-Group.o: /usr/include/unittest++/TestList.h
test-Group.o: /usr/include/unittest++/TestSuite.h
test-Group.o: /usr/include/unittest++/TestResults.h
test-Group.o: /usr/include/unittest++/TestMacros.h
test-Group.o: /usr/include/unittest++/ExecuteTest.h
test-Group.o: /usr/include/unittest++/MemoryOutStream.h
test-Group.o: /usr/include/unittest++/AssertException.h
test-Group.o: /usr/include/unittest++/CurrentTest.h
test-Group.o: /usr/include/unittest++/CheckMacros.h
test-Group.o: /usr/include/unittest++/Checks.h
test-Group.o: /usr/include/unittest++/TestRunner.h
test-Group.o: /usr/include/unittest++/TimeConstraint.h
test-Group.o: /usr/include/unittest++/TimeHelpers.h ../src/Group.hpp
test-Group.o: ../src/Node.hpp ../src/Transformable.hpp ../src/Object3D.hpp
test-Group.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp ../src/Object.hpp
test-Group.o: ../src/Quaternion.hpp ../src/Transform.hpp ../src/Matrix.hpp
test-Image2D.o: /usr/include/unittest++/UnitTest++.h
test-Image2D.o: /usr/include/unittest++/Config.h
test-Image2D.o: /usr/include/unittest++/Test.h
test-Image2D.o: /usr/include/unittest++/TestDetails.h
test-Image2D.o: /usr/include/unittest++/TestList.h
test-Image2D.o: /usr/include/unittest++/TestSuite.h
test-Image2D.o: /usr/include/unittest++/TestResults.h
test-Image2D.o: /usr/include/unittest++/TestMacros.h
test-Image2D.o: /usr/include/unittest++/ExecuteTest.h
test-Image2D.o: /usr/include/unittest++/MemoryOutStream.h
test-Image2D.o: /usr/include/unittest++/AssertException.h
test-Image2D.o: /usr/include/unittest++/CurrentTest.h
test-Image2D.o: /usr/include/unittest++/CheckMacros.h
test-Image2D.o: /usr/include/unittest++/Checks.h
test-Image2D.o: /usr/include/unittest++/TestRunner.h
test-Image2D.o: /usr/include/unittest++/TimeConstraint.h
test-Image2D.o: /usr/include/unittest++/TimeHelpers.h ../src/Image2D.hpp
test-Image2D.o: ../src/Object3D.hpp ../src/m3gdef.hpp ../src/m3ginternal.hpp
test-Image2D.o: ../src/Object.hpp ../src/Exception.hpp ../src/Loader.hpp
test-Image2D.o: ../src/M3GReader.hpp ../src/InMemoryStream.hpp
test-Image2D.o: ../src/M3GStruct.hpp ../src/m3g.hpp ../src/Graphics3D.hpp
test-Image2D.o: ../src/AnimationController.hpp ../src/AnimationTrack.hpp
test-Image2D.o: ../src/Appearance.hpp ../src/Background.hpp
test-Image2D.o: ../src/CompositingMode.hpp ../src/Fog.hpp
test-Image2D.o: ../src/IndexBuffer.hpp ../src/TriangleStripArray.hpp
test-Image2D.o: ../src/KeyframeSequence.hpp ../src/Keyframe.hpp
test-Image2D.o: ../src/Material.hpp ../src/PolygonMode.hpp
test-Image2D.o: ../src/Transformable.hpp ../src/Quaternion.hpp
test-Image2D.o: ../src/Transform.hpp ../src/Matrix.hpp ../src/Node.hpp
test-Image2D.o: ../src/Camera.hpp ../src/Group.hpp ../src/World.hpp
test-Image2D.o: ../src/Light.hpp ../src/Mesh.hpp ../src/MorphingMesh.hpp
test-Image2D.o: ../src/SkinnedMesh.hpp ../src/BoneIndex.hpp
test-Image2D.o: ../src/Sprite3D.hpp ../src/Texture2D.hpp
test-Image2D.o: ../src/VertexArray.hpp ../src/VertexBuffer.hpp
test-Image2D.o: ../src/RayIntersection.hpp ../src/Vector.hpp
test-Image2D.o: ../src/RenderState.hpp
test-Intersect.o: /usr/include/unittest++/UnitTest++.h
test-Intersect.o: /usr/include/unittest++/Config.h
test-Intersect.o: /usr/include/unittest++/Test.h
test-Intersect.o: /usr/include/unittest++/TestDetails.h
test-Intersect.o: /usr/include/unittest++/TestList.h
test-Intersect.o: /usr/include/unittest++/TestSuite.h
test-Intersect.o: /usr/include/unittest++/TestResults.h
test-Intersect.o: /usr/include/unittest++/TestMacros.h
test-Intersect.o: /usr/include/unittest++/ExecuteTest.h
test-Intersect.o: /usr/include/unittest++/MemoryOutStream.h
test-Intersect.o: /usr/include/unittest++/AssertException.h
test-Intersect.o: /usr/include/unittest++/CurrentTest.h
test-Intersect.o: /usr/include/unittest++/CheckMacros.h
test-Intersect.o: /usr/include/unittest++/Checks.h
test-Intersect.o: /usr/include/unittest++/TestRunner.h
test-Intersect.o: /usr/include/unittest++/TimeConstraint.h
test-Intersect.o: /usr/include/unittest++/TimeHelpers.h ../src/Intersect.hpp
test-Intersect.o: ../src/Vector.hpp
test-Keyframe.o: /usr/include/unittest++/UnitTest++.h
test-Keyframe.o: /usr/include/unittest++/Config.h
test-Keyframe.o: /usr/include/unittest++/Test.h
test-Keyframe.o: /usr/include/unittest++/TestDetails.h
test-Keyframe.o: /usr/include/unittest++/TestList.h
test-Keyframe.o: /usr/include/unittest++/TestSuite.h
test-Keyframe.o: /usr/include/unittest++/TestResults.h
test-Keyframe.o: /usr/include/unittest++/TestMacros.h
test-Keyframe.o: /usr/include/unittest++/ExecuteTest.h
test-Keyframe.o: /usr/include/unittest++/MemoryOutStream.h
test-Keyframe.o: /usr/include/unittest++/AssertException.h
test-Keyframe.o: /usr/include/unittest++/CurrentTest.h
test-Keyframe.o: /usr/include/unittest++/CheckMacros.h
test-Keyframe.o: /usr/include/unittest++/Checks.h
test-Keyframe.o: /usr/include/unittest++/TestRunner.h
test-Keyframe.o: /usr/include/unittest++/TimeConstraint.h
test-Keyframe.o: /usr/include/unittest++/TimeHelpers.h ../src/Keyframe.hpp
test-Keyframe.o: ../src/Quaternion.hpp
test-KeyframeSequence.o: /usr/include/unittest++/UnitTest++.h
test-KeyframeSequence.o: /usr/include/unittest++/Config.h
test-KeyframeSequence.o: /usr/include/unittest++/Test.h
test-KeyframeSequence.o: /usr/include/unittest++/TestDetails.h
test-KeyframeSequence.o: /usr/include/unittest++/TestList.h
test-KeyframeSequence.o: /usr/include/unittest++/TestSuite.h
test-KeyframeSequence.o: /usr/include/unittest++/TestResults.h
test-KeyframeSequence.o: /usr/include/unittest++/TestMacros.h
test-KeyframeSequence.o: /usr/include/unittest++/ExecuteTest.h
test-KeyframeSequence.o: /usr/include/unittest++/MemoryOutStream.h
test-KeyframeSequence.o: /usr/include/unittest++/AssertException.h
test-KeyframeSequence.o: /usr/include/unittest++/CurrentTest.h
test-KeyframeSequence.o: /usr/include/unittest++/CheckMacros.h
test-KeyframeSequence.o: /usr/include/unittest++/Checks.h
test-KeyframeSequence.o: /usr/include/unittest++/TestRunner.h
test-KeyframeSequence.o: /usr/include/unittest++/TimeConstraint.h
test-KeyframeSequence.o: /usr/include/unittest++/TimeHelpers.h
test-KeyframeSequence.o: ../src/KeyframeSequence.hpp ../src/Object3D.hpp
test-KeyframeSequence.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp
test-KeyframeSequence.o: ../src/Object.hpp ../src/Keyframe.hpp
test-Light.o: /usr/include/unittest++/UnitTest++.h
test-Light.o: /usr/include/unittest++/Config.h /usr/include/unittest++/Test.h
test-Light.o: /usr/include/unittest++/TestDetails.h
test-Light.o: /usr/include/unittest++/TestList.h
test-Light.o: /usr/include/unittest++/TestSuite.h
test-Light.o: /usr/include/unittest++/TestResults.h
test-Light.o: /usr/include/unittest++/TestMacros.h
test-Light.o: /usr/include/unittest++/ExecuteTest.h
test-Light.o: /usr/include/unittest++/MemoryOutStream.h
test-Light.o: /usr/include/unittest++/AssertException.h
test-Light.o: /usr/include/unittest++/CurrentTest.h
test-Light.o: /usr/include/unittest++/CheckMacros.h
test-Light.o: /usr/include/unittest++/Checks.h
test-Light.o: /usr/include/unittest++/TestRunner.h
test-Light.o: /usr/include/unittest++/TimeConstraint.h
test-Light.o: /usr/include/unittest++/TimeHelpers.h ../src/Light.hpp
test-Light.o: ../src/Node.hpp ../src/Transformable.hpp ../src/Object3D.hpp
test-Light.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp ../src/Object.hpp
test-Light.o: ../src/Quaternion.hpp ../src/Transform.hpp ../src/Matrix.hpp
test-Loader.o: /usr/include/unittest++/UnitTest++.h
test-Loader.o: /usr/include/unittest++/Config.h
test-Loader.o: /usr/include/unittest++/Test.h
test-Loader.o: /usr/include/unittest++/TestDetails.h
test-Loader.o: /usr/include/unittest++/TestList.h
test-Loader.o: /usr/include/unittest++/TestSuite.h
test-Loader.o: /usr/include/unittest++/TestResults.h
test-Loader.o: /usr/include/unittest++/TestMacros.h
test-Loader.o: /usr/include/unittest++/ExecuteTest.h
test-Loader.o: /usr/include/unittest++/MemoryOutStream.h
test-Loader.o: /usr/include/unittest++/AssertException.h
test-Loader.o: /usr/include/unittest++/CurrentTest.h
test-Loader.o: /usr/include/unittest++/CheckMacros.h
test-Loader.o: /usr/include/unittest++/Checks.h
test-Loader.o: /usr/include/unittest++/TestRunner.h
test-Loader.o: /usr/include/unittest++/TimeConstraint.h
test-Loader.o: /usr/include/unittest++/TimeHelpers.h ../src/Loader.hpp
test-Loader.o: ../src/Object.hpp ../src/M3GReader.hpp
test-Loader.o: ../src/InMemoryStream.hpp ../src/M3GStruct.hpp ../src/m3g.hpp
test-Loader.o: ../src/m3gdef.hpp ../src/Graphics3D.hpp ../src/Object3D.hpp
test-Loader.o: ../src/m3ginternal.hpp ../src/AnimationController.hpp
test-Loader.o: ../src/AnimationTrack.hpp ../src/Appearance.hpp
test-Loader.o: ../src/Background.hpp ../src/CompositingMode.hpp
test-Loader.o: ../src/Fog.hpp ../src/Image2D.hpp ../src/IndexBuffer.hpp
test-Loader.o: ../src/TriangleStripArray.hpp ../src/KeyframeSequence.hpp
test-Loader.o: ../src/Keyframe.hpp ../src/Material.hpp ../src/PolygonMode.hpp
test-Loader.o: ../src/Transformable.hpp ../src/Quaternion.hpp
test-Loader.o: ../src/Transform.hpp ../src/Matrix.hpp ../src/Node.hpp
test-Loader.o: ../src/Camera.hpp ../src/Group.hpp ../src/World.hpp
test-Loader.o: ../src/Light.hpp ../src/Mesh.hpp ../src/MorphingMesh.hpp
test-Loader.o: ../src/SkinnedMesh.hpp ../src/BoneIndex.hpp
test-Loader.o: ../src/Sprite3D.hpp ../src/Texture2D.hpp
test-Loader.o: ../src/VertexArray.hpp ../src/VertexBuffer.hpp
test-Loader.o: ../src/RayIntersection.hpp ../src/Vector.hpp
test-Loader.o: ../src/Exception.hpp ../src/RenderState.hpp
test-Material.o: /usr/include/unittest++/UnitTest++.h
test-Material.o: /usr/include/unittest++/Config.h
test-Material.o: /usr/include/unittest++/Test.h
test-Material.o: /usr/include/unittest++/TestDetails.h
test-Material.o: /usr/include/unittest++/TestList.h
test-Material.o: /usr/include/unittest++/TestSuite.h
test-Material.o: /usr/include/unittest++/TestResults.h
test-Material.o: /usr/include/unittest++/TestMacros.h
test-Material.o: /usr/include/unittest++/ExecuteTest.h
test-Material.o: /usr/include/unittest++/MemoryOutStream.h
test-Material.o: /usr/include/unittest++/AssertException.h
test-Material.o: /usr/include/unittest++/CurrentTest.h
test-Material.o: /usr/include/unittest++/CheckMacros.h
test-Material.o: /usr/include/unittest++/Checks.h
test-Material.o: /usr/include/unittest++/TestRunner.h
test-Material.o: /usr/include/unittest++/TimeConstraint.h
test-Material.o: /usr/include/unittest++/TimeHelpers.h ../src/Material.hpp
test-Material.o: ../src/Object3D.hpp ../src/m3gdef.hpp ../src/m3ginternal.hpp
test-Material.o: ../src/Object.hpp
test-Matrix.o: /usr/include/unittest++/UnitTest++.h
test-Matrix.o: /usr/include/unittest++/Config.h
test-Matrix.o: /usr/include/unittest++/Test.h
test-Matrix.o: /usr/include/unittest++/TestDetails.h
test-Matrix.o: /usr/include/unittest++/TestList.h
test-Matrix.o: /usr/include/unittest++/TestSuite.h
test-Matrix.o: /usr/include/unittest++/TestResults.h
test-Matrix.o: /usr/include/unittest++/TestMacros.h
test-Matrix.o: /usr/include/unittest++/ExecuteTest.h
test-Matrix.o: /usr/include/unittest++/MemoryOutStream.h
test-Matrix.o: /usr/include/unittest++/AssertException.h
test-Matrix.o: /usr/include/unittest++/CurrentTest.h
test-Matrix.o: /usr/include/unittest++/CheckMacros.h
test-Matrix.o: /usr/include/unittest++/Checks.h
test-Matrix.o: /usr/include/unittest++/TestRunner.h
test-Matrix.o: /usr/include/unittest++/TimeConstraint.h
test-Matrix.o: /usr/include/unittest++/TimeHelpers.h ../src/Matrix.hpp
test-Matrix.o: ../src/Vector.hpp
test-MemoryReader.o: ../src/MemoryReader.hpp /usr/include/png.h
test-MemoryReader.o: /usr/include/zlib.h /usr/include/zconf.h
test-MemoryReader.o: /usr/include/zlibdefs.h /usr/include/sys/types.h
test-MemoryReader.o: /usr/include/features.h /usr/include/bits/predefs.h
test-MemoryReader.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
test-MemoryReader.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
test-MemoryReader.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
test-MemoryReader.o: /usr/include/time.h /usr/include/endian.h
test-MemoryReader.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
test-MemoryReader.o: /usr/include/sys/select.h /usr/include/bits/select.h
test-MemoryReader.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
test-MemoryReader.o: /usr/include/sys/sysmacros.h
test-MemoryReader.o: /usr/include/bits/pthreadtypes.h /usr/include/unistd.h
test-MemoryReader.o: /usr/include/bits/posix_opt.h
test-MemoryReader.o: /usr/include/bits/confname.h /usr/include/getopt.h
test-MemoryReader.o: /usr/include/pngconf.h /usr/include/stdio.h
test-MemoryReader.o: /usr/include/libio.h /usr/include/_G_config.h
test-MemoryReader.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
test-MemoryReader.o: /usr/include/bits/sys_errlist.h /usr/include/setjmp.h
test-MemoryReader.o: /usr/include/bits/setjmp.h /usr/include/string.h
test-MemoryReader.o: /usr/include/xlocale.h
test-MemoryReader.o: /usr/include/unittest++/UnitTest++.h
test-MemoryReader.o: /usr/include/unittest++/Config.h
test-MemoryReader.o: /usr/include/unittest++/Test.h
test-MemoryReader.o: /usr/include/unittest++/TestDetails.h
test-MemoryReader.o: /usr/include/unittest++/TestList.h
test-MemoryReader.o: /usr/include/unittest++/TestSuite.h
test-MemoryReader.o: /usr/include/unittest++/TestResults.h
test-MemoryReader.o: /usr/include/unittest++/TestMacros.h
test-MemoryReader.o: /usr/include/unittest++/ExecuteTest.h
test-MemoryReader.o: /usr/include/unittest++/MemoryOutStream.h
test-MemoryReader.o: /usr/include/unittest++/AssertException.h
test-MemoryReader.o: /usr/include/unittest++/CurrentTest.h
test-MemoryReader.o: /usr/include/unittest++/CheckMacros.h
test-MemoryReader.o: /usr/include/unittest++/Checks.h
test-MemoryReader.o: /usr/include/unittest++/TestRunner.h
test-MemoryReader.o: /usr/include/unittest++/TimeConstraint.h
test-MemoryReader.o: /usr/include/unittest++/TimeHelpers.h
test-Mesh.o: /usr/include/unittest++/UnitTest++.h
test-Mesh.o: /usr/include/unittest++/Config.h /usr/include/unittest++/Test.h
test-Mesh.o: /usr/include/unittest++/TestDetails.h
test-Mesh.o: /usr/include/unittest++/TestList.h
test-Mesh.o: /usr/include/unittest++/TestSuite.h
test-Mesh.o: /usr/include/unittest++/TestResults.h
test-Mesh.o: /usr/include/unittest++/TestMacros.h
test-Mesh.o: /usr/include/unittest++/ExecuteTest.h
test-Mesh.o: /usr/include/unittest++/MemoryOutStream.h
test-Mesh.o: /usr/include/unittest++/AssertException.h
test-Mesh.o: /usr/include/unittest++/CurrentTest.h
test-Mesh.o: /usr/include/unittest++/CheckMacros.h
test-Mesh.o: /usr/include/unittest++/Checks.h
test-Mesh.o: /usr/include/unittest++/TestRunner.h
test-Mesh.o: /usr/include/unittest++/TimeConstraint.h
test-Mesh.o: /usr/include/unittest++/TimeHelpers.h ../src/Mesh.hpp
test-Mesh.o: ../src/Node.hpp ../src/Transformable.hpp ../src/Object3D.hpp
test-Mesh.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp ../src/Object.hpp
test-Mesh.o: ../src/Quaternion.hpp ../src/Transform.hpp ../src/Matrix.hpp
test-Mesh.o: ../src/VertexArray.hpp ../src/VertexBuffer.hpp
test-Mesh.o: ../src/TriangleStripArray.hpp ../src/IndexBuffer.hpp
test-Mesh.o: ../src/Appearance.hpp ../src/RayIntersection.hpp
test-Mesh.o: ../src/Vector.hpp
test-MorphingMesh.o: /usr/include/unittest++/UnitTest++.h
test-MorphingMesh.o: /usr/include/unittest++/Config.h
test-MorphingMesh.o: /usr/include/unittest++/Test.h
test-MorphingMesh.o: /usr/include/unittest++/TestDetails.h
test-MorphingMesh.o: /usr/include/unittest++/TestList.h
test-MorphingMesh.o: /usr/include/unittest++/TestSuite.h
test-MorphingMesh.o: /usr/include/unittest++/TestResults.h
test-MorphingMesh.o: /usr/include/unittest++/TestMacros.h
test-MorphingMesh.o: /usr/include/unittest++/ExecuteTest.h
test-MorphingMesh.o: /usr/include/unittest++/MemoryOutStream.h
test-MorphingMesh.o: /usr/include/unittest++/AssertException.h
test-MorphingMesh.o: /usr/include/unittest++/CurrentTest.h
test-MorphingMesh.o: /usr/include/unittest++/CheckMacros.h
test-MorphingMesh.o: /usr/include/unittest++/Checks.h
test-MorphingMesh.o: /usr/include/unittest++/TestRunner.h
test-MorphingMesh.o: /usr/include/unittest++/TimeConstraint.h
test-MorphingMesh.o: /usr/include/unittest++/TimeHelpers.h
test-MorphingMesh.o: ../src/MorphingMesh.hpp ../src/Mesh.hpp ../src/Node.hpp
test-MorphingMesh.o: ../src/Transformable.hpp ../src/Object3D.hpp
test-MorphingMesh.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp
test-MorphingMesh.o: ../src/Object.hpp ../src/Quaternion.hpp
test-MorphingMesh.o: ../src/Transform.hpp ../src/Matrix.hpp
test-MorphingMesh.o: ../src/VertexArray.hpp ../src/VertexBuffer.hpp
test-MorphingMesh.o: ../src/TriangleStripArray.hpp ../src/IndexBuffer.hpp
test-MorphingMesh.o: ../src/Appearance.hpp ../src/Group.hpp
test-Node.o: /usr/include/unittest++/UnitTest++.h
test-Node.o: /usr/include/unittest++/Config.h /usr/include/unittest++/Test.h
test-Node.o: /usr/include/unittest++/TestDetails.h
test-Node.o: /usr/include/unittest++/TestList.h
test-Node.o: /usr/include/unittest++/TestSuite.h
test-Node.o: /usr/include/unittest++/TestResults.h
test-Node.o: /usr/include/unittest++/TestMacros.h
test-Node.o: /usr/include/unittest++/ExecuteTest.h
test-Node.o: /usr/include/unittest++/MemoryOutStream.h
test-Node.o: /usr/include/unittest++/AssertException.h
test-Node.o: /usr/include/unittest++/CurrentTest.h
test-Node.o: /usr/include/unittest++/CheckMacros.h
test-Node.o: /usr/include/unittest++/Checks.h
test-Node.o: /usr/include/unittest++/TestRunner.h
test-Node.o: /usr/include/unittest++/TimeConstraint.h
test-Node.o: /usr/include/unittest++/TimeHelpers.h ../src/Node.hpp
test-Node.o: ../src/Transformable.hpp ../src/Object3D.hpp ../src/m3gdef.hpp
test-Node.o: ../src/m3ginternal.hpp ../src/Object.hpp ../src/Quaternion.hpp
test-Node.o: ../src/Transform.hpp ../src/Matrix.hpp ../src/Group.hpp
test-Node.o: ../src/World.hpp
test-Object.o: /usr/include/unittest++/UnitTest++.h
test-Object.o: /usr/include/unittest++/Config.h
test-Object.o: /usr/include/unittest++/Test.h
test-Object.o: /usr/include/unittest++/TestDetails.h
test-Object.o: /usr/include/unittest++/TestList.h
test-Object.o: /usr/include/unittest++/TestSuite.h
test-Object.o: /usr/include/unittest++/TestResults.h
test-Object.o: /usr/include/unittest++/TestMacros.h
test-Object.o: /usr/include/unittest++/ExecuteTest.h
test-Object.o: /usr/include/unittest++/MemoryOutStream.h
test-Object.o: /usr/include/unittest++/AssertException.h
test-Object.o: /usr/include/unittest++/CurrentTest.h
test-Object.o: /usr/include/unittest++/CheckMacros.h
test-Object.o: /usr/include/unittest++/Checks.h
test-Object.o: /usr/include/unittest++/TestRunner.h
test-Object.o: /usr/include/unittest++/TimeConstraint.h
test-Object.o: /usr/include/unittest++/TimeHelpers.h ../src/Object.hpp
test-Object3D.o: /usr/include/unittest++/UnitTest++.h
test-Object3D.o: /usr/include/unittest++/Config.h
test-Object3D.o: /usr/include/unittest++/Test.h
test-Object3D.o: /usr/include/unittest++/TestDetails.h
test-Object3D.o: /usr/include/unittest++/TestList.h
test-Object3D.o: /usr/include/unittest++/TestSuite.h
test-Object3D.o: /usr/include/unittest++/TestResults.h
test-Object3D.o: /usr/include/unittest++/TestMacros.h
test-Object3D.o: /usr/include/unittest++/ExecuteTest.h
test-Object3D.o: /usr/include/unittest++/MemoryOutStream.h
test-Object3D.o: /usr/include/unittest++/AssertException.h
test-Object3D.o: /usr/include/unittest++/CurrentTest.h
test-Object3D.o: /usr/include/unittest++/CheckMacros.h
test-Object3D.o: /usr/include/unittest++/Checks.h
test-Object3D.o: /usr/include/unittest++/TestRunner.h
test-Object3D.o: /usr/include/unittest++/TimeConstraint.h
test-Object3D.o: /usr/include/unittest++/TimeHelpers.h ../src/Object3D.hpp
test-Object3D.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp ../src/Object.hpp
test-Object3D.o: ../src/AnimationTrack.hpp ../src/KeyframeSequence.hpp
test-Object3D.o: ../src/Keyframe.hpp
test-PolygonMode.o: /usr/include/unittest++/UnitTest++.h
test-PolygonMode.o: /usr/include/unittest++/Config.h
test-PolygonMode.o: /usr/include/unittest++/Test.h
test-PolygonMode.o: /usr/include/unittest++/TestDetails.h
test-PolygonMode.o: /usr/include/unittest++/TestList.h
test-PolygonMode.o: /usr/include/unittest++/TestSuite.h
test-PolygonMode.o: /usr/include/unittest++/TestResults.h
test-PolygonMode.o: /usr/include/unittest++/TestMacros.h
test-PolygonMode.o: /usr/include/unittest++/ExecuteTest.h
test-PolygonMode.o: /usr/include/unittest++/MemoryOutStream.h
test-PolygonMode.o: /usr/include/unittest++/AssertException.h
test-PolygonMode.o: /usr/include/unittest++/CurrentTest.h
test-PolygonMode.o: /usr/include/unittest++/CheckMacros.h
test-PolygonMode.o: /usr/include/unittest++/Checks.h
test-PolygonMode.o: /usr/include/unittest++/TestRunner.h
test-PolygonMode.o: /usr/include/unittest++/TimeConstraint.h
test-PolygonMode.o: /usr/include/unittest++/TimeHelpers.h
test-PolygonMode.o: ../src/PolygonMode.hpp ../src/Object3D.hpp
test-PolygonMode.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp
test-PolygonMode.o: ../src/Object.hpp
test-Quaternion.o: /usr/include/unittest++/UnitTest++.h
test-Quaternion.o: /usr/include/unittest++/Config.h
test-Quaternion.o: /usr/include/unittest++/Test.h
test-Quaternion.o: /usr/include/unittest++/TestDetails.h
test-Quaternion.o: /usr/include/unittest++/TestList.h
test-Quaternion.o: /usr/include/unittest++/TestSuite.h
test-Quaternion.o: /usr/include/unittest++/TestResults.h
test-Quaternion.o: /usr/include/unittest++/TestMacros.h
test-Quaternion.o: /usr/include/unittest++/ExecuteTest.h
test-Quaternion.o: /usr/include/unittest++/MemoryOutStream.h
test-Quaternion.o: /usr/include/unittest++/AssertException.h
test-Quaternion.o: /usr/include/unittest++/CurrentTest.h
test-Quaternion.o: /usr/include/unittest++/CheckMacros.h
test-Quaternion.o: /usr/include/unittest++/Checks.h
test-Quaternion.o: /usr/include/unittest++/TestRunner.h
test-Quaternion.o: /usr/include/unittest++/TimeConstraint.h
test-Quaternion.o: /usr/include/unittest++/TimeHelpers.h
test-Quaternion.o: ../src/Quaternion.hpp ../src/Matrix.hpp ../src/Vector.hpp
test-RayIntersect.o: /usr/include/unittest++/UnitTest++.h
test-RayIntersect.o: /usr/include/unittest++/Config.h
test-RayIntersect.o: /usr/include/unittest++/Test.h
test-RayIntersect.o: /usr/include/unittest++/TestDetails.h
test-RayIntersect.o: /usr/include/unittest++/TestList.h
test-RayIntersect.o: /usr/include/unittest++/TestSuite.h
test-RayIntersect.o: /usr/include/unittest++/TestResults.h
test-RayIntersect.o: /usr/include/unittest++/TestMacros.h
test-RayIntersect.o: /usr/include/unittest++/ExecuteTest.h
test-RayIntersect.o: /usr/include/unittest++/MemoryOutStream.h
test-RayIntersect.o: /usr/include/unittest++/AssertException.h
test-RayIntersect.o: /usr/include/unittest++/CurrentTest.h
test-RayIntersect.o: /usr/include/unittest++/CheckMacros.h
test-RayIntersect.o: /usr/include/unittest++/Checks.h
test-RayIntersect.o: /usr/include/unittest++/TestRunner.h
test-RayIntersect.o: /usr/include/unittest++/TimeConstraint.h
test-RayIntersect.o: /usr/include/unittest++/TimeHelpers.h
test-RayIntersect.o: ../src/Intersect.hpp ../src/VertexArray.hpp
test-RayIntersect.o: ../src/Object3D.hpp ../src/m3gdef.hpp
test-RayIntersect.o: ../src/m3ginternal.hpp ../src/Object.hpp
test-RayIntersect.o: ../src/VertexBuffer.hpp ../src/TriangleStripArray.hpp
test-RayIntersect.o: ../src/IndexBuffer.hpp ../src/Appearance.hpp
test-RayIntersect.o: ../src/Mesh.hpp ../src/Node.hpp ../src/Transformable.hpp
test-RayIntersect.o: ../src/Quaternion.hpp ../src/Transform.hpp
test-RayIntersect.o: ../src/Matrix.hpp ../src/Vector.hpp
test-RayIntersect.o: ../src/RayIntersection.hpp
test-SkinnedMesh.o: /usr/include/unittest++/UnitTest++.h
test-SkinnedMesh.o: /usr/include/unittest++/Config.h
test-SkinnedMesh.o: /usr/include/unittest++/Test.h
test-SkinnedMesh.o: /usr/include/unittest++/TestDetails.h
test-SkinnedMesh.o: /usr/include/unittest++/TestList.h
test-SkinnedMesh.o: /usr/include/unittest++/TestSuite.h
test-SkinnedMesh.o: /usr/include/unittest++/TestResults.h
test-SkinnedMesh.o: /usr/include/unittest++/TestMacros.h
test-SkinnedMesh.o: /usr/include/unittest++/ExecuteTest.h
test-SkinnedMesh.o: /usr/include/unittest++/MemoryOutStream.h
test-SkinnedMesh.o: /usr/include/unittest++/AssertException.h
test-SkinnedMesh.o: /usr/include/unittest++/CurrentTest.h
test-SkinnedMesh.o: /usr/include/unittest++/CheckMacros.h
test-SkinnedMesh.o: /usr/include/unittest++/Checks.h
test-SkinnedMesh.o: /usr/include/unittest++/TestRunner.h
test-SkinnedMesh.o: /usr/include/unittest++/TimeConstraint.h
test-SkinnedMesh.o: /usr/include/unittest++/TimeHelpers.h
test-SkinnedMesh.o: ../src/SkinnedMesh.hpp ../src/Mesh.hpp ../src/Node.hpp
test-SkinnedMesh.o: ../src/Transformable.hpp ../src/Object3D.hpp
test-SkinnedMesh.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp
test-SkinnedMesh.o: ../src/Object.hpp ../src/Quaternion.hpp
test-SkinnedMesh.o: ../src/Transform.hpp ../src/Matrix.hpp
test-SkinnedMesh.o: ../src/BoneIndex.hpp ../src/VertexArray.hpp
test-SkinnedMesh.o: ../src/VertexBuffer.hpp ../src/TriangleStripArray.hpp
test-SkinnedMesh.o: ../src/IndexBuffer.hpp ../src/Appearance.hpp
test-SkinnedMesh.o: ../src/Group.hpp ../src/Exception.hpp
test-Sprite3D.o: /usr/include/unittest++/UnitTest++.h
test-Sprite3D.o: /usr/include/unittest++/Config.h
test-Sprite3D.o: /usr/include/unittest++/Test.h
test-Sprite3D.o: /usr/include/unittest++/TestDetails.h
test-Sprite3D.o: /usr/include/unittest++/TestList.h
test-Sprite3D.o: /usr/include/unittest++/TestSuite.h
test-Sprite3D.o: /usr/include/unittest++/TestResults.h
test-Sprite3D.o: /usr/include/unittest++/TestMacros.h
test-Sprite3D.o: /usr/include/unittest++/ExecuteTest.h
test-Sprite3D.o: /usr/include/unittest++/MemoryOutStream.h
test-Sprite3D.o: /usr/include/unittest++/AssertException.h
test-Sprite3D.o: /usr/include/unittest++/CurrentTest.h
test-Sprite3D.o: /usr/include/unittest++/CheckMacros.h
test-Sprite3D.o: /usr/include/unittest++/Checks.h
test-Sprite3D.o: /usr/include/unittest++/TestRunner.h
test-Sprite3D.o: /usr/include/unittest++/TimeConstraint.h
test-Sprite3D.o: /usr/include/unittest++/TimeHelpers.h ../src/Sprite3D.hpp
test-Sprite3D.o: ../src/Node.hpp ../src/Transformable.hpp ../src/Object3D.hpp
test-Sprite3D.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp ../src/Object.hpp
test-Sprite3D.o: ../src/Quaternion.hpp ../src/Transform.hpp ../src/Matrix.hpp
test-Sprite3D.o: ../src/Image2D.hpp ../src/Appearance.hpp
test-Texture2D.o: /usr/include/unittest++/UnitTest++.h
test-Texture2D.o: /usr/include/unittest++/Config.h
test-Texture2D.o: /usr/include/unittest++/Test.h
test-Texture2D.o: /usr/include/unittest++/TestDetails.h
test-Texture2D.o: /usr/include/unittest++/TestList.h
test-Texture2D.o: /usr/include/unittest++/TestSuite.h
test-Texture2D.o: /usr/include/unittest++/TestResults.h
test-Texture2D.o: /usr/include/unittest++/TestMacros.h
test-Texture2D.o: /usr/include/unittest++/ExecuteTest.h
test-Texture2D.o: /usr/include/unittest++/MemoryOutStream.h
test-Texture2D.o: /usr/include/unittest++/AssertException.h
test-Texture2D.o: /usr/include/unittest++/CurrentTest.h
test-Texture2D.o: /usr/include/unittest++/CheckMacros.h
test-Texture2D.o: /usr/include/unittest++/Checks.h
test-Texture2D.o: /usr/include/unittest++/TestRunner.h
test-Texture2D.o: /usr/include/unittest++/TimeConstraint.h
test-Texture2D.o: /usr/include/unittest++/TimeHelpers.h ../src/Texture2D.hpp
test-Texture2D.o: ../src/Transformable.hpp ../src/Object3D.hpp
test-Texture2D.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp ../src/Object.hpp
test-Texture2D.o: ../src/Quaternion.hpp ../src/Transform.hpp
test-Texture2D.o: ../src/Matrix.hpp ../src/Image2D.hpp
test-Transform.o: /usr/include/unittest++/UnitTest++.h
test-Transform.o: /usr/include/unittest++/Config.h
test-Transform.o: /usr/include/unittest++/Test.h
test-Transform.o: /usr/include/unittest++/TestDetails.h
test-Transform.o: /usr/include/unittest++/TestList.h
test-Transform.o: /usr/include/unittest++/TestSuite.h
test-Transform.o: /usr/include/unittest++/TestResults.h
test-Transform.o: /usr/include/unittest++/TestMacros.h
test-Transform.o: /usr/include/unittest++/ExecuteTest.h
test-Transform.o: /usr/include/unittest++/MemoryOutStream.h
test-Transform.o: /usr/include/unittest++/AssertException.h
test-Transform.o: /usr/include/unittest++/CurrentTest.h
test-Transform.o: /usr/include/unittest++/CheckMacros.h
test-Transform.o: /usr/include/unittest++/Checks.h
test-Transform.o: /usr/include/unittest++/TestRunner.h
test-Transform.o: /usr/include/unittest++/TimeConstraint.h
test-Transform.o: /usr/include/unittest++/TimeHelpers.h ../src/Transform.hpp
test-Transform.o: ../src/Matrix.hpp ../src/Object.hpp ../src/VertexArray.hpp
test-Transform.o: ../src/Object3D.hpp ../src/m3gdef.hpp
test-Transform.o: ../src/m3ginternal.hpp ../src/Quaternion.hpp
test-Transform.o: ../src/Vector.hpp
test-Transformable.o: /usr/include/unittest++/UnitTest++.h
test-Transformable.o: /usr/include/unittest++/Config.h
test-Transformable.o: /usr/include/unittest++/Test.h
test-Transformable.o: /usr/include/unittest++/TestDetails.h
test-Transformable.o: /usr/include/unittest++/TestList.h
test-Transformable.o: /usr/include/unittest++/TestSuite.h
test-Transformable.o: /usr/include/unittest++/TestResults.h
test-Transformable.o: /usr/include/unittest++/TestMacros.h
test-Transformable.o: /usr/include/unittest++/ExecuteTest.h
test-Transformable.o: /usr/include/unittest++/MemoryOutStream.h
test-Transformable.o: /usr/include/unittest++/AssertException.h
test-Transformable.o: /usr/include/unittest++/CurrentTest.h
test-Transformable.o: /usr/include/unittest++/CheckMacros.h
test-Transformable.o: /usr/include/unittest++/Checks.h
test-Transformable.o: /usr/include/unittest++/TestRunner.h
test-Transformable.o: /usr/include/unittest++/TimeConstraint.h
test-Transformable.o: /usr/include/unittest++/TimeHelpers.h
test-Transformable.o: ../src/Transformable.hpp ../src/Object3D.hpp
test-Transformable.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp
test-Transformable.o: ../src/Object.hpp ../src/Quaternion.hpp
test-Transformable.o: ../src/Transform.hpp ../src/Matrix.hpp
test-TriangleStripArray.o: /usr/include/unittest++/UnitTest++.h
test-TriangleStripArray.o: /usr/include/unittest++/Config.h
test-TriangleStripArray.o: /usr/include/unittest++/Test.h
test-TriangleStripArray.o: /usr/include/unittest++/TestDetails.h
test-TriangleStripArray.o: /usr/include/unittest++/TestList.h
test-TriangleStripArray.o: /usr/include/unittest++/TestSuite.h
test-TriangleStripArray.o: /usr/include/unittest++/TestResults.h
test-TriangleStripArray.o: /usr/include/unittest++/TestMacros.h
test-TriangleStripArray.o: /usr/include/unittest++/ExecuteTest.h
test-TriangleStripArray.o: /usr/include/unittest++/MemoryOutStream.h
test-TriangleStripArray.o: /usr/include/unittest++/AssertException.h
test-TriangleStripArray.o: /usr/include/unittest++/CurrentTest.h
test-TriangleStripArray.o: /usr/include/unittest++/CheckMacros.h
test-TriangleStripArray.o: /usr/include/unittest++/Checks.h
test-TriangleStripArray.o: /usr/include/unittest++/TestRunner.h
test-TriangleStripArray.o: /usr/include/unittest++/TimeConstraint.h
test-TriangleStripArray.o: /usr/include/unittest++/TimeHelpers.h
test-TriangleStripArray.o: ../src/TriangleStripArray.hpp
test-TriangleStripArray.o: ../src/IndexBuffer.hpp ../src/Object3D.hpp
test-TriangleStripArray.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp
test-TriangleStripArray.o: ../src/Object.hpp
test-Vector.o: /usr/include/unittest++/UnitTest++.h
test-Vector.o: /usr/include/unittest++/Config.h
test-Vector.o: /usr/include/unittest++/Test.h
test-Vector.o: /usr/include/unittest++/TestDetails.h
test-Vector.o: /usr/include/unittest++/TestList.h
test-Vector.o: /usr/include/unittest++/TestSuite.h
test-Vector.o: /usr/include/unittest++/TestResults.h
test-Vector.o: /usr/include/unittest++/TestMacros.h
test-Vector.o: /usr/include/unittest++/ExecuteTest.h
test-Vector.o: /usr/include/unittest++/MemoryOutStream.h
test-Vector.o: /usr/include/unittest++/AssertException.h
test-Vector.o: /usr/include/unittest++/CurrentTest.h
test-Vector.o: /usr/include/unittest++/CheckMacros.h
test-Vector.o: /usr/include/unittest++/Checks.h
test-Vector.o: /usr/include/unittest++/TestRunner.h
test-Vector.o: /usr/include/unittest++/TimeConstraint.h
test-Vector.o: /usr/include/unittest++/TimeHelpers.h ../src/Vector.hpp
test-VertexArray.o: /usr/include/unittest++/UnitTest++.h
test-VertexArray.o: /usr/include/unittest++/Config.h
test-VertexArray.o: /usr/include/unittest++/Test.h
test-VertexArray.o: /usr/include/unittest++/TestDetails.h
test-VertexArray.o: /usr/include/unittest++/TestList.h
test-VertexArray.o: /usr/include/unittest++/TestSuite.h
test-VertexArray.o: /usr/include/unittest++/TestResults.h
test-VertexArray.o: /usr/include/unittest++/TestMacros.h
test-VertexArray.o: /usr/include/unittest++/ExecuteTest.h
test-VertexArray.o: /usr/include/unittest++/MemoryOutStream.h
test-VertexArray.o: /usr/include/unittest++/AssertException.h
test-VertexArray.o: /usr/include/unittest++/CurrentTest.h
test-VertexArray.o: /usr/include/unittest++/CheckMacros.h
test-VertexArray.o: /usr/include/unittest++/Checks.h
test-VertexArray.o: /usr/include/unittest++/TestRunner.h
test-VertexArray.o: /usr/include/unittest++/TimeConstraint.h
test-VertexArray.o: /usr/include/unittest++/TimeHelpers.h
test-VertexArray.o: /usr/include/GL/gl.h /usr/include/GL/glext.h
test-VertexArray.o: /usr/include/inttypes.h /usr/include/features.h
test-VertexArray.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
test-VertexArray.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
test-VertexArray.o: /usr/include/gnu/stubs-32.h /usr/include/stdint.h
test-VertexArray.o: /usr/include/bits/wchar.h ../src/VertexArray.hpp
test-VertexArray.o: ../src/Object3D.hpp ../src/m3gdef.hpp
test-VertexArray.o: ../src/m3ginternal.hpp ../src/Object.hpp
test-VertexBuffer.o: /usr/include/unittest++/UnitTest++.h
test-VertexBuffer.o: /usr/include/unittest++/Config.h
test-VertexBuffer.o: /usr/include/unittest++/Test.h
test-VertexBuffer.o: /usr/include/unittest++/TestDetails.h
test-VertexBuffer.o: /usr/include/unittest++/TestList.h
test-VertexBuffer.o: /usr/include/unittest++/TestSuite.h
test-VertexBuffer.o: /usr/include/unittest++/TestResults.h
test-VertexBuffer.o: /usr/include/unittest++/TestMacros.h
test-VertexBuffer.o: /usr/include/unittest++/ExecuteTest.h
test-VertexBuffer.o: /usr/include/unittest++/MemoryOutStream.h
test-VertexBuffer.o: /usr/include/unittest++/AssertException.h
test-VertexBuffer.o: /usr/include/unittest++/CurrentTest.h
test-VertexBuffer.o: /usr/include/unittest++/CheckMacros.h
test-VertexBuffer.o: /usr/include/unittest++/Checks.h
test-VertexBuffer.o: /usr/include/unittest++/TestRunner.h
test-VertexBuffer.o: /usr/include/unittest++/TimeConstraint.h
test-VertexBuffer.o: /usr/include/unittest++/TimeHelpers.h
test-VertexBuffer.o: ../src/VertexBuffer.hpp ../src/Object3D.hpp
test-VertexBuffer.o: ../src/m3gdef.hpp ../src/m3ginternal.hpp
test-VertexBuffer.o: ../src/Object.hpp ../src/VertexArray.hpp
test-World.o: /usr/include/unittest++/UnitTest++.h
test-World.o: /usr/include/unittest++/Config.h /usr/include/unittest++/Test.h
test-World.o: /usr/include/unittest++/TestDetails.h
test-World.o: /usr/include/unittest++/TestList.h
test-World.o: /usr/include/unittest++/TestSuite.h
test-World.o: /usr/include/unittest++/TestResults.h
test-World.o: /usr/include/unittest++/TestMacros.h
test-World.o: /usr/include/unittest++/ExecuteTest.h
test-World.o: /usr/include/unittest++/MemoryOutStream.h
test-World.o: /usr/include/unittest++/AssertException.h
test-World.o: /usr/include/unittest++/CurrentTest.h
test-World.o: /usr/include/unittest++/CheckMacros.h
test-World.o: /usr/include/unittest++/Checks.h
test-World.o: /usr/include/unittest++/TestRunner.h
test-World.o: /usr/include/unittest++/TimeConstraint.h
test-World.o: /usr/include/unittest++/TimeHelpers.h ../src/World.hpp
test-World.o: ../src/Group.hpp ../src/Node.hpp ../src/Transformable.hpp
test-World.o: ../src/Object3D.hpp ../src/m3gdef.hpp ../src/m3ginternal.hpp
test-World.o: ../src/Object.hpp ../src/Quaternion.hpp ../src/Transform.hpp
test-World.o: ../src/Matrix.hpp ../src/Camera.hpp ../src/Background.hpp
test-World.o: ../src/Light.hpp
test-main.o: /usr/include/unittest++/UnitTest++.h
test-main.o: /usr/include/unittest++/Config.h /usr/include/unittest++/Test.h
test-main.o: /usr/include/unittest++/TestDetails.h
test-main.o: /usr/include/unittest++/TestList.h
test-main.o: /usr/include/unittest++/TestSuite.h
test-main.o: /usr/include/unittest++/TestResults.h
test-main.o: /usr/include/unittest++/TestMacros.h
test-main.o: /usr/include/unittest++/ExecuteTest.h
test-main.o: /usr/include/unittest++/MemoryOutStream.h
test-main.o: /usr/include/unittest++/AssertException.h
test-main.o: /usr/include/unittest++/CurrentTest.h
test-main.o: /usr/include/unittest++/CheckMacros.h
test-main.o: /usr/include/unittest++/Checks.h
test-main.o: /usr/include/unittest++/TestRunner.h
test-main.o: /usr/include/unittest++/TimeConstraint.h
test-main.o: /usr/include/unittest++/TimeHelpers.h /usr/include/GL/glut.h
test-main.o: /usr/include/GL/freeglut_std.h /usr/include/GL/gl.h
test-main.o: /usr/include/GL/glext.h /usr/include/inttypes.h
test-main.o: /usr/include/features.h /usr/include/bits/predefs.h
test-main.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
test-main.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
test-main.o: /usr/include/stdint.h /usr/include/bits/wchar.h
test-main.o: /usr/include/GL/glu.h /usr/include/stdlib.h
test-main.o: /usr/include/sys/types.h /usr/include/bits/types.h
test-main.o: /usr/include/bits/typesizes.h /usr/include/time.h
test-main.o: /usr/include/endian.h /usr/include/bits/endian.h
test-main.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
test-main.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
test-main.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
test-main.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
