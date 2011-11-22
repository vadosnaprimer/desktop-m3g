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
         * @~Japanese 明示的なインデックスで指定したトライアングルストリップ配列の作成.
         * @param[in] num_indices         ストリップで使用する全インデックスの総数.
         * @param[in] indices             ストリップで使用する全インデックスの配列
         * @param[in] num_strip_lengths   ストリップの本数
         * @param[in] srip_lengths        ストリップの長さの配列
         */
        TriangleStripArray (int num_indices, const int* indices, int num_strip_lengths, const int* strip_lengths);

        /**
         * @~English  Constructs a triangle strip array with implicit indices.
         * @~Japanese インデックスを暗黙的に指定したトライアングルストリップ配列の作成.
         * @param[in] first_index          使用する最初のインデックス（以下暗黙的に+1ずつずらした値が使われる）
         * @param[in] num_strip_lengths    ストリップの本数
         * @param[in] srip_lengths         ストリップの長さの配列
         */
        TriangleStripArray (int first_index, int num_strip_lengths, const int* strip_lengths);


        /**
         * @~English  Destruct this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~TriangleStripArray ();

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         * @param[in] 複製されたTriangleStripArrayオブジェクト.
         */
        TriangleStripArray* duplicate () const;


        /**
         * @~English  Print out information of this object, for debug only.
         * @~Japanese このTriangleStripArrayクラスの情報を表示する。デバッグ用の関数.
         * @param[in] out  表示先のストリーム
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
