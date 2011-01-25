#ifndef __M3G_INDEX_BUFFER_HPP__
#define __M3G_INDEX_BUFFER_HPP__


#include "m3g/Object3D.hpp"
#include "m3g/m3ginternal.hpp"
#include <iosfwd>

namespace m3g {

    /**
     * @~English  An abstract class defining how to connect vertices to form a geometric object.
     * @~Japanese 頂点を連結し幾何形状を定義する抽象クラス.
     */
    class IndexBuffer : public Object3D
    {


    public:
        /**
         * @~English  Construct a new IndexBuffer object.
         * @~Japanese 新しいIndexBufferオブジェクトを作成するコンストラクタ.
         */
        IndexBuffer ();

        /**
         * @~English  Destruct this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~IndexBuffer ();

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         */
        virtual IndexBuffer* duplicate () const;

        /**
         * @~English  Copy this Object3D to specified Object3D, not defined by M3G. 
         * @~Japanese このオブジェクトのデータを引数で指定されたオブジェクトにコピーするM3G非標準の関数.
         */
        void copy (IndexBuffer* ibuf) const;

        /**
         * @~English  Get a number of faces, not in M3G.
         * @~Japanese この面数の合計を取得する, M3G非標準.
         */
        virtual int getFaceCount () const;

        /**
         * @~English  Get a vertex number of 1 face, not in M3G.
         * @~Japanese 1面あたりの頂点数を取得する, M3G非標準.
         */
        virtual int getFaceVertexCount () const;

        /**
         * @~English  Get a vertex number of 1 face, not in M3G.
         * @~Japanese 指定の面の頂点インデックスを取得する, M3G非標準.
         */
        virtual void getFaceVertexIndex (int face_index, int* vertex_indices) const;

        /**
         * @~English  Returns the number of indices in this buffer.
         * @~Japanese このバッファーの頂点インデックスの総数を取得.
         */
        virtual int getIndexCount () const;

        /**
         * @~English  Retrieves vertex indices for the rendering primitives stored in this buffer.
         * @~Japanese このバッファーに収納されているインデックスを取得.
         */
        virtual void getIndices (int* indices) const;


        /**
         * @~English  Print out information of this object, for only debug.
         * @~Japanese このIndexBufferクラスの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

        /**
         * @~English  Print out raw data of this object, for debug only.
         * @~Japanese このIndexBufferクラスの保持しているデータを表示する。デバッグ用.
         */
        virtual std::ostream& print_raw_data (std::ostream& out) const;

    protected:

        /**
         * @~English  
         * @~Japanese 
         */
        virtual void render_xxx (RenderState& state) const;


    private:
        IndexBuffer (const IndexBuffer& ibuf);
        IndexBuffer& operator= (const IndexBuffer& ibuf);
    };


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::IndexBuffer& ib);


#endif

