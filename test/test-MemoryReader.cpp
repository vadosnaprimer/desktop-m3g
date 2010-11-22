#include "m3g/MemoryReader.hpp"
#include <unittest++/UnitTest++.h>
#include <iostream>


using namespace std;
//using namespace m3g;


TEST (MemoryReader)
{
    int size = 16;
    char buf[size];
    for (int i = 0; i < size; i++) {
        buf[i] = i;
    }
    MemoryReader* reader = new MemoryReader (buf, size);

    char c[2];
    reader->read (c, 2);
    CHECK_EQUAL (0, (int)c[0]);
    CHECK_EQUAL (1, (int)c[1]);

    for (int i = 2; i < size; i++) {
        reader->read (c, 1);
        CHECK_EQUAL (i, (int)c[0]);
    }

}

