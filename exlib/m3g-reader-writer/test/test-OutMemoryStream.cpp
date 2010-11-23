#include "m3g/OutMemoryStream.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (OutMemoryStream)
{
    OutMemoryStream* stream = new OutMemoryStream ("out-memory-stream-1.m3g");
    int cur;

    char buf_1 = 1;
    stream->write (&buf_1, 1);
    cur = stream->tellp ();
    CHECK_EQUAL (1, cur);

    // アライメントがずれているが
    // x86なら問題ない

    short buf_2 = 2;
    stream->write ((char*)&buf_2, 2);
    cur = stream->tellp ();
    CHECK_EQUAL (3, cur);


    int buf_4 = 4;
    stream->write ((char*)&buf_4, 4);
    cur = stream->tellp ();
    CHECK_EQUAL (7, cur);


    float buf_4f = 999999.f;
    stream->write ((char*)&buf_4f, 4);
    cur = stream->tellp ();
    CHECK_EQUAL (11, cur);

    const char* ptr = stream->pointer();
    CHECK_EQUAL (1,        *(char*) (ptr+0));
    CHECK_EQUAL (2,        *(short*)(ptr+1));
    CHECK_EQUAL (4,        *(int*)  (ptr+3));
    CHECK_EQUAL (999999.f, *(float*)(ptr+7));


    delete stream;

    ifstream ifs ("out-memory-stream-2.m3g");
    ifs >> buf_1 >> buf_2 >>  buf_4 >> buf_4f;
    CHECK_EQUAL (1, buf_1);
    CHECK_EQUAL (2, buf_2);
    CHECK_EQUAL (4, buf_4);
    CHECK_EQUAL (999999.f, buf_4f);

}


TEST (OutMemoryStream_seekp)
{
    OutMemoryStream* stream = new OutMemoryStream ("out-memory-stream-2.m3g");
    
    char  buf_1  = 1;
    short buf_2  = 2;
    int   buf_4  = 4;
    float buf_4f = 99.f;
    
    stream->write ((char*)&buf_1, 1);
    stream->write ((char*)&buf_2, 2);
    stream->write ((char*)&buf_4, 4);
    stream->seekp (1);
    stream->write ((char*)&buf_4f, 4);

    CHECK_EQUAL (7,    stream->size());

    const char* ptr = stream->pointer();
    CHECK_EQUAL (1,    *(char*) (ptr+0));
    CHECK_EQUAL (99.f, *(float*)(ptr+1));


    delete stream;
    
    ifstream ifs ("out-memory-stream-2.m3g");
    ifs.read ((char*)&buf_1, 1);
    ifs.read ((char*)&buf_4f, 4);
    CHECK_EQUAL (1, buf_1);
    CHECK_EQUAL (99.f, buf_4f);

}

TEST (OutMemoryStream_erase)
{
    OutMemoryStream* stream = new OutMemoryStream ("out-memory-stream-3.m3g");
    
    char  buf_1  = 1;
    short buf_2  = 2;
    int   buf_4  = 4;
    
    stream->write ((char*)&buf_1, 1);
    stream->write ((char*)&buf_2, 2);
    stream->write ((char*)&buf_4, 4);
    CHECK_EQUAL (7, stream->size());

    stream->erase (1, 2);
    CHECK_EQUAL (5, stream->size());

    const char* ptr = stream->pointer();
    CHECK_EQUAL (1, *(char*)(ptr+0));
    CHECK_EQUAL (4, *(int*) (ptr+1));


    delete stream;
}

TEST (OutMemoryStream_insert)
{
    OutMemoryStream* stream = new OutMemoryStream ("out-memory-stream-4.m3g");
    
    char  buf_1  = 1;
    short buf_2  = 2;
    int   buf_4  = 4;
    int   buf_4f  = 99;
    
    stream->write ((char*)&buf_1, 1);
    stream->write ((char*)&buf_2, 2);
    stream->write ((char*)&buf_4, 4);
    CHECK_EQUAL    (7, stream->size());

    stream->insert (3, (char*)&buf_4f, 4);
    CHECK_EQUAL    (11, stream->size());


    const char* ptr = stream->pointer();
    CHECK_EQUAL (1,  *(char*) (ptr+0));
    CHECK_EQUAL (2,  *(short*)(ptr+1));
    CHECK_EQUAL (99, *(int*)  (ptr+3));
    CHECK_EQUAL (4,  *(int*)  (ptr+7));

    delete stream;
}
