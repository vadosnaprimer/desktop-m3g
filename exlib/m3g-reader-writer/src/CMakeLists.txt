
# m3g-reader-writer srcs
file (GLOB M3G_READER_WRITER_SRCS *.cpp)

# m3g-reader-writer headers
file (GLOB M3G_READER_WRITER_HEADERS *.hpp)

# m3g-reader-writer target
add_library (m3g-reader-writer STATIC ${M3G_READER_WRITER_SRCS})


# installer
install (FILES ${M3G_READER_WRITER_HEADERS}  DESTINATION include/m3g)
install (TARGETS m3g-reader-writer ARCHIVE DESTINATION lib)


# compile flags
set (CMAKE_CXX_FLAGS         "-Wall -fPIC")
set (CMAKE_CXX_FLAGS_DEBUG   "-g")
set (CMAKE_CXX_FLAGS_RELEASE "-O2")
set (CMAKE_INCLUDE_CURRENT_DIR ON)


# m3g-reader-writer include directory
# set (M3G_READER_WRITER_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR})


# m3g-reader-writer lib directory
# set (M3G_READER_WRITER_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR})



