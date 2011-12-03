project (M3G-SAMPLE-08)

cmake_minimum_required (VERSION 2.0)

# dependend libraries
find_package (OpenGL REQUIRED)
find_package (GLUT   REQUIRED)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/../../bin/include)
link_directories    (${CMAKE_CURRENT_SOURCE_DIR}/../../bin/lib/linux)

set  (LIBS m3g glut)
file (GLOB SRCS *.cpp)

add_executable        (a.out ${SRCS})
target_link_libraries (a.out ${LIBS})

