#include <iostream>
#include <fstream>
#include <strstream>
#include <zlib.h>
#include "Exception.hpp"
#include "m3g.hpp"
#include "Loader.hpp"
using namespace std;
using namespace m3g;
#include <stdlib.h>

std::istrstream* Loader::iss = 0;
std::vector<Object3D*> Loader::objs;
Loader::FileInfo Loader::file_info;

const char m3g_ident[12] = {0xAB,0x4A,0x53,0x52,0x31,0x38,0x34,0xBB,0x0D,0x0A,0x1A,0x0A};

Loader:: Loader () 
{
}

Loader:: ~Loader ()
{
}


std::vector<Object3D*> Loader:: load (int length, const char* data, int offset)
{
  if (data == NULL) {
    throw NullPointException (__FILE__, __func__, "Data is NULL.");
  }
  if (length <= 0) {
    throw IllegalArgumentException (__FILE__, __func__, "length is invalid, len=%d.", length);
  }
  if (offset < 0 || offset >= length) {
    throw IndexOutOfBoundsException (__FILE__, __func__, "Offset is invalid, %d in [0, ).", offset, length);
  }

  iss = new istrstream ((char*)data+offset, length-offset);
  if (iss == 0) {
    throw IOException (__FILE__, __func__, "Can't load from memory 0x%p.", data);
  }
  if (!getM3GIdent()) {
    throw IOException (__FILE__, __func__, "This is not M3G format.");
  }

  while (1) {
    // section
    //cout << "----------start section--------------\n";
    int start_of_section = (int)iss->tellg();

    char         compression_scheme   = getByte();
    unsigned int total_section_length = getUInt32 ();
    unsigned int uncompressed_length  = getUInt32 ();
    //cout << "compression_scheme = "   << (int)compression_scheme << "\n";
    //cout << "total_section_length = " << total_section_length << "\n";
    //cout << "uncompressed_length = "  << uncompressed_length << "\n";

    if (iss->eof())
      break;
    if (compression_scheme != 0 && compression_scheme != 1) {
    }

    char* uncompressed_objects = new char[uncompressed_length];
    switch (compression_scheme) {
    case 0: read_raw (uncompressed_objects,
                      total_section_length-13); break;
    case 1: read_zlib (uncompressed_objects, 
                       uncompressed_length,
                       total_section_length-13); break;
    default: 
      throw IOException (__FILE__, __func__, "Compression scheme is invalid, scheme=%d.", compression_scheme);
    }
    istrstream* tmp = iss;
    iss = new istrstream (uncompressed_objects, uncompressed_length);

    // 注意：オブジェクトインデックスは１から始まる
    // int i = 0;

    while (1) {

      //cout << "object -------- " << i++ << " --------\n";
      int          start_of_object = (int)iss->tellg();
      char         object_type     = getByte ();
      unsigned int length          = getUInt32 ();

      if (iss->eof())
	break;

      //cout << "object type = " << objtype_to_string(object_type) << "(" << (int)obje

      switch (object_type) {
      case OBJTYPE_HEADER_OBJECT       : parseHeader()             ; break;
      case OBJTYPE_ANIMATION_CONTROLLER: parseAnimationController(); break;
      case OBJTYPE_ANIMATION_TRACK     : parseAnimationTrack ()    ; break;
      case OBJTYPE_APPEARANCE          : parseAppearance ()        ; break;
      case OBJTYPE_BACKGROUND          : parseBackground ()        ; break;
      case OBJTYPE_CAMERA              : parseCamera ()            ; break;
      case OBJTYPE_COMPOSITING_MODE    : parseCompositingMode ()   ; break;
      case OBJTYPE_FOG                 : parseFog ()               ; break;
      case OBJTYPE_GROUP               : parseGroup ()             ; break;
      case OBJTYPE_IMAGE2D             : parseImage2D ()           ; break;
      case OBJTYPE_KEYFRAME_SEQUENCE   : parseKeyframeSequence ()  ; break;
      case OBJTYPE_LIGHT               : parseLight ()             ; break;
      case OBJTYPE_MATERIAL            : parseMaterial ()          ; break;
      case OBJTYPE_MESH                : parseMesh ()              ; break;
      case OBJTYPE_POLYGON_MODE        : parsePolygonMode ()       ; break;
      case OBJTYPE_SKINNED_MESH        : parseSkinnedMesh ()       ; break;
      case OBJTYPE_SPRITE3D            : parseSprite3D ()          ; break;
      case OBJTYPE_TEXTURE2D           : parseTexture2D ()         ; break;
      case OBJTYPE_TRIANGLE_STRIP_ARRAY: parseTriangleStripArray (); break;
      case OBJTYPE_VERTEX_ARRAY        : parseVertexArray ()       ; break;
      case OBJTYPE_VERTEX_BUFFER       : parseVertexBuffer ()      ; break;
      case OBJTYPE_WORLD               : parseWorld ()             ; break;
      default: 
	throw IOException (__FILE__, __func__, "Object type is invalid, type=%d.", object_type);
	//cout << "Unknown obj type = " << object_type << " is ignored.\n";
	//iss->seekg (length, ios_base::cur);
      }

      int end_of_object = (int)iss->tellg();
      if (end_of_object - start_of_object != (int)length+5) {
	throw IOException (__FILE__, __func__, "Object length is invalid. %d != %d.", end_of_object - start_of_object, length+5);
      }
    }

    delete iss;
    iss = tmp;

    unsigned int file_checksum    = getUInt32();
    unsigned int memory_checksum  = adler32 ((const unsigned char*)data+start_of_section, total_section_length-4);
    if (memory_checksum != file_checksum) {
      throw IOException (__FILE__, __func__, "Checksum is invalid. file=0x%x, mem=0x%x.", file_checksum, memory_checksum);
    }

  }

  return objs;
}


