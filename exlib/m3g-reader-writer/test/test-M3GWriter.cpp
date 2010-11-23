#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

const unsigned char id[12] = {0xab, 0x4a, 0x53, 0x52, 0x31, 0x38, 0x34, 0xbb, 0x0d, 0x0a, 0x1a, 0x0a};

TEST (M3GWriter_default_value)
{
    M3GWriter* writer = new M3GWriter ("id-only.m3g");
    writer->writeID ();
    delete writer;

    M3GReader* reader = new M3GReader ("id-only.m3g");
    const unsigned char* buf;
    buf = reader->readID ();
    delete reader;

    CHECK_ARRAY_EQUAL (buf, id, 12);
}


TEST (M3GWriter_putXXX)
{
    M3GWriter* writer = new M3GWriter ("putXXX.m3g");
    writer->putBoolean   (true);   // 0
    writer->putByte      (78);     // 1
    writer->putByte      (130);    // 2
    writer->putUInt16    (1129);   // 3
    writer->putUInt32    (75535);  // 5
    writer->putFloat32   (1.11);   // 9
    writer->putByteArray ((char*)id, 12); // 13
    writer->putString    ("hello world"); // 25
    delete writer;                 // 37
    
    M3GReader* reader = new M3GReader ("putXXX.m3g");
    CHECK_EQUAL (true,  reader->getBoolean());
    CHECK_EQUAL (78,    reader->getByte());
    CHECK_EQUAL (130,   reader->getUByte());
    CHECK_EQUAL (1129,  reader->getUInt16());
    CHECK_EQUAL (75535, reader->getUInt32());
    CHECK_EQUAL (1.11f, reader->getFloat32());
    char* byte = reader->getByteArray(12);
    CHECK_ARRAY_EQUAL ((char*)id, byte, 12);
    const char* string = reader->getString();
    CHECK_EQUAL ("hello world", string);

    delete [] byte;
    delete [] string;
    delete reader;
}


