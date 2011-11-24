#include "m3g/m3g-gl.hpp"
#include "m3g/TriangleStripArray.hpp"
#include "m3g/Exception.hpp"
#include "m3g/RenderState.hpp"
#include <iostream>
using namespace std;
using namespace m3g;

/**
 * メモ：このクラスは何もせずIndexBufferが全て処理する。
 *       事実TriangleStripArrayクラスはM3G-2.0で廃止され、
 *       IndexBufferクラスに統合される事が決定している。
 *       それの先取り。
 */
TriangleStripArray:: TriangleStripArray (int        num_indices,
                                         const int* indices,
                                         int        num_lengths,
                                         const int* lengths     )
    : IndexBuffer(IndexBuffer::TRIANGLES, num_indices, indices, num_lengths, lengths)
{
}


TriangleStripArray:: TriangleStripArray (int        first_index,
                                         int        num_lengths,
                                         const int* lengths     )
    : IndexBuffer(IndexBuffer::TRIANGLES, first_index, num_lengths, lengths)
{
}

TriangleStripArray:: ~TriangleStripArray ()
{
}

TriangleStripArray* TriangleStripArray:: duplicate () const
{
    return duplicate_xxx (NULL);
}

TriangleStripArray* TriangleStripArray:: duplicate_xxx (Object3D* obj) const
{
    TriangleStripArray* tris = dynamic_cast<TriangleStripArray*>(obj);
    if (tris == NULL) {
        tris = new TriangleStripArray (strip_indices.size(),
                                       &strip_indices[0],
                                       strip_lengths.size(),
                                       &strip_lengths[0]);
    }
    IndexBuffer:: duplicate_xxx (tris);

    return tris;
}


std::ostream& TriangleStripArray:: print (std::ostream& out) const
{
    out << "TriangleStripArray : ";
    IndexBuffer:: print (out);
    return out;
}


std::ostream& operator<< (std::ostream& out, const TriangleStripArray& tris)
{
    return tris.print(out);
}


