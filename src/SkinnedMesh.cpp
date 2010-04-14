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
  skeleton(0), skinned_vertices(0), bone_indices(0)
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
  if (positions) {
    skinned_vertices->setPositions (positions->duplicate(), scale_bias[0], &scale_bias[1]);
  }
 VertexArray* normals   = vertices->getNormals();
 if (normals) {
   skinned_vertices->setNormals (normals->duplicate());
 }

  int    vertex_count = positions->getVertexCount();

  // (空の)ボーンインデックスの作成
  bone_indices        = new VertexArray (vertex_count, 4, 2);
  short* values       = new short[vertex_count*4];
  for (int i = 0; i < vertex_count*4; i+=4) {
    values[i]   = -1;  // bone1 index
    values[i+1] =  0;  // bone1 weight
    values[i+2] = -1;  // bone2 index
    values[i+3] =  0;  // bone2 weight
  }
  bone_indices->set (0, vertex_count, values);

  delete [] values;
  bind_poses.clear();
}

SkinnedMesh:: SkinnedMesh (VertexBuffer* vertices, 
	   IndexBuffer* submeshes, 
	   Appearance* appearances_, 
	   Group* skeleton_) :
  Mesh (vertices, submeshes, appearances_),
  skeleton(0), skinned_vertices(0), bone_indices(0)
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
  skinned_mesh->bone_indices = this->bone_indices->duplicate();
  return skinned_mesh;
}

int SkinnedMesh:: animate (int world_time)
{
  Mesh:: animate (world_time);

  // ボーンの移動
  skeleton->animate (world_time);

  // マトリックスパレットの作成
  std::vector<Matrix> matrix_palette (bind_poses.size());
  for (int i = 0; i < (int)bind_poses.size(); i++) {
    Matrix global_pose = getGlobalPose (bind_poses[i]->bone);
    matrix_palette[i]  = global_pose * bind_poses[i]->inverse;
  }

  float        scale_bias[4];
  VertexArray* bind_positions = vertices->getPositions(scale_bias);

  //  short* values = (short*)bind_positions->values;
  //  for (int i = 0; i < 42*3; i+=3) {
  //        cout << values[i] << ", " << values[i+1] << ", " << values[i+2] << "\n";
  //  }

  // スキンメッシュの更新
  // 法線は省略
  int vertex_count = bind_positions->getVertexCount();
  float* xyz_values = new float[vertex_count*3];
  short* bone_index_values = new short[vertex_count*4];
  bind_positions->get (0, vertex_count, scale_bias[0], &scale_bias[1], xyz_values);

  bone_indices->get (0, vertex_count, bone_index_values);
  for (int i = 0; i < vertex_count; i++) {
    Vector v0 (xyz_values[i*3], xyz_values[i*3+1], xyz_values[i*3+2]);
    int bone_index_1  = bone_index_values[i*4];
    int bone_weight_1 = bone_index_values[i*4+1];
    int bone_index_2  = bone_index_values[i*4+2];
    int bone_weight_2 = bone_index_values[i*4+3];
    float weight = 0;
    weight += (bone_index_1 > -1) ? bone_weight_1 : 0;
    weight += (bone_index_2 > -1) ? bone_weight_2 : 0;
    Vector v1 (0,0,0);
    v1 += (bone_index_1 > -1) ? matrix_palette[bone_index_1] * v0 * (bone_weight_1/weight) : Vector(0,0,0);
    v1 += (bone_index_2 > -1) ? matrix_palette[bone_index_2] * v0 * (bone_weight_2/weight) : Vector(0,0,0);
    if (weight > 0) {
      xyz_values[i*3]   = v1.x/v1.w;
      xyz_values[i*3+1] = v1.y/v1.w;
      xyz_values[i*3+2] = v1.z/v1.w;
    }
  }

  VertexArray* skinned_positions = skinned_vertices->getPositions(0);
  //cout << "skinned_positions = " << *skinned_positions << "\n";
  skinned_positions->set (0, vertex_count, scale_bias[0], &scale_bias[1], xyz_values);

    //short* values = (short*)skinned_positions->values;
 //  for (int i = 0; i < 42*3; i+=3) {
 //        cout << values[i] << ", " << values[i+1] << ", " << values[i+2] << "\n";
 //  }

  skinned_vertices->setPositions (skinned_positions, scale_bias[0], &scale_bias[1]);

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
  if (first_vertex + num_vertices > 65535) {
    throw IllegalArgumentException (__FILE__, __func__, "First vertex + number of vertices is invalid, first_vertex=%d, num_vertices=%d.", first_vertex, num_vertices);
  }

  // ボーンインデックスの決定
  short index = addBoneIndex (node);

  // ボーンインデックス（index,weight）の保存
  short* values = new short[num_vertices*4];
  bone_indices->get (first_vertex, num_vertices, values);

  for (int i = 0; i < num_vertices*4; i+=4) {
    if (values[i] == -1) {
      values[i]   = index;   // bone1に格納
      values[i+1] = weight;
    } else if (values[i+2] == -1) {
      values[i+2] = index;
      values[i+3] = weight;  // bone2に格納
    } else if (weight > values[i+1] || weight > values[i+3] ) {
      if (values[i+1] < values[i+3]) {    // weightの小さい方と差し替え
	values[i]   = index;
	values[i+1] = weight;
      } else {
	values[i+2] = index;
	values[i+3] = weight;
      }
    }
  }
  bone_indices->set (first_vertex, num_vertices, values);

  //cout << "bone_indices = " << *bone_indices << "\n";


  // メモ：同じボーンを2回addTransformすると
  // inv_bind_poseとindexの値が違くなる。バグ
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
  int vertex_count    = bone_indices->getVertexCount();

  short* values = new short[vertex_count*4];
  bone_indices->get (0, vertex_count, values);

  int num = 0;
  for (int i = 0; i < vertex_count*4; i+=4) {
    float weight = 0;
    if (values[i] == bone_index || values[i+2] == bone_index) {
      weight += (values[i] > -1) ? values[i+1] : 0;
      weight += (values[i+2] > -1) ? values[i+3] : 0;
      if (vertex_indices) {
	*vertex_indices++ = i/4;
      }
      if (weights) {
	if (values[i] == bone_index)
	  *weights++ = values[i+1]/weight;
	else
	  *weights++ = values[i+3]/weight;
      }
      num += 1;
    }
  }


  return num;
}

