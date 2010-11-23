
# project src

# m3g-reader-writer
add_subdirectory (m3g-reader-writer)
set (M3G_READER_WRITER_INCLUDE_DIR ${M3G_READER_WRITER_SOURCE_DIR}/src                             PARENT_SCOPE)
set (M3G_READER_WRITER_LINK_DIR    ${M3G_READER_WRITER_BINARY_DIR}/src                             PARENT_SCOPE)
set (M3G_READER_WRITER_LIBRARY     -Wl,-whole-archive libm3g-reader-writer.a -Wl,-no-whole-archive PARENT_SCOPE)


