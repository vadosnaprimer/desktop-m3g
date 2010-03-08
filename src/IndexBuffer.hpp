#ifndef __INDEX_BUFFER_HPP__
#define __INDEX_BUFFER_HPP__

#include <GL/glew.h>
#include "Object3D.hpp"
#include "m3ginternal.hpp"
#include <iosfwd>

namespace m3g {

/**
 * 頂点を連結し幾何形状を定義する抽象クラス.
 */
class IndexBuffer : public Object3D
{
  friend class Mesh; // for render

private:
  static const int EXPLICIT = 1;
  static const int IMPLICIT = 2;

public:
    /**
     * デストラクタ.
     */
  IndexBuffer ();

    /**
     * デストラクタ.
     */
    virtual ~IndexBuffer ();

    /**
     * このバッファーのインデックスの数を取得.
     */
    int getIndexCount () const;

    /**
     * このバッファーに収納されているインデックスを取得する.
     */
    void getIndices (int* indices);

  /**
   * このImage2Dクラスの情報を表示する。デバッグ用.
   */
  virtual std::ostream& print (std::ostream& out) const;

protected:
  virtual void render (int pass, int index=0) const;

PROTECTED:
    /**
     * インデックス配列を明示的に確保する.
     */
  void setIndices (int num_index, int* indices);
    /**
     * インデックス配列を暗黙的に確保する.
     */
  void setIndices (int num_index, int first_index);

protected:
  /**
   * OpenGLのバッファーオブジェクトを取得する.
   */
  GLuint getIBO () const;

private:
  int  index_count;
  int* indices;

private:
  GLuint ibuf;
};


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::IndexBuffer& ib);


#endif

