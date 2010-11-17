#include "m3g/m3ginternal.hpp"
#include "m3g/m3gdef.hpp"
#include <limits>
using namespace m3g;

const float m3g::M3G_EPSILON = std::numeric_limits<float>::epsilon()*100;


const char* m3g::objtype_to_string(int objtype)
{
    switch (objtype) {
    case OBJTYPE_HEADER_OBJECT       : return "header object";
    case OBJTYPE_ANIMATION_CONTROLLER: return "AnimationController";
    case OBJTYPE_ANIMATION_TRACK     : return "AnimationTrack";
    case OBJTYPE_APPEARANCE          : return "Appearance";
    case OBJTYPE_BACKGROUND          : return "Background";
    case OBJTYPE_CAMERA              : return "Camera";
    case OBJTYPE_COMPOSITING_MODE    : return "CompositingMode";
    case OBJTYPE_FOG                 : return "Fog";
    case OBJTYPE_POLYGON_MODE        : return "PolygonMode";
    case OBJTYPE_GROUP               : return "Group";
    case OBJTYPE_IMAGE2D             : return "Image2D";
    case OBJTYPE_TRIANGLE_STRIP_ARRAY: return "TriangleStripArray";
    case OBJTYPE_LIGHT               : return "Light";
    case OBJTYPE_MATERIAL            : return "Material";
    case OBJTYPE_MESH                : return "Mesh";
    case OBJTYPE_MORPHING_MESH       : return "MorphingMesh";
    case OBJTYPE_SKINNED_MESH        : return "SkinnedMesh";
    case OBJTYPE_TEXTURE2D           : return "Texture2D";
    case OBJTYPE_SPRITE3D            : return "Sprite3D";
    case OBJTYPE_KEYFRAME_SEQUENCE   : return "KeyframeSequence";
    case OBJTYPE_VERTEX_ARRAY        : return "VertexArray";
    case OBJTYPE_VERTEX_BUFFER       : return "VertexBuffer";
    case OBJTYPE_WORLD               : return "World";
    case OBJTYPE_EXTERNAL_REFERENCE  : return "external reference";
    default                          : return "Unknown";
    }
}
