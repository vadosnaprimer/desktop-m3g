#ifndef __MORPHING_MESH_HPP__
#define __MORPHING_MESH_HPP__

#include "Mesh.hpp"
#include <iosfwd>


namespace m3g {

  class VertexBuffer;
  class IndexBuffer;
  class Appearance;

  /**
   * @~English  A scene graph node that represents a vertex morphing polygon mesh.
   * @~Japanese 頂点モーフィングメッシュを表すシーングラフのノード.
   */
  class MorphingMesh : public Mesh
  {
  public:
    /**
     * @~English  Construct a new MorphingMesh with the given base mesh and morph targets.
     * @~Japanese 指定されたベースメッシュとモーフターゲットを持つ新しいモーフィングメッシュを作成.
     */
    MorphingMesh (VertexBuffer* base, int num_target, VertexBuffer** targets, int num_submesh, IndexBuffer** sumeshes, int num_appearance, Appearance** appearances);

    /**
     * @~English  Constructs a new MorphingMesh with the given base mesh and morph targets.
     * @~Japanese 指定されたベースメッシュとモーフターゲットを持つ新しいモーフィングメッシュを作成.
     */
    MorphingMesh (VertexBuffer* base, int num_target, VertexBuffer** targets, IndexBuffer* sumeshes, Appearance* appearances);

    /**
     * @~English  Destruct this object.
     * @~Japanese このオブジェクトを削除するデストラクタ.
     */
    virtual ~MorphingMesh ();

    /**
     * @~English  Creates a duplicate of this Object3D. 
     * @~Japanese このオブジェクトの複製の作成.
     */
    MorphingMesh* duplicate () const;

    /**
     * @~English  Adds the given AnimationTrack to this Object3D, 
     *            potentially changing the order and indices of the previously added tracks.
     * @~Japanese アニメーショントラックの追加。
     *            既存のトラックの順番とインデックスは変更されるかもしれない.
     */
    virtual void addAnimationTrack (AnimationTrack* animation_track);

    /**
     * @~English  Updates all animated properties in this Object3D and all Object3Ds that are reachable from this Object3D.
     * @~Japanese このObject3D自身とここから到達できるObject3Dのアニメーテッドプロパティを更新する.
     */
    virtual int animate (int world_time);

    /**
     * @~English  Returns the morph target VertxBuffer at the given index.
     * @~Japanese 指定されたインデックスのモーフターゲット頂点バッファーの取得.
     */
    VertexBuffer* getMorphTarget (int index) const;

    /**
     * @~English  Returns the number of morph targets in this MorphingMesh.
     * @~Japanese このモーフィングメッシュのモーフターゲット数の取得.
     */
    int getMorphTargetCount () const;

    /**
     * @~English  Gets the current morph target weights for this mesh.
     * @~Japanese このメッシュのカレントのモーフターゲットのウェイトの取得.
     */
    void getWeights (float* weights) const;

    /**
     * @~English  Sets the weights for all morph targets in this mesh.
     * @~Japanese このメッシュの全てのモーフターゲットのウエイトの設定.
     */
    void setWeights (float* weights);

    /**
     * @~English  Print out information of this object.
     * @~Japanese このオブジェクトの情報を表示。デバッグ用.
     */
    virtual std::ostream& print (std::ostream& out) const;

  protected:
    /**
     * @~English  Render this object, for inner use.
     * @~Japanese このMorphingMeshをレンダリングする内部使用の関数.
     */
    virtual void render (int pass, int index=0) const;

  };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::MorphingMesh& m);



#endif
