project (M3G-TEST-04)

cmake_minimum_required (VERSION 2.0)

# dependend libraries
find_package (GLUT   REQUIRED)

link_directories (../../bin/lib)
set  (LIBS m3g glut)
file (GLOB SRCS *.cpp)

add_executable        (a.out ${SRCS})
target_link_libraries (a.out ${LIBS})

