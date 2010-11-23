#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (KeyframeSequence_encoding_0)
{
    int object_type = M3G_TYPE_KEYFRAME_SEQUENCE;
    unsigned int object_index;
    M3GKeyframeSequenceStruct keyframe_sequence;

    keyframe_sequence.interpolation     = 3;
    keyframe_sequence.repeat_mode       = 4;
    keyframe_sequence.encoding          = M3GKeyframeSequenceStruct::ENCODING_0;
    keyframe_sequence.duration          = 5;
    keyframe_sequence.valid_range_first = 6;
    keyframe_sequence.valid_range_last  = 7;
    keyframe_sequence.component_count   = 2;
    keyframe_sequence.keyframe_count    = 3;
    keyframe_sequence.time              = new unsigned int[3];
    keyframe_sequence.time[0]           = 1;
    keyframe_sequence.time[1]           = 2;
    keyframe_sequence.time[2]           = 3;
    keyframe_sequence.vector_value       = new float* [3];
    keyframe_sequence.vector_value[0]    = new float  [2];
    keyframe_sequence.vector_value[1]    = new float  [2];
    keyframe_sequence.vector_value[2]    = new float  [2];
    keyframe_sequence.vector_value[0][0] = 1;
    keyframe_sequence.vector_value[0][1] = 2;
    keyframe_sequence.vector_value[1][0] = 3;
    keyframe_sequence.vector_value[1][1] = 4;
    keyframe_sequence.vector_value[2][0] = 5;
    keyframe_sequence.vector_value[2][1] = 6;


    M3GWriter* writer = new M3GWriter ("keyframe_sequence.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeKeyframeSequence     (keyframe_sequence);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;


    M3GReader* reader = new M3GReader ("keyframe_sequence.m3g");
    M3GKeyframeSequenceStruct keyframe_sequence2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readKeyframeSequence      (&keyframe_sequence2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_KEYFRAME_SEQUENCE, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (3, keyframe_sequence2.interpolation);
    CHECK_EQUAL (4, keyframe_sequence2.repeat_mode);
    CHECK_EQUAL (M3GKeyframeSequenceStruct::ENCODING_0, keyframe_sequence2.encoding);
    CHECK_EQUAL (5, keyframe_sequence2.duration);
    CHECK_EQUAL (6, keyframe_sequence2.valid_range_first);
    CHECK_EQUAL (7, keyframe_sequence2.valid_range_last );
    CHECK_EQUAL (2, keyframe_sequence2.component_count);
    CHECK_EQUAL (3, keyframe_sequence2.keyframe_count);
    CHECK_EQUAL (1, keyframe_sequence2.time[0]);
    CHECK_EQUAL (2, keyframe_sequence2.time[1]);
    CHECK_EQUAL (3, keyframe_sequence2.time[2]);
    CHECK_EQUAL (1, keyframe_sequence2.vector_value[0][0]);
    CHECK_EQUAL (2, keyframe_sequence2.vector_value[0][1]);
    CHECK_EQUAL (3, keyframe_sequence2.vector_value[1][0]);
    CHECK_EQUAL (4, keyframe_sequence2.vector_value[1][1]);
    CHECK_EQUAL (5, keyframe_sequence2.vector_value[2][0]);
    CHECK_EQUAL (6, keyframe_sequence2.vector_value[2][1]);

    delete reader;
}

TEST (KeyframeSequence_encoding_1)
{
    int object_type = M3G_TYPE_KEYFRAME_SEQUENCE;
    unsigned int object_index;
    M3GKeyframeSequenceStruct keyframe_sequence;

    keyframe_sequence.interpolation     = 3;
    keyframe_sequence.repeat_mode       = 4;
    keyframe_sequence.encoding          = M3GKeyframeSequenceStruct::ENCODING_1;
    keyframe_sequence.duration          = 5;
    keyframe_sequence.valid_range_first = 6;
    keyframe_sequence.valid_range_last  = 7;
    keyframe_sequence.component_count   = 2;
    keyframe_sequence.keyframe_count    = 3;
    keyframe_sequence.time              = new unsigned int[3];
    keyframe_sequence.time[0]           = 1;
    keyframe_sequence.time[1]           = 2;
    keyframe_sequence.time[2]           = 3;
    keyframe_sequence.vector_value       = new float* [3];
    keyframe_sequence.vector_value[0]    = new float  [2];
    keyframe_sequence.vector_value[1]    = new float  [2];
    keyframe_sequence.vector_value[2]    = new float  [2];
    keyframe_sequence.vector_value[0][0] = 1;
    keyframe_sequence.vector_value[0][1] = 2;
    keyframe_sequence.vector_value[1][0] = 3;
    keyframe_sequence.vector_value[1][1] = 4;
    keyframe_sequence.vector_value[2][0] = 5;
    keyframe_sequence.vector_value[2][1] = 6;


    M3GWriter* writer = new M3GWriter ("keyframe_sequence.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeKeyframeSequence     (keyframe_sequence);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;


    M3GReader* reader = new M3GReader ("keyframe_sequence.m3g");
    M3GKeyframeSequenceStruct keyframe_sequence2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readKeyframeSequence      (&keyframe_sequence2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_KEYFRAME_SEQUENCE, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (3, keyframe_sequence2.interpolation);
    CHECK_EQUAL (4, keyframe_sequence2.repeat_mode);
    CHECK_EQUAL (M3GKeyframeSequenceStruct::ENCODING_1, keyframe_sequence2.encoding);
    CHECK_EQUAL (5, keyframe_sequence2.duration);
    CHECK_EQUAL (6, keyframe_sequence2.valid_range_first);
    CHECK_EQUAL (7, keyframe_sequence2.valid_range_last );
    CHECK_EQUAL (2, keyframe_sequence2.component_count);
    CHECK_EQUAL (3, keyframe_sequence2.keyframe_count);
    CHECK_EQUAL (1, keyframe_sequence2.time[0]);
    CHECK_EQUAL (2, keyframe_sequence2.time[1]);
    CHECK_EQUAL (3, keyframe_sequence2.time[2]);
    // 量子化に伴う誤差が有るので入力値と完全に等しくはならない
    CHECK_CLOSE (1, keyframe_sequence2.vector_value[0][0], 0.01f);
    CHECK_CLOSE (2, keyframe_sequence2.vector_value[0][1], 0.01f);
    CHECK_CLOSE (3, keyframe_sequence2.vector_value[1][0], 0.01f);
    CHECK_CLOSE (4, keyframe_sequence2.vector_value[1][1], 0.01f);
    CHECK_CLOSE (5, keyframe_sequence2.vector_value[2][0], 0.01f);
    CHECK_CLOSE (6, keyframe_sequence2.vector_value[2][1], 0.01f);

    delete reader;
}

TEST (KeyframeSequence_encoding_2)
{
    int object_type = M3G_TYPE_KEYFRAME_SEQUENCE;
    unsigned int object_index;
    M3GKeyframeSequenceStruct keyframe_sequence;

    keyframe_sequence.interpolation     = 3;
    keyframe_sequence.repeat_mode       = 4;
    keyframe_sequence.encoding          = M3GKeyframeSequenceStruct::ENCODING_2;
    keyframe_sequence.duration          = 5;
    keyframe_sequence.valid_range_first = 6;
    keyframe_sequence.valid_range_last  = 7;
    keyframe_sequence.component_count   = 2;
    keyframe_sequence.keyframe_count    = 3;
    keyframe_sequence.time              = new unsigned int[3];
    keyframe_sequence.time[0]           = 1;
    keyframe_sequence.time[1]           = 2;
    keyframe_sequence.time[2]           = 3;
    keyframe_sequence.vector_value       = new float* [3];
    keyframe_sequence.vector_value[0]    = new float  [2];
    keyframe_sequence.vector_value[1]    = new float  [2];
    keyframe_sequence.vector_value[2]    = new float  [2];
    keyframe_sequence.vector_value[0][0] = 1;
    keyframe_sequence.vector_value[0][1] = 2;
    keyframe_sequence.vector_value[1][0] = 3;
    keyframe_sequence.vector_value[1][1] = 4;
    keyframe_sequence.vector_value[2][0] = 5;
    keyframe_sequence.vector_value[2][1] = 6;


    M3GWriter* writer = new M3GWriter ("keyframe_sequence.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeKeyframeSequence     (keyframe_sequence);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;


    M3GReader* reader = new M3GReader ("keyframe_sequence.m3g");
    M3GKeyframeSequenceStruct keyframe_sequence2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readKeyframeSequence      (&keyframe_sequence2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_KEYFRAME_SEQUENCE, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (3, keyframe_sequence2.interpolation);
    CHECK_EQUAL (4, keyframe_sequence2.repeat_mode);
    CHECK_EQUAL (M3GKeyframeSequenceStruct::ENCODING_2, keyframe_sequence2.encoding);
    CHECK_EQUAL (5, keyframe_sequence2.duration);
    CHECK_EQUAL (6, keyframe_sequence2.valid_range_first);
    CHECK_EQUAL (7, keyframe_sequence2.valid_range_last );
    CHECK_EQUAL (2, keyframe_sequence2.component_count);
    CHECK_EQUAL (3, keyframe_sequence2.keyframe_count);
    CHECK_EQUAL (1, keyframe_sequence2.time[0]);
    CHECK_EQUAL (2, keyframe_sequence2.time[1]);
    CHECK_EQUAL (3, keyframe_sequence2.time[2]);
    // 量子化に伴う誤差が有るので入力値と完全に等しくはならない
    CHECK_CLOSE (1, keyframe_sequence2.vector_value[0][0], 0.01f);
    CHECK_CLOSE (2, keyframe_sequence2.vector_value[0][1], 0.01f);
    CHECK_CLOSE (3, keyframe_sequence2.vector_value[1][0], 0.01f);
    CHECK_CLOSE (4, keyframe_sequence2.vector_value[1][1], 0.01f);
    CHECK_CLOSE (5, keyframe_sequence2.vector_value[2][0], 0.01f);
    CHECK_CLOSE (6, keyframe_sequence2.vector_value[2][1], 0.01f);

    delete reader;
}
