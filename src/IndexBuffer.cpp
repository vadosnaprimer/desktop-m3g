#include "IndexBuffer.hpp"
#include "Exception.hpp"
#include <iostream>
#include <cstring>
using namespace m3g;
using namespace std;


IndexBuffer:: IndexBuffer ()
{
}

IndexBuffer:: ~IndexBuffer ()
{
}

IndexBuffer* IndexBuffer:: duplicate () const
{
    return new IndexBuffer (*this);
}


/**
 *
 */
int IndexBuffer:: getFaceCount () const
{
    // 後で実装する
    return 0;
}

/**
 *
 */
int IndexBuffer:: getFaceVertexCount () const
{
    // 後で実装する
    return 0;
}

/**
 *
 */
void IndexBuffer:: getFaceIndex (int face, int* indices) const
{
    // 後で実装する
    return;
}


int IndexBuffer:: getIndexCount () const
{
    return 0;
}

void IndexBuffer:: getIndices (int*)
{
}

/**
 * Note: Background should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void IndexBuffer:: render (RenderState& state) const
{
    // nothing to do.
}

std::ostream& IndexBuffer:: print (std::ostream& out) const
{
    out << "IndexBuffer: ";
    return out;
}


std::ostream& operator<< (std::ostream& out, const IndexBuffer& ibuf)
{
    return ibuf.print (out);
}


