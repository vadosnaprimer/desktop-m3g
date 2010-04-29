#include "SkinnedMesh.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Exception.hpp"
#include <iostream>
#include <vector>
#include "Group.hpp"
using namespace std;
using namespace m3g;


SkinnedMesh:: SkinnedMesh (VertexBuffer* vertices, int num_submesh,
                           IndexBuffer** submeshes, Appearance** appearances_,
                           Group* skeleton_) :
  Mesh (vertices, num_submesh, submeshes, appearances_),
  skeleton(0), skinned_vertices(0)
{
  setObjectType (OBJTYPE_SKINNED_MESH);
  if (vertices->getPositions(0) == NULL) {
    throw NullPointException (__FILE__, __func__, "Vertices has no positions.");
  }

  skeleton = skeleton_;

  skinned_vertices = vertices->duplicate ();

  // 注意：スキン変形後のpositionsとnormalsを保存するために新しくnewし直す。
  // VertexBufferをduplicate()しただけでは同じインスタンスを指している。
  // positionsは内部float型でデータを保持しないと精度・有効範囲が足りない。

  float scale_bias[4];
  VertexArray* bind_positions = vertices->getPositions(scale_bias);
  if (bind_positions) {
    VertexArray* skinned_positions = bind_positions->duplicate ();
    skinned_vertices->setPositions (skinned_positions, scale_bias[0], &scale_bias[1]);
  }

  VertexArray* bind_normals   = vertices->getNormals();
  if (bind_normals) {
    VertexArray* skinned_normals = bind_normals->duplicate();
    skinned_vertices->setNormals (skinned_normals);
  }


  int vertex_count = bind_positions->getVertexCount();
  bone_indices.reserve(vertex_count);
  for (int v = 0; v < vertex_count; v++) {
    bone_indices.push_back (std::vector<BoneIndex>());
  }
  bind_poses.clear();
}

SkinnedMesh:: SkinnedMesh (VertexBuffer* vertices, 
	   IndexBuffer* submeshes, 
	   Appearance* appearances_, 
	   Group* skeleton_) :
  Mesh (vertices, submeshes, appearances_),
  skeleton(0), skinned_vertices(0)
{
  *this = SkinnedMesh (vertices, 1, &submeshes, &appearances_, skeleton_);
}

SkinnedMesh:: ~SkinnedMesh ()
{
}

SkinnedMesh* SkinnedMesh:: duplicate () const
{
  SkinnedMesh* skinned_mesh = new SkinnedMesh (*this);
  Mesh* mesh = Mesh::duplicate();
  *(Mesh*)skinned_mesh = *mesh;
  delete mesh;
  skinned_mesh->skeleton = this->skeleton->duplicate();
  // メモ:skinned_verticesはduplicate()しなくて良いんだよな？
  return skinned_mesh;
}

int SkinnedMesh:: animate (int world_time)
{
  //cout << "SkinnedMesh: animate\n";
  
  Mesh:: animate (world_time);

  // ボーンの移動
  skeleton->animate (world_time);

  // スキンメッシュの更新
  updateSkinnedVertices ();


  return 0;
}

void SkinnedMesh:: updateSkinnedVertices ()
{
  float        scale_bias[4];
  VertexArray* bind_positions    = vertices->getPositions (scale_bias);
  VertexArray* bind_normals      = vertices->getNormals ();
  VertexArray* skinned_positions = skinned_vertices->getPositions(0);
  VertexArray* skinned_normals   = skinned_vertices->getNormals ();
  //int          vertex_count      = bind_positions->getVertexCount();

  //cout << "scale = " << scale_bias[0] << "\n";
  //cout << "bias  = " << scale_bias[1] << ", " << scale_bias[2] << ", " << scale_bias[3] << "\n";

  // 基本マトリックスパレットの作成
  int bone_count = bind_poses.size();
  std::vector<Matrix> matrix_palette (bone_count);
  for (int b = 0; b < bone_count; b++) {
    Matrix global_pose = bind_poses[b].bone->getGlobalPose ();
    matrix_palette[b]  = global_pose * bind_poses[b].inverse;
    //cout << "global_pose[" << b << "] = " << global_pose << "\n";
  }
   // for (int b = 0; b < bone_count; b++) {
   //   cout << "bind_pose[" << b << "].inverse = " << bind_poses[b].inverse << "\n";
   // }
   // for (int b = 0; b < bone_count; b++) {
   //   cout << "matrix_palette[" << b << "] = " << matrix_palette[b] << "\n";
   // }


  // Position用マトリックスパレットの作成
  // (scale,biasの補正を考慮したもの)
  std::vector<Matrix> positions_matrix_palette (bone_count);
  Matrix mat;
  mat.setScale (scale_bias[0], scale_bias[0], scale_bias[0]);
  mat.setTranslate (scale_bias[1], scale_bias[2], scale_bias[3]);
  //cout << "mat = " << mat << "\n";
  //cout << "mat_inv = " << mat.getInverse() << "\n";
  for (int b = 0; b < bone_count; b++) {
    positions_matrix_palette[b] = mat.getInverse() * matrix_palette[b] * mat;
  }
  //for (int b = 0; b < bone_count; b++) {
  //  cout << "positions_matrix_palette[" << b << "] = " << positions_matrix_palette[b] << "\n";
  //}

  // Normal用マトリックスパレットの作成
  // (3x3成分のみを取りだし逆行列の転置したもの)
  std::vector<Matrix> normals_matrix_palette (bone_count);
  if (bind_normals) {
    for (int b = 0; b < bone_count; b++) {
      normals_matrix_palette[b] = matrix_palette[b];
      normals_matrix_palette[b].invert().transpose();
      normals_matrix_palette[b][3] = normals_matrix_palette[b][7] = normals_matrix_palette[b][11] = 0;
      normals_matrix_palette[b][12] = normals_matrix_palette[b][13] = normals_matrix_palette[b][14] = 0;
      normals_matrix_palette[b][15] = 1;
    }
  }
  
  // 位置
  if (bind_positions) {
    skinned_positions->setSkinning (bind_positions, bone_indices, positions_matrix_palette);
  }

  // 法線
  if (bind_normals) {
    skinned_normals->setSkinning (bind_normals, bone_indices, normals_matrix_palette);
  }


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
  if (num_vertices <= 0) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of vertices is invalid, num_vertex=%d.", num_vertices);
  }
  if (first_vertex + num_vertices > 65535) {
    throw IllegalArgumentException (__FILE__, __func__, "First vertex + number of vertices is invalid, first_vertex=%d, num_vertices=%d.", first_vertex, num_vertices);
  }

  // void SkinnedMesh:: addTransform (Node* node, int weight, int first_vertex, int num_vertices)
  //cout << "addTransform : \n";
  //cout << "  node = "         << *node << "\n";
  //cout << "  weight = "       << weight << "\n";
  //cout << "  first_vertex = " << first_vertex << "\n";
  //cout << "  num_vertices = " << num_vertices << "\n";

  // ボーンインデックスの決定
  int index = addBoneIndex (node);

  // ボーンインデックス（index,weight）の保存
  for (int v = first_vertex; v < first_vertex+num_vertices; v++) {
    bone_indices[v].push_back (BoneIndex(index,weight));
  }

}

