#include "Bone.hpp"
#include "Group.hpp"
#include "m3gexcept.hpp"
#include <iostream>
using namespace std;
using namespace m3g;

Bone:: Bone (Node* node_, int weight_, int first_vertex_, int num_vertex_) :
  node(0), weight(0), first_vertex(-1), num_vertex(0)
{
  if (node_ == NULL) {
    null_point_error ("Bone node is Null.");
  }

  node        = node_;
  weight      = weight_;
  first_vertex = first_vertex_;
  num_vertex  = num_vertex_;
}

Bone:: ~Bone ()
{
}

Matrix Bone:: getInverseBindMatrix () const
{
  return inv_bind_matrix;
}

void Bone:: setInverseBindMatrix (Matrix mat)
{
  inv_bind_matrix = mat;
}

float Bone:: getWeight (int vertex) const
{
  if (vertex >= first_vertex && vertex < first_vertex+num_vertex)
    return weight;
  else
    return 0;
}

std::ostream& Bone:: print (std::ostream& out) const
{
  out << "Bone: ";
  out << ", node=" << node;
  out << ", weight=" << weight;
  out << ", first_vertex=" << first_vertex;
  out << ", num_vertex=" << num_vertex;
  out << ", inv_bind_matrix=" << inv_bind_matrix;
  return out << "\n";
}

std::ostream& operator<< (std::ostream& out, const m3g::Bone& bone)
{
  return bone.print (out);
}



