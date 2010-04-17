#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
#include "Exception.hpp"
#include "RenderState.hpp"
#include <iostream>
using namespace std;
using namespace m3g;


VertexBuffer:: VertexBuffer () :
  positions(0), normals(0), colors(0), positions_scale(1),
  default_color(0xffffffff), vbuf(0), ibuf(0), nbuf(0)
{
  setObjectType (OBJTYPE_VERTEX_BUFFER);

  for (int i = 0; i < 3; i++) {
    positions_bias[i] = 0;
  }
  for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
    tex_coords[i] = 0;
    tex_coords_scale[i] = 1;
    for (int j = 0; j < 3; j++) {
      tex_coords_bias[i][j] = 0;
    }
    tcbuf[i] = 0;
  }
  //glGenBuffers (1, &vbuf);
  //glGenBuffers (1, &ibuf);
  //glGenBuffers (1, &nbuf);
  //glGenBuffers (MAX_TEXTURE_UNITS, (GLuint*)&tcbuf);
}

VertexBuffer:: ~VertexBuffer ()
{
}

VertexBuffer* VertexBuffer:: duplicate () const
{
  VertexBuffer* vbuf = new VertexBuffer (*this);
  Object3D* obj      = Object3D:: duplicate();
  *(Object3D*)vbuf   = *obj;
  // 現状ではOpenGLのバッファーオブジェクトを共通で使用するのでコメントアウト
  // vbuf->setPositons (vertex_position_array, positions_scale, positions_bias);
  // vbuf->setNormals (normals);
  // vbuf->setColors (colors);
  // for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
  //  vbuf->setTexCoords (i, tex_coord_scale[i], tex_coords_bias[i]);
  // }
  return vbuf;
}


void VertexBuffer:: addAnimationTrack (AnimationTrack* animation_track)
{
  if (animation_track == NULL) {
    throw NullPointException (__FILE__, __func__, "Animation track is NULL.");
  }
  int property = animation_track->getTargetProperty();
  if (property != AnimationTrack::COLOR &&
      property != AnimationTrack::ALPHA) {
    throw IllegalArgumentException (__FILE__, __func__, "Animation target is invalid for this VertexBuffer, property=%d.", property);
  }
 
  Object3D:: addAnimationTrack (animation_track);
}

int VertexBuffer:: animate (int world_time)
{
  Object3D:: animate (world_time);

  //cout << "VertexBuffer: animate, track=" << getAnimationTrackCount() << "\n";
  
  bool  is_color_modefied = false;
  bool  is_alpha_modefied = false;
  float rgb[]  = {0,0,0};
  float new_alpha  = 0;

  for (int i = 0; i < getAnimationTrackCount(); i++) {
    AnimationTrack*      track      = getAnimationTrack (i);
    KeyframeSequence*    keyframe   = track->getKeyframeSequence();
    AnimationController* controller = track->getController();
    if (controller == NULL) {
      //cout << "VertexBuffer: missing controller, this animation track is ignored.\n";
      continue;
    }
    if (!controller->isActiveInterval(world_time)) {
      continue;
    }
    float weight     = controller->getWeight ();
    float local_time = controller->getPosition (world_time);
    
    switch (track->getTargetProperty()) {
    case AnimationTrack::COLOR: {
      float value[3] = {1,1,1};
      keyframe->getFrame (local_time, value);
      rgb[0] += value[0] * weight;
      rgb[1] += value[1] * weight;
      rgb[2] += value[2] * weight;
      is_color_modefied = true;
      //cout << "VertexBuffer: default color --> " << rgb[0] << ", " << rgb[1] << ", " << rgb[2] << "\n";
      break;
    }
    case AnimationTrack::ALPHA: {
      float value[1] = {1};
      keyframe->getFrame (local_time, value);
      new_alpha += value[0] * weight;
      is_alpha_modefied = true;
      //cout << "VertexBuffer: alpha --> " << alpha << "\n";
      break;
    }
    default: {
      // Unknwon target should be ignored.
      // animate() of Base class (of Derived class) retrieve it.
    }
    }
  }

  if (is_color_modefied) {
    unsigned char r = clamp (0, 1, rgb[0]) * 255;
    unsigned char g = clamp (0, 1, rgb[1]) * 255;
    unsigned char b = clamp (0, 1, rgb[2]) * 255;
      //cout << "VertexBuffer: r,g,b = " << (int)r << ", " << (int)g << ", " << (int)b << "\n";
    default_color = (default_color & 0xff000000) | (r << 16) | (g << 8) | (b << 0);
  }
  if (is_alpha_modefied) {
    unsigned char a = clamp (0, 1, new_alpha) * 255;
    default_color = (default_color & 0x00ffffff) | (a << 24);
  }

  //cout << hex << "VertexBuffer: default_color = 0x" << default_color << dec << "\n";

  // メモ：
  // 0でも間違えではないが仕様書をよく読んでから実装する。

  return 0;
}

