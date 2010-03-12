#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iosfwd>

namespace m3g {

  class Vector;

/**
 * 行列クラス。内部使用専用.
 */
class Matrix
{
public:
  Matrix ();
  Matrix (float* m4x4);
  Matrix (float m00, float m01, float m02, float m03, 
	  float m10, float m11, float m12, float m13, 
	  float m20, float m21, float m22, float m23, 
	  float m30, float m31, float m32, float m33);
  ~Matrix ();

  void set(const float* mat);
  void setIdentity();
  void setRotate (float angle, float ax, float ay, float az);
  void setScale (float sx, float sy, float sz);
  void setTranslate (float tx, float ty, float tz);

  void invert ();
  void transpose ();
  Matrix& operator*= (const Matrix& rhs);

    /**
     * このMatrixクラスの情報を表示する。デバッグ用.
     */
  std::ostream& print (std::ostream& out) const;

public:
  float m[4][4];
};




} // namespace m3g {


m3g:: Matrix operator* (const m3g::Matrix& lhs, const m3g::Matrix& rhs);
m3g:: Vector operator* (const m3g::Matrix& m, const m3g::Vector& v);
std::ostream& operator<< (std::ostream& out, const m3g::Matrix& mat);


#endif
