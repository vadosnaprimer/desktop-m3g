project (M3G-TEST-16)

cmake_minimum_required (VERSION 2.0)
cmake_policy (SET CMP0015 OLD)

# dependend libraries
find_package (GLUT   REQUIRED)

include_directories (../../bin/include)
link_directories    (../../bin/lib)
set  (LIBS m3g glut GLEW)
file (GLOB SRCS *.cpp)

add_executable        (a.out ${SRCS})
target_link_libraries (a.out ${LIBS})

