#ifndef __VERTEX_ARRAY_HPP__
#define __VERTEX_ARRAY_HPP__

#include <GL/glew.h>
#include "Object3D.hpp"
#include <iosfwd>
#include "m3ginternal.hpp"

namespace m3g {

  class VertexBuffer;

  /**
   * @~English  An array of integer vectors representing vertex positions, normals, colors, or texture coordinates.
   * @~Japanese 頂点座標、頂点法線、頂点カラー、テクスチャー座標を表す整数ベクトルの配列.
   */
  class VertexArray : public Object3D
  {
    friend class VertexBuffer;

  public:
    /**
     * @~English  Constructs a new VertexArray with the given dimensions.
     * @~Japanese 指定されたサイズで新しいVertxArrayを作成する.
     */
    VertexArray (int num_vertices, int num_components, int component_size);

    /**
     * @~English  Destructs this object.
     * @~Japanese このオブジェクトを削除するデストラクタ.
     */
    virtual ~VertexArray ();

    /**
     * @~English  Returns a range of 8-bit vertex attributes. 
     * @~Japanese 8bit頂点属性値のレンジの取得.
     */
    void get (int first_vertex, int num_vertices, char* values) const;

    /**
     * @~English  Returns a range of 16-bit vertex attributes.
     * @~Japanese 16bit頂点属性値のレンジの取得.
     */
    void get (int first_vertex, int num_vertices, short* values) const;

    /**
     * @~English  Returns the number of components per vertex.
     * @~Japanese 1頂点当たりの要素数の取得.
     */
    int getComponentCount () const;

    /**
     * @~English  Returns the data type (size) of vertex components.
     * @~Japanese 頂点要素のデータタイプ（サイズ）の取得.
     */
    int getComponentType () const;


    /**
     * @~English  Returns the number of vertices in this array.
     * @~Japanese この配列の超点数の取得.
     */
    int getVertexCount () const;

    /**
     * @~English  Copies in an array of 8-bit vertex attributes.
     * @~Japanese 8bit頂点属性値のコピー.
     */
    void set (int first_vertex, int num_vrertices, char* values);

    /**
     * @~English  Copies in an array of 16-bit vertex attributes.
     * @~Japanese 16bit頂点属性値のコピー.
     */
    void set (int first_vertex, int num_vertices, short* values);

    /**
     * @~English  Print out information of this object, for debug only.
     * @~Japanese このVertexArrayクラスの情報を表示する。デバッグ用.
     */
    virtual std::ostream& print (std::ostream& out) const;


    /**
     * @~English  Returns the scaled and biased value as float, this is not under M3G.
     * @~Japanese 値にscale,biasをかけてfloatで取り出すM3G非標準の関数.
     */
    void get (int first_vertex, int num_vertices, float scale, float* bias, float* values) const;


  private:
    int   component_count;
    int   component_size;
    int   vertex_count;
    char* values;

  };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::VertexArray& va);


#endif
