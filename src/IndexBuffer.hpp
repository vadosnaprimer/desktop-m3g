#ifndef __M3G_INDEX_BUFFER_HPP__
#define __M3G_INDEX_BUFFER_HPP__


#include "m3g/Object3D.hpp"
#include "m3g/m3ginternal.hpp"
#include <iosfwd>

namespace m3g {

    /**
     * @~English  An abstract class defining how to connect vertices to form a geometric object.
     * @~Japanese 頂点を連結し物体の形状を定義する抽象クラス.
     */
    class IndexBuffer : public Object3D
    {
    public:

        /**
         * @~English  A constructor parameter specifying that 
         *            the new IndexBuffer is to contain an array of triangles or triangle strips.
         * @~Japanese このIndexBufferのプリミティブがトライアングル・リストまたは
         *            トライアングル・ストリップの配列であることを示す定数値.
         */
        static const int TRIANGLES     = 8;

        /**
         * @~English  A constructor parameter specifying that 
         *            the new IndexBuffer is to contain an array of lines or line strips.
         * @~Japanese このIndexBufferのプリミティブがライン・リストまたは
         *            ライン・ストリップの配列であることを示す定数値.
         */
        static const int LINES         = 9;

        /**
         * @~English  A constructor parameter specifying that 
         *            the new IndexBuffer is to contain an array of point sprites.
         * @~Japanese このIndexBufferのプリミティブがポイントスプライトの配列であることを示す定数値.
         */
        static const int POINT_SPRITES = 10;

    public:

        /**
         * @~English  Constructs a triangle strip array with explicit indices.
         * @~Japanese ストリップ形式のインデックスを、インデックス配列を明示的に指定しての作成.
         */
        IndexBuffer (int type, const int* strip_indices, int num_strips, const int* strip_lengths);

        /**
         * @~English  Constructs a triangle strip array with implicit indices.
         * @~Japanese ストリップ形式のインデックスを、インデックスを暗黙的に指定して作成.
         */
        IndexBuffer (int type, int first_index, int num_strips, const int* strip_lengths);


        /**
         * @~English  Destruct this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~IndexBuffer ();

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         */
        IndexBuffer* duplicate () const;

        /**
         * @~English  Retrieve the type of rendering primitives stored in this indexBuffer.  
         * @~Japanese プリミティブのタイプを取得する.
         */
        int getPrimitiveType () const;

        /**
         * @~English  Returns the number of indices in this buffer.
         * @~Japanese 頂点のインデックスの総数を取得する.
         *            トライアングル・ストリップの場合、分解されてリストとして数える。
         *            従ってgetIndexCount()/3がトライアングルの個数になる。
         */
        int getIndexCount () const;

        /**
         * @~English  Retrieves vertex indices for the rendering primitives stored in this buffer.
         * @~Japanese 頂点のインデックス配列をプリミティブのリスト形式で取得する.
         *            トライアングル・ストリップは分解されてトライアングル・リストとして返される。
         */
        void getIndices (int* indices) const;

        /**
         * @~English  Print out raw data of this object, for debug only.
         * @~Japanese このIndexBufferクラスの保持しているデータを表示する。デバッグ用.
         */
        std::ostream& print_raw_data (std::ostream& out) const;

        /**
         * @~English  Print out information of this object, for only debug.
         * @~Japanese このIndexBufferクラスの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;


    protected:

        /**
         * @~English  
         * @~Japanese 
         */
        virtual IndexBuffer* duplicate_xxx (Object3D* obj) const;

        /**
         * @~English  
         * @~Japanese 
         */
        virtual void render_xxx (RenderState& state) const;


    private:
        IndexBuffer (const IndexBuffer& ibuf);
        IndexBuffer& operator= (const IndexBuffer& ibuf);

    protected:
        int              type;
        std::vector<int> strip_indices;
        std::vector<int> strip_lengths;

        unsigned int     name;
    };


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::IndexBuffer& ib);


#endif

