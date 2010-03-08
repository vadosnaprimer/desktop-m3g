#ifndef __BONE_HPP__
#define __BONE_HPP__

#include <iosfwd>
#include <vector>
#include "Matrix.hpp"

namespace m3g {

class Matrix;
class Node;

  /**
   * ボーンを表すM3Gの定義外の内部使用のクラス.
   */
  class Bone
  {
  public:
    Bone (Node* node, int weight, int first_vertex, int num_vertex);
    ~Bone ();

    Matrix getInverseBindMatrix () const;

    void setInverseBindMatrix (Matrix mat);


    float getWeight (int vertex_index) const;
    
    std::ostream& print (std::ostream& out) const;

  public:
    Node*  node;
    int    weight;
    int    first_vertex;
    int    num_vertex;
    Matrix inv_bind_matrix;
  };


} // namespace m3g


std::ostream& operator<< (std::ostream& out, const m3g::Bone& bone);


#endif
