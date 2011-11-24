#include "m3g/m3g-gl.hpp"
#include "m3g/IndexBuffer.hpp"
#include "m3g/Exception.hpp"
#include "m3g/RenderState.hpp"
#include <iostream>
#include <climits>
using namespace m3g;
using namespace std;

const int IndexBuffer:: TRIANGLES;
const int IndexBuffer:: LINES;
const int IndexBuffer:: POINT_SPRITES;


IndexBuffer:: IndexBuffer (int        type_,
                           int        num_indices,
                           const int* indices,
                           int        num_lengths,
                           const int* lengths     ) : type(type_), gl(0)
{
    if (type != TRIANGLES) {
        throw IllegalArgumentException (__FILE__, __func__, "Primitive type is invalid, type=%d.", type);        
    }
    if (indices == NULL) {
        throw NullPointerException (__FILE__, __func__, "Indices is NULL.");
    }
    if (lengths == NULL) {
        throw NullPointerException (__FILE__, __func__, "Strip lengths is NULL.");
    }
    if (num_lengths < 1) {
        throw IllegalArgumentException (__FILE__, __func__, "Number of strips is invalid, num_lengths=%d.", num_lengths);
    }
    int sum = 0;
    for (int i = 0; i < num_lengths; i++) {
        int len = lengths[i];
        if (len < 0 || len > (int)INT_MAX) {
            throw IndexOutOfBoundsException (__FILE__, __func__, "Strip lengths[%d] is out of index, len=%d.", i, len);
        }
        if (len < 3) {
            throw IllegalArgumentException (__FILE__, __func__, "Strip lengths[%d] is invalid, len=%d.", i, len);
        }
        sum += len;
    }
    if (num_indices < sum) {
        throw IllegalArgumentException (__FILE__, __func__, "Too few indices, indices=%d < sum of lengths=%d.", num_indices, sum);
    }

    strip_indices.assign (indices, indices + num_indices);
    strip_lengths.assign (lengths, lengths + num_lengths);

    glGenBuffers (1, &gl.indices);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, gl.indices); 
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*num_indices, &strip_indices[0], GL_STATIC_DRAW);
}


IndexBuffer:: IndexBuffer (int        type_,
                           int        first_index,
                           int        num_lengths,
                           const int* lengths     ) : type(type_), gl(0)
{
    if (type != TRIANGLES) {
        throw IllegalArgumentException (__FILE__, __func__, "Primitive type is invalid, type=%d.", type);        
    }
    if (lengths == NULL) {
        throw NullPointerException (__FILE__, __func__, "Strip lengths is NULL.");
    }
    if (num_lengths <= 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Number of strips is invalid, num_lengths=%d.", num_lengths);
    }

    int num_indices = 0;
    for (int i = 0; i < num_lengths; i++) {
        int len = lengths[i];
        if (len < 0 || len > (int)INT_MAX) {
            throw IndexOutOfBoundsException (__FILE__, __func__, "Strip lengths[%d] is out of index, len=%d.", i, len);
        }
        if (len < 3) {
            throw IllegalArgumentException (__FILE__, __func__, "Strip lengths[%d] is invalid, len=%d.", i, len);
        }
        num_indices += len;
    }
    if (first_index + num_indices > (int)INT_MAX) {
        throw IllegalArgumentException (__FILE__, __func__, "Number of indices is invalid, num=%d > INT_MAX.", first_index+num_indices);
    }

    strip_indices.reserve (num_indices);
    for (int i = 0; i < num_indices; i++) {
        strip_indices.push_back (first_index + i);
    }
    strip_lengths.assign (lengths, lengths + num_lengths);


    glGenBuffers (1, &gl.indices);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, gl.indices); 
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*num_indices, &strip_indices[0], GL_STATIC_DRAW);
}

IndexBuffer:: ~IndexBuffer ()
{
    if (glIsBuffer(gl.indices)) {
        glDeleteBuffers (1, &gl.indices);
    }
}