std::vector<Object3D*> Loader:: load (const char* name)
{
  ifstream ifs (name);
  if (!ifs) {
    throw IOException (__FILE__, __func__, "Can't open file, name=%s.", name);
  }
  int size = ifs.seekg(0, ios::end).tellg();
  ifs.seekg(0, ios::beg); 
  char* buf = new char[size];
  ifs.read (buf, size);

  load (size, buf, 0);

  delete [] buf;
  return objs;
}

bool Loader:: getBoolean ()
{
  bool buf;
  iss->read ((char*)&buf, 1);
  return buf;
}

char Loader:: getByte ()
{
  char buf;
  iss->read ((char*)&buf, 1);
  return buf;
}

short Loader:: getInt16 ()
{
  short buf;
  iss->read ((char*)&buf, 2);
  return buf;
}

unsigned short Loader:: getUInt16 ()
{
  unsigned short buf;
  iss->read ((char*)&buf, 2);
  return buf;
}

int Loader:: getInt32 ()
{
  int buf;
  iss->read ((char*)&buf, 4);
  return buf;
}

unsigned int Loader:: getUInt32 ()
{
  unsigned int buf;
  iss->read ((char*)&buf, 4);
  return buf;
}

float        Loader:: getFloat32 ()
{
  float buf;
  iss->read ((char*)&buf, 4);
  return buf;
}

const char* Loader:: getString ()
{
  char* buf = new char[256];
  iss->getline (buf, 256, '\0');
  return buf;
}

unsigned int Loader:: getObjectIndex ()
{
  unsigned int buf;
  iss->read ((char*)&buf, 4);
  return buf;
}

int          Loader:: getColorRGBA ()
{
  unsigned char r,g,b,a;
  iss->read ((char*)&r, 1);
  iss->read ((char*)&g, 1);
  iss->read ((char*)&b, 1);
  iss->read ((char*)&a, 1);
  return (a << 24) | (r << 16) | (g << 8) | (b << 0);
}

int          Loader:: getColorRGB ()
{
  unsigned char r,g,b;
  iss->read ((char*)&r, 1);
  iss->read ((char*)&g, 1);
  iss->read ((char*)&b, 1);
  return (r << 16) | (g << 8) | (b << 0);
}

bool         Loader:: getM3GIdent ()
{
  char ident[12];
  iss->read ((char*)ident, 12);
  //cout << "ident = ";
  //for (int i = 0; i < 12; i++) {
  //  cout << ident[i];
  //}
  //cout << "\n";
  return true;
}

char* Loader:: getByteArray (int n)
{
  char* p = new char[n];
  iss->read ((char*)p, n);
  return p;
}


short* Loader:: getInt16Array (int n)
{
  short* p = new short[n];
  iss->read ((char*)p, n*2);
  return p;
}

unsigned short* Loader:: getUInt16Array (int n)
{
  unsigned short* p = new unsigned short[n];
  iss->read ((char*)p, n*2);
  return p;
}


unsigned int* Loader:: getUInt32Array (int n)
{
  unsigned int* p = new unsigned int[n];
  iss->read ((char*)p, n*4);
  return p;
}

float* Loader:: getFloat32Array (int n)
{
  float* p = new float[n];
  iss->read ((char*)p, n*4);
  return p;
}

unsigned int Loader:: adler32 (const unsigned char* data, int len)
{
  unsigned int a = 1, b = 0;
  while (len > 0) {
    int tlen = len > 5550 ? 5550 : len;
    len -= tlen;
    do {
      a += *data++;
      b += a;
    } while (--tlen);
    a %= 65521;
    b %= 65521;
  }
  return (b << 16) | a;
}

void Loader:: read_raw (char* buf, int length)
{
  iss->read (buf, length);
}

