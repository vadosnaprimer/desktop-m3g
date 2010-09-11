#ifndef __INDEX_BUFFER_HPP__
#define __INDEX_BUFFER_HPP__


#include "Object3D.hpp"
#include "m3ginternal.hpp"
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
         * @~English  Construct a new IndexBuffer Object.
         * @~Japanese 新しいIndexBufferオブジェクトを作成するコンストラクタ.
         */
        IndexBuffer ();

        /**
         * @~English  このオブジェクトを削除するデストラクタ.
         * @~Japanese デストラクタ.
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
         *
         */
        virtual int getFaceCount () const;

        /**
         *
         */
        virtual int getFaceVertexCount () const;

        /**
         *
         */
        virtual void getFaceVertexIndex (int face_index, int* vertex_indices) const;

        /**
         * @~English  Returns the number of indices in this buffer.
         * @~Japanese このバッファーのインデックスの数を取得.
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

        /**
         * @~English  Redner this object, for inner use.
         * @~Japanese このIndexBufferをレンダリングする内部使用の関数.
         */
        virtual void render (RenderState& state) const;


    private:
        IndexBuffer (const IndexBuffer& ibuf);
        IndexBuffer& operator= (const IndexBuffer& ibuf);
    };


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::IndexBuffer& ib);


#endif

