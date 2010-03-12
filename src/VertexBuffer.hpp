#ifndef __VERTEX_BUFFER_HPP__
#define __VERTEX_BUFFER_HPP__

#include <GL/glew.h>
#include "Object3D.hpp"
#include "m3gdef.hpp"
#include <iosfwd>

namespace m3g {

class VertexArray;

/**
 * VertexBufferは頂点位置、法線、色、テクスチャー座標を含むVertexArrayへのポインターを含む.
 */
class VertexBuffer : public Object3D
{
  friend class Mesh;  // for render

public:
    /**
     * デフォルトの値のVertexBufferオブジェクトを作成.
     */
    VertexBuffer ();

    /**
     * デストラクタ.
     */
    virtual ~VertexBuffer ();

    /**
     * アニメーショントラックの追加。
     * 既存のトラックの順番とインデックスは変更されるかもしれない.
     */
    virtual void addAnimationTrack (AnimationTrack* animation_track);

    /**
     * アニメーションの更新.
     */
    virtual int animate (int time);

    /**
     * カレントのカラー配列を取得する。もし頂点カラーが定義されていなければnullが返る.
     */
    VertexArray* getColors () const;

    /**
     * このVertexBufferのデフォルトカラーを取得.
     */
    int getDefaultColor () const;

    /**
     * カレントの法線ベクトルの配列を取得する。もし頂点法線が定義されていなければnullが返る.
     */
    VertexArray* getNormals () const;

    /**
     * カレントの頂点座標の配列を取得する。もし頂点配列が定義されていなければnullが返る.
     */
    VertexArray* getPositions (float* scale_bias) const;

    /**
     * カレントのテクスチャー座標の配列を取得する。もしテクスチャー座標が定義されていなければnullが返る.
     */
  VertexArray* getTexCoords (int index, float* scale_bias) const;

    /**
     * このVertexBufferに頂点カラーを設定する.
     */
    void setColors (VertexArray* colors);

    /**
     * 頂点カラーが設定されていないときのカラーを設定する.
     */
    void setDefaultColor (int rgb);

    /**
     * このVertexBufferに頂点法線を設定する.
     */
    void setNormals (VertexArray* normals);

    /**
     * このVertexBufferに頂点座標を設定する.
     */
    void setPositions (VertexArray* positios, float scale, float* bias);

    /**
     * このVertexBufferにテクスチャー座標を設定する.
     */
    void setTexCoords (int index, VertexArray* texCoords, float scale, float* bias);

  /**
   * このVertexBufferクラスの情報を表示する。デバッグ用.
   */
  virtual std::ostream& print (std::ostream& out) const;


protected:
  virtual void findByObjectType (int obj_type, std::vector<Object3D*>& objs) const;

private:
  virtual void render (int pass, int index=0) const;

private:
  VertexArray* vertex_position_array;
  float        positions_scale;
  float        positions_bias[3];
  VertexArray* texture_coordinate_arrays[MAX_TEXTURE_UNITS];
  float        tex_coord_scale[MAX_TEXTURE_UNITS];
  float        tex_coord_bias[MAX_TEXTURE_UNITS][3];
  VertexArray* normal_array;
  VertexArray* color_array;
  union {
    int default_color;
    unsigned char argb[4];
  };

private:
  GLuint vbuf, ibuf, nbuf, tcbuf[MAX_TEXTURE_UNITS];

};


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::VertexBuffer& vb);


#endif