VertexArray* VertexBuffer:: getColors () const
{
  return colors;
}

int VertexBuffer:: getDefaultColor () const
{
    return default_color;
}

VertexArray* VertexBuffer:: getNormals () const
{
  return normals;
}

VertexArray* VertexBuffer:: getPositions (float* scale_bias) const
{
  if (scale_bias) {
    scale_bias[0] = positions_scale;
    scale_bias[1] = positions_bias[0];
    scale_bias[2] = positions_bias[1];
    scale_bias[3] = positions_bias[2];
  }
  return positions;
}

VertexArray* VertexBuffer:: getTexCoords (int index, float* scale_bias) const
{
  if (index < 0 || index >= MAX_TEXTURE_UNITS) {
    throw IllegalArgumentException (__FILE__, __func__, "Texture index is invalid.");
  }

  VertexArray* tex = tex_coords[index];

  if (tex && scale_bias) {
    scale_bias[0] = tex_coords_scale[index];
    for (int i = 0; i < tex->getComponentCount(); i++) {
      scale_bias[i+1] = tex_coords_bias[index][i];
    }
  }

  return tex;
}

/**
 * x:[-128,127] --> y:[0,1]
 * y = (x+128)/255
 */
void VertexBuffer:: setColors (VertexArray* colors_)
{
  if (colors_->getComponentType() != 1) {
    throw IllegalArgumentException (__FILE__, __func__, "Component size must be 1, size=%d.", colors_->getComponentType());
  }
  if (colors_->getComponentCount() != 3 && colors_->getComponentCount() != 4) {
    throw IllegalArgumentException (__FILE__, __func__, "Component count must be 3 or 4, size=%d.", colors_->getComponentCount());
  }

  colors = colors_;

  float scale   = 1/255.f;
  float bias[4] = {0,0,0};
  int   num     = colors->getComponentCount()*colors->getVertexCount();
  int   size    = sizeof(float)* num;

  // メモ： Colorの場合に限りデータを0〜255のunsigned型として解釈する
  unsigned char* uchar_values = new unsigned char[num];
  colors->get (0, colors->getVertexCount(), (char*)uchar_values);

  float* float_values = new float[num];
  for (int i = 0; i < num; i++) {
    float_values[i] = uchar_values[i]*scale + bias[i%3];
  }

  glGenBuffers (1, &ibuf);
  glBindBuffer (GL_ARRAY_BUFFER, ibuf);
  glBufferData (GL_ARRAY_BUFFER, size, float_values, GL_STATIC_DRAW);

  delete [] uchar_values;
  delete [] float_values;
}

void VertexBuffer:: setDefaultColor (int argb)
{
  default_color = argb;
}

/**
 * x:[-128,127] --> y:[-1,1], or x:[-32768,32767] --> y:[-1,1]
 * y = (2x+1)/255, or y = (2x+1)/65535
 */
void VertexBuffer:: setNormals (VertexArray* normals_)
{
  if (normals_ == NULL) {
    normals = NULL;
    return;
  }

  if (normals_->getComponentType() != 1 && normals_->getComponentType() != 2) {
    throw IllegalArgumentException (__FILE__, __func__, "Component size must be 1 or 2, size=%d.", normals_->getComponentType());
  }
  if (normals_->getComponentCount() != 3) {
    throw IllegalArgumentException (__FILE__, __func__, "Component count must be 3, size=%d.", normals_->getComponentCount());
  }
  if (positions && positions->getVertexCount() != normals_->getVertexCount()) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of Positions is different from number of Normals_., count(pos)=%d, count(normals_)", positions->getVertexCount(), normals_->getVertexCount());
  }
  for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
    if (tex_coords[i] && tex_coords[i]->getVertexCount() != normals_->getVertexCount()) {
      throw IllegalArgumentException (__FILE__, __func__, "Number of Texture Coordinate is different from number of Normals_, count(tex)=%d, count(normals_)=%d.",  tex_coords[i]->getVertexCount(), normals_->getVertexCount());
    }
  }
  if (colors && colors->getVertexCount() != normals_->getVertexCount()) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of Colors is different from number of Normals_, count(color)=%d, count(normals_)=%d.", colors->getVertexCount(), normals_->getVertexCount());
  }

  normals = normals_;

  float scale;
  float bias[4];
  scale   = (normals->getComponentType() == 1) ? 2/255.f : 2/65535;
  bias[0] = bias[1] = bias[2] = bias[3] = (normals->getComponentType() == 1) ? 1/255.f : 1/65535.f;

  int    num    = normals->getComponentCount()*normals->getVertexCount();
  int    size   = sizeof(float)* num;
  float* values = new float [num];
  normals->get (0, normals->getVertexCount(), scale, bias, values);

  glGenBuffers (1, &nbuf);
  glBindBuffer (GL_ARRAY_BUFFER, nbuf);
  glBufferData (GL_ARRAY_BUFFER, size, values, GL_STATIC_DRAW);

  delete [] values;

}

