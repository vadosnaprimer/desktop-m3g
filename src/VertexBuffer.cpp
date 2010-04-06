#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
#include "Exception.hpp"
#include <iostream>
using namespace std;
using namespace m3g;


VertexBuffer:: VertexBuffer () :
  vertex_position_array(0), positions_scale(1),
  normal_array(0), color_array(0),
  default_color(0xffffffff),
  vbuf(0), ibuf(0)
{
  setObjectType (OBJTYPE_VERTEX_BUFFER);

  for (int i = 0; i < 3; i++) {
    positions_bias[i] = 0;
  }
  for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
    texture_coordinate_arrays[i] = 0;
    tex_coord_scale[i] = 1;
    for (int j = 0; j < 3; j++) {
      tex_coord_bias[i][j] = 0;
    }
  }
  glGenBuffers (1, &vbuf);
  glGenBuffers (1, &ibuf);
  glGenBuffers (1, &nbuf);
  glGenBuffers (MAX_TEXTURE_UNITS, (GLuint*)&tcbuf);
}

VertexBuffer:: ~VertexBuffer ()
{
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
  return color_array;
}

int VertexBuffer:: getDefaultColor () const
{
    return default_color;
}

VertexArray* VertexBuffer:: getNormals () const
{
    return normal_array;
}

VertexArray* VertexBuffer:: getPositions (float* scale_bias) const
{
  if (scale_bias) {
    scale_bias[0] = positions_scale;
    scale_bias[1] = positions_bias[0];
    scale_bias[2] = positions_bias[1];
    scale_bias[3] = positions_bias[2];
  }
  return vertex_position_array;
}

VertexArray* VertexBuffer:: getTexCoords (int index, float* scale_bias) const
{
  if (index < 0 || index >= MAX_TEXTURE_UNITS) {
    throw IllegalArgumentException (__FILE__, __func__, "Texture index is invalid.");
  }

  VertexArray* tex = texture_coordinate_arrays[index];

  if (tex && scale_bias) {
    scale_bias[0] = tex_coord_scale[index];
    for (int i = 0; i < tex->getComponentCount(); i++) {
      scale_bias[i+1] = tex_coord_bias[index][i];
    }
  }

  return tex;
}

/**
 * x:[-128,127] --> y:[0,1]
 * y = (x+128)/255
 */
void VertexBuffer:: setColors (VertexArray* colors)
{
  if (colors->getComponentType() != 1) {
    throw IllegalArgumentException (__FILE__, __func__, "Component size must be 1, size=%d.", colors->getComponentType());
  }
  if (colors->getComponentCount() != 3 && colors->getComponentCount() != 4) {
    throw IllegalArgumentException (__FILE__, __func__, "Component count must be 3 or 4, size=%d.", colors->getComponentCount());
  }

  float scale = 1/255.f;
  float bias[4] = {128/255.f,128/255.f,128/255.f};

  int    num    = colors->getComponentCount()*colors->getVertexCount();
  int    size   = sizeof(float)* num;
  float* values = new float [num];
  colors->get (0, colors->getVertexCount(), scale, bias, values);

  //cout << "size = "<< size << "\n";
  //for (int i = 0; i < size/4; i++) {
  //  cout << values[i] << ", ";
  //}
  //cout << "\n";
  
  glBindBuffer (GL_ARRAY_BUFFER, ibuf);
  glBufferData (GL_ARRAY_BUFFER, size, values, GL_STATIC_DRAW);

  delete [] values;

  color_array = colors;
}

void VertexBuffer:: setDefaultColor (int argb)
{
  default_color = argb;
}

/**
 * x:[-128,127] --> y:[-1,1], or x:[-32768,32767] --> y:[-1,1]
 * y = (2x+1)/255, or y = (2x+1)/65535
 */
