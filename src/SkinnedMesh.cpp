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


SkinnedMesh:: SkinnedMesh (VertexBuffer* vertices,
	   int num_submesh, IndexBuffer** submeshes,
	   int num_appearance, Appearance** appearances_,
	   Group* skeleton_) :
  Mesh (vertices, num_submesh, submeshes, num_appearance, appearances_),
  skeleton(0), skinned_vertices(0)
{
  setObjectType (OBJTYPE_SKINNED_MESH);
  if (vertices->getPositions(0) == NULL) {
    throw NullPointException (__FILE__, __func__, "Vertices has no positions.");
  }

  skeleton = skeleton_;

  skinned_vertices = vertices->duplicate ();

  // 変形後の頂点位置と法線の保存用
  float scale_bias[4];
  VertexArray* positions = vertices->getPositions(scale_bias);
  VertexArray* normals   = vertices->getNormals();
  if (positions)
    skinned_vertices->setPositions (positions->duplicate(), scale_bias[0], &scale_bias[1]);
 if (normals)
   skinned_vertices->setNormals (normals->duplicate());

  int vertex_count = positions->getVertexCount();
  bone_indices.clear();
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
  setObjectType (OBJTYPE_SKINNED_MESH);

  *this = SkinnedMesh (vertices, 1, &submeshes, 1, &appearances_, skeleton_);
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
  cout << "SkinnedMesh: animate\n";
  cout << "  bones = " << bind_poses.size() << "\n";
  
  //for (int i = 0; i < (int)bind_poses.size(); i++) {
  //  cout << "i = " << i << ", " << bind_poses[i].bone->Transformable::print (cout) << "\n";
  //  cout << "global_pose = \n" << getGlobalPose (bind_poses[i].bone) << "\n";
  //  cout << "inv_bind_pose = \n" << bind_poses[i].inverse << "\n"; 
  //}

  Mesh:: animate (world_time);

  // ボーンの移動
  skeleton->animate (world_time);

  // マトリックスパレットの作成
  int bone_count = bind_poses.size();
  std::vector<Matrix> matrix_palette (bone_count);
  for (int b = 0; b < bone_count; b++) {
    //cout << "b = " << b << "\n";
    //cout << "bind_poses.inverse = " << bind_poses[b].inverse << "\n";
    Matrix global_pose = getGlobalPose (bind_poses[b].bone);
    //cout << "global_pose = " << global_pose << "\n";
    matrix_palette[b]  = global_pose * bind_poses[b].inverse;
    //cout << "matrix_palette[" << b << "] = " << matrix_palette[b] << "\n";
  }


  // スキンメッシュの更新
  float        scale_bias[4];
  VertexArray* bind_positions    = vertices->getPositions (scale_bias);
  VertexArray* bind_normals      = vertices->getNormals ();
  VertexArray* skinned_positions = skinned_vertices->getPositions(0);
  VertexArray* skinned_normals   = skinned_vertices->getNormals ();
  int          vertex_count      = bind_positions->getVertexCount();

  float* values       = new float[vertex_count*3];

  // 位置
  bind_positions->get (0, vertex_count, scale_bias[0], &scale_bias[1], values);
  for (int v = 0; v < vertex_count; v++) {
    Vector v0 (values[v*3], values[v*3+1], values[v*3+2]);
    Vector v1 (0,0,0);
    float  weight     = 0;
    int    bone_count = bone_indices[v].size();
    for (int b = 0; b < bone_count; b++) {
      weight += bone_indices[v][b].weight;
    }
    for (int b = 0; b < bone_count; b++) {
      int i = bone_indices[v][b].index;
      //cout << "b = " << b << ", i = " << i << "\n";
      //cout << "matrix_palette[" << i << "] = " << matrix_palette[i] << "\n";
      //cout << "v0 = " << v0 << "\n";
      v1 += matrix_palette[i] * v0 * (bone_indices[v][b].weight/weight);
    }
    if (weight > 0)
      v1.get (&values[v*3]);
  }
  skinned_positions->set (0, vertex_count, scale_bias[0], &scale_bias[1], values);
  skinned_vertices->setPositions (skinned_positions, scale_bias[0], &scale_bias[1]);

  // 法線
  if (bind_normals) {
    int component_size = bind_normals->getComponentType();
    scale_bias[0] = (component_size == 1) ? 2/255.f : 2/65535.f;
    scale_bias[1] = scale_bias[2] = scale_bias[3] = (component_size == 2) ? 1/255.f : 1/65535.f;
    bind_normals->get (0, vertex_count, scale_bias[0], &scale_bias[1], values);
    for (int v = 0; v < vertex_count; v++) {
      Vector v0 (values[v*3], values[v*3+1], values[v*3+2]);
      Vector v1 (0,0,0);
      float  weight     = 0;
      int    bone_count = bone_indices[v].size();
      for (int b = 0; b < bone_count; b++) {
	weight += bone_indices[v][b].weight;
      }
      for (int b = 0; b < bone_count; b++) {
	int i = bone_indices[v][b].index;
	v1 += matrix_palette[i].invert().transpose() * v0 * (bone_indices[v][b].weight/weight);
      }
      if (weight > 0) {
	values[v*3]   = v1.x/v1.w;
	values[v*3+1] = v1.y/v1.w;
	values[v*3+2] = v1.z/v1.w;
      }
    }
    skinned_normals->set (0, vertex_count, scale_bias[0], &scale_bias[1], values);
    skinned_vertices->setNormals (skinned_normals);
  }

  delete [] values;

  //cout << "skinned_positions = " << *skinned_positions << "\n";

 
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
  
  Matrix global_pose = getGlobalPose(node);
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

  Mesh::render (state);

  (const_cast<SkinnedMesh*>(this))->vertices = tmp;

  // 注意：骨には（レンダリングすべき）任意のノードを付加できるのでこれは必要。
  skeleton->render (state);
}


Matrix SkinnedMesh:: getGlobalPose (Node* node) const
{
  //int i = 0;
  Matrix global_pose;
  do {
    //cout << "global_pose = " << global_pose << "\n";
    Transform trans;
    //cout << i++ << " : node transform = " << node->Transformable::print(cout) << "\n";    
    node->getCompositeTransform (&trans);
    //cout << i++ << " : composite transform = " << trans << "\n";
    float m[16];
    trans.get (m);
    global_pose *= Matrix(m);
  } while ((node = node->getParent()) != NULL);

  return global_pose;
}

int SkinnedMesh:: addBoneIndex (Node* bone)
{
  for (int i = 0; i < (int)bind_poses.size(); i++) {
    if (bind_poses[i].bone == bone) {
      Matrix bind_pose = getGlobalPose (bone);
      bind_poses[i].inverse = bind_pose.invert();
      return i;
    }
  }
  // ボーンとバインドポーズ（の逆行列）を保存
  Matrix bind_pose = getGlobalPose (bone);
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
  return out << "\n";
}

std::ostream& operator<< (std::ostream& out, const SkinnedMesh& mesh)
{
  return mesh.print (out);
}


