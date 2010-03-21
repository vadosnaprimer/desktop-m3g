#include "SkinnedMesh.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Bone.hpp"
#include "Matrix.hpp"
#include "Exception.hpp"
#include <iostream>
#include <vector>
#include "Group.hpp"
using namespace std;
using namespace m3g;


SkinnedMesh:: SkinnedMesh (VertexBuffer* vertices,
	   int num_submesh, IndexBuffer** submeshes,
	   int num_appearance, Appearance** appearances_,
	   Group* skeleton) :
  Mesh (vertices, num_submesh, submeshes, num_appearance, appearances_),
  root(0)
{
  setObjectType (OBJTYPE_SKINNED_MESH);

  // このチェックはMeshでやっているので不要。あとで消す。
  if (vertices == NULL) {
    throw NullPointException (__FILE__, __func__, "Vertices is NULL.");
  }
  if (submeshes == NULL) {
    throw NullPointException (__FILE__, __func__, "Submesh is NULL.");
  }
  if (skeleton == NULL) {
    throw NullPointException (__FILE__, __func__, "Skeleton is NULL.");
  }
  if (skeleton->getObjectType() != OBJTYPE_GROUP) {
    throw IllegalArgumentException (__FILE__, __func__, "Skelton root shoud be Group.");
  }
  if (skeleton->getParent() != NULL) {
    throw IllegalArgumentException (__FILE__, __func__, "Skeleton root has parent. it must be NULL.");
  }

  // 間違い！
  // positionsの深いコピーが必要。あとで修正する
  bind_vertices = new VertexBuffer (*vertices);

  root = skeleton;
}

SkinnedMesh:: SkinnedMesh (VertexBuffer* vertices, 
	   IndexBuffer* submeshes, 
	   Appearance* appearances_, 
	   Group* skeleton) :
    Mesh (vertices, submeshes, appearances_)
{
  setObjectType (OBJTYPE_SKINNED_MESH);

  // このチェックはMeshでやっているので不要。あとで消す。

  /*
  if (vertices == NULL) {
    throw null_point_error ("vertices is NULL.");
  }
  if (submeshes == NULL) {
    throw null_point_error ("submesh is NULL.");
  }
  if (skeleton == NULL) {
    throw null_point_error ("skeleton is NULL.");
  }
  if (skeleton->getObjectType() != OBJTYPE_GROUP) {
    throw invalid_argument ("Skelton root shoud be Group.");
  }
  if (skeleton->getParent() != NULL) {
    throw invalid_argument ("Skeleton root has parent. it must be NULL.");
  }
  */

  root = skeleton;
}

SkinnedMesh:: ~SkinnedMesh ()
{
}

void SkinnedMesh:: addTransform (Node* node, int weight, int first_vertex, int num_vertices)
{
  if (node == NULL) {
    throw NullPointException (__FILE__, __func__, "Bone node is NULL.");
  }
  if (node->getObjectType() != OBJTYPE_GROUP && node->getObjectType() != OBJTYPE_WORLD) {
    throw IllegalArgumentException (__FILE__, __func__, "Bone node must be Group or its descendant.");
  }
  if (weight <= 0) {
    throw IllegalArgumentException (__FILE__, __func__, "Bone weight must be positive integer, weight=%f.", weight);
  }
  if (first_vertex < 0) {
    throw IllegalArgumentException (__FILE__, __func__, "First vertex is invalid, first_vertex=%d.", first_vertex);
  }
  if (first_vertex + num_vertices > 65535) {
    throw IllegalArgumentException (__FILE__, __func__, "First vertex + number of vertices is invalid, first_vertex=%d, num_vertices=%d.", first_vertex, num_vertices);
  }
  
  Bone* bone = new Bone (node, weight, first_vertex, num_vertices);

  // bind_poseの作成  
  Matrix global_pose;
  do {
    Transform trans;
    node->getCompositeTransform (&trans);
    // cout << "trans = " << trans << "\n";
    float m[16];
    trans.get (m);
    global_pose *= Matrix(m);
  } while ((node = node->getParent()) != NULL);
  global_pose.invert();
  bone->setInverseBindMatrix (global_pose);

  bones.push_back (bone);
}

/**
 * 
 */
void SkinnedMesh:: getBoneTransorm (Node* node, Transform* transform) const
{
  if (node == NULL) {
    throw NullPointException (__FILE__, __func__, "Bone node is NULL.");
  }
  if (transform == NULL) {
    throw NullPointException (__FILE__, __func__, "Transform is NULL.");
  }

  for (int i = 0; i < (int)bones.size(); i++) {
    if (bones[i]->node == node) {
      Matrix mat = bones[i]->getInverseBindMatrix();
      transform->set ((float*)mat.m);
      return;
    }
  }

  // transform is undefined.
  *transform = Transform();
}

int SkinnedMesh:: getBoneVertices (Node* node, int* indices, float* weights) const
{
  if (node == NULL) {
    throw NullPointException (__FILE__, __func__, "Bone node is NULL.");
  }
  if (vertices->getPositions(0) == NULL) {
    throw NullPointException (__FILE__, __func__, "Positions are not set.");
  }

  int n = 0;
  int index = 0;

  int vertex_count = vertices->getPositions(0)->getVertexCount();
  for (int i = 0; i < vertex_count; i++) {
    float w    = 0;
    float wall = 0;
    for (int j = 0; j < (int)bones.size(); j++) {
      float x = bones[j]->getWeight(i);
      if (x > 0 && bones[j]->node == node) {
	w += x;
      }
      wall += x;
    }
    if (w > 0) {
      n += 1;
    }
    if (w > 0 && indices && weights) {
      indices[index] = i;
      weights[index] = w/wall;
      index += 1;
    }
  }

  return n;
}

Group* SkinnedMesh:: getSkeleton () const
{
    return root;
}

void SkinnedMesh:: render (int pass, int index) const
{
  cout << "SkinnedMesh: render\n";

  // MatrixPaletteの作成
  vector<Matrix> matrix_palette;
  matrix_palette.reserve (bones.size());

  for (int i = 0; i < (int)bones.size(); i++) {
    Matrix global_pose;
    Node* node = bones[i]->node;
    while (node != root) {
      Transform trans;
      node->getTransform (&trans);
      float m[16];
      trans.get (m);
      global_pose *= Matrix(m);

      node = node->getParent();
    };
    matrix_palette.push_back (global_pose * bones[i]->getInverseBindMatrix());
  }

  cout << "Matrix Palette = " << matrix_palette.size() << "\n";
  for (int i = 0; i < (int)matrix_palette.size(); i++) {
    cout << i << ": " << matrix_palette[i] << "\n";
  }

  // int vertex_count = vertices->getPositions(0)->getVertexCount();

  

  // レンダリング
  Mesh:: render (pass, index);
}

std::ostream& SkinnedMesh:: print (std::ostream& out) const
{
  out << "SkinnedMesh: ";
  VertexArray* varry = vertices->getPositions(0);
  out << ((varry) ? varry->getVertexCount() : 0) << " vertices, ";
  out << bones.size() << " bones";
  return out << "\n";
}

std::ostream& operator<< (std::ostream& out, const SkinnedMesh& mesh)
{
  return mesh.print (out);
}