void Loader:: read_zlib (char* uncomporessed_buf, int uncomporessed_buf_length, int compressed_length)
{
  char* compressed_buf = new char[compressed_length];
  iss->read (compressed_buf, compressed_length);

  int ret;
  int uncomporessed_length = uncomporessed_buf_length;
  ret = uncompress ((Bytef*)uncomporessed_buf, (uLongf*)&uncomporessed_length,
                    (const Bytef*)compressed_buf, (uLong)compressed_length);
  if (ret != Z_OK) {
    throw IOException (__FILE__, __func__, "Decode error(zlib), err=%d.", ret);
  }
  if (uncomporessed_length != uncomporessed_buf_length) {
    throw IOException (__FILE__, __func__, "Decode error(zlib), %d != %d.", uncomporessed_length, uncomporessed_buf_length);
  }

  delete [] compressed_buf;
}


void Loader:: parseHeader ()
{
  char         version_major            = getByte();
  char         version_minor            = getByte();
  bool         has_external_refference  = getBoolean();
  unsigned int total_file_size          = getUInt32 ();
  unsigned int approximate_content_size = getUInt32 ();
  const char*  authoring_field          = getString ();

  file_info.version_major            = version_major;
  file_info.version_minor            = version_minor;
  file_info.has_external_refference  = has_external_refference;
  file_info.total_file_size          = total_file_size;
  file_info.approximate_content_size = approximate_content_size;
  file_info.authoring_field          = authoring_field;

  //cout << "M3G Header ---\n";
  //cout << "  version_major = "            << (int)version_major       << "\n";
  //cout << "  version_minor = "            << (int)version_minor       << "\n";
  //cout << "  has_external_refference  = " << has_external_refference  << "\n";
  //cout << "  total_file_size          = " << total_file_size          << "\n";
  //cout << "  approximate_content_size = " << approximate_content_size << "\n";
  ////cout << "  authoring_field          = " << authoring_field          << "\n";

  if (has_external_refference) {
    throw NotImplementedException (__FILE__, __func__, "Has_external_reference is not implemented.");
  }

  // delete authoring_field;

  // 注意1：index 0はダミー
  // 注意2：Header objectもオブジェクトに含む
  objs.clear ();
  objs.reserve (16);
  objs.push_back ((Object3D*)0);  // for dummy
  objs.push_back ((Object3D*)0);  // for header
}

void Loader:: parseExref ()
{
  const char* uri = getString();
  file_info.external_refference_uri = uri;
  //cout << "uri = " << uri << "\n";
}

void Loader:: parseAnimationController ()
{
  AnimationController* ctr = new AnimationController;
  parseObject3D (ctr);

  float speed                   = getFloat32 ();
  float weight                  = getFloat32 (); 
  int   active_interval_start   = getInt32 ();
  int   active_interval_end     = getInt32 ();
  float reference_sequence_time = getFloat32 ();
  int   reference_world_time    = getInt32 ();

  ctr->setSpeed (speed, reference_world_time);
  ctr->setWeight (weight);
  ctr->setActiveInterval (active_interval_start, active_interval_end);
  ctr->setPosition (reference_sequence_time, reference_world_time);

  //ctr->AnimationController:: print (cout);

  objs.push_back (ctr);
}

void Loader:: parseAnimationTrack ()
{
  Object3D* obj = new Object3D;
  parseObject3D (obj);

  unsigned int keyframe_sequence_index    = getUInt32();
  unsigned int animation_controller_index = getUInt32();
  unsigned int property_id = getInt32();
 
   
  KeyframeSequence* kseq = dynamic_cast<KeyframeSequence*>(objs.at(keyframe_sequence_index));
  AnimationTrack*   track = new AnimationTrack (kseq, property_id);

  if (animation_controller_index > 0) {
    AnimationController* ctr = dynamic_cast<AnimationController*>(objs.at(animation_controller_index));
    track->setController (ctr);
  }

  //track->AnimationTrack:: print (cout);

  objs.push_back (track);
}

void Loader:: parseAppearance ()
{
  Appearance* app = new Appearance;
  parseObject3D (app);

  char         layer                  = getByte ();
  unsigned int compositing_mode_index = getUInt32 ();
  unsigned int fog_index              = getUInt32 ();
  unsigned int polygon_mode_index     = getUInt32 ();
  unsigned int material_index         = getUInt32 ();

  app->setLayer (layer);

  if (compositing_mode_index > 0) {
    CompositingMode* cmode = dynamic_cast<CompositingMode*>(objs.at(compositing_mode_index));
    app->setCompositingMode (cmode);
  }
  if (fog_index > 0) {
    Fog* fog = dynamic_cast<Fog*>(objs.at(fog_index));
    app->setFog (fog);
  }
  if (polygon_mode_index > 0) {
    PolygonMode* pmode = dynamic_cast<PolygonMode*>(objs.at(polygon_mode_index));
    app->setPolygonMode (pmode);
  }
  if (material_index > 0) {
    Material* mat = dynamic_cast<Material*>(objs.at(material_index));
    app->setMaterial (mat);
  }

  unsigned int textures_count = getUInt32 ();
  for (int i = 0; i < (int)textures_count; i++) {
    unsigned int texture_index = getUInt32 ();
    Texture2D* tex = dynamic_cast<Texture2D*>(objs.at(texture_index));
    app->setTexture (i, tex);
  }

  //app->Appearance:: print (cout);

  objs.push_back (app);
}

