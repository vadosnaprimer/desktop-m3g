#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstring>
#include "m3g/TriangleStripArray.hpp"
using namespace std;
using namespace m3g;


TEST (TriangleStripArray_set_variables_explicit)
{
    // TriangleStripArray (int* indices, int num_strip_lengths, int* strip_lengths);

    int indices[10] = {2,4,6,8,10,12,14,16,18,20};
    int strip_lengths[3] = {4,3,3};
    TriangleStripArray* tris = new TriangleStripArray (indices, 3, strip_lengths);

    CHECK_EQUAL (10, tris->getIndexCount());

    int index_buf[10];
    tris->getIndices (index_buf);
    CHECK_EQUAL (2, index_buf[0]);
    CHECK_EQUAL (20, index_buf[9]);

  
    CHECK_EQUAL (10, (int)tris->getIndexCount());
}

TEST (TriangleStripArray_set_variables_implicit)
{
    // TriangleStripArray (int first_index, int num_strip_lengths, int* strip_lengths);

    int strip_lengths[3] = {4,3,3};
    TriangleStripArray* tris = new TriangleStripArray (100, 3, strip_lengths);

    CHECK_EQUAL (10, tris->getIndexCount());

    int index_buf[10];
    tris->getIndices (index_buf);
    CHECK_EQUAL (100, index_buf[0]);
    CHECK_EQUAL (109, index_buf[9]);
}

TEST (TriangleStripArray_duplicate)
{
    int strip_lengths[3] = {4,3,3};
    TriangleStripArray* tris0 = new TriangleStripArray (100, 3, strip_lengths);
    TriangleStripArray* tris1 = tris0->duplicate();

    CHECK_EQUAL (tris0->getIndexCount(), tris1->getIndexCount());

    int indices0[10];
    tris0->getIndices (indices0);
    CHECK_EQUAL (100, indices0[0]);
    CHECK_EQUAL (109, indices0[9]);

    int indices1[10];
    tris1->getIndices (indices1);
    CHECK_EQUAL (100, indices1[0]);
    CHECK_EQUAL (109, indices1[9]);

    // duplicate()は深いコピーなので
    // インターフェースがないのでチェックできない……
}

TEST (TriangleStripArray_get_face_index)
{
    int strips[3] = {4,3,3};
    TriangleStripArray* tris = new TriangleStripArray (100, 3, strips);
    
    CHECK_EQUAL (4, tris->getFaceCount());
    CHECK_EQUAL (3, tris->getFaceVertexCount());
    
    int indices[3];

    tris->getFaceVertexIndex (0, indices);
    CHECK_EQUAL (100, indices[0]);
    CHECK_EQUAL (101, indices[1]);
    CHECK_EQUAL (102, indices[2]);

    tris->getFaceVertexIndex (1, indices);
    CHECK_EQUAL (101, indices[0]);
    CHECK_EQUAL (102, indices[1]);
    CHECK_EQUAL (103, indices[2]);

    tris->getFaceVertexIndex (2, indices);
    CHECK_EQUAL (104, indices[0]);
    CHECK_EQUAL (105, indices[1]);
    CHECK_EQUAL (106, indices[2]);

    tris->getFaceVertexIndex (3, indices);
    CHECK_EQUAL (107, indices[0]);
    CHECK_EQUAL (108, indices[1]);
    CHECK_EQUAL (109, indices[2]);



}
