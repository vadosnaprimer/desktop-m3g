#ifndef __TRIANGLE_STRIP_ARRAY_HPP__
#define __TRIANGLE_STRIP_ARRAY_HPP__

#include "IndexBuffer.hpp"
#include <iosfwd>

namespace m3g {

/**
 * トライアングルストリップを定義する.
 */
class TriangleStripArray : public IndexBuffer
{
public:
    /**
     * 明示的なインデックスで指定したトライアングルストリップ配列の作成
     */
  TriangleStripArray (int* indices, int num_strips, int* strips);

    /**
     * 暗黙的にインデックスで指定したトライアングルストリップ配列の作成
     */
  TriangleStripArray (int first_index, int num_strips, int* strips);


    /**
     * デストラクタ.
     */
    virtual ~TriangleStripArray ();

  /**
   * このTriangleStripArrayクラスの情報を表示する。デバッグ用の関数.
   */
  virtual std::ostream& print (std::ostream& out) const;

protected:
  /**
   *
   */
  virtual void render (int pass, int index=0) const;


PRIVATE:
  std::vector<int> strips;
};


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::TriangleStripArray& a);


#endif