/**
 * 
 */
void SkinnedMesh:: getBoneTransform (Node* node, Transform* transform) const
{
  if (node == NULL) {
    throw NullPointException (__FILE__, __func__, "Bone node is NULL.");
  }
  if (transform == NULL) {
    throw NullPointException (__FILE__, __func__, "Transform is NULL.");
  }
  if (getBoneIndex(node) == -1) {
    throw IllegalArgumentException (__FILE__, __func__, "Node is not bone of this SkinnedmEsh, node=0x%x.", node);
  }
  
  Matrix global_pose = node->getGlobalPose();
  global_pose.invert ();

  transform->set ((float*)global_pose.m);
}

int SkinnedMesh:: getBoneVertices (Node* node, int* vertex_indices, float* weights) const
{
  if (node == NULL) {
    throw NullPointException (__FILE__, __func__, "Bone node is NULL.");
  }
  if (vertices->getPositions(0) == NULL) {
    throw NullPointException (__FILE__, __func__, "Positions are not set.");
  }
  if (getBoneIndex(node) == -1) {
    throw IllegalArgumentException (__FILE__, __func__, "Node is not bone of this SkinnedMesh., node=0x%x", node);
  }

  int bone_index      = getBoneIndex (node);
  int vertex_count    = bone_indices.size();
  int find            = 0;

  for (int v = 0; v < vertex_count; v++) {
    float weight     = 0;
    int   bone_count = bone_indices[v].size();
    for (int b = 0; b < bone_count; b++) {
      weight += bone_indices[v][b].weight;
    }
    for (int b = 0; b < bone_count; b++) {
      if (bone_indices[v][b].index == bone_index) {
	find++;
	if (vertex_indices)
	  *vertex_indices++ = v;
	if (weights)
	  *weights++        = bone_indices[v][b].weight/weight;
      }
    }
  }

  return find;
}

Group* SkinnedMesh:: getSkeleton () const
{
    return skeleton;
}

/**
 * Note: Mesh should be rendered only at second rendering pass(pass=2).
 *       In other cases, do nothing.
 */
void SkinnedMesh:: render (RenderState& state) const
{
  // Mesh::render()でチェックするのでここでは何もしなくて良い

  //cout << "SkinnedMesh: render\n";

  // 注意：vertices が skinned_vertices に変わった事を除けば Mesh::render()と同一。
  // M3Gの仕様で vertices を書き換える事は禁止されているので元に戻す。



  VertexBuffer* tmp = vertices;
  (const_cast<SkinnedMesh*>(this))->vertices = skinned_vertices;

  glPushMatrix ();
  Mesh::render (state);
  glPopMatrix ();

  (const_cast<SkinnedMesh*>(this))->vertices = tmp;

  // 注意：骨には（レンダリングすべき）任意のノードを付加できるのでこれは必要。
  skeleton->render (state);


}



int SkinnedMesh:: addBoneIndex (Node* bone)
{
  for (int i = 0; i < (int)bind_poses.size(); i++) {
    if (bind_poses[i].bone == bone) {
      Matrix bind_pose = bone->getGlobalPose ();
      bind_poses[i].inverse = bind_pose.invert();
      return i;
    }
  }
  // ボーンとバインドポーズ（の逆行列）を保存
  Matrix bind_pose = bone->getGlobalPose ();
  bind_poses.push_back (BindPose(bone, bind_pose.invert()));
  return bind_poses.size()-1;
}

int SkinnedMesh:: getBoneIndex (Node* bone) const
{
  for (int i = 0; i < (int)bind_poses.size(); i++) {
    if (bind_poses[i].bone == bone)
      return i;
  }
  return -1;
}



std::ostream& SkinnedMesh:: print (std::ostream& out) const
{
  out << "SkinnedMesh: ";
  VertexArray* varry = vertices->getPositions(0);
  out << ((varry) ? varry->getVertexCount() : 0) << " vertices, ";
  out << bind_poses.size() << " bones";
  return out;
}

std::ostream& operator<< (std::ostream& out, const SkinnedMesh& mesh)
{
  return mesh.print (out);
}


