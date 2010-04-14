#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <iosfwd>

namespace m3g {

  /**
   * @~Japanese ベクトルクラス。M3G非標準.
   */
  class Vector
  {
  public:
    Vector ();
    Vector (float x, float y, float z, float w=1);
    ~Vector ();

    void get (float* xyz) const;
    float length () const;

    void normalize ();
    
    float& operator[] (int n);
    const float& operator[] (int n) const;

    Vector& operator+= (const Vector& rhs);

    float x,y,z,w;
  };

  float dot (const Vector& v0, const Vector& v1);
  Vector cross (const Vector& v0, const Vector& v1);


}; // namespace m3g {

m3g::Vector operator* (const m3g::Vector& lhs, float f);
m3g::Vector operator* (float f, const m3g::Vector& rhs);
m3g::Vector operator+ (const m3g::Vector& lhs, const m3g::Vector& rhs);
std::ostream& operator<< (std::ostream& out , const m3g::Vector& v);

#endif
