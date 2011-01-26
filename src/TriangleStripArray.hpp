#ifndef __M3G_TRIANGLE_STRIP_ARRAY_HPP__
#define __M3G_TRIANGLE_STRIP_ARRAY_HPP__

#include "m3g/IndexBuffer.hpp"
#include <iosfwd>

namespace m3g {

    /**
     * @~English  TriangleStripArray defines an array  of triangle strips.
     * @~Japanese トライアングルストリップの配列を定義する.
     */
    class TriangleStripArray : public IndexBuffer
    {

    public:
        /**
         * @~English  Constructs a triangle strip array with explicit indices.
         * @~Japanese 明示的なインデックスで指定したトライアングルストリップ配列の作成
         */
        TriangleStripArray (const int* indices, int num_strips, const int* strip_lengthss);

        /**
         * @~English  Constructs a triangle strip array with implicit indices.
         * @~Japanese 暗黙的にインデックスで指定したトライアングルストリップ配列の作成
         */
        TriangleStripArray (int first_index, int num_strips, const int* strip_lengths);


        /**
         * @~English  Destruct this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~TriangleStripArray ();

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         */
        TriangleStripArray* duplicate () const;


        /**
         * @~English  Print out information of this object, for debug only.
         * @~Japanese このTriangleStripArrayクラスの情報を表示する。デバッグ用の関数.
         */
        virtual std::ostream& print (std::ostream& out) const;


    protected:

        /**
         * @~English  
         * @~Japanese 
         */
        virtual TriangleStripArray* duplicate_xxx (Object3D* obj) const;


    private:
        TriangleStripArray (const TriangleStripArray& tris);
        TriangleStripArray& operator= (const TriangleStripArray& tris);

    };
  

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::TriangleStripArray& a);


#endif
