#ifndef __INDEX_BUFFER_HPP__
#define __INDEX_BUFFER_HPP__

#include <GL/glew.h>
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
    friend class Mesh; // for render

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
     * @~English  Returns the number of indices in this buffer.
     * @~Japanese このバッファーのインデックスの数を取得.
     */
    int getIndexCount () const;

    /**
     * @~English  Retrieves vertex indices for the rendering primitives stored in this buffer.
     * @~Japanese このバッファーに収納されているインデックスを取得する.
     */
    void getIndices (int* indices);

    /**
     * @~English  Print out information of this object, for only debug.
     * @~Japanese このImage2Dクラスの情報を表示する。デバッグ用.
     */
    virtual std::ostream& print (std::ostream& out) const;

  protected:

    /**
     * @~English  Redner this object, for inner use.
     * @~Japanese このIndexBufferをレンダリングする内部使用の関数.
     */
    virtual void render (int pass, int index=0) const;

  PROTECTED:
    /**
     * @~English  Allocate indices, for inner use.
     * @~Japanese インデックス配列を明示的に確保する.
     */
    void setIndices (int num_index, int* indices);
    /**
     * @~English  Allocate indices, for inner use.
     * @~Japanese インデックス配列を暗黙的に確保する.
     */
    void setIndices (int num_index, int first_index);


  private:
    int  index_count;
    int* indices;

  private:
    GLuint ibuf;
  };


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::IndexBuffer& ib);


#endif