void VertexBuffer:: setNormals (VertexArray* normals)
{
  if (normals == NULL) {
    normal_array = normals;
    return;
  }

  if (normals->getComponentType() != 1 && normals->getComponentType() != 2) {
    throw IllegalArgumentException (__FILE__, __func__, "Component size must be 1 or 2, size=%d.", normals->getComponentType());
  }
  if (normals->getComponentCount() != 3) {
    throw IllegalArgumentException (__FILE__, __func__, "Component count must be 3, size=%d.", normals->getComponentCount());
  }
  if (vertex_position_array && vertex_position_array->getVertexCount() != normals->getVertexCount()) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of Positions is different from number of Normals., count(pos)=%d, count(normals)", vertex_position_array->getVertexCount(), normals->getVertexCount());
  }
  for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
    if (texture_coordinate_arrays[i] && texture_coordinate_arrays[i]->getVertexCount() != normals->getVertexCount()) {
      throw IllegalArgumentException (__FILE__, __func__, "Number of Texture Coordinate is different from number of Normals, count(tex)=%d, count(normals)=%d.",  texture_coordinate_arrays[i]->getVertexCount(), normals->getVertexCount());
    }
  }
  if (color_array && color_array->getVertexCount() != normals->getVertexCount()) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of Colors is different from number of Normals, count(color)=%d, count(normals)=%d.", color_array->getVertexCount(), normals->getVertexCount());
  }

  float scale;
  float bias[4];
  scale   = (normals->getComponentType() == 1) ? 2/255.f : 2/65535;
  bias[0] = bias[1] = bias[2] = bias[3] = (normals->getComponentType() == 1) ? 1/255.f : 1/65535.f;

  int    num    = normals->getComponentCount()*normals->getVertexCount();
  int    size   = sizeof(float)* num;
  float* values = new float [num];
  normals->get (0, normals->getVertexCount(), scale, bias, values);

  glBindBuffer (GL_ARRAY_BUFFER, nbuf);
  glBufferData (GL_ARRAY_BUFFER, size, values, GL_STATIC_DRAW);

  delete [] values;

  normal_array = normals;
}

void VertexBuffer:: setPositions (VertexArray* positions, float scale, float* bias)
{
  if (positions == NULL) {
    vertex_position_array = NULL;
    return;
  }

  if (positions->getComponentType() != 1 && positions->getComponentType() != 2) {
    throw IllegalArgumentException (__FILE__, __func__, "Component size must be 1 or 2, size=%d.", positions->getComponentType());
  }
  if (positions->getComponentCount() != 3) {
    throw IllegalArgumentException (__FILE__, __func__, "Component count must be 3, count=%d.", positions->getComponentCount());
  }
  if (normal_array && normal_array->getVertexCount() != positions->getVertexCount()) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of Normals is different from one of Vertex Positions, count(normal)=%d, count(pos)=%d.", normal_array->getVertexCount(), positions->getVertexCount());
  }
  for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
    if (texture_coordinate_arrays[i] && texture_coordinate_arrays[i]->getVertexCount() != positions->getVertexCount()) {
      throw IllegalArgumentException (__FILE__, __func__, "Number of Texture Coordinate is different from one of Vertex Positions, count(tex)=%d, count(pos)=%d.", texture_coordinate_arrays[i]->getVertexCount(), positions->getVertexCount());
    }
  }
  if (color_array && color_array->getVertexCount() != positions->getVertexCount()) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of Colors is different from number of Vertex Positions.", color_array->getVertexCount(), positions->getVertexCount());
  }
  if (bias == NULL) {
    throw NullPointException (__FILE__, __func__, "Bias is NULL.");
  }

  int    num    = positions->getComponentCount()*positions->getVertexCount();
  int    size   = sizeof(float)* num;
  float* values = new float [num];
  positions->get (0, positions->getVertexCount(), scale, bias, values);

  glBindBuffer (GL_ARRAY_BUFFER, vbuf);
  glBufferData (GL_ARRAY_BUFFER, size, values, GL_STATIC_DRAW);

  delete [] values;

  vertex_position_array = positions;
  positions_scale   = scale;
  positions_bias[0] = bias[0];
  positions_bias[1] = bias[1];
  positions_bias[2] = bias[2];
}

