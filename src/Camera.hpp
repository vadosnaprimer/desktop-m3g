#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <iosfwd>
#include "Node.hpp"
#include "Projection.hpp"


namespace m3g {

class Transform;


/**
 * シーン中のカメラ位置を定義するノード。3Dから2Dへの透視変換を行う.
 */
class Camera : public Node
{
  friend class Graphics3D;  // for render
  friend class World;  // for render

public:
  /**
   * 4x4行列で汎用の投影を指定を表す定数.
   */
    static const int GENERIC     = 48;
  /**
   * 平行投影を指定する定数.
   */
    static const int PARALLEL    = 49;
  /**
   * 投資投影を指定する定数.
   */
    static const int PERSPECTIVE = 50;

public:
    
    /**
     * コンストラクタ.
     */
    Camera ();

    /**
     * デストラクタ.
     */
    virtual ~Camera ();

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
     * 透視変換パラメーターと種類の取得。
     * paramsには4要素(fovy,aspect_ratio,near,far)がこの順番で書き込まれる.
     */
    int getProjection (float* params) const;

    /**
     * カレントの透視変換行列と種類の取得.
     */
    int getProjection (Transform* transform) const;

    /**
     * 指定された4x4行列を透視変換行列として設定する.
     */
    void setGeneric (const Transform& transorm);

    /**
     * 平行投影行列を作成し、カレントの透視変換行列として設定する.
     */
    void setParallel (float fovy, float aspect_ratio, float near, float far);

    /**
     * 射影投影行列を作成し、カレントの透視変換行列として設定する.
     */
    void setPerspective (float fovy, float aspect_ratio, float near, float far);

    /**
     * このCameraクラスの情報を表示する。デバッグ用.
     */
  virtual std::ostream& print (std::ostream& out) const;

  void lookAt (float from_x, float from_y, float from_z,
	       float to_x, float to_y, float to_z, 
	       float up_x, float up_y, float up_z);

protected:
  /**
   * このCameraをレンダリングする内部使用の関数.
   */
  virtual void render (int pass, int index=0) const;

private:
  int   type;
  float fovy;
  float aspect_ratio;
  float near;
  float far;

  Transform proj_trans;
};


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Camera& c);


#endif