Group* SkinnedMesh:: getSkeleton () const
{
    return skeleton;
}

void SkinnedMesh:: render (int pass, int index) const
{
  cout << "SkinnedMesh: render\n";

  // 注意：vertices が skinned_vertices に変わった事を除けば Mesh::render()と同一。
  // M3Gの仕様で vertices を書き換える事は禁止されているので元に戻す。

  VertexBuffer* tmp = vertices;
  (const_cast<SkinnedMesh*>(this))->vertices = skinned_vertices;

  Mesh::render (pass, index);

  (const_cast<SkinnedMesh*>(this))->vertices = tmp;

}


Matrix SkinnedMesh:: getGlobalPose (Node* node)
{
  Matrix global_pose;
  do {
    Transform trans;
    node->getCompositeTransform (&trans);
    float m[16];
    trans.get (m);
    global_pose *= Matrix(m);
  } while ((node = node->getParent()) != NULL);

  return global_pose;
}

int SkinnedMesh:: addBoneIndex (Node* bone)
{
  for (int i = 0; i < (int)bind_poses.size(); i++) {
    if (bind_poses[i]->bone == bone) {
      Matrix bind_pose = getGlobalPose (bone);
      bind_poses[i]->inverse = bind_pose.invert();
      return i;
    }
  }
  // ボーンとバインドポーズ（の逆行列）を保存
  Matrix bind_pose = getGlobalPose (bone);
  bind_poses.push_back (new BindPose(bone, bind_pose.invert()));
  return bind_poses.size()-1;
}

int SkinnedMesh:: getBoneIndex (Node* bone) const
{
  for (int i = 0; i < (int)bind_poses.size(); i++) {
    if (bind_poses[i]->bone == bone)
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


