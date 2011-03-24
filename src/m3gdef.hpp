#ifndef __M3G_DEF_HPP__
#define __M3G_DEF_HPP__

namespace m3g {


const int MAX_TEXTURE_UNITS = 2;

const int OBJTYPE_HEADER_OBJECT        = 0;
const int OBJTYPE_ANIMATION_CONTROLLER = 1;
const int OBJTYPE_ANIMATION_TRACK      = 2;
const int OBJTYPE_APPEARANCE           = 3;
const int OBJTYPE_BACKGROUND           = 4;
const int OBJTYPE_CAMERA               = 5;
const int OBJTYPE_COMPOSITING_MODE     = 6;
const int OBJTYPE_FOG                  = 7;
const int OBJTYPE_POLYGON_MODE         = 8;
const int OBJTYPE_GROUP                = 9;
const int OBJTYPE_IMAGE2D              = 10;
const int OBJTYPE_TRIANGLE_STRIP_ARRAY = 11;
const int OBJTYPE_LIGHT                = 12;
const int OBJTYPE_MATERIAL             = 13;
const int OBJTYPE_MESH                 = 14;
const int OBJTYPE_MORPHING_MESH        = 15;
const int OBJTYPE_SKINNED_MESH         = 16;
const int OBJTYPE_TEXTURE2D            = 17;
const int OBJTYPE_SPRITE3D             = 18;
const int OBJTYPE_KEYFRAME_SEQUENCE    = 19;
const int OBJTYPE_VERTEX_ARRAY         = 20;
const int OBJTYPE_VERTEX_BUFFER        = 21;
const int OBJTYPE_WORLD                = 22;
const int OBJTYPE_EXTERNAL_REFERENCE   = 255;

// これ使ってる?
// These variables are not defined in M3G specification.
// It is only for easy use.
const int OBJTYPE_OBJECT3D      = -1;
const int OBJTYPE_TRANSFORMABLE = -2;
const int OBJTYPE_NODE          = -3;
const int OBJTYPE_INDEX_BUFFER  = -4;


} // namesapce m3g


#endif
