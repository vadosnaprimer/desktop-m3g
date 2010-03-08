#ifndef __MORPHING_MESH_HPP__
#define __MORPHING_MESH_HPP__

#include "Mesh.hpp"
#include <iosfwd>


namespace m3g {

  class VertexBuffer;
  class IndexBuffer;
  class Appearance;

/**
 * 頂点モーフィングメッシュを表すシーングラフのノード.
 */
class MorphingMesh : public Mesh
{
public:
    /**
     * 指定されたベースメッシュとモーフターゲットを持つ新しいモーフィングメッシュを作成.
     */
  MorphingMesh (VertexBuffer* base, int num_target, VertexBuffer** targets, int num_submesh, IndexBuffer** sumeshes, int num_appearance, Appearance** appearances);

    /**
     * 指定されたベースメッシュとモーフターゲットを持つ新しいモーフィングメッシュを作成.
     */
  MorphingMesh (VertexBuffer* base, int num_target, VertexBuffer** targets, IndexBuffer* sumeshes, Appearance* appearances);

    /**
     * デストラクタ.
     */
    virtual ~MorphingMesh ();

    /**
     * アニメーショントラックの追加。
     * 既存のトラックの順番とインデックスは変更されるかもしれない.
     */
    virtual void addAnimationTrack (AnimationTrack* animation_track);

    /**
     * アニメーションの更新.
     */
    virtual int animate (int world_time);

    /**
     * 指定されたインデックスのモーフターゲット頂点バッファーの取得.
     */
    VertexBuffer* getMorphTarget (int index) const;

    /**
     * このモーフィングメッシュのモーフターゲット数の取得.
     */
    int getMorphTargetCount () const;

    /**
     * このメッシュのカレントのモーフターゲットのウェイトの取得.
     */
    void getWeights (float* weights) const;

    /**
     * このメッシュの全てのモーフターゲットのウエイトの設定.
     */
    void setWeights (float* weights);

  /**
   *
   */
  std::ostream& print (std::ostream& out) const;

protected:
  /**
   * このMorphingMeshをレンダリングする内部使用の関数.
   */
  virtual void render (int pass, int index=0) const;

};

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::MorphingMesh& m);



#endif
