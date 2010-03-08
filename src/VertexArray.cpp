#include "VertexArray.hpp"
#include "m3gexcept.hpp"
#include <iostream>
#include <cstring>
using namespace std;
using namespace m3g;



VertexArray:: VertexArray (int num_vertices, int num_components, int component_size_) :
  component_count(num_components),
  component_size(component_size_),
  vertex_count(num_vertices),
  values(0)
{
  setObjectType (OBJTYPE_VERTEX_ARRAY);

  if (vertex_count < 1 || vertex_count > 65535) {
    throw invalid_argument ("Invalid vertex count is specified.");
  }
  if (component_count < 2 || component_count > 4) {
    throw invalid_argument ("Invalid component count is specified.");
  }
  if (component_size < 1 || component_size > 2) {
    throw invalid_argument ("Invalid component size is specified.");
  }

  int size = vertex_count * component_count * component_size;
  values = new char[size];
}

VertexArray:: ~VertexArray ()
{
  delete [] values;
}

void VertexArray:: get (int first_vertex, int num_vertices, char* values_) const
{
  if (first_vertex < 0 || first_vertex >= vertex_count) {
    throw invalid_argument ("Invalid first_vertex is specified.");
  }
  if (num_vertices < 0 || first_vertex + num_vertices > vertex_count) {
    throw invalid_argument ("Invalid num_vertices is specified.");
  }
  if (values_ == NULL) {
    throw null_point_error ("Null value is specified.");
  }
  if (component_size != 1) {
    throw domain_error ("Component size of this vertex array is not 1 byte.");
  }

  char* p = values + first_vertex * component_count * component_size;
  int size = num_vertices * component_count * component_size;
  memcpy (values_, p, size);
}

void VertexArray:: get (int first_vertex, int num_vertices, short* values_) const
{
  if (first_vertex < 0 || first_vertex >= vertex_count) {
    throw invalid_argument ("Invalid first_vertex is specified.");
  }
  if (num_vertices < 0 || first_vertex + num_vertices > vertex_count) {
    throw invalid_argument ("Invalid num_vertices is specified.");
  }
  if (values_ == NULL) {
    throw null_point_error ("Null value is specified.");
  }
  if (component_size != 2) {
    throw domain_error ("Component size of this vertex array is not 2 byte.");
  }
  char* p = values + first_vertex * component_count * component_size;
  int size = num_vertices * component_count * component_size;
  memcpy (values_, p, size);
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

void VertexArray:: set (int first_vertex, int num_vertices, char* values_)
{
  if (first_vertex < 0 || first_vertex >= vertex_count) {
    throw invalid_argument ("Invalid first_vertex is specified.");
  }
  if (num_vertices < 0 || first_vertex + num_vertices > vertex_count) {
    throw invalid_argument ("Invalid num_vertices is specified.");
  }
  if (values_ == NULL) {
    throw null_point_error ("Null value is specified.");
  }
  if (component_size != 1) {
    throw domain_error ("Component size of this vertex array is not 1 byte.");
  }

  char* p = values + first_vertex * component_count * component_size;
  int size = num_vertices * component_count * component_size;
  memcpy (p, values_, size);

}

void VertexArray:: set (int first_vertex, int num_vertices, short* values_)
{
  if (first_vertex < 0 || first_vertex >= vertex_count) {
    throw invalid_argument ("Invalid first_vertex is specified.");
  }
  if (num_vertices < 0 || first_vertex + num_vertices > vertex_count) {
    throw invalid_argument ("Invalid num_vertices is specified.");
  }
  if (values_ == NULL) {
    throw null_point_error ("Null value is specified.");
  }
  if (component_size != 2) {
    throw domain_error ("Component size of this vertex array is not 2 byte.");
  }
  char* p = values + first_vertex * component_count * component_size;
  int size = num_vertices * component_count * component_size;
  memcpy (p, values_, size);

}

void VertexArray:: get (int first_vertex, int num_vertices, float scale, float* bias, float* out_values) const
{
  //cout << "scale = " << scale << "\n";
  //cout << "bias[0] = " << bias[0] << "\n";
  for (int i = 0, k = 0; i < vertex_count; i++) {
    for (int j = 0; j < component_count; j++, k++) {
      if (component_size == 1) {
	out_values[k] = scale*((char*)values)[k] + bias[j];
      }
      else {
	out_values[k] = scale*((short*)values)[k] + bias[j];
      }
      //cout << out_values[k] << ", " << (int)values[k] << "\n";
    }
  }
}

//  glBufferData (GL_ARRAY_BUFFER, size, p, GL_STATIC_DRAW);

std::ostream& VertexArray:: print (std::ostream& out) const
{
  out << "VertexArray: ";
  out << vertex_count << " vertices (";
  out << component_size << "byte x " << component_count << "comps / vertex),  ";
  return out << "\n";;
}

std::ostream& operator<< (std::ostream& out, const VertexArray& vary)
{
  return vary.print(out);
}
