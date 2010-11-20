#include "m3g/m3g-gl.hpp"
#include "m3g/VertexArray.hpp"
#include "m3g/Exception.hpp"
#include "m3g/Vector.hpp"
#include "m3g/BoneWeight.hpp"
#include <iostream>
#include <cstring>
using namespace std;
using namespace m3g;



VertexArray:: VertexArray (int num_vertices, int num_components, int component_size_) :
    component_count(num_components),
    component_size(component_size_),
    vertex_count(num_vertices),
    char_values(0), vbo(0)
{
    if (vertex_count < 1 || vertex_count > 65535) {
        throw IllegalArgumentException (__FILE__, __func__, "Vertex count is invalid, vertex_count=%d.", vertex_count);
    }
    if (component_count < 2 || component_count > 4) {
        throw IllegalArgumentException (__FILE__, __func__, "Component count is invalid, component_count=%d.", component_count);
    }
    if (component_size != 1 && component_size != 2 && component_size != 4) {
        throw IllegalArgumentException (__FILE__, __func__, "Component size is invalid, component_size=%d.", component_size);
    }

    int size = vertex_count * component_count * component_size;

    char_values = new char[size];
    memset (char_values, 0, size);

    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);

    int err = glGetError ();
    if (err != GL_NO_ERROR) {
        throw OpenGLException (__FILE__, __func__, "Can't make vertex buffer object, err=%d.", err);
    }
}

VertexArray:: ~VertexArray ()
{
    delete [] char_values;
    if (glIsBuffer(vbo)) {
        glDeleteBuffers (1, &vbo);
    }
}

VertexArray:: VertexArray () :
    component_count(0),
    component_size(0),
    vertex_count(0),
    char_values(0), vbo(0)
{
}

VertexArray* VertexArray:: duplicate () const
{
    VertexArray* varry = new VertexArray (vertex_count, component_count, component_size);
    this->Object3D   :: copy (varry);
    this->VertexArray:: copy (varry);
    return varry;
}

void VertexArray:: copy (VertexArray* varry) const
{
    if (varry->component_count != component_count ||
        varry->component_size  != component_size ||
        varry->vertex_count    != vertex_count) {
        throw IllegalArgumentException (__FILE__, __func__, "VertexArray size is invalid.\n");
    }
    
    switch (component_size) {
    case 1: varry->set (0, vertex_count, char_values); break;
    case 2: varry->set (0, vertex_count, short_values); break;
    case 4: varry->set (0, vertex_count, float_values); break;
    }
}


void VertexArray:: get (int first_vertex, int num_vertices, char* values) const
{
    if (first_vertex < 0 || first_vertex >= vertex_count) {
        throw IllegalArgumentException (__FILE__, __func__, "First vertex is invalid, first_vertex=%d", first_vertex);
    }
    if (num_vertices < 0 || first_vertex + num_vertices > vertex_count) {
        throw IllegalArgumentException(__FILE__, __func__, "Number of vertices is Invalid, first_vertex=%d, num_vertices=%d.", first_vertex, num_vertices);
    }
    if (values == NULL) {
        throw NullPointerException (__FILE__, __func__, "Values is NULL.");
    }
    if (component_size != 1) {
        throw IllegalStateException (__FILE__, __func__, "Component size of this vertex array is not 1 byte, component_size=%d.", component_size);
    }

    memcpy ((char*)values, 
            (char*)&char_values[first_vertex*component_count],
            num_vertices*component_count*sizeof(char));
}

void VertexArray:: get (int first_vertex, int num_vertices, short* values) const
{
    if (first_vertex < 0 || first_vertex >= vertex_count) {
        throw IllegalStateException (__FILE__, __func__, "First vertex is invalid, first_vertex=%d.", first_vertex);
    }
    if (num_vertices < 0 || first_vertex + num_vertices > vertex_count) {
        throw IllegalStateException (__FILE__, __func__, "Number of vertices is invalid, first_vertex=%d, num_vertices=%d.", first_vertex, num_vertices);
    }
    if (values == NULL) {
        throw NullPointerException (__FILE__, __func__, "Values is NULL.");
    }
    if (component_size != 2) {
        throw IllegalStateException (__FILE__, __func__, "Component size of this vertex array is not 2 byte, component_size=%d.", component_size);
    }

    memcpy ((char*)values,
            (char*)&short_values[first_vertex*component_count],
            num_vertices*component_count*sizeof(short));
}

