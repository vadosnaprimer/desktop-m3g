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
	   Group* skeleton_) :
  Mesh (vertices, num_submesh, submeshes, num_appearance, appearances_),
  skeleton(0)
{
  setObjectType (OBJTYPE_SKINNED_MESH);

  // これはダメだなあ
  // valuesの中身が同じなので、深いコピーをしないと。
  float scale_bias[4];
  bind_positions = new VertexArray (*vertices->getPositions(scale_bias));
  bind_positions_scale   = scale_bias[0];
  bind_positions_bias[0] = scale_bias[1];
  bind_positions_bias[1] = scale_bias[2];
  bind_positions_bias[2] = scale_bias[3];

  bind_normals   = new VertexArray (*vertices->getNormals());
  // bone_indicesも。(index,weight)=(-1,0)で全部

  skeleton = skeleton_;
}

SkinnedMesh:: SkinnedMesh (VertexBuffer* vertices, 
	   IndexBuffer* submeshes, 
	   Appearance* appearances_, 
	   Group* skeleton_) :
    Mesh (vertices, submeshes, appearances_)
{
  setObjectType (OBJTYPE_SKINNED_MESH);


  skeleton = skeleton_;
}

SkinnedMesh:: ~SkinnedMesh ()
{
}

SkinnedMesh* SkinnedMesh:: duplicate () const
{
  SkinnedMesh* mesh = new SkinnedMesh (*this);
  throw NotImplementedException (__FILE__, __func__, "not yet.");
  
  // skeletonの深いコピー
  // bonesの差し替え（できるか？）
}

int SkinnedMesh:: animate (int world_time)
{
  Mesh:: animate (world_time);

  // ボーンの移動
  skeleton->animate (world_time);

  // スキンメッシュの更新
  // マトリックスパレットの作成
  // 全部の頂点に対して更新(bind_poses-->Mesh::poses)

  return 0;
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

  short index = bones.size();
  bones.push_back (node);

  // VertexArrayにindexとweightを追加
  short* bindx = new short[first_vertex + num_vertices];
  // get
  for (int i = first_vertex; i < first_vertex + num_vertices; i++) {
    

  }
  // set

  // inv_bind_poseを追加
  Matrix global_pose;
  do {
    Transform trans;
    node->getCompositeTransform (&trans);
    // cout << "trans = " << trans << "\n";
    float m[16];
    trans.get (m);
    global_pose *= Matrix(m);
  } while ((node = node->getParent()) != NULL);
  
  inv_bind_poses.push_back (global_pose.invert());
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
  /*
  for (int i = 0; i < (int)bones.size(); i++) {
    if (bones[i]->node == node) {
      Matrix mat = bones[i]->getInverseBindMatrix();
      transform->set ((float*)mat.m);
      return;
    }
  }
  */

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

  /*
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
  */

  return 0;
}

Group* SkinnedMesh:: getSkeleton () const
{
    return skeleton;
}

void SkinnedMesh:: render (int pass, int index) const
{
  //cout << "SkinnedMesh: render\n";

  // SkinnedMeshでする事はない。
  // Mesh::render()を呼び出すのみ。
  Mesh::render (pass, index);

  // これは間違え。render()ではなくanimate()で行う。
  // 移動！
  // MatrixPaletteの作成
  /*
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
  */

  //cout << "Matrix Palette = " << matrix_palette.size() << "\n";
  //for (int i = 0; i < (int)matrix_palette.size(); i++) {
  //  cout << i << ": " << matrix_palette[i] << "\n";
  //}

  // int vertex_count = vertices->getPositions(0)->getVertexCount();

  

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


