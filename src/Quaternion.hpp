#ifndef __QUATERNION_HPP__
#define __QUATERNION_HPP__

#include <iosfwd>

namespace m3g {

/**
 * @~English   Quaterion class representing rotation, for inner use.
 * @~Japanese  回転を表すクォータニオンクラス。内部使用専用.
 */
class Quaternion
{
public:

  /**
   * @~English  Construct this object as unit quaternion.
   * @~Japanese 単位クォータニオンを作成するコンストラクタ.
   */
  Quaternion (); 

  /**
   * @~English   Construct this object by angle-axis form, no need to be unit vector.
   * @~Japanese  回転角度、回転軸の形式でクォータニオンを作成するコンストラクタ。
   *             回転軸は正規化されている必要はない.
   */
  Quaternion (float angle, float ax, float ay, float az);


  /**
   * @~English    Destruct this object.
   * @~Japanese  このオブジェクトを削除するデストラクタ.
   */
  ~Quaternion ();

  /**
   * @~English   make vector components to be 0, scaler componet to be 1.
   * @~Japanese  単位クォータニオン化する.
   */
  void setIdentity ();

  /**
   * @~English   make all components to zero.
   * @~Japanese  クォータニオンをゼロ化する.
   */
  void setZero ();

  /**
   * @~English  make this unit quaternion. 
   * @~Japanese  クォータニオンを正規化化する.
   */
  Quaternion& normalize ();

  /**
   * @~English   set quaternion, to be normalized.
   * @~Japanese  クォータニオンを設定する。関数内部で正規化される.
   */
  void set (float qx, float qy, float qz, float qw);

  /**
   * @~English   Retriev this as angle-axis form.
   * @~Japanese  このクォータニオンを角度-回転軸の形式で取得.
   */
  void getAngleAxis (float* angle_axis) const;

  /**
   * @~English   Rtrieve lenght of this quaternion.
   * @~Japanese  このクォータニオンを長さを取得.
   */
  float getLength () const;


public:
  float x;   //< vector component i of Quaternion
  float y;   //< vector component j of Quaternion
  float z;   //< vector component k of Quaternion
  float w;   //< scaler component of Quaternion
};


/**
 * @~English   slerp 2 quaternions.
 * @~Japanese  クォータニオンの球面線形補間を行う。a=0の時q0, a=1の時q1が返る.
 */
  m3g::Quaternion slerp (const m3g::Quaternion& q0, const m3g::Quaternion& q1, float alpha);


} // namespace m3g {



m3g::Quaternion operator* (float f, const m3g::Quaternion& q);
m3g::Quaternion operator* (const m3g::Quaternion& p, float f);
m3g::Quaternion operator* (const m3g::Quaternion& q1, const m3g::Quaternion& q2);
m3g::Quaternion operator+ (const m3g::Quaternion& q1, const m3g::Quaternion& q2);
std::ostream& operator<< (std::ostream& out, const m3g::Quaternion& q);

#endif
