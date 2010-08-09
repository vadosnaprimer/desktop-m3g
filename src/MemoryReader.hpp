

#ifndef __MEMORY_READER_HPP__
#define __MEMORY_READER_HPP__

#include <png.h>

/**
 *
 */
class MemoryReader
{
public:
    MemoryReader (const char* p, int size);
    ~MemoryReader ();

    int read (char* p, int length);

private:
    
    const char* buf;
    int         cur;
    int         size;
};

void my_png_read_func (png_structp png_ptr, png_bytep data, png_size_t length);


#endif
