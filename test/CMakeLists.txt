project (M3G-UnitTest)

cmake_minimum_required (VERSION 2.0)
#cmake_policy (SET CMP0015 OLD)


# dependend libraries
find_package (ZLIB   REQUIRED)
find_package (PNG    REQUIRED)
find_package (JPEG   REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLUT   REQUIRED)

# m3g
include_directories (../bin/include)
link_directories    (../bin/lib)
set  (M3G_UNITTEST_REQUIRED_LIBRARIES 
        m3g
        UnitTest++
        glut)

# unit-test
file (GLOB M3G_UNITTEST_SRCS *.cpp)
#file (GLOB M3G_UNITTEST_SRCS test-main.cpp test-picking-2.cpp)

add_executable        (a.out ${M3G_UNITTEST_SRCS})
target_link_libraries (a.out ${M3G_UNITTEST_REQUIRED_LIBRARIES})