void VertexBuffer:: setPositions (VertexArray* positions_, float scale, float* bias)
{
  if (positions_ == NULL) {
    positions = NULL;
    return;
  }

  if (positions_->getComponentType() != 1 && positions_->getComponentType() != 2) {
    throw IllegalArgumentException (__FILE__, __func__, "Component size must be 1 or 2, size=%d.", positions_->getComponentType());
  }
  if (positions_->getComponentCount() != 3) {
    throw IllegalArgumentException (__FILE__, __func__, "Component count must be 3, count=%d.", positions_->getComponentCount());
  }
  if (normals && normals->getVertexCount() != positions_->getVertexCount()) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of Normals is different from one of Vertex Positions_, count(normal)=%d, count(pos)=%d.", normals->getVertexCount(), positions_->getVertexCount());
  }
  for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
    if (tex_coords[i] && tex_coords[i]->getVertexCount() != positions_->getVertexCount()) {
      throw IllegalArgumentException (__FILE__, __func__, "Number of Texture Coordinate is different from one of Vertex Positions_, count(tex)=%d, count(pos)=%d.", tex_coords[i]->getVertexCount(), positions_->getVertexCount());
    }
  }
  if (colors && colors->getVertexCount() != positions_->getVertexCount()) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of Colors is different from number of Vertex Positions_.", colors->getVertexCount(), positions_->getVertexCount());
  }
  if (bias == NULL) {
    throw NullPointException (__FILE__, __func__, "Bias is NULL.");
  }

  positions = positions_;
  positions_scale   = scale;
  positions_bias[0] = bias[0];
  positions_bias[1] = bias[1];
  positions_bias[2] = bias[2];

  int    num    = positions->getComponentCount()*positions->getVertexCount();
  int    size   = sizeof(float)* num;
  float* values = new float [num];
  positions->get (0, positions->getVertexCount(), scale, bias, values);

  glGenBuffers (1, &vbuf);
  glBindBuffer (GL_ARRAY_BUFFER, vbuf);
  glBufferData (GL_ARRAY_BUFFER, size, values, GL_STATIC_DRAW);

  delete [] values;
}

void VertexBuffer:: setTexCoords (int index, VertexArray* tex_coords_, float scale, float* bias)
{
  if (index < 0 || index >= MAX_TEXTURE_UNITS) {
    throw IllegalArgumentException (__FILE__, __func__, "Index is invalid, index=%d.", index);
  }
  if (bias == NULL) {
    throw NullPointException (__FILE__, __func__, "Bias is NULL.");
  }

  if (tex_coords_ == NULL) {
    tex_coords[index] = NULL;
    return;
  }

  if (tex_coords_->getComponentType() != 1 && tex_coords_->getComponentType() != 2) {
    throw IllegalArgumentException (__FILE__, __func__, "Component size must be 1 or 2, size=%d.", tex_coords_->getComponentType());
  }
  if (tex_coords_->getComponentCount() != 2 && tex_coords_->getComponentCount() != 3) {
    throw IllegalArgumentException (__FILE__, __func__, "Component count must be 2 or 3, count=%d.", tex_coords_->getComponentCount());
  }

  if (positions && positions->getVertexCount() != tex_coords_->getVertexCount()) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of Vertex Positions is different from number of Texture Coordinates, count(color)=%d, count(texture)=%d.", positions->getVertexCount(), tex_coords_->getVertexCount());
  }
  if (normals && normals->getVertexCount() != tex_coords_->getVertexCount()) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of Normals is different from number of Texture Coordinates, count(normal)=%d, count(texture)=%d.", normals->getVertexCount(), tex_coords_->getVertexCount());
  }
  if (colors && colors->getVertexCount() != tex_coords_->getVertexCount()) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of Colors is different from number of Texture Coordinagtes, count(color)=%d, count(texture)=%d.", colors->getVertexCount(), tex_coords_->getVertexCount());
  }
  if (bias == NULL) {
    throw NullPointException (__FILE__, __func__, "Bias is NULL.");
  }

  tex_coords[index] = tex_coords_;

  int    num    = tex_coords[index]->getComponentCount() * tex_coords[index]->getVertexCount();
  int    size   = sizeof(float)* num;
  float* values = new float [num];
  tex_coords[index]->get (0, tex_coords[index]->getVertexCount(), scale, bias, values);

  glGenBuffers (MAX_TEXTURE_UNITS, &tcbuf[index]);
  glBindBuffer (GL_ARRAY_BUFFER, tcbuf[index]);
  glBufferData (GL_ARRAY_BUFFER, size, values, GL_STATIC_DRAW);

  delete [] values;
}

