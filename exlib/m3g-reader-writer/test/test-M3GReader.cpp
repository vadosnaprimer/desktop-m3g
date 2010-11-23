#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;


const unsigned char m3g_id[12] = {0xab, 0x4a, 0x53, 0x52, 0x31, 0x38, 0x34, 0xbb, 0x0d, 0x0a, 0x1a, 0x0a};

TEST (M3GReader_from_file)
{
    M3GReader* reader = new M3GReader ("id-only.hex");
    const unsigned char* id = reader->readID ();

    CHECK_ARRAY_EQUAL (m3g_id, id, 12);

    delete reader;
}

TEST (M3GReader_from_memory)
{
    ifstream ifs ("id-only.hex");
    char buf[12];
    ifs.read (buf, 12);
    M3GReader* reader = new M3GReader (buf, 12);
    const unsigned char* id = reader->readID ();

    CHECK_ARRAY_EQUAL (m3g_id, id, 12);

    delete reader;
}
