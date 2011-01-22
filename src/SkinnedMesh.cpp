#include "m3g/m3g-gl.hpp"
#include "m3g/SkinnedMesh.hpp"
#include "m3g/VertexBuffer.hpp"
#include "m3g/IndexBuffer.hpp"
#include "m3g/VertexArray.hpp"
#include "m3g/Matrix.hpp"
#include "m3g/Vector.hpp"
#include "m3g/Exception.hpp"
#include "m3g/World.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include "m3g/Group.hpp"
#include "m3g/RayIntersection.hpp"
using namespace std;
using namespace m3g;

/**
 * メモ: スキニング済みの頂点座標(skinned_positions)は必ずfloat型に変換して持つ。
 *       これは静止した状態でchar型,short型の有効範囲をすべて使いきっているモデルデータが
 *       アニメーションした結果有効範囲外に飛び出すのを防止するためである。
 */

/**
 * メモ: ローカルポーズ   := ボーン座標から1個上のボーン座標への変換行列
 *       グローバルポーズ := ボーン座標からモデル(ローカル)座標への変換行列
 *       バインドポーズ   := 静止姿勢のグローバルポーズ
 */

/**
 * メモ: スキニングは (静止姿勢の)モデル座標 --> ボーン座標 --> (カレントの)モデル座標、で行う。
 *       従ってマトリックスパレットは
 *          matrix_pallete = global_pose * bind_pose.inverse
 *       詳しくは Jason Gregory の Game Engine Architecture を参照の事。
 */
SkinnedMesh:: SkinnedMesh (VertexBuffer* vertices, 
                           int num_submesh, IndexBuffer** submeshes, Appearance** appearances_,
                           Group* skeleton_) :
    Mesh (vertices, num_submesh, submeshes, appearances_),
    skeleton(0), skinned_vertices(0)
{
    if (vertices->getPositions(0) == NULL) {
        throw NullPointerException (__FILE__, __func__, "Vertices has no positions.");
    }
    if (skeleton_ == NULL) {
        throw NullPointerException (__FILE__, __func__, "Skeleton is NULL.");
    }

    skeleton = skeleton_;
    skeleton->setParent (this);

    initialize ();
}

SkinnedMesh:: SkinnedMesh (VertexBuffer* vertices, 
                           IndexBuffer* submesh, Appearance* appearance, 
                           Group* skeleton_) :
    Mesh (vertices, submesh, appearance),
    skeleton(0), skinned_vertices(0)
{
    if (vertices->getPositions(0) == NULL) {
        throw NullPointerException (__FILE__, __func__, "Vertices has no positions.");
    }
    if (skeleton_ == NULL) {
        throw NullPointerException (__FILE__, __func__, "Skeleton is NULL.");
    }

    skeleton = skeleton_;
    skeleton->setParent (this);
    
    initialize ();
}

void SkinnedMesh:: initialize ()
{
    skinned_vertices = vertices->duplicate ();

    float        scale_bias[4];
    VertexArray* bind_positions = vertices->getPositions(scale_bias);
    if (bind_positions) {
        VertexArray* skinned_positions = bind_positions->duplicate ();
        skinned_positions->convert (4);
        skinned_vertices->setPositions (skinned_positions, scale_bias[0], &scale_bias[1]);
    }

    VertexArray* bind_normals   = vertices->getNormals();
    if (bind_normals) {
        VertexArray* skinned_normals = bind_normals->duplicate();
        skinned_vertices->setNormals (skinned_normals);
    }

    int vertex_count = bind_positions->getVertexCount();
    bone_weights.reserve(vertex_count);
    for (int v = 0; v < vertex_count; v++) {
        bone_weights.push_back (std::vector<BoneWeight>());
    }
    bind_poses.clear();
}

SkinnedMesh:: ~SkinnedMesh ()
{
    if (skinned_vertices) {
        delete skinned_vertices;
    }
}


SkinnedMesh* SkinnedMesh:: duplicate () const
{
    Group*       skl  = skeleton->duplicate ();
    SkinnedMesh* mesh = new SkinnedMesh (vertices, indices.size(), (IndexBuffer**)&indices[0], (Appearance**)&appearances[0], skl);
    this->Object3D     :: copy (mesh);
    this->Transformable:: copy (mesh);
    this->Node         :: copy (mesh);
    this->Mesh         :: copy (mesh);
    this->SkinnedMesh  :: copy (mesh);
    return mesh;
}


int SkinnedMesh:: getReferences_xxx (Object3D** references) const
{
    int n  = Mesh:: getReferences_xxx (references);
    if (skeleton)
        references ? references[n] = skeleton, n++ : n++;

    return n;
}




void SkinnedMesh:: copy (SkinnedMesh* mesh) const
{
    // skeletonとskinned_verticesはコンストラクタで処理済み
    mesh->bone_weights = bone_weights;
    mesh->bind_poses   = bind_poses;
    for (int i = 0; i < (int)bind_poses.size(); i++) {
        mesh->bind_poses[i].bone = bind_poses[i].bone->getDuplicatedNode();
    }
}


int SkinnedMesh:: animate (int world_time)
{
    //cout << "SkinnedMesh: animate\n";
  
    Mesh:: animate (world_time);

    // ボーンの移動
    skeleton->animate (world_time);

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
        Matrix global_pose = bind_poses[b].bone->getGlobalPose (this);
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
    mat.setTranslate (scale_bias[1], scale_bias[2], scale_bias[3]);
    mat.setScale (scale_bias[0], scale_bias[0], scale_bias[0]);
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
        skinned_positions->setSkinning (bind_positions, bone_weights, positions_matrix_palette);
    }

    // 法線
    if (bind_normals) {
        skinned_normals->setSkinning (bind_normals, bone_weights, normals_matrix_palette);
    }


}