void VertexArray:: get (int first_vertex, int num_vertices, float* values) const
{
    if (first_vertex < 0 || first_vertex >= vertex_count) {
        throw IllegalStateException (__FILE__, __func__, "First vertex is invalid, first_vertex=%d.", first_vertex);
    }
    if (num_vertices < 0 || first_vertex + num_vertices > vertex_count) {
        throw IllegalStateException (__FILE__, __func__, "Number of vertices is invalid, first_vertex=%d, num_vertices=%d.", first_vertex, num_vertices);
    }
    if (values == NULL) {
        throw NullPointerException (__FILE__, __func__, "Values is NULL.");
    }
    if (component_size != 4) {
        throw IllegalStateException (__FILE__, __func__, "Component size of this vertex array is not 4 byte, component_size=%d.", component_size);
    }

    memcpy ((char*)values,
            (char*)&float_values[first_vertex*component_count],
            num_vertices*component_count*sizeof(float));
}


void VertexArray:: get (int first_vertex, int num_vertices, float scale, float* bias, float* values) const
{
    if (first_vertex < 0 || first_vertex >= vertex_count) {
        throw IllegalStateException (__FILE__, __func__, "First vertex is invalid, first_vertex=%d.", first_vertex);
    }
    if (num_vertices < 0 || first_vertex + num_vertices > vertex_count) {
        throw IllegalStateException (__FILE__, __func__, "Number of vertices is invalid, first_vertex=%d, num_vertices=%d.", first_vertex, num_vertices);
    }
    if (bias == NULL) {
        throw NullPointerException (__FILE__, __func__, "Bias is NULL.");
    }
    if (values == NULL) {
        throw NullPointerException (__FILE__, __func__, "Values is NULL.");
    }

    int cc = component_count;

    switch (component_size) {
    case 1:
        for (int v = 0; v < num_vertices; v++) {
            for (int i = 0; i < cc; i++) {
                values[v*cc+i] = char_values[(first_vertex+v)*cc+i] * scale + bias[i];
            }
        }
        break;
    case 2:
        for (int v = 0; v < num_vertices; v++) {
            for (int i = 0; i < cc; i++) {
                values[v*cc+i] = short_values[(first_vertex+v)*cc+i] * scale + bias[i];
            }
        }
        break;
    case 4:
        for (int v = 0; v < num_vertices; v++) {
            for (int i = 0; i < cc; i++) {
                values[v*cc+i] = float_values[(first_vertex+v)*cc+i] * scale + bias[i];
            }
        }
        break;
    default:
        throw IllegalStateException (__FILE__, __func__, "Comonent size is invalid, size=%d.", component_size);
    }

}


int VertexArray:: getComponentCount () const
{
    return component_count;
}

int VertexArray:: getComponentType () const
{
    return component_size;
}

int VertexArray:: getVertexCount () const
{
    return vertex_count;
}

void VertexArray:: set (int first_vertex, int num_vertices, const char* values)
{
    if (values == NULL) {
        throw NullPointerException (__FILE__, __func__, "Values is NULL.");
    }
    if (num_vertices < 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Number of vertices is invalid, num_vertices=%d.", num_vertices);
    }
    if (first_vertex < 0 || first_vertex + num_vertices > vertex_count) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Vertex is out of bounds, [%d,%d) in [0,%d).", first_vertex, first_vertex+num_vertices, vertex_count);
    }
    if (component_size != 1) {
        throw IllegalStateException (__FILE__, __func__, "Component size of this vertex array is not 1 byte, component_size=%d.", component_size);
    }
    if (vbo == 0) {
        throw OpenGLException (__FILE__, __func__, "Vertex Buffre Object is not ready.");
    }

    int offset      = first_vertex*component_count;
    int offset_size = first_vertex*component_count*sizeof(char);
    int size        = num_vertices*component_count*sizeof(char);

    memcpy ((char*)&char_values[offset],
            (char*)values,
            size);

    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferSubData (GL_ARRAY_BUFFER,
                     offset_size,
                     size, 
                     &char_values[offset]);

    int err = glGetError ();
    if (err != GL_NO_ERROR) {
        throw OpenGLException (__FILE__, __func__, "Can't send to GPU, err=%d.", err);
    }
    
}

