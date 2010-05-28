#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <iosfwd>

namespace m3g {

    /**
     * @~English  Vector class, not defined by M3G.
     * @~Japanese ベクトルクラス。M3G非標準.
     */
    class Vector
    {
    public:
        Vector ();
        explicit Vector (float* xyz);
        Vector (float x, float y, float z, float w=1);
        ~Vector ();

        void  get (float* xyz) const;
        void  get4 (float* xyzw) const;
        float length () const;

        Vector& normalize ();
        Vector& divided_by_w ();
    
        float& operator[] (int n);
        const float& operator[] (int n) const;

        Vector operator- () const;

        Vector& operator+= (const Vector& rhs);

        std::ostream& print (std::ostream& out) const;

    public:
        float x,y,z,w;
    };

    float  dot (const Vector& v0, const Vector& v1);
    Vector cross (const Vector& v0, const Vector& v1);
    Vector lerp (float u, float v, const Vector& v0, const Vector& v1, const Vector& v2);


}; // namespace m3g {

m3g::Vector operator* (const m3g::Vector& lhs, float f);
m3g::Vector operator* (float f, const m3g::Vector& rhs);
m3g::Vector operator/ (const m3g::Vector& lhs, float f);
m3g::Vector operator+ (const m3g::Vector& lhs, const m3g::Vector& rhs);
m3g::Vector operator- (const m3g::Vector& lhs, const m3g::Vector& rhs);




std::ostream& operator<< (std::ostream& out , const m3g::Vector& v);



#endif