void Loader:: parseBackground ()
{
  Background* bg = new Background;
  parseObject3D (bg);

  int          background_color        = getColorRGBA ();
  unsigned int background_image_index  = getUInt32 ();
  char         background_image_mode_x = getByte ();
  char         background_image_mode_y = getByte ();
  int          crop_x                  = getInt32 ();
  int          crop_y                  = getInt32 ();
  int          crop_width              = getInt32 ();
  int          crop_height             = getInt32 ();
  bool         depth_clear_enabled     = getBoolean ();
  bool         color_clear_enabled     = getBoolean ();

  bg->setColor (background_color);
  if (background_image_index > 0) {
    Image2D* img = dynamic_cast<Image2D*>(objs.at(background_image_index));
    bg->setImage (img);
  }
  bg->setImageMode (background_image_mode_x, background_image_mode_y);
  bg->setCrop (crop_x, crop_y, crop_width, crop_height);
  bg->setDepthClearEnable (depth_clear_enabled);
  bg->setColorClearEnable (color_clear_enabled);
   
  //bg->Background:: print (cout);

  objs.push_back (bg);
}

void Loader:: parseCamera ()
{
  Camera* cam = new Camera;
  parseNode (cam);
   
  char projection_type = getByte();
  if (projection_type == Camera::GENERIC) {
    float matrix[16];
    for (int i = 0; i < 16; i++)
      matrix[i] = getFloat32 ();
    Transform trns;
    trns.set (matrix);
    cam->setGeneric (trns);
  } else {
    float fovy         = getFloat32 ();
    float aspect_ratio = getFloat32 ();
    float near         = getFloat32 ();
    float far          = getFloat32 ();
    cam->setPerspective (fovy, aspect_ratio, near, far);
  }

  //cam->print (cout);

  objs.push_back (cam);
}

void Loader:: parseCompositingMode ()
{
  CompositingMode* cmode = new CompositingMode;
  parseObject3D (cmode);

  bool  depth_test_enabled  = getBoolean ();
  bool  depth_write_enabled = getBoolean ();
  bool  color_write_enabled = getBoolean ();
  bool  alpha_write_enabled = getBoolean ();
  char  blending            = getByte ();
  char  alpha_threshold     = getByte ();
  float depth_offset_factor = getFloat32 ();
  float depth_offset_units  = getFloat32 ();

  cmode->setDepthTestEnable (depth_test_enabled);
  cmode->setDepthWriteEnable (depth_write_enabled);
  cmode->setColorWriteEnable (color_write_enabled);
  cmode->setAlphaWriteEnable (alpha_write_enabled);
  cmode->setBlending (blending);
  cmode->setAlphaThreshold (alpha_threshold);
  cmode->setDepthOffset (depth_offset_factor, depth_offset_units);

  objs.push_back (cmode);
}

void Loader:: parseFog ()
{
  Fog* fog = new Fog;
  parseObject3D (fog);

  int  color = getColorRGB ();
  char mode  = getByte ();

  fog->setColor (color);

  if (mode == Fog::EXPONENTIAL) {
    float density = getFloat32 ();
    fog->setDensity (density);
  } else {
    float near = getFloat32 ();
    float far  = getFloat32 ();
    fog->setLinear (near, far);
  }

  objs.push_back (fog);
}

void Loader:: parseGroup ()
{
  Group* grp = new Group;
  parseGroup (grp);

  objs.push_back (grp);
}

void Loader:: parseGroup (Group* grp)
{
  parseNode (grp);

  unsigned int children_count = getUInt32 ();
  for (int i = 0; i < (int)children_count; i++) {
    unsigned int children_index = getUInt32 ();
    if (children_index > 0) {
      Node* node = dynamic_cast<Node*>(objs.at(children_index));
      grp->addChild (node);
    }

  }

  //grp->Group:: print (cout);
}

