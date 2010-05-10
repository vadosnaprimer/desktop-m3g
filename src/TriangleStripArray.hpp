#ifndef __TRIANGLE_STRIP_ARRAY_HPP__
#define __TRIANGLE_STRIP_ARRAY_HPP__

#include "IndexBuffer.hpp"
#include <iosfwd>

namespace m3g {

  /**
   * @~English  TriangleStripArray defines an array  of triangle strips.
   * @~Japanese トライアングルストリップを定義する.
   */
  class TriangleStripArray : public IndexBuffer
  {

  public:
    /**
     * @~English  Constructs a triangle strip array with explicit indices.
     * @~Japanese 明示的なインデックスで指定したトライアングルストリップ配列の作成
     */
    TriangleStripArray (int* indices, int num_strips, int* strips);

    /**
     * @~English  Constructs a triangle strip array with implicit indices.
     * @~Japanese 暗黙的にインデックスで指定したトライアングルストリップ配列の作成
     */
    TriangleStripArray (int first_index, int num_strips, int* strips);


    /**
     * @~English  Destruct this object.
     * @~Japanese このオブジェクトを削除するデストラクタ.
     */
    virtual ~TriangleStripArray ();

    /**
     * @~English  Creates a duplicate of this Object3D. 
     * @~Japanese このオブジェクトの複製の作成.
     */
    virtual TriangleStripArray* duplicate () const;

    /**
     * @~English  Returns the number of indices in this buffer.
     * @~Japanese このバッファーのインデックスの数を取得.
     */
    virtual int getIndexCount () const;

    /**
     * @~English  Retrieves vertex indices for the rendering primitives stored in this buffer.
     * @~Japanese このバッファーに収納されているインデックスを取得する.
     */
    virtual void getIndices (int* indices);

    /**
     * @~English  Print out information of this object, for debug only.
     * @~Japanese このTriangleStripArrayクラスの情報を表示する。デバッグ用の関数.
     */
    virtual std::ostream& print (std::ostream& out) const;


    /**
     * @~English  Render this object, for inner use.
     * @~Japanese このオブジェクトのレンダリング.
     */
    virtual void render (RenderState& state) const;


  private:
    int*             indices;
    std::vector<int> strips;

    GLuint ibuf;
  };
  

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::TriangleStripArray& a);


#endif
