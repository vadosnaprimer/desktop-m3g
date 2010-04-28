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
     * @~English  Creates a duplicate of this Object3D. 
     * @~Japanese このオブジェクトの複製の作成.
     */
    VertexArray* duplicate () const;

    /**
     * @~English  Returns a range of 8-bit vertex attributes. 
     * @~Japanese 8bitレンジの頂点データの取得.
     */
    void get (int first_vertex, int num_vertices, char* values) const;

    /**
     * @~English  Returns a range of 16-bit vertex attributes.
     * @~Japanese 16bitレンジの頂点データの取得.
     */
    void get (int first_vertex, int num_vertices, short* values) const;

    /**
     * @~English  Returns a range of 32-bit float vertex attributes.
     * @~Japanese 32bit浮動小数点レンジの頂点データの取得.
     */
    void get (int first_vertex, int num_vertices, float* values) const;

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
     * @~Japanese 8bit頂点データの設定.
     */
    void set (int first_vertex, int num_vertices, const char* values);

    /**
     * @~English  Copies in an array of 16-bit vertex attributes.
     * @~Japanese 16bit頂点データの設定.
     */
    void set (int first_vertex, int num_vertices, const short* values);

    /**
     * @~English  Copies in an array of 32-bit float vertex attributes.
     * @~Japanese 32bit浮動小数点頂点データの設定.
     */
    void set (int first_vertex, int num_vertices, const float* values);

    void setMorphing (const VertexArray* base_positions,
                   const std::vector<const VertexArray*>& morph_target_positions,
                   const std::vector<float>& morph_wegiths);


    void convert (int component_size);

    /**
     * @~English  Retrieve OpenGL' vbo name.
     * @~Japanese OpenGLのvbo名を取得する.
     */
    unsigned int getOpenGLVBO () const;

    /**
     * @~English  Retrieve OpenGL' type name.
     * @~Japanese OpenGLの型名を取得する.
     */
    unsigned int getOpenGLFormat () const;


    /**
     * @~English  Print out information of this object, for debug only.
     * @~Japanese このVertexArrayクラスの情報を表示する。デバッグ用.
     */
    virtual std::ostream& print (std::ostream& out) const;

    /**
     * @~English  Print out raw data of this object, for debug only.
     * @~Japanese このVertexArrayクラスの保持しているデータを表示する。デバッグ用.
     */
    std::ostream& print_raw_data (std::ostream& out) const;


  private:
    int   component_count;
    int   component_size;
    int   vertex_count;
    union {
      char*  char_values;
      short* short_values;
      float* float_values;
    };
    GLuint vbo;
  };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::VertexArray& va);


#endif