void VertexArray:: set (int first_vertex, int num_vertices, const short* values)
{
    if (values == NULL) {
        throw NullPointerException (__FILE__, __func__, "Values is NULL.");
    }
    if (num_vertices < 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Number of vertices is invalid, num_vertices=%d.", num_vertices);
    }
    if (first_vertex < 0 || first_vertex + num_vertices > vertex_count) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Vertex is out of bounds, [%d,%d) in [0,%d).", first_vertex, first_vertex+num_vertices, vertex_count);
    }
    if (component_size != 2) {
        throw IllegalStateException (__FILE__, __func__, "Component size of this vertex array is not 2 byte, component_size=%d.", component_size);
    }
    if (vbo == 0) {
        throw OpenGLException (__FILE__, __func__, "Vertex Buffre Object is not ready.");
    }

    int offset      = first_vertex*component_count;
    int offset_size = first_vertex*component_count*sizeof(short);
    int size        = num_vertices*component_count*sizeof(short);

    //cout << "vbo         = " << vbo << "\n";
    //cout << "offset      = " << offset      << "\n";
    //cout << "offset_size = " << offset_size << "\n";
    //cout << "size        = " << size        << "\n";

    memcpy ((char*)&short_values[offset],
            (char*)values,
            size);

    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferSubData (GL_ARRAY_BUFFER,
                     offset_size,
                     size,
                     &short_values[offset]);

    int err = glGetError ();
    if (err != GL_NO_ERROR) {
        throw OpenGLException (__FILE__, __func__, "Can't send to GPU, err=%d.", err);
    }
}

void VertexArray:: set (int first_vertex, int num_vertices, const float* values)
{
    if (values == NULL) {
        throw NullPointerException (__FILE__, __func__, "Values is NULL.");
    }
    if (num_vertices < 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Number of vertices is invalid, num_vertices=%d.", num_vertices);
    }
    if (first_vertex < 0 || first_vertex + num_vertices > vertex_count) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Vertex is out of bounds, [%d,%d) in [0,%d).", first_vertex, first_vertex+num_vertices, vertex_count);
    }
    if (component_size != 4) {
        throw IllegalStateException (__FILE__, __func__, "Component size of this vertex array is not 4 byte, component_size=%d.", component_size);
    }
    if (vbo == 0) {
        throw OpenGLException (__FILE__, __func__, "Vertex Buffre Object is not ready.");
    }

    int offset      = first_vertex*component_count;
    int offset_size = first_vertex*component_count*sizeof(float);
    int size        = num_vertices*component_count*sizeof(float);

    memcpy ((char*)&float_values[offset],
            (char*)values,
            size);

    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferSubData (GL_ARRAY_BUFFER,
                     offset_size,
                     size,
                     &float_values[offset]);

    int err = glGetError ();
    if (err != GL_NO_ERROR) {
        throw OpenGLException (__FILE__, __func__, "Can't send to GPU, err=%d.", err);
    }
}