void Loader:: parseImage2D ()
{
  Object3D* obj = new Object3D;
  parseObject3D (obj);

  Image2D* img = 0;

  char format         = getByte ();
  bool is_mutable     = getBoolean ();
  unsigned int width  = getUInt32 ();
  unsigned int height = getUInt32 ();
  if (!is_mutable) {
    unsigned int palette_count = getUInt32 ();
    if (palette_count > 0) {
      throw NotImplementedException (__FILE__, __func__, "Paletted Image is not supported.");
    }
    unsigned int pixel_count = getUInt32 ();
    char*        pixels      = getByteArray(pixel_count);
    img = new Image2D (format, width, height, pixels);
    delete [] pixels;
  }

  // img->print (cout);

  objs.push_back (img);
}

void Loader:: parseIndexBuffer (IndexBuffer* ibuf)
{
  parseObject3D (ibuf);
  // nothing to do.
}

void Loader:: parseKeyframeSequence ()
{
  Object3D* obj = new Object3D;
  parseObject3D (obj);

  KeyframeSequence* kseq = 0;

  unsigned char interpolation     = getByte ();
  unsigned char repeat_mode       = getByte ();
  unsigned char encoding          = getByte ();
  unsigned int  duration          = getUInt32 ();
  unsigned int  valid_range_first = getUInt32 ();
  unsigned int  valid_range_last  = getUInt32 ();
  unsigned int  component_count   = getUInt32 ();
  unsigned int  keyframe_count    = getUInt32 ();

  kseq = new KeyframeSequence (keyframe_count, component_count, interpolation);

  switch (encoding) {
  case 0: {
    for (int i = 0; i < (int)keyframe_count; i++) {
      unsigned int time  = getUInt32 ();
      float*       value = getFloat32Array (component_count);
      kseq->setKeyframe (i, time, value);
      delete [] value;
    }
    break;
  }
  case 1: {
    float* bias  = getFloat32Array (component_count);
    float* scale = getFloat32Array (component_count);
    for (int i = 0; i < (int)keyframe_count; i++) {
      unsigned int   time           = getUInt32 ();
      unsigned char* encoded_values = (unsigned char*)getByteArray (component_count);
      float* values = new float[component_count];
      for (int j = 0; j < (int)component_count; j++) {
	values[j] = encoded_values[j]*scale[j]/255.f + bias[j];
      }
      kseq->setKeyframe (i, time, values);
      delete [] encoded_values;
      delete [] values;
    }
    delete [] bias;
    delete [] scale;
    break;
  }
  case 2: {
    float* bias  = getFloat32Array (component_count);
    float* scale = getFloat32Array (component_count);
    for (int i = 0; i < (int)keyframe_count; i++) {
      unsigned int    time           = getUInt32 ();
      unsigned short* encoded_values = (unsigned short*)getInt16Array (component_count);
      float* values = new float[component_count];
      for (int j = 0; j < (int)component_count; j++) {
	values[j] = encoded_values[j]*scale[j]/65535.f + bias[j];
      }
      kseq->setKeyframe (i, time, values);
      delete encoded_values;
      delete values;
    }
    delete [] bias;
    delete [] scale;
    break;
  }
  default: {
    throw IOException (__FILE__, __func__, "Encoding is invalid, enc=%d.", encoding);
  }
  }

  kseq->setRepeatMode (repeat_mode);
  kseq->setDuration (duration);
  kseq->setValidRange (valid_range_first, valid_range_last);
  
  //kseq->KeyframeSequence:: print (cout);

  objs.push_back (kseq);
}

void Loader:: parseLight ()
{
  Light* lig = new Light;
  parseNode (lig);

  float attenuation_constant  = getFloat32 ();
  float attenuation_linear    = getFloat32 ();
  float attenuation_quadratic = getFloat32 ();
  int   color                 = getColorRGB ();
  unsigned char mode          = getByte ();
  float intensity             = getFloat32 ();
  float spot_angle            = getFloat32 ();
  float spot_exponent         = getFloat32 ();

  lig->setAttenuation (attenuation_constant, attenuation_linear, attenuation_quadratic);
  lig->setColor (color);
  lig->setMode (mode);
  lig->setIntensity (intensity);
  lig->setSpotAngle (spot_angle);
  lig->setSpotExponent (spot_exponent);

  //lig->Light:: print (cout);

  objs.push_back (lig);
}

void Loader:: parseMaterial ()
{
  Material* mat = new Material;
  parseObject3D (mat);

  int   ambient_color  = getColorRGB();
  int   diffuse_color  = getColorRGBA();
  int   emissive_color = getColorRGB();
  int   specular_color = getColorRGB();
  float shininess      = getFloat32();
  bool  vertex_color_tracking_enabled = getBoolean();

  mat->setColor (Material::AMBIENT, ambient_color);
  mat->setColor (Material::DIFFUSE, diffuse_color);
  mat->setColor (Material::EMISSIVE, emissive_color);
  mat->setColor (Material::SPECULAR, specular_color);
  mat->setShininess (shininess);
  mat->setVertexColorTrackingEnable (vertex_color_tracking_enabled);

  //mat->Material:: print (cout);

  objs.push_back (mat);
}

