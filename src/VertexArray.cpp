#include "VertexArray.hpp"
#include "Exception.hpp"
#include "Vector.hpp"
#include "BoneIndex.hpp"
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
}

VertexArray:: ~VertexArray ()
{
    delete [] char_values;
    if (glIsBuffer(vbo)) {
        glDeleteBuffers (1, &vbo);
    }
}

VertexArray* VertexArray:: duplicate () const
{
    VertexArray* varry = new VertexArray (*this);
    Object3D* obj      = Object3D::duplicate();
    *(Object3D*)varry  = *obj;

    int size           = vertex_count * component_count * component_size;
    varry->char_values = new char[size];
    memcpy (varry->char_values, this->char_values, size);

    glGenBuffers (1, &varry->vbo);
    glBindBuffer (GL_ARRAY_BUFFER, varry->vbo);
    glBufferData (GL_ARRAY_BUFFER, size, varry->char_values, GL_STATIC_DRAW);
    return varry;
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
        for (int v = first_vertex; v < first_vertex+num_vertices; v++) {
            for (int i = 0; i < cc; i++) {
                values[v*cc+i] = char_values[v*cc+i] * scale + bias[i];
            }
        }
        break;
    case 2:
        for (int v = first_vertex; v < first_vertex+num_vertices; v++) {
            for (int i = 0; i < cc; i++) {
                values[v*cc+i] = short_values[v*cc+i] * scale + bias[i];
            }
        }
        break;
    case 4:
        for (int v = first_vertex; v < first_vertex+num_vertices; v++) {
            for (int i = 0; i < cc; i++) {
                values[v*cc+i] = float_values[v*cc+i] * scale + bias[i];
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
}


void VertexArray:: setMorphing (const VertexArray* base,
                                const std::vector<const VertexArray*>& targets,
                                const std::vector<float>& weights)
{
    int size = vertex_count * component_count * component_size;
    memcpy (char_values, base->char_values, size);

    //cout << "targets.size() = " << targets.size() << "\n";
    //for (int t = 0; t < (int)targets.size(); t++) {
    //  cout << t << " : target = " << targets[t] << ", weights = " << weights[t] << "\n";
    //}

    for (int t = 0; t < (int)targets.size(); t++) {
        if (targets[t]) {
            for (int v = 0; v < vertex_count; v++) {
                switch (component_size) {
                case 1:
                    char_values[v*3  ] += weights[t] * (targets[t]->char_values[v*3  ] - base->char_values[v*3  ]);
                    char_values[v*3+1] += weights[t] * (targets[t]->char_values[v*3+1] - base->char_values[v*3+1]);
                    char_values[v*3+2] += weights[t] * (targets[t]->char_values[v*3+2] - base->char_values[v*3+2]);
                    break;
                case 2:
                    short_values[v*3  ] += weights[t] * (targets[t]->short_values[v*3  ] - base->short_values[v*3  ]);
                    short_values[v*3+1] += weights[t] * (targets[t]->short_values[v*3+1] - base->short_values[v*3+1]);
                    short_values[v*3+2] += weights[t] * (targets[t]->short_values[v*3+2] - base->short_values[v*3+2]);
                    break;
                case 4:
                    float_values[v*3  ] += weights[t] * (targets[t]->float_values[v*3  ] - base->float_values[v*3  ]);
                    float_values[v*3+1] += weights[t] * (targets[t]->float_values[v*3+1] - base->float_values[v*3+1]);
                    float_values[v*3+2] += weights[t] * (targets[t]->float_values[v*3+2] - base->float_values[v*3+2]);
                    break;
                }
            }  // バーテックスループ
        }
    }  // ターゲットループ

    glBindBuffer    (GL_ARRAY_BUFFER, vbo);
    glBufferSubData (GL_ARRAY_BUFFER,
                     0,
                     vertex_count * component_count * component_size,
                     char_values);
}


void VertexArray:: setSkinning (const VertexArray* base_positions,
                                const std::vector<std::vector<BoneIndex> >& bone_indices,
                                const std::vector<Matrix>& matrix_palette)
{
    for (int v = 0; v < vertex_count; v++) {
        Vector v0;
        switch (component_size) {
        case 1: v0 = Vector(base_positions->char_values [v*3  ],
                            base_positions->char_values [v*3+1],
                            base_positions->char_values [v*3+2]); break;
        case 2: v0 = Vector(base_positions->short_values[v*3  ],
                            base_positions->short_values[v*3+1],
                            base_positions->short_values[v*3+2]); break;
        case 4: v0 = Vector(base_positions->float_values[v*3  ],
                            base_positions->float_values[v*3+1],
                            base_positions->float_values[v*3+2]); break;
        default: throw IllegalStateException (__FILE__, __func__, "Component type is invalid, size=%d.", component_size);
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
            float vector_values[3];
            v1.get (vector_values);
            for (int i = 0; i < 3; i++) {
                switch (component_size) {
                case 1: char_values [v*3+i] = vector_values[i]; break;
                case 2: short_values[v*3+i] = vector_values[i]; break;
                case 4: float_values[v*3+i] = vector_values[i]; break;
                }
            }
        }
    }   // バーテックスループ

    glBindBuffer    (GL_ARRAY_BUFFER, vbo);
    glBufferSubData (GL_ARRAY_BUFFER,
                     0,
                     vertex_count * component_count * component_size,
                     char_values);

}

void VertexArray:: convert (int to)
{
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
    default: IllegalStateException (__FILE__, __func__, "Component type is invalid, type=%d.", component_size);
    }
    return 0;
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