void VertexArray:: setMorphing (const VertexArray* base,
                                const std::vector<const VertexArray*>& targets,
                                const std::vector<float>& weights)
{
    if (base == NULL) {
        throw NullPointerException (__FILE__, __func__, "Base vertex array is NULL.");
    }
    if (targets.size() != weights.size()) {
        throw IllegalArgumentException (__FILE__, __func__, "Size of targes and weight must be same, %d,%d.", targets.size(), weights.size());
    }
    if (vbo == 0) {
        throw OpenGLException (__FILE__, __func__, "Vertex Buffre Object is not ready.");
    }


    for (int v = 0; v < vertex_count; v++) {
        Vector v0, v2;
        switch (base->component_size) {
        case 1: v2 = v0 = Vector (base->char_values[v*3  ],
                                  base->char_values[v*3+1],
                                  base->char_values[v*3+2]); break;
        case 2: v2 = v0 = Vector (base->short_values[v*3  ],
                                  base->short_values[v*3+1],
                                  base->short_values[v*3+2]); break;
        case 4: v2 = v0 = Vector (base->float_values[v*3  ],
                                  base->float_values[v*3+1],
                                  base->float_values[v*3+2]); break;
        }
        for (int t = 0; t < (int)targets.size(); t++) {
            Vector v1;
            switch (targets[t]->component_size) {
            case 1: v1 = Vector (targets[t]->char_values[v*3  ],
                                 targets[t]->char_values[v*3+1],
                                 targets[t]->char_values[v*3+2]); break;
            case 2: v1 = Vector (targets[t]->short_values[v*3  ],
                                 targets[t]->short_values[v*3+1],
                                 targets[t]->short_values[v*3+2]); break;
            case 4: v1 = Vector (targets[t]->float_values[v*3  ],
                                 targets[t]->float_values[v*3+1],
                                 targets[t]->float_values[v*3+2]); break;
            }
            v2 += weights[t] * (v1 - v0);
        }
        for (int i = 0; i < 3; i++) {
            switch (component_size) {
            case 1: char_values  [v*3+i] = v2[i]; break;
            case 2: short_values [v*3+i] = v2[i]; break;
            case 4: float_values [v*3+i] = v2[i]; break;
            }
        }
    }  // バーテックスループ

    glBindBuffer    (GL_ARRAY_BUFFER, vbo);
    glBufferSubData (GL_ARRAY_BUFFER,
                     0,
                     vertex_count * component_count * component_size,
                     char_values);

    int err = glGetError ();
    if (err != GL_NO_ERROR) {
        throw OpenGLException (__FILE__, __func__, "Can't send to GPU, err=%d.", err);
    }
}


void VertexArray:: setSkinning (const VertexArray* base_positions,
                                const std::vector<std::vector<BoneWeight> >& bone_indices,
                                const std::vector<Matrix>& matrix_palette)
{
    if (base_positions == NULL) {
        throw NullPointerException (__FILE__, __func__, "Base vertex array is NULL.");
    }
    if (vbo == 0) {
        throw OpenGLException (__FILE__, __func__, "Vertex Buffre Object is not ready.");
    }

    for (int v = 0; v < vertex_count; v++) {
        Vector v0;
        switch (base_positions->component_size) {
        case 1: v0 = Vector(base_positions->char_values [v*3  ],
                            base_positions->char_values [v*3+1],
                            base_positions->char_values [v*3+2]); break;
        case 2: v0 = Vector(base_positions->short_values[v*3  ],
                            base_positions->short_values[v*3+1],
                            base_positions->short_values[v*3+2]); break;
        case 4: v0 = Vector(base_positions->float_values[v*3  ],
                            base_positions->float_values[v*3+1],
                            base_positions->float_values[v*3+2]); break;
        default: throw IllegalStateException (__FILE__, __func__, "Component size is invalid, size=%d.", base_positions->component_size);
        }
        Vector v1         = Vector(0,0,0);
        float  weight     = 0;
        int    bone_count = bone_indices[v].size();
        for (int b = 0; b < bone_count; b++) {
            weight += bone_indices[v][b].weight;
        }
        for (int b = 0; b < bone_count; b++) {
            int i = bone_indices[v][b].index;
            v1 += matrix_palette[i] * v0 * (bone_indices[v][b].weight/weight);
        }
        if (weight > 0) {
            for (int i = 0; i < 3; i++) {
                switch (component_size) {
                case 1: char_values [v*3+i] = v1[i]; break;
                case 2: short_values[v*3+i] = v1[i]; break;
                case 4: float_values[v*3+i] = v1[i]; break;
                }
            }
        }
    }   // バーテックスループ

    glBindBuffer    (GL_ARRAY_BUFFER, vbo);
    glBufferSubData (GL_ARRAY_BUFFER,
                     0,
                     vertex_count * component_count * component_size,
                     char_values);

    int err = glGetError ();
    if (err != GL_NO_ERROR) {
        throw OpenGLException (__FILE__, __func__, "Can't send to GPU, err=%d.", err);
    }
}