void Loader:: parseMesh ()
{
  Node* node = new Node;
  parseNode (node);

  unsigned int vertex_buffer_index = getUInt32 ();
  unsigned int submesh_count       = getUInt32 ();

  IndexBuffer** indices = new IndexBuffer* [submesh_count];
  Appearance**  appears = new Appearance* [submesh_count];
   
  VertexBuffer*  vbuf = dynamic_cast<VertexBuffer*>(objs.at(vertex_buffer_index));

  for (int i = 0; i < (int)submesh_count; i++) {
    unsigned int index_buffer_index = getUInt32();
    unsigned int appearance_index   = getUInt32();
     
    indices[i] = dynamic_cast<IndexBuffer*>(objs.at(index_buffer_index));
    appears[i] = dynamic_cast<Appearance*>(objs.at(appearance_index));
  }

  Mesh* mesh = new Mesh (vbuf, submesh_count, indices, submesh_count, appears);

  //mesh->Mesh:: print (cout);

  delete [] indices;
  delete [] appears;

  objs.push_back (mesh);
}


 
void Loader:: parseNode (Node* node)
{
  parseTransformable (node);

  bool         enable_rendering = getBoolean();
  bool         enable_picking   = getBoolean();
  char         alpha_factor     = getByte ();
  unsigned int scope            = getUInt32();
  bool         has_alignment    = getBoolean();
  if (has_alignment) {
    char z_target                  = getByte();
    char y_target                  = getByte();
    unsigned int z_reference_index = getUInt32();
    unsigned int y_reference_index = getUInt32();

    Node* z_ref = dynamic_cast<Node*>(objs.at(z_reference_index));
    Node* y_ref = dynamic_cast<Node*>(objs.at(y_reference_index));
    node->setAlignment (z_ref, z_target, y_ref, y_target);
  }
  node->setAlphaFactor ((alpha_factor+128)/255.f);
  node->setPickingEnable (enable_picking);
  node->setRenderingEnable (enable_rendering);
  node->setScope (scope);

  //node->Node::print (cout);
}

void Loader:: parseObject3D (Object3D* obj)
{
  unsigned int user_id                = getUInt32(); 

  obj->setUserID (user_id);

  unsigned int animation_tracks_count = getUInt32();
  for (int i = 0; i < (int)animation_tracks_count; i++) {
    unsigned int animation_track_index = getUInt32();
    if (animation_track_index > 0) {
      AnimationTrack* track = dynamic_cast<AnimationTrack*>(objs.at(animation_track_index));
      obj->addAnimationTrack (track);
    }
  }
  unsigned int user_parameter_count = getUInt32();
  for (int i = 0; i < (int)user_parameter_count; i++) {
    unsigned int parameter_id          = getUInt32();
    unsigned int parameter_value_count = getUInt32();
    char*        parameter_value       = getByteArray (parameter_value_count);
    obj->setUserObject (parameter_id, parameter_value);
  }
   
  //obj->Object3D::print (cout);
}

void Loader:: parsePolygonMode ()
{
  PolygonMode* pmode = new PolygonMode;
  parseObject3D (pmode);

  unsigned char  culling  = getByte();
  unsigned char  shading  = getByte();
  unsigned char  winding  = getByte();
  bool two_sided_lighting_enabled     = getBoolean();
  bool local_camera_lighting_enabled  = getBoolean();
  bool perspective_correction_enabled = getBoolean();

  pmode->setCulling (culling);
  pmode->setShading (shading);
  pmode->setWinding (winding);
  pmode->setTwoSidedLightingEnable (two_sided_lighting_enabled);
  pmode->setLocalCameraLightingEnable (local_camera_lighting_enabled);
  pmode->setPerspectiveCorrectionEnable (perspective_correction_enabled);

  //pmode->PolygonMode:: print (cout);

  objs.push_back (pmode);
}

