#include "m3g/InMemoryStream.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (InMemoryStream)
{
    InMemoryStream* stream = new InMemoryStream ("in-memory-stream.hex");
    int cur;

    CHECK_EQUAL (11, stream->size());

    char buf_1;
    stream->read (&buf_1, 1);
    cur = stream->tellg ();
    CHECK_EQUAL (1, buf_1);
    CHECK_EQUAL (1, cur);

    short buf_2;
    stream->read ((char*)&buf_2, 2);
    cur = stream->tellg ();
    CHECK_EQUAL (2, buf_2);
    CHECK_EQUAL (3, cur);

    int buf_4;
    stream->read ((char*)&buf_4, 4);
    cur = stream->tellg ();
    CHECK_EQUAL (4, buf_4);
    CHECK_EQUAL (7, cur);

    float buf_4f;
    stream->read ((char*)&buf_4f, 4);
    cur = stream->tellg ();
    CHECK_EQUAL (999999.f, buf_4f);
    CHECK_EQUAL (11, cur);

    CHECK_EQUAL (true, stream->eof());

    const char* ptr = stream->pointer();
    CHECK (stream->pointer() != NULL);
    CHECK_EQUAL (1, *(char*)ptr);
    CHECK_EQUAL (2, *(short*)(ptr+1));
    CHECK_EQUAL (4, *(int*)(ptr+3));
    CHECK_EQUAL (999999.f, *(float*)(ptr+7));


    delete stream;
}

TEST (InMemoryStream_insert)
{
    char buf[] = {0,1,2,3,4};
    InMemoryStream* stream = new InMemoryStream (buf, 5);
    
    char buf2[] = {5,6,7,8};
    stream->insert (2, buf2, 4);

    CHECK_EQUAL (9, stream->size());
    // --> 0,1, 5,6,7,8, 2,3,4
    char c;
    stream->read (&c, 1);
    CHECK_EQUAL (0, (int)c);
    stream->read (&c, 1);
    CHECK_EQUAL (1, (int)c);
    stream->read (&c, 1);
    CHECK_EQUAL (5, (int)c);
    stream->read (&c, 1);
    CHECK_EQUAL (6, (int)c);
    stream->read (&c, 1);
    CHECK_EQUAL (7, (int)c);
    stream->read (&c, 1);
    CHECK_EQUAL (8, (int)c);
    stream->read (&c, 1);
    CHECK_EQUAL (2, (int)c);
    stream->read (&c, 1);
    CHECK_EQUAL (3, (int)c);
    stream->read (&c, 1);
    CHECK_EQUAL (4, (int)c);

    CHECK_EQUAL (true, stream->eof());

    delete stream;
}

TEST (InMemoryStream_erase)
{
    char buf[] = {0,1,2,3,4};
    InMemoryStream* stream = new InMemoryStream (buf, 5);
    
    stream->erase (2, 2);
    
    CHECK_EQUAL (3, stream->size());
    // --> 0,1, 4
    char c;
    stream->read (&c, 1);
    CHECK_EQUAL (0, (int)c);
    stream->read (&c, 1);
    CHECK_EQUAL (1, (int)c);
    stream->read (&c, 1);
    CHECK_EQUAL (4, (int)c);
    stream->read (&c, 1);

    CHECK_EQUAL (true, stream->eof());

    delete stream;
}
