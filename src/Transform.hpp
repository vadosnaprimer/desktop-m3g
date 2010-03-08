#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__

#include <iosfwd>
#include "Matrix.hpp"

namespace m3g {

class VertexArray;

/**
 * 座標変換を表す汎用の4x4行列.
 */
class Transform 
{
public:
    /**
     * デフォルトの値のTransformオブジェクトの生成.
     */
    Transform ();

    /**
     * 指定されたTransformをコピーしてTransformオブジェクトを生成.
     */
    Transform (const Transform& t);

    /**
     * デストラクタ.
     */
    ~Transform ();

    /**
     * この変換を16個のfloatの配列として取り出す.
     */
    void get (float* matrix) const;

    /**
     * (可能なら)この行列の逆行列を計算し置き換える.
     */
    void invert ();

    /**
     * 指定された変換行列を右から乗算する.
     */
    void postMultiply (const Transform& transform);

    /**
     * 指定された回転軸と角度で回転する回転行列を右から乗算する。角度の単位はdegree.
     */
    void postRotate (float angle, float ax, float ay, float az);

    /**
     * クォータニオン形式で指定された回転を行う回転行列を右から乗算する.
     */
    void postRotateQuat (float qx, float qy, float qz, float qw);

    /**
     * 指定されたスケーリング行列を右から乗算する.
     */
    void postScale (float sx, float sy, float sz);

    /**
     * 指定された移動行列を右から乗算する.
     */
    void postTranslate (float tx, float ty, float tz);

    /**
     * 指定された16個のfloatの配列をコピーして変換を設定する.
     */
    void set (const float* matrix);

    /**
     * 指定されたTransformをコピーして変換を設定する.
     */
    void set (const Transform& transform);

    /**
     * この変換を4x4の単位行列に設定する.
     */
    void setIdentity ();

    /**
     * 指定された4要素のfloatのベクトルにこの変換行列を乗算する.
     */
    void transform (float* vectors) const;

    /**
     * 指定されたVertexArrayの要素にこの変換行列を乗算する。
     * 結果はfloatの配列として収納する.
     */
    void transform (VertexArray* in, float* out, bool w) const;

  /**
   * 転置を取りこの行列と入れ替える.
   */
  void transpose ();

    /**
     * このTransformクラスの情報を表示する。デバッグ用.
     */
  virtual std::ostream& print (std::ostream& out) const;

private:
  Matrix matrix;
};



} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Transform& t);

#endif
