#
# M3G project config file.
#

# project info
project (M3G)

# required cmake
cmake_minimum_required (VERSION 2.0)

# Default is "Debug"
if (NOT CMAKE_BUILD_TYPE)
    message (STATUS "Build type is not specified, then")
    message (STATUS "  set CMAKE_BUILD_TYPE=Debug")
    set (CMAKE_BUILD_TYPE "Debug")
endif (NOT CMAKE_BUILD_TYPE)

  message (STATUS "Configuring m3g for ${CMAKE_BUILD_TYPE}...")

# for "Debug"
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message (STATUS "  set CMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/bin")
    set (CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

# for "Release"
if  (CMAKE_BUILD_TYPE STREQUAL "Release")
    # nothing
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

# dependend libraries
find_package (ZLIB   REQUIRED)
find_package (PNG    REQUIRED)
find_package (JPEG   REQUIRED)
find_package (OpenGL REQUIRED)
# i don't need glu
#find_package (GLU    REQUIRED)

set (M3G_REQUIRED_LIBRARIES
         ${ZLIB_LIBRARIES}
         ${PNG_LIBRARIES}
         ${JPEG_LIBRARIES}
         ${OPENGL_LIBRARIES})
set (M3G_REQUIRED_INCLUDE_DIR 
         ${ZLIB_INCLUDE_DIR}
         ${PNG_INCLUDE_DIR}
         ${JPEG_INCLUDE_DIR}
         ${OPENGL_INCLUDE_DIR})


# my custom libraries
add_subdirectory (exlib)
link_directories (${M3G_READER_WRITER_LINK_DIR})
link_directories (${JPEG_HELPER_LINK_DIR})
link_directories (${PNG_HELPER_LINK_DIR})


# project src
add_subdirectory (src)


