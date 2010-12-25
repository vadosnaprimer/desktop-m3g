project (M3G-UnitTest)

cmake_minimum_required (VERSION 2.0)

# dependend libraries
find_package (ZLIB   REQUIRED)
find_package (PNG    REQUIRED)
find_package (JPEG   REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLU    REQUIRED)
find_package (GLUT   REQUIRED)



link_directories (../bin/lib)
set  (M3G_UNITTEST_REQUIRED_LIBRARIES 
        m3g
        UnitTest++
        glut)
file (GLOB M3G_UNITTEST_SRCS *.cpp)

add_executable        (a.out ${M3G_UNITTEST_SRCS})
target_link_libraries (a.out ${M3G_UNITTEST_REQUIRED_LIBRARIES})

