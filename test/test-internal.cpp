#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/m3ginternal.hpp"
using namespace std;
using namespace m3g;


TEST (clamp)
{
    float value = 50.f;
    CHECK_EQUAL (50.f, clamp( 0.f, 100.0f, value));
    CHECK_EQUAL (40.f, clamp( 0.f,  40.0f, value));
    CHECK_EQUAL (60.f, clamp(60.f, 100.0f, value));
}

TEST (memswap)
{
    int buf1[4] = {1,2,3,4};
    int buf2[4] = {5,6,7,8};
    int tmp [4] = {0,0,0,0};
    memswap ((unsigned char*)buf1,
             (unsigned char*)buf2,
             (unsigned char*)tmp,
             sizeof(buf1));

    CHECK_EQUAL (buf1[0], 5);
    CHECK_EQUAL (buf1[1], 6);
    CHECK_EQUAL (buf1[2], 7);
    CHECK_EQUAL (buf1[3], 8);

    CHECK_EQUAL (buf2[0], 1);
    CHECK_EQUAL (buf2[1], 2);
    CHECK_EQUAL (buf2[2], 3);
    CHECK_EQUAL (buf2[3], 4);
}

