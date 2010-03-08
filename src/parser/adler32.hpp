#ifndef __ADLER32_HPP__
#define __ADLER32_HPP__

#include <stdint.h>

namespace m3g { 

/**
 * Adler-23 チェックサムの計算.
 */
int adler32 (unsigned char* data, int len)
{
  const int MOD_ADLER = 65521;
    unsigned int a = 1, b = 0;
 
    while (len > 0) 
    {
        int tlen = len > 5550 ? 5550 : len;
        len -= tlen;
        do 
        {
            a += *data++;
            b += a;
        } while (--tlen);
 
        a %= MOD_ADLER;
        b %= MOD_ADLER;
    }
 
    return (b << 16) | a;
}


} // namespace m3g { 

#endif
