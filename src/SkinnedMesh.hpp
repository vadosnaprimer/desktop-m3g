#ifndef __SKINNED_MESH_HPP__
#define __SKINNED_MESH_HPP__

#include "Mesh.hpp"
#include <iosfwd>
#include <vector>


namespace m3g {

    class Group;
    class VertexBuffer;
    class IndexBuffer;
  class Bone;

/**
 * スケレタルアニメーテッドポリゴンメッシュを表すシーングラフノード.
 */
class SkinnedMesh : public Mesh
{
public:
    /**
     * 指定された頂点、サブメッシュ、スケルトンを持つSkinnedMeshを新しく作成する.
     */
  SkinnedMesh (VertexBuffer* vertices, 
	       int num_submesh, IndexBuffer** submeshes,
	       int num_appearance, Appearance** apperarances,
	       Group* skelton);

    /**
     * 指定された頂点、サブメッシュ、スケルトンを持つSkinnedMeshを新しく作成する.
     */
    SkinnedMesh (VertexBuffer* vertices, 
		 IndexBuffer* submeshes, 
		 Appearance* apperarances,
		 Group* skelton);

    /**
     * デストラクタ.
     */
    virtual ~SkinnedMesh ();

    /**
     * このスキンメッシュの頂点配列に対してウェイト付き変形(ボーン)を関連づける.
     */
    void addTransform (Node* bone, int weight, int firstVertex, int numVertices);

    /**
     * ボーンノードの基本姿勢の変形(ローカル座標系からボーン座標系への変換行列)を返す.
     */
    void getBoneTransorm (Node* bone, Transform* transform) const;

    /**
     * 指定されたボーンに影響を受ける頂点の数を返す。与えられた配列に頂点のインデックスとウェイト値が入る.
     */
    int getBoneVertices (Node* bone, int* indices, float* weights) const;

    /**
     * このスキンメッシュのスケルトンGroupを返す.
     */
    Group* getSkeleton () const;

    /**
     * このSkinnedMeshクラスの情報を表示する。デバッグ用.
     */
  virtual std::ostream& print (std::ostream& out) const;

protected:

  /**
   * このSkinnedMeshをレンダリングする内部使用の関数.
   */
  virtual void render (int pass, int index=0) const;


public:
  Group* root;  ///< skeleton root.
  std::vector<Bone*> bones;

  VertexBuffer* bind_vertices;
};


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::SkinnedMesh& mesh);


#endif