void Loader:: parseSkinnedMesh ()
{
  // 注意：Mesh部分はparseMesh()と完全に同じ。
  // ---- ここからparseMesh()と同じ ----

  Node* node = new Node;
  parseNode (node);

  unsigned int vertex_buffer_index = getUInt32 ();
  unsigned int submesh_count       = getUInt32 ();

  IndexBuffer** indices = new IndexBuffer* [submesh_count];
  Appearance**  appears = new Appearance*  [submesh_count];
   
  VertexBuffer*  vbuf = dynamic_cast<VertexBuffer*>(objs.at(vertex_buffer_index));

  for (int i = 0; i < (int)submesh_count; i++) {
    unsigned int index_buffer_index = getUInt32();
    unsigned int appearance_index   = getUInt32();
     
    indices[i] = dynamic_cast<IndexBuffer*>(objs.at(index_buffer_index));
    appears[i] = dynamic_cast<Appearance*>(objs.at(appearance_index));
  }

  // ---- ここまでparseMesh()と同じ ----

  unsigned int skeleton_index = getUInt32();
  Group*       skeleton       = dynamic_cast<Group*>(objs.at(skeleton_index));

  SkinnedMesh* mesh = new SkinnedMesh (vbuf, submesh_count, indices, submesh_count, appears, skeleton);
  *(Node*)mesh = *node;

  //mesh->Mesh:: print (cout);

  delete [] indices;
  delete [] appears;


  unsigned int transform_reference_count = getUInt32();
  for (int i = 0; i < (int)transform_reference_count; i++) {
    unsigned int transfrom_node_index = getUInt32();
    unsigned int first_vertex         = getUInt32();
    unsigned int vertex_count         = getUInt32();
    int          weight               = getInt32();
    Node* node = dynamic_cast<Node*>(objs.at(transfrom_node_index));
    mesh->addTransform (node, weight, first_vertex, vertex_count);
  }

  //mesh->SkinnedMesh:: print (cout);

  objs.push_back (mesh);
}

void Loader:: parseSprite3D ()
{
  Node* node = new Node;
  parseNode (node);

  unsigned int image_index      = getUInt32();
  unsigned int appearance_index = getUInt32();
  bool         is_scaled        = getBoolean();
  int          crop_x           = getInt32();
  int          crop_y           = getInt32();
  int          crop_width       = getInt32();
  int          crop_height      = getInt32();

  Image2D*    img = dynamic_cast<Image2D*>(objs.at(image_index));
  Appearance* app = dynamic_cast<Appearance*>(objs.at(appearance_index));
  Sprite3D*   spr = new Sprite3D (is_scaled, img, app);

  *(Node*)spr = *node;
  spr->setCrop (crop_x, crop_y, crop_width, crop_height);

  //spr->Sprite3D:: print (cout);

  objs.push_back (spr);
}

void Loader:: parseTexture2D ()
{
  Transformable* trns = new Transformable;
  parseTransformable (trns);

  unsigned int image_index   = getUInt32();
  int  blend_color           = getColorRGB();
  unsigned char blending     = getByte ();
  unsigned char wrapping_s   = getByte ();
  unsigned char wrapping_t   = getByte ();
  unsigned char level_filter = getByte ();
  unsigned char image_filter = getByte ();

  Image2D*   img = dynamic_cast<Image2D*>(objs.at(image_index));
  Texture2D* tex = new Texture2D (img);

  *(Transformable*)tex = *trns;
  tex->setBlendColor (blend_color);
  tex->setBlending (blending);
  tex->setWrapping (wrapping_s, wrapping_t);
  tex->setFiltering (level_filter, image_filter);
   
  //tex->Texture2D:: print (cout);
   
  objs.push_back (tex);
}

void Loader:: parseTransformable (Transformable* trans)
{
  parseObject3D (trans);

  bool has_component_transform = getBoolean();
  if (has_component_transform) {
    float tx    = getFloat32();
    float ty    = getFloat32();
    float tz    = getFloat32();
    float sx    = getFloat32();
    float sy    = getFloat32();
    float sz    = getFloat32();
    float angle = getFloat32();
    float ax    = getFloat32();
    float ay    = getFloat32();
    float az    = getFloat32();
    trans->setTranslation (tx, ty, tz);
    trans->setScale       (sx, sy, sz);
    trans->setOrientation (angle, ax, ay, az);
  }
  bool has_general_transform = getBoolean();
  if (has_general_transform) {
    float matrix[16];
    for (int i = 0; i < 16; i++)
      matrix[i] = getFloat32();
    Transform tra;
    tra.set (matrix);
    trans->setTransform (tra);
  }

  //trans->Transformable::print (cout);
}
 

void Loader:: parseTriangleStripArray ()
{
  IndexBuffer* ibuf = new IndexBuffer;
  parseIndexBuffer (ibuf);

  unsigned int        start_index;
  unsigned int        indices_count;
  int*                indices;
  TriangleStripArray* tris;

  unsigned char encoding = getByte();
  switch (encoding) {
  case 0:
    start_index = getUInt32();
    break;
  case 1:
    start_index = getByte();
    break;
  case 2:
    start_index = getUInt16();
    break;
  case 128:
    indices_count = getUInt32();
    indices       = new int [indices_count];
    for (int i = 0; i < (int)indices_count; i++) 
      indices[i] = getUInt32();
    break;
  case 129:
    indices_count = getUInt32();
    indices       = new int [indices_count];
    for (int i = 0; i < (int)indices_count; i++)
      indices[i] = getByte();
    break;
  case 130:
    indices_count = getUInt32();
    indices       = new int [indices_count];
    for (int i = 0; i < (int)indices_count; i++)
      indices[i] = getUInt16();
    break;
  default:
    throw IOException (__FILE__, __func__, "Encoding is invalid, enc=%d.", encoding);
  }

  unsigned int strips_len = getUInt32();
  int*         strips     = (int*)getUInt32Array(strips_len);
  //cout << "encoding = " << (int)encoding << "\n";
  //cout << "1<<7 = " << 1<<7 << "\n";

  if (encoding & (1<<7)) {
    tris = new TriangleStripArray (indices, strips_len, strips);
    //cout << "A\n";
  }
  else {
    tris = new TriangleStripArray (start_index, strips_len, strips);
    //cout << "B\n";
  }
   
  *(IndexBuffer*)tris = *ibuf;

  //tris->TriangleStripArray:: print(cout);

  objs.push_back (tris);
}

