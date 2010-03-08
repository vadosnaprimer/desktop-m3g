#ifndef __QUATERNION_HPP__
#define __QUATERNION_HPP__

#include <iosfwd>

namespace m3g {

/**
 * 長さが必ず１のクォータニオンクラス。内部使用専用.
 */
class Quaternion
{
public:
  Quaternion (); 
  Quaternion (float angle, float ax, float ay, float az);
  ~Quaternion ();
  
  void set (float qx, float qy, float qz, float qw);
  void getAngleAxis (float* angle_axis) const;


  float x;   //< vector component i of Quaternion
  float y;   //< vector component j of Quaternion
  float z;   //< vector component k of Quaternion
  float w;   //< scaler component of Quaternion
};


/**
 * クォータニオンの球面線形補間。a=0の時q0, a=1の時q1が返る.
 */
  m3g::Quaternion slerp (const m3g::Quaternion& q0, const m3g::Quaternion& q1, float alpha);


} // namespace m3g {




m3g::Quaternion operator* (float f, const m3g::Quaternion& q);
m3g::Quaternion operator* (const m3g::Quaternion& p, float f);
m3g::Quaternion operator* (const m3g::Quaternion& q1, const m3g::Quaternion& q2);
m3g::Quaternion operator+ (const m3g::Quaternion& q1, const m3g::Quaternion& q2);
std::ostream& operator<< (std::ostream& out, const m3g::Quaternion& q);

#endif
