#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
#include <cstring>
using namespace std;


TEST (Section_uncompressed)
{
    M3GWriter*  writer = new M3GWriter ("section-uncompressed.m3g");
    const char  buf[] = "Minna-Dietlinde Wilcke";

    writer->startSection ();
    writer->writeString  (buf);
    writer->endSection   ();
    
    delete writer;

    M3GReader*  reader = new M3GReader ("section-uncompressed.m3g");
    const char* str;

    reader->startSection ();
    reader->readString   (&str);
    reader->endSection   ();

    CHECK_EQUAL (buf, str);

    delete [] str;
    delete reader;
}


TEST (Section_comporessed)
{
    M3GWriter* writer = new M3GWriter ("section-compressed.m3g");
    const char  buf[] = "Gertrud Barkhorn";

    writer->startSection (1);
    writer->writeString  (buf);
    writer->endSection   ();
    
    delete writer;

    M3GReader*  reader = new M3GReader ("section-compressed.m3g");
    const char* str;

    reader->startSection ();
    reader->readString   (&str);
    reader->endSection   ();

    CHECK_EQUAL (buf, str);

    delete [] str;
    delete reader;
}

TEST (Section_2)
{
    M3GWriter*  writer = new M3GWriter ("section-sections.m3g");
    const char  buf1[] = "Lynette Bishop";
    const char  buf2[] = "Erica Hartmann";

    writer->startSection ();
    writer->writeString  (buf1);
    writer->endSection   ();

    writer->startSection ();
    writer->writeString  (buf2);
    writer->endSection   ();
    
    delete writer;

    M3GReader*  reader = new M3GReader ("section-sections.m3g");
    const char* str;

    reader->startSection ();
    reader->readString   (&str);
    reader->endSection   ();

    CHECK_EQUAL (buf1, str);

    delete [] str;

    reader->startSection ();
    reader->readString   (&str);
    reader->endSection   ();

    CHECK_EQUAL (buf2, str);

    delete [] str;
    delete reader;
}