void Loader:: parseVertexArray ()
{
  Object3D* obj = new Object3D;
  parseObject3D (obj);

  char component_size         = getByte();
  char component_count        = getByte();
  char encoding               = getByte();
  unsigned short vertex_count = getUInt16();

  VertexArray* varr = new VertexArray (vertex_count, component_count, component_size);
  *(Object3D*)varr = *obj;
   
  if (component_size == 1) {
    char* vertex_values = getByteArray(vertex_count*component_count);
    if (encoding) {
      for (int i = component_count; i < vertex_count*component_count; i++)
	vertex_values[i] += vertex_values[i-component_count];
    }
    varr->set (0, vertex_count, vertex_values);
    delete [] vertex_values;
  } else if (component_size == 2) {
    short* vertex_values = getInt16Array (vertex_count*component_count);
    if (encoding) {
      for (int i = component_count; i < vertex_count*component_count; i++)
	vertex_values[i] += vertex_values[i-component_count];
    }
    varr->set (0, vertex_count, vertex_values);
    delete [] vertex_values;
  } else {
    throw IOException (__FILE__, __func__, "Component size is invalid, size=%d.", component_size);
  }

  //varr->VertexArray:: print (cout);

  objs.push_back (varr);
}

void Loader:: parseVertexBuffer ()
{
  VertexBuffer* vbuf = new VertexBuffer;
  parseObject3D(vbuf);

  int          default_color   = getColorRGBA();
  unsigned int positions_index = getUInt32();
  float        bias[3]         = {getFloat32(), getFloat32(), getFloat32()};
  float        scale           = getFloat32();
  unsigned int normals_index   = getUInt32();
  unsigned int colors_index    = getUInt32();
   
  //cout << "positions_index = " << positions_index << "\n";
  //cout << "normals_index = " << normals_index << "\n";
  //cout << "colors_index = " << colors_index << "\n";

  vbuf->setDefaultColor (default_color);
  if (positions_index > 0) {
    VertexArray* positions = dynamic_cast<VertexArray*>(objs.at(positions_index));
    vbuf->setPositions (positions, scale, bias);
  }
  if (normals_index > 0) {
    VertexArray* normals = dynamic_cast<VertexArray*>(objs.at(normals_index));
    vbuf->setNormals (normals);
  }
  if (colors_index > 0) {
    VertexArray* colors = dynamic_cast<VertexArray*>(objs.at(colors_index));
    vbuf->setColors (colors);
  }

  unsigned int tex_coord_array_count = getUInt32();
  for (int i = 0; i < (int)tex_coord_array_count; i++) {
    unsigned int tex_coords_index = getUInt32();
    float        bias[3]          = {getFloat32(), getFloat32(), getFloat32()};
    float        scale            = getFloat32();
    if (tex_coords_index > 0) {
      VertexArray* tex_coords = dynamic_cast<VertexArray*>(objs.at(tex_coords_index));
      vbuf->setTexCoords (i, tex_coords, scale, bias);
    }
  }
   
  //vbuf->VertexBuffer:: print (cout);

  objs.push_back (vbuf);
}

void Loader:: parseWorld ()
{
  World* wld = new World;
  parseGroup (wld);

  unsigned int active_camera_index = getUInt32();
  unsigned int background_index    = getUInt32();

  //cout << "camera_index = " << active_camera_index << "\n";
  //cout << "background_index = " << background_index << "\n";

  if (active_camera_index > 0) {
    Camera*     cam = dynamic_cast<Camera*>(objs.at(active_camera_index));
    wld->setActiveCamera (cam);
  }

  if (background_index > 0) {
    Background* bg  = dynamic_cast<Background*>(objs.at(background_index));
    wld->setBackground (bg);
  }

  //wld->World:: print (cout);

  objs.push_back (wld);
}

std::ostream& operator<< (std::ostream& out, const Loader& ldr)
{
  out << "Loader: ";
  return out << "\n";
}