void VertexArray:: updateOpenGLData (const void* values) const
{
    if (values == NULL) {
        throw NullPointerException (__FILE__, __func__, "Values is NULL.");
    }
    if (vbo == 0) {
        throw OpenGLException (__FILE__, __func__, "Vertex Buffre Object is not ready.");
    }

    glBindBuffer    (GL_ARRAY_BUFFER, vbo);
    glBufferSubData (GL_ARRAY_BUFFER,
                     0,
                     vertex_count * component_count * component_size,
                     values);

    int err = glGetError ();
    if (err != GL_NO_ERROR) {
        throw OpenGLException (__FILE__, __func__, "Can't send to GPU, err=%d.", err);
    }
}

void VertexArray:: convert (int to)
{
    if (component_size == to)
        return;

    int from = component_size;
    int num  = vertex_count * component_count;
    union {
        char*  target_char_values;
        short* target_short_values;
        float* target_float_values;
    };

    switch (to) {
    case 1: target_char_values  = new char[num]; break;
    case 2: target_short_values = new short[num]; break;
    case 4: target_float_values = new float[num]; break;
    default: throw IllegalStateException (__FILE__, __func__, "Target component type is invalid, type=%d.", to);
    }

    switch (from) {
    case 1: {
        switch (to) {
        case 1: for (int i = 0; i < num; i++) target_char_values[i]  = char_values[i]; break;
        case 2: for (int i = 0; i < num; i++) target_short_values[i] = char_values[i]; break;
        case 4: for (int i = 0; i < num; i++) target_float_values[i] = char_values[i]; break;
        }
        break;
    }
    case 2: {
        switch (to) {
        case 1: for (int i = 0; i < num; i++) target_char_values[i]  = short_values[i]; break;
        case 2: for (int i = 0; i < num; i++) target_short_values[i] = short_values[i]; break;
        case 4: for (int i = 0; i < num; i++) target_float_values[i] = short_values[i]; break;
        }
        break;
    }
    case 4: {
        switch (to) {
        case 1: for (int i = 0; i < num; i++) target_char_values[i]  = float_values[i]; break;
        case 2: for (int i = 0; i < num; i++) target_short_values[i] = float_values[i]; break;
        case 4: for (int i = 0; i < num; i++) target_float_values[i] = float_values[i]; break;
        }
        break;
    }
    default: {
        throw IllegalStateException (__FILE__, __func__, "Source component type is invalid, type=%d.", from);
    }
    }

    component_size = to;
    delete [] char_values;
    char_values = target_char_values;

    if (glIsBuffer (vbo)) {
        glDeleteBuffers (1, &vbo);
    }
    int size = vertex_count * component_count * component_size;

    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, size, char_values, GL_STATIC_DRAW);
}


unsigned int VertexArray:: getOpenGLVBO () const
{
    return vbo;
}

unsigned int VertexArray:: getOpenGLFormat () const
{
    switch (component_size) {
    case 1: return GL_BYTE;
    case 2: return GL_SHORT;
    case 4: return GL_FLOAT;
    default: throw IllegalStateException (__FILE__, __func__, "Component type is invalid, type=%d.", component_size);
    }
}


std::ostream& VertexArray:: print (std::ostream& out) const
{
    out << "VertexArray: ";
    out << vertex_count << " vertices (";
    out << component_size << "byte x " << component_count << "comps / vertex)";
    out << ", vbo=" << vbo;
    return out;
}

std::ostream& VertexArray:: print_raw_data (std::ostream& out) const
{
    print (out) << "\n";
    for (int i = 0; i < vertex_count*component_count; i+=component_count) {
        out << i/component_count << " : (";
        for (int j = 0; j < component_count; j++) {
            switch (component_size) {
            case 1: out << (int)char_values[i+j]  << ", "; break;
            case 2: out << (int)short_values[i+j] << ", "; break;
            case 4: out <<      float_values[i+j] << ", "; break;
            default: throw IllegalStateException (__FILE__, __func__, "Component size is invalid, size=%d.", component_size);
            }
        }
        out << ")\n";
    }

    return out;
}

std::ostream& operator<< (std::ostream& out, const VertexArray& vary)
{
    return vary.print(out);
}
