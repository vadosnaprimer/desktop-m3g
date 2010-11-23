
# jpeg-helper srcs
file (GLOB JPEG_HELPER_SRCS *.cpp)

# jpeg-helper headers
file (GLOB JPEG_HELPER_HEADERS *.hpp)

# jpeg-helper target
add_library (jpeg-helper STATIC ${JPEG_HELPER_SRCS})


# installer
install (FILES ${JPEG_HELPER_HEADERS}  DESTINATION include/m3g)
install (TARGETS jpeg-helper ARCHIVE DESTINATION lib)


# compile flags
set (CMAKE_CXX_FLAGS         "-Wall -fPIC")
set (CMAKE_CXX_FLAGS_DEBUG   "-g")
set (CMAKE_CXX_FLAGS_RELEASE "-O2")
set (CMAKE_INCLUDE_CURRENT_DIR ON)