IndexBuffer* IndexBuffer:: duplicate () const
{
    return duplicate_xxx (NULL);
}

IndexBuffer* IndexBuffer:: duplicate_xxx (Object3D* obj) const
{
    IndexBuffer* ibuf = dynamic_cast<IndexBuffer*>(obj);
    if (ibuf == NULL) {
        ibuf = new IndexBuffer (type,
                                strip_indices.size(),
                                &strip_indices[0],
                                strip_lengths.size(),
                                &strip_lengths[0]);
    }
    Object3D:: duplicate_xxx (ibuf);

    return ibuf;
}


int IndexBuffer:: getPrimitiveType () const
{
    return type;
}

// メモ：ストリップはトライアングルの集合に分解して返す
int IndexBuffer:: getIndexCount () const
{
    int num = 0;
    switch (type) {
    case TRIANGLES:
        for (int i = 0; i < (int)strip_lengths.size(); i++) {
            num += (strip_lengths[i]-2)*3;
        }
        break;
    case LINES:
    case POINT_SPRITES:
    default:
        throw InternalException (__FILE__, __func__, "Primitive type is invalid, type=%d.", type);
    };
    return num;
}

// メモ：ストリップはトライアングルの集合に分解して返す
void IndexBuffer:: getIndices (int* indices) const
{
    int i = 0;
    int j = 0;
    switch (type) {
    case TRIANGLES:
        for (int s = 0; s < (int)strip_lengths.size(); s++) {
            for (int t = 0; t < strip_lengths[s]-2; t++) {
                indices[j++] = strip_indices[i+0];
                indices[j++] = strip_indices[i+1];
                indices[j++] = strip_indices[i+2];
                i++;
            }
            i += 2;
        }   
        break;
    case LINES:
    case POINT_SPRITES:
    default:
        throw InternalException (__FILE__, __func__, "Primitive type is invalid, type=%d.", type);
    };

}

/**
 * Note: Background should be rendered only at 2nd rendering pass(pass=2).
 * In other cases, do nothing.
 */
void IndexBuffer:: render_xxx (RenderState& state) const
{
   if (state.pass != 2) {
        return;
    }

    if (gl.indices == 0) {
        throw OpenGLException (__FILE__, __func__, "Buffer object of index is not ready, vbo=%d.", gl.indices);
    }

    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, gl.indices);

    long long offset = 0;
    for (int i = 0; i < (int)strip_lengths.size(); i++) {
        glDrawElements (GL_TRIANGLE_STRIP,
                        strip_lengths[i],
                        GL_UNSIGNED_INT,
                        (GLvoid*)offset);
        offset += strip_lengths[i] * sizeof(int);
    }
}

std::ostream& IndexBuffer:: print_raw_data (std::ostream& out) const
{
    print (out) << "\n";
    int offset = 0;
    for (int i = 0; i < (int)strip_lengths.size(); i++) {
        out << " " << i << " (" << strip_lengths[i] << ") : ";
        for (int j = 0; j < strip_lengths[i]; j++) {
            out << strip_indices[offset] << ",";
            offset++;
        }
        out << "\n";
    }

    return out;
}

static
const char* type_to_string (int type)
{
    switch (type) {
    case IndexBuffer::TRIANGLES    :return "TRIANGLES";
    case IndexBuffer::LINES        :return "LINES";
    case IndexBuffer::POINT_SPRITES:return "POINT_SPRITES";
    default: return "Unknown";
    }
}

std::ostream& IndexBuffer:: print (std::ostream& out) const
{
    out << "IndexBuffer: ";
    out << "  type=" << type_to_string(type) << ", strip_lengths=[";
    for (int i = 0; i < (int)strip_lengths.size(); i++) {
        out << strip_lengths[i] << " ";
    }
    out << "]";
    return out;
}


std::ostream& operator<< (std::ostream& out, const IndexBuffer& ibuf)
{
    return ibuf.print (out);
}


