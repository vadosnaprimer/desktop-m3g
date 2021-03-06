#ifndef __M3G_INTERNAL_HPP__
#define __M3G_INTERNAL_HPP__

#include <cstring>

namespace m3g {

/**
 * このライブラリで許容できる誤差の指定.
 * 手元のPCで見たときは1.19209e-07*100だった。
 */
    extern const float M3G_EPSILON;

    /**
     *
     */
    inline
    float clamp(float min, float max, float value)
    {
        return (value < min) ? min :
            (value > max) ? max :
            value;
    }

    /**
     *
     */
    const char* objtype_to_string(int objtype);

    /**
     *
     */
    inline
    void memswap (char* p, char* q, char* tmp, int size)
    {
        memcpy (tmp, p  , size);
        memcpy (p  , q  , size);
        memcpy (q  , tmp, size);
     }

} // namespace m3g {

#endif