/**
 * Note: VertexBuffer should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void VertexBuffer:: render (RenderState& state) const
{
  if (state.pass != 2) {
    return;
  }

  //cout << "VertexBuffer: vbuf = " << vbuf << "\n";

  if (positions) {
    //cout << "render vertex array\n";
    int cc = positions->getComponentCount();
    glBindBuffer (GL_ARRAY_BUFFER, vbuf);
    glEnableClientState (GL_VERTEX_ARRAY);
    glVertexPointer (cc, GL_FLOAT, 0, 0);  // 0,0=stride,offset
  } else {
    glDisableClientState (GL_VERTEX_ARRAY);
  }

  // TODO: vertex_color_tracking=enableの時のみ頂点カラーを使うべき。
  // あとこれだとDIFFUSE COLORが設定されていない。
  if (colors) {
    //cout << "VertexBuffer: render color array\n";
    int cc = colors->getComponentCount();
    glBindBuffer (GL_ARRAY_BUFFER, ibuf);
    glEnableClientState (GL_COLOR_ARRAY);
    glColorPointer (cc, GL_FLOAT, 0, 0);  // 0,0=stride,offset
  } else {
    //cout << "VertexBuffer: render default color\n";
    glDisableClientState (GL_COLOR_ARRAY);
    float r = ((default_color & 0x00ff0000) >> 16) / 255.f;
    float g = ((default_color & 0x0000ff00) >>  8) / 255.f;
    float b = ((default_color & 0x000000ff) >>  0) / 255.f;
    float a = ((default_color & 0xff000000) >> 24) / 255.f;
    glColor4f (r,g,b,a);
  }

  if (normals) {
    //cout << "render normal array\n";
    glBindBuffer (GL_ARRAY_BUFFER, nbuf);
    glEnableClientState (GL_NORMAL_ARRAY);
    glNormalPointer (GL_FLOAT, 0, 0);
  } else {
    glDisableClientState (GL_NORMAL_ARRAY);
  }

  for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
    if (tex_coords[i]) {
      cout << "VertexBuffer: render " << i << "th texture coordinate array\n";
      int cc = tex_coords[i]->getComponentCount();
      glBindBuffer          (GL_ARRAY_BUFFER, tcbuf[i]);  // VBOの選択
      glClientActiveTexture (GL_TEXTURE0+i);              // (クライアントを含む）テクスチャーユニットの選択
      glEnableClientState   (GL_TEXTURE_COORD_ARRAY);     // 頂点配列の有効化
      glTexCoordPointer     (cc, GL_FLOAT, 0, 0);         // テクスチャー座標の指定
    }
  }
  
}

void VertexBuffer:: findByObjectType (int type, std::vector<Object3D*>& objs) const
{
  if (positions) {
    positions->findByObjectType (type, objs);
  }
  for (int i = 0;i < MAX_TEXTURE_UNITS; i++) {
    if (tex_coords[i]) {
      tex_coords[i]->findByObjectType (type, objs);
    }
  }
  if (normals) {
    normals->findByObjectType (type, objs);
  }
  if (colors) {
    colors->findByObjectType (type, objs);
  }

}



std::ostream& VertexBuffer:: print (std::ostream& out) const
{
  out << "VertexBuffer: ";
  if (positions)
    out << "  positions = " << *positions;
  else
    out << "  positions = 0";
  if (normals)
    out << ", normals = " << *normals;
  else
    out << ", normals = 0";
  
  if (colors)
    out << ", colors  = " << *colors;
  else
    out << ", colors  = 0";
  out << ", default color = 0x" << hex << default_color << dec;
  return out << "\n";;
}

std::ostream& operator<< (std::ostream& out, const VertexBuffer& vbuf)
{
  return vbuf.print(out);
}



