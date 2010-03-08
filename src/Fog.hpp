
#ifndef __FOG_HPP__
#define __FOG_HPP__

#include <iostream>
#include "Object3D.hpp"

namespace m3g {

/**
 * フォグを設定するアピアランスの構成要素.
 */
class Fog : public Object3D
{
  friend class Appearance;  // for findByType

public:
  /**
   * 指数フォグを表す定数.
   */
    static const int EXPONENTIAL = 80;
  /**
   * 線形フォグを表す定数.
   */
    static const int LINEAR      = 81;

public:
    /**
     * デフォルトのコンストラクタ.
     */
    Fog ();

    /**
     * デストラクタ.
     */
    virtual ~Fog ();

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
     * フォグカラーの取得.
     */
    int getColor () const;

    /**
     * フォグ密度の取得.
     */
    float getDensity () const;

    /**
     * 線形フォグのFar距離の取得.
     */
    float getFarDistance () const;

    /**
     * カレンドのフォグモードの取得.
     */
    int getMode () const;

    /**
     * 線形フォグのnear距離の取得.
     */
    float getNearDistance () const;

    /**
     * このフォグのカラーの設定.
     */
    void setColor (int rgb);

    /**
     * exponentialフォグの密度の設定.
     */
    void setDensity (float density);

    /**
     * 線形フォグのnear,far距離の設定.
     */
    void setLinear (float near, float far);

    /**
     * フォグモードを線形もしくはexponentialに設定する.
     */
    void setMode (int mode);

  /**
   * このFogクラスの情報を表示する。デバッグ用.
   */
  virtual std::ostream& print (std::ostream& out) const;

protected:
  /**
   * このFogノードをレンダリングする内部使用の関数.
   */
  virtual void render (int pass, int index=0) const;

private:
  int   mode;
  float density;
  float near;
  float far;
  int   color;
};



} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Fog& f);


#endif
