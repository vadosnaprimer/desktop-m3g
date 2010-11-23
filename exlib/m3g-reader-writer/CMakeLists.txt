#
#  M3G-Reader-Writer project file.
#


# project info
project (M3G_READER_WRITER)
cmake_minimum_required (VERSION 2.0)

# dependend libraries

# build type = Debug (defualt)
if (NOT CMAKE_BUILD_TYPE)
    message (STATUS "Build type is not specified, then")
    message (STATUS "  set CMAKE_BUILD_TYPE=Debug")
    message (STATUS "  set CMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/bin")
    set (CMAKE_BUILD_TYPE "DEBUG")
    set (CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin)
endif (NOT CMAKE_BUILD_TYPE)
message (STATUS "Configuring for ${CMAKE_BUILD_TYPE}...")


# project src
add_subdirectory (src)


