project (M3G-TEST-08)

cmake_minimum_required (VERSION 2.0)
cmake_policy (SET CMP0015 OLD)

# dependend libraries
find_package (Qt4     REQUIRED)
include (${QT_USE_FILE})

include_directories (../../bin/include)
link_directories    (../../bin/lib)
set  (LIBS m3g ${QT_LIBRARIES} QtOpenGL)
file (GLOB SRCS *.cpp)

add_executable        (a.out ${SRCS})
target_link_libraries (a.out ${LIBS})