void VertexBuffer:: setTexCoords (int index, VertexArray* tex_coords, float scale, float* bias)
{
  if (index < 0 || index >= MAX_TEXTURE_UNITS) {
    throw IllegalArgumentException (__FILE__, __func__, "Index is invalid, index=%d.", index);
  }
  if (bias == NULL) {
    throw NullPointException (__FILE__, __func__, "Bias is NULL.");
  }

  if (tex_coords == NULL) {
    texture_coordinate_arrays[index] = tex_coords;
    return;
  }

  if (tex_coords->getComponentType() != 1 && tex_coords->getComponentType() != 2) {
    throw IllegalArgumentException (__FILE__, __func__, "Component size must be 1 or 2, size=%d.", tex_coords->getComponentType());
  }
  if (tex_coords->getComponentCount() != 2 && tex_coords->getComponentCount() != 3) {
    throw IllegalArgumentException (__FILE__, __func__, "Component count must be 2 or 3, count=%d.", tex_coords->getComponentCount());
  }

  if (vertex_position_array && vertex_position_array->getVertexCount() != tex_coords->getVertexCount()) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of Vertex Positions is different from number of Texture Coordinates, count(color)=%d, count(texture)=%d.", vertex_position_array->getVertexCount(), tex_coords->getVertexCount());
  }
  if (normal_array && normal_array->getVertexCount() != tex_coords->getVertexCount()) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of Normals is different from number of Texture Coordinates, count(normal)=%d, count(texture)=%d.", normal_array->getVertexCount(), tex_coords->getVertexCount());
  }
  if (color_array && color_array->getVertexCount() != tex_coords->getVertexCount()) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of Colors is different from number of Texture Coordinagtes, count(color)=%d, count(texture)=%d.", color_array->getVertexCount(), tex_coords->getVertexCount());
  }
  if (bias == NULL) {
    throw NullPointException (__FILE__, __func__, "Bias is NULL.");
  }

  int    num    = tex_coords->getComponentCount()*tex_coords->getVertexCount();
  int    size   = sizeof(float)* num;
  float* values = new float [num];
  tex_coords->get (0, tex_coords->getVertexCount(), scale, bias, values);

  glBindBuffer (GL_ARRAY_BUFFER, tcbuf[index]);
  glBufferData (GL_ARRAY_BUFFER, size, values, GL_STATIC_DRAW);

  delete [] values;

  texture_coordinate_arrays[index] = tex_coords;
}

/**
 * Note: VertexBuffer should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void VertexBuffer:: render (int pass, int index) const
{
  if (pass != 2) {
    return;
  }

  //cout << "VertexBuffer: vbuf = " << vbuf << "\n";

  if (vertex_position_array) {
    //cout << "render vertex array\n";
    int cc = vertex_position_array->getComponentCount();
    glBindBuffer (GL_ARRAY_BUFFER, vbuf);
    glVertexPointer (cc, GL_FLOAT, 0, 0);  // 0,0=stride,offset
  }

  // TODO: vertex_color_tracking=enableの時のみ頂点カラーを使うべき。
  // あとこれだとDIFFUSE COLORが設定されていない。
  if (color_array) {
    //cout << "VertexBuffer: render color array\n";
    int cc = color_array->getComponentCount();
    glBindBuffer (GL_ARRAY_BUFFER, ibuf);
    glColorPointer (cc, GL_FLOAT, 0, 0);  // 0,0=stride,offset
  } else {
    //cout << "VertexBuffer: render default color\n";
    float r = ((default_color & 0x00ff0000) >> 16) / 255.f;
    float g = ((default_color & 0x0000ff00) >>  8) / 255.f;
    float b = ((default_color & 0x000000ff) >>  0) / 255.f;
    float a = ((default_color & 0xff000000) >> 24) / 255.f;
    glColor4f (r,g,b,a);
  }

  if (normal_array) {
    //cout << "render normal array\n";
    glBindBuffer (GL_ARRAY_BUFFER, nbuf);
    glNormalPointer (GL_FLOAT, 0, 0);  // 0,0=stride,offset
  }

  for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
    if (texture_coordinate_arrays[i]) {
      //cout << "render " << i << "th texture coordinate array\n";
      int cc = texture_coordinate_arrays[i]->getComponentCount();
      glClientActiveTexture (GL_TEXTURE0 + i);
      glBindBuffer (GL_ARRAY_BUFFER, tcbuf[i]);
      glTexCoordPointer (cc, GL_FLOAT, 0, 0);  // 0,0=stride,offset
    }
  }
  
}

void VertexBuffer:: findByObjectType (int type, std::vector<Object3D*>& objs) const
{
  if (vertex_position_array) {
    vertex_position_array->findByObjectType (type, objs);
  }
  for (int i = 0;i < MAX_TEXTURE_UNITS; i++) {
    if (texture_coordinate_arrays[i]) {
      texture_coordinate_arrays[i]->findByObjectType (type, objs);
    }
  }
  if (normal_array) {
    normal_array->findByObjectType (type, objs);
  }
  if (color_array) {
    color_array->findByObjectType (type, objs);
  }

}



std::ostream& VertexBuffer:: print (std::ostream& out) const
{
  out << "VertexBuffer: \n";
  if (vertex_position_array)
    out << "  positions = " << *vertex_position_array;
  else
    out << "  positions = 0\n";
  if (normal_array)
    out << ", normals = " << *normal_array;
  else
    out << ", normals = 0\n";
  
  if (color_array)
    out << ", colors  = " << *color_array;
  else
    out << ", colors  = 0\n";
  out << ", default color = 0x" << hex << default_color << dec;
  return out << "\n";;
}

std::ostream& operator<< (std::ostream& out, const VertexBuffer& vbuf)
{
  return vbuf.print(out);
}



