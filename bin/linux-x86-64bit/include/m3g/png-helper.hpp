
#ifndef __M3G_PNG_HELPER_HPP__
#define __M3G_PNG_HELPER_HPP__

#include "m3g/Config.hpp"
#ifdef USE_PNG

#include <png.h>

namespace m3g {

/**
 * 
 */
void my_png_read_func (png_structp png_ptr, png_bytep data, png_size_t length);


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


} // namespace m3g {

#endif // USE_PNG

#endif // __M3G_PNG_HELPER_HPP__