void SkinnedMesh:: addTransform (Node* node, int weight, int first_vertex, int num_vertices)
{
    if (node == NULL) {
        throw NullPointerException (__FILE__, __func__, "Bone node is NULL.");
    }
    if (dynamic_cast<Group*>(node) == NULL) {
        throw IllegalArgumentException (__FILE__, __func__, "Bone node must be Group.");
    }
    if (!skeleton || !skeleton->isDescendant (node)) {
        throw IllegalArgumentException (__FILE__, __func__, "Node is not descendant of this skeleton. node=%p", node);
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


    // ボーンインデックスの決定
    int index = addBoneIndex (node);

    // ボーンウェイト（index,weight）の保存
    for (int v = first_vertex; v < first_vertex+num_vertices; v++) {
        bone_weights[v].push_back (BoneWeight(index,weight));
    }

}

/**
 * ボーン行列(ボーン座標からローカル座標への変換行列)の取得.
 */
void SkinnedMesh:: getBoneTransform (Node* node, Transform* transform) const
{
    if (node == NULL) {
        throw NullPointerException (__FILE__, __func__, "Bone node is NULL.");
    }
    if (transform == NULL) {
        throw NullPointerException (__FILE__, __func__, "Transform is NULL.");
    }
    if (getBoneIndex(node) == -1) {
        throw IllegalArgumentException (__FILE__, __func__, "Node is not bone of this SkinnedmEsh, node=0x%x.", node);
    }
  
    Matrix global_pose = node->getGlobalPose(this);
    global_pose.invert ();

    transform->set ((float*)global_pose.m);
}

int SkinnedMesh:: getBoneVertices (Node* node, int* vertex_indices, float* weights) const
{
    if (node == NULL) {
        throw NullPointerException (__FILE__, __func__, "Bone node is NULL.");
    }
    if (vertices->getPositions(0) == NULL) {
        throw NullPointerException (__FILE__, __func__, "Positions are not set.");
    }
    if (getBoneIndex(node) == -1) {
        throw IllegalArgumentException (__FILE__, __func__, "Node is not bone of this SkinnedMesh., node=0x%x", node);
    }

    int bone_index      = getBoneIndex (node);
    int vertex_count    = bone_weights.size();
    int find            = 0;

    for (int v = 0; v < vertex_count; v++) {
        float weight     = 0;
        int   bone_count = bone_weights[v].size();
        for (int b = 0; b < bone_count; b++) {
            weight += bone_weights[v][b].weight;
        }
        for (int b = 0; b < bone_count; b++) {
            if (bone_weights[v][b].index == bone_index) {
                find++;
                if (vertex_indices)
                    *vertex_indices++ = v;
                if (weights)
                    *weights++        = bone_weights[v][b].weight/weight;
            }
        }
    }

    return find;
}

Group* SkinnedMesh:: getSkeleton () const
{
    return skeleton;
}

bool SkinnedMesh:: intersect (const Vector& org, const Vector& dir, RayIntersection* ri) const
{
    bool hit;
    VertexBuffer* tmp = vertices;

    (const_cast<SkinnedMesh*>(this))->vertices = skinned_vertices;
    hit = Mesh::intersect (org, dir, ri);
    (const_cast<SkinnedMesh*>(this))->vertices = tmp;
    if (hit) {
        return true;
    }

    Transform trans;
    bool      pass;
    pass = getTransformTo (skeleton, &trans);

    Vector org_skel = trans.transform (org).divided_by_w();
    Vector dir_skel = trans.transform3x3 (dir).divided_by_w().normalize();

    hit = skeleton->pick (-1, 
                          org_skel.x, org_skel.y, org_skel.z,
                          dir_skel.x, dir_skel.y, dir_skel.z,
                          ri);
    if (ri) {
        skeleton->getTransformTo (this, &trans);
        ri->transformRay (trans);
    }


    return hit;
}

/**
 * Note: Mesh should be rendered only at second rendering pass(pass=2).
 *       In other cases, do nothing.
 */
void SkinnedMesh:: render (RenderState& state) const
{
    if (!isGlobalRenderingEnabled()) {
        return;
    }

    //cout << "SkinnedMesh: render\n";

    // スキンメッシュの更新
    (const_cast<SkinnedMesh*>(this))->updateSkinnedVertices ();

    // 注意：vertices が skinned_vertices に変わった事を除けば Mesh::render()と同一。
    // M3Gの仕様で vertices を書き換える事は禁止されているので元に戻す。

    VertexBuffer* tmp = vertices;
    (const_cast<SkinnedMesh*>(this))->vertices = skinned_vertices;

    glPushMatrix ();
    Mesh::render (state);
    glPopMatrix ();

    // 注意：骨には（レンダリングすべき）任意のノードを付加できるのでこれは必要
    Transformable::render (state);
    skeleton->render (state);

    (const_cast<SkinnedMesh*>(this))->vertices = tmp;
}


/**
 * 指定ノードをボーンとして登録する.
 * すでに登録済みなら何もしない。
 * 戻り値はそのインデックス.
 */
int SkinnedMesh:: addBoneIndex (Node* bone)
{
    for (int i = 0; i < (int)bind_poses.size(); i++) {
        if (bind_poses[i].bone == bone) {
            Matrix bind_pose = bone->getGlobalPose (this);
            bind_poses[i].inverse = bind_pose.invert();
            return i;
        }
    }
    // ボーンとバインドポーズ（の逆行列）を保存
    Matrix bind_pose = bone->getGlobalPose (this);
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


