#ifndef __VERTEX_BUFFER_HPP__
#define __VERTEX_BUFFER_HPP__

#include <GL/glew.h>
#include "Object3D.hpp"
#include "m3gdef.hpp"
#include <iosfwd>

namespace m3g {

  class VertexArray;

  /**
   * @~English  VertexBuffer holds references to VertexArrays that 
   *            contain the positions, colors, normals, and 
   *            texture coordinates for a set of vertices.
   * @~Japanese VertexBufferは頂点位置、法線、色、テクスチャー座標を保持する
   *            VertexArrayへのポインターを持つホルダークラス.
   */
  class VertexBuffer : public Object3D
  {
    friend class Mesh;  // for render

  public:
    /**
     * @~English  Creates an empty VertexBuffer with default values.
     * @~Japanese デフォルトの値のVertexBufferオブジェクトを作成.
     */
    VertexBuffer ();

    /**
     * @~English  Destructs this object.
     * @~Japanese このオブジェクトを削除するデストラクタ.
     */
    virtual ~VertexBuffer ();


    virtual void addAnimationTrack (AnimationTrack* animation_track);


    virtual int animate (int time);

    /**
     * @~English  Gets the current color array.
     * @~Japanese カレントのカラー配列の取得.
     */
    VertexArray* getColors () const;

    /**
     * @~English  Retrieves the default color of this VertexBuffer.
     * @~Japanese このVertexBufferのデフォルトカラーを取得.
     */
    int getDefaultColor () const;

    /**
     * @~English  Gets the current normal vector array.
     * @~Japanese カレントの法線ベクトルの配列の取得.
     */
    VertexArray* getNormals () const;

    /**
     * @~English  Returns the current vertex position array.
     * @~Japanese カレントの頂点座標の配列の取得.
     */
    VertexArray* getPositions (float* scale_bias) const;

    /**
     * @~English  Gets the current texture coordinate array for the specified texture unit.
     * @~Japanese カレントのテクスチャー座標の配列の取得.
     */
    VertexArray* getTexCoords (int index, float* scale_bias) const;

    /**
     * @~English  Sets the per-vertex color for this VertexBuffer.
     * @~Japanese このVertexBufferに頂点カラーを設定する.
     */
    void setColors (VertexArray* colors);

    /**
     * @~English  Sets the color to use in absence of per-vetex colors.
     * @~Japanese 頂点カラーが設定されていないときのカラーを設定する.
     */
    void setDefaultColor (int rgb);

    /**
     * @~English  Sets the normal vectors for this VertexBuffer.
     * @~Japanese このVertexBufferに頂点法線を設定する.
     */
    void setNormals (VertexArray* normals);

    /**
     * @~English  Sets the vertex positions for this VertexBuffer.
     * @~Japanese このVertexBufferに頂点座標を設定する.
     */
    void setPositions (VertexArray* positios, float scale, float* bias);

    /**
     * @~English  Sets the texture coordinates for the specified textureing unit.
     * @~Japanese このVertexBufferにテクスチャー座標を設定する.
     */
    void setTexCoords (int index, VertexArray* tex_coords, float scale, float* bias);

    /**
     * @~English  Print out information of this object, for debug only.
     * @~Japanese このVertexBufferクラスの情報を表示する。デバッグ用.
     */
    virtual std::ostream& print (std::ostream& out) const;


  protected:
    virtual void findByObjectType (int obj_type, std::vector<Object3D*>& objs) const;

  private:
    virtual void render (int pass, int index=0) const;


    // normal_array --> normals に名前を変えようか？

  private:
    VertexArray* vertex_position_array;
    float        positions_scale;
    float        positions_bias[3];
    VertexArray* texture_coordinate_arrays[MAX_TEXTURE_UNITS];
    float        tex_coord_scale[MAX_TEXTURE_UNITS];
    float        tex_coord_bias[MAX_TEXTURE_UNITS][3];
    VertexArray* normal_array;
    VertexArray* color_array;
    int          default_color;

  private:
    GLuint vbuf, ibuf, nbuf, tcbuf[MAX_TEXTURE_UNITS];

  };


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::VertexBuffer& vb);


#endif

