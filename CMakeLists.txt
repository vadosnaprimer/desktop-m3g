# =================================
# M3G project config file.
# =================================

# project info
project (M3G)

# required cmake
cmake_minimum_required (VERSION 2.0)


# Avairable options
option (USE_GL    "Set ON, if you use OpenGL (default ON)"      ON )
option (USE_GL_ES "Set ON, if you use OpenGL ES (default OFF)"  OFF)
option (USE_PNG   "Set ON, if you use PNG format (default ON)"  ON )
option (USE_JPEG  "Set ON, if you use JPEG format (default ON)" ON )
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/src/m3g/Config.hpp.in
                ${CMAKE_CURRENT_BINARY_DIR}/src/m3g/Config.hpp)

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
# libz.so
find_package (ZLIB   REQUIRED)
# libpng
if (USE_PNG BOOLEQUAL ON)
  find_package (PNG    REQUIRED)
endif (USE_PNG BOOLEQUAL ON)
# libjpeg.so
if (USE_JPEG BOOLEQUAL ON)
  find_package (JPEG   REQUIRED)
endif (USE_JPEG BOOLEQUAL ON)
# libGL.so
if (USE_GL BOOLEQUAL ON)
  find_package (OpenGL REQUIRED)
endif (USE_GL_BOOLEQUAL ON)


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


message (STATUS "Generating Config.hpp ...")
message (STATUS "USE_GL    = ${USE_GL}")
message (STATUS "USE_GL_ES = ${USE_GL_ES}")
message (STATUS "USE_PNG   = ${USE_PNG}")
message (STATUS "USE_JPEG  = ${USE_JPEG}")


