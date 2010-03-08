#ifndef __NODE_HPP__
#define __NODE_HPP__

#include "Transformable.hpp"
#include "m3ginternal.hpp"
#include <iosfwd>

namespace m3g {

class Transform;

/**
 * シーングラフのノードを表す抽象クラス.
 */
class Node : public Transformable
{
  friend class Group;      // for setParent
  friend class World;      // for ???
  friend class Graphics3D; // for render
  friend class Mesh;       // for node

  struct Alignment {
    Alignment (int t, Node* r) : target(t), reference(r) {};
    int target;
    Node* reference;
  };

public:
    static const int NONE   = 144;
    static const int ORIGIN = 145;
    static const int X_AXIS = 146;
    static const int Y_AXIS = 147;
    static const int Z_AXIS = 148;

    /**
     * コンストラクタ.
     */
    Node ();

    /**
     * デストラクタ.
     */
    virtual ~Node ();

    /**
     * このノードと子孫ノードにアライメントを適応する.
     */
    void align (Node* reference);

    /**
     * アニメーショントラックの追加。
     * 既存のトラックの順番とインデックスは変更されるかもしれない.
     */
  virtual void addAnimationTrack (AnimationTrack* animation_track);

    /**
     * このノードをアニメーションする.
     */
  virtual int animate (int world_time);

    /**
     * 指定された軸にアライメントされた参照ノードを返す.
     */
    Node* getAlignmentReference (int axis) const;

    /**
     * 指定された軸に対するアライメントターゲットを返す.
     */
    int getAlignmentTarget (int axis) const;

    /**
     * このノードのα値の取得.
     */
    float getAlphaFactor () const;

    /**
     * このノードの親ノードの取得.
     */
    Node* getParent () const;

    /**
     * このノードのスコープの取得.
     */
    int getScope () const;

    /**
     * このノードから指定されたノードへの座標変換の取得.
     */
    bool getTransformTo (Node* target, Transform* transform) const;

    /**
     * このノードのピッキング可能フラグを返す.
     */
    bool isPickingEnabled () const;

    /** 
     * このノードのレンダリング可能フラグを返す.
     */
    bool isRenderingEnabled () const;


    /**
     * このノードを指定されたノードに整列させる。もしくはアライメントを無効にする.
     */
    void setAlignment (Node* z_ref, int z_target, Node* y_ref, int y_target);


    /**
     * このノードのα値を設定.
     */
    void setAlphaFactor (float alpha_factor) ;

    /**
     * このノードのピッキング可能フラグの設定.
     */
    void setPickingEnable (bool enable);

    /**
     * このノードのレンダリング可能フラグの設定.
     */
    void setRenderingEnable (bool enable);

    /**
     * このノードのスコープを設定する.
     */
    void setScope (int scope);

    /**
     * このNodeクラスの情報を表示する。デバッグ用.
     */
  virtual std::ostream& print (std::ostream& out) const;

PRIVATE:
  /**
   * このノードの親ノードを設定する. 
   */
  void setParent (Node* node);

protected:


protected:
  /**
   * このNodeをレンダリングする内部使用の関数.
   */
  virtual void render (int pass, int index=0) const;

private:
  Node*     parent;
  bool      rendering_enable;
  bool      picking_enable;
  float     alpha_factor;
  int       scope;
  Alignment z_alignment;
  Alignment y_alignment;

};

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Node& n);



#endif
