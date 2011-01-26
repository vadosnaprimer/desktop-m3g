#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstring>
#include "m3g/IndexBuffer.hpp"
#include "m3g/TriangleStripArray.hpp"
using namespace std;
using namespace m3g;


TEST (TriangleStripArray_default_variables)
{
    int indices[] = {0,1,2};
    int strip_lengths[1] = {3};
    TriangleStripArray* tris = new TriangleStripArray (indices, 1, strip_lengths);
    
    CHECK_EQUAL (IndexBuffer::TRIANGLES, tris->getPrimitiveType());
}

TEST (TriangleStripArray_set_variables_explicit)
{
    // TriangleStripArray (int* indices, int num_strip_lengths, int* strip_lengths);

    int indices[10] = {2,4,6,8,10,12,14,16,18,20};
    int strip_lengths[3] = {4,3,3};
    TriangleStripArray* tris = new TriangleStripArray (indices, 3, strip_lengths);

    CHECK_EQUAL (12, tris->getIndexCount());

    int index_buf[12];
    tris->getIndices (index_buf);
    CHECK_EQUAL (2, index_buf[0]);
    CHECK_EQUAL (4, index_buf[1]);
    CHECK_EQUAL (6, index_buf[2]);
    CHECK_EQUAL (4, index_buf[3]);
    CHECK_EQUAL (6, index_buf[4]);
    CHECK_EQUAL (8, index_buf[5]);
    CHECK_EQUAL (10, index_buf[6]);
    CHECK_EQUAL (12, index_buf[7]);
    CHECK_EQUAL (14, index_buf[8]);
    CHECK_EQUAL (16, index_buf[9]);
    CHECK_EQUAL (18, index_buf[10]);
    CHECK_EQUAL (20, index_buf[11]);
}

TEST (TriangleStripArray_set_variables_implicit)
{
    int first_index = 100;
    int strip_lengths[3] = {4,3,3};
    TriangleStripArray* tris = new TriangleStripArray (first_index, 3, strip_lengths);

    CHECK_EQUAL (12, tris->getIndexCount());

    int index_buf[12];
    tris->getIndices (index_buf);
    CHECK_EQUAL (100, index_buf[0]);
    CHECK_EQUAL (101, index_buf[1]);
    CHECK_EQUAL (102, index_buf[2]);
    CHECK_EQUAL (101, index_buf[3]);
    CHECK_EQUAL (102, index_buf[4]);
    CHECK_EQUAL (103, index_buf[5]);
    CHECK_EQUAL (104, index_buf[6]);
    CHECK_EQUAL (105, index_buf[7]);
    CHECK_EQUAL (106, index_buf[8]);
    CHECK_EQUAL (107, index_buf[9]);
    CHECK_EQUAL (108, index_buf[10]);
    CHECK_EQUAL (109, index_buf[11]);
}

TEST (TriangleStripArray_duplicate)
{
    int first_index = 100;
    int strip_lengths[3] = {4,3,3};
    TriangleStripArray* tris0 = new TriangleStripArray (first_index, 3, strip_lengths);
    TriangleStripArray* tris1 = tris0->duplicate();

    CHECK_EQUAL (tris0->getIndexCount(), tris1->getIndexCount());

    int index_buf[12];
    tris1->getIndices (index_buf);
    CHECK_EQUAL (100, index_buf[0]);
    CHECK_EQUAL (101, index_buf[1]);
    CHECK_EQUAL (102, index_buf[2]);
    CHECK_EQUAL (101, index_buf[3]);
    CHECK_EQUAL (102, index_buf[4]);
    CHECK_EQUAL (103, index_buf[5]);
    CHECK_EQUAL (104, index_buf[6]);
    CHECK_EQUAL (105, index_buf[7]);
    CHECK_EQUAL (106, index_buf[8]);
    CHECK_EQUAL (107, index_buf[9]);
    CHECK_EQUAL (108, index_buf[10]);
    CHECK_EQUAL (109, index_buf[11]);
}

