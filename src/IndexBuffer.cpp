#include "m3g/m3g-gl.hpp"
#include "m3g/IndexBuffer.hpp"
#include "m3g/Exception.hpp"
#include "m3g/RenderState.hpp"
#include <iostream>
#include <numeric>
using namespace m3g;
using namespace std;

const int IndexBuffer:: TRIANGLES;
const int IndexBuffer:: LINES;
const int IndexBuffer:: POINT_SPRITES;


IndexBuffer:: IndexBuffer (int        t,
                           const int* indices,
                           int        num_strips,
                           const int* lengths) : type(t), name(0)
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
    if (num_strips < 1 || num_strips > 65535) {
        throw IllegalArgumentException (__FILE__, __func__, "Number of strips is invalid, num_strips=%d.", num_strips);
    }

    strip_lengths.assign (lengths, lengths + num_strips);
    
    int num = accumulate (strip_lengths.begin(), strip_lengths.end(), 0);
    strip_indices.assign (indices, indices + num);

    glGenBuffers (1, &name);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, name); 
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*num, &strip_indices[0], GL_STATIC_DRAW);
}


IndexBuffer:: IndexBuffer (int        t,
                           int        first_index,
                           int        num_strips,
                           const int* lengths) : type(t), name(0)
{
    if (type != TRIANGLES) {
        throw IllegalArgumentException (__FILE__, __func__, "Primitive type is invalid, type=%d.", type);        
    }
    if (lengths == NULL) {
        throw NullPointerException (__FILE__, __func__, "Strip lengths is NULL.");
    }
    if (first_index < 0 || first_index > 65535) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Fist index is invalid, first_idex=%d.", first_index);
    }
    if (num_strips < 1 || first_index + num_strips > 65536) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Nummber of strip is invalid, first_index=%d, num_strips=%d.", first_index, num_strips);
    }

    strip_lengths.assign (lengths, lengths + num_strips);

    int num = accumulate (strip_lengths.begin(), strip_lengths.end(), 0);
    strip_indices.reserve (num);
    for (int i = 0; i < num; i++) {
        strip_indices.push_back (first_index + i);
    }

    glGenBuffers (1, &name);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, name); 
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*num, &strip_indices[0], GL_STATIC_DRAW);


}

IndexBuffer:: ~IndexBuffer ()
{
    if (glIsBuffer(name)) {
        glDeleteBuffers (1, &name);
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

// メモ：プリミティブのリストで返す。
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
        throw InternalException (__FILE__, __func__, "Primitive type is invalid, type=%d\n", type);
    };
    return num;
}

// メモ：プリミティブのリストで返す。
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
        throw InternalException (__FILE__, __func__, "Primitive type is invalid, type=%d\n", type);
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

    if (name == 0) {
        throw OpenGLException (__FILE__, __func__, "Buffer object of index is not ready, name=%d.", name);
    }

    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, name);

    int offset = 0;
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


