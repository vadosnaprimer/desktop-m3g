
#ifndef __M3G_STRUCT_H__
#define __M3G_STRUCT_H__

#include <iosfwd>

const int M3G_TYPE_HEADER               = 0;
const int M3G_TYPE_ANIMATION_CONTROLLER = 1;
const int M3G_TYPE_ANIMATION_TRACK      = 2;
const int M3G_TYPE_APPEARANCE           = 3;
const int M3G_TYPE_BACKGROUND           = 4;
const int M3G_TYPE_CAMERA               = 5;
const int M3G_TYPE_COMPOSITING_MODE     = 6;
const int M3G_TYPE_FOG                  = 7;
const int M3G_TYPE_POLYGON_MODE         = 8;
const int M3G_TYPE_GROUP                = 9;
const int M3G_TYPE_IMAGE2D              = 10;
const int M3G_TYPE_TRIANGLE_STRIP_ARRAY = 11;
const int M3G_TYPE_LIGHT                = 12;
const int M3G_TYPE_MATERIAL             = 13;
const int M3G_TYPE_MESH                 = 14;
const int M3G_TYPE_MORPHING_MESH        = 15;
const int M3G_TYPE_SKINNED_MESH         = 16;
const int M3G_TYPE_TEXTURE2D            = 17;
const int M3G_TYPE_SPRITE3D             = 18;
const int M3G_TYPE_KEYFRAME_SEQUENCE    = 19;
const int M3G_TYPE_VERTEX_ARRAY         = 20;
const int M3G_TYPE_VERTEX_BUFFER        = 21;
const int M3G_TYPE_WORLD                = 22;
const int M3G_TYPE_EXTERNAL_REFERENCE   = 255;



struct M3GHeaderStruct
{
    M3GHeaderStruct ();
    ~M3GHeaderStruct ();
    char         version_major;
    char         version_minor;
    bool         has_external_references;
    unsigned int total_file_size;             // don't touch, auto calculated
    unsigned int approximate_content_size;    // don't touch, auto calculated
    char*        authoring_field;
};
std::ostream& operator<< (std::ostream& out, const M3GHeaderStruct& header);


struct M3GExternalReferenceStruct
{
    M3GExternalReferenceStruct ();
    ~M3GExternalReferenceStruct ();
    char* uri;
};
std::ostream& operator<< (std::ostream& out, const M3GExternalReferenceStruct& ex_ref);

    
struct M3GAnimationControllerStruct
{
    M3GAnimationControllerStruct ();
    ~M3GAnimationControllerStruct ();
    float  speed;
    float  weight;
    int    active_interval_start;
    int    active_interval_end;
    float  reference_sequence_time;
    int    reference_world_time;
};
std::ostream& operator<< (std::ostream& out, const M3GAnimationControllerStruct& anim_ctr);


struct M3GAnimationTrackStruct
{
    M3GAnimationTrackStruct ();
    ~M3GAnimationTrackStruct ();
    unsigned int  keyframe_sequence_index;
    unsigned int  animation_controller_index;
    unsigned int  property_id;
};
std::ostream& operator<< (std::ostream& out, const M3GAnimationTrackStruct& anim_track);


struct M3GAppearanceStruct
{
    M3GAppearanceStruct ();
    ~M3GAppearanceStruct ();
    char          layer;
    unsigned int  compositing_mode_index;
    unsigned int  fog_index;
    unsigned int  polygon_mode_index;
    unsigned int  material_index;
    unsigned int  textures_count;
    unsigned int* textures_index;
};
std::ostream& operator<< (std::ostream& out, const M3GAppearanceStruct& app);


struct M3GBackgroundStruct
{
    M3GBackgroundStruct ();
    ~M3GBackgroundStruct ();
    int           background_color;
    unsigned int  background_image_index;
    unsigned char background_image_mode_x;
    unsigned char  background_image_mode_y;
    unsigned int  crop_x;
    unsigned int  crop_y;
    unsigned int  crop_width;
    unsigned int  crop_height;
    bool          depth_clear_enabled;
    bool          color_clear_enabled;
};
std::ostream& operator<< (std::ostream& out, const M3GBackgroundStruct& bg);


struct M3GCameraStruct
{
    static const int GENERIC     = 48;
    static const int PARALLEL    = 49;
    static const int PERSPECTIVE = 50;
    M3GCameraStruct ();
    ~M3GCameraStruct ();
    unsigned char projection_type;
    float         matrix[16];
    float         fovy;
    float         aspect_ratio;
    float         near;
    float         far;
};
std::ostream& operator<< (std::ostream& out, const M3GCameraStruct& cam);


struct M3GCompositingModeStruct
{
    M3GCompositingModeStruct ();
    ~M3GCompositingModeStruct ();
    bool           depth_test_enabled;
    bool           depth_write_enabled;
    bool           color_write_enabled;
    bool           alpha_write_enabled;
    unsigned char  blending;
    unsigned char  alpha_threshold;
    float          depth_offset_factor;
    float          depth_offset_units;
};
std::ostream& operator<< (std::ostream& out, const M3GCompositingModeStruct& comp);


struct M3GFogStruct
{
    static const int EXPONENTIAL = 80;
    static const int LINEAR      = 81;
    M3GFogStruct ();
    ~M3GFogStruct ();
    int            color;
    unsigned char  mode;
    float          density;
    float          near;
    float          far;
};
std::ostream& operator<< (std::ostream& out, const M3GFogStruct& fog);


struct M3GGroupStruct
{
    M3GGroupStruct ();
    ~M3GGroupStruct ();
    unsigned int  children_index_count;
    unsigned int* children_index;
};
std::ostream& operator<< (std::ostream& out, const M3GGroupStruct& grp);


struct M3GImage2DStruct
{
    static const int ALPHA           = 96;
    static const int LUMINANCE       = 97;
    static const int LUMINANCE_ALPHA = 98;
    static const int RGB             = 99;
    static const int RGBA            = 100;
    M3GImage2DStruct ();
    ~M3GImage2DStruct ();
    unsigned char  format;
    bool           is_mutable;
    unsigned int   width;
    unsigned int   height;
    unsigned int   palette_count;
    unsigned char* palette;
    unsigned int   pixels_count;
    unsigned char* pixels;
};
std::ostream& operator<< (std::ostream& out, const M3GImage2DStruct& img);
int format_to_bpp (int format);


struct M3GIndexBufferStruct
{
    M3GIndexBufferStruct ();
    ~M3GIndexBufferStruct ();
};
std::ostream& operator<< (std::ostream& out, const M3GIndexBufferStruct& ibuf);


struct M3GKeyframeSequenceStruct
{
    static const int ENCODING_0 = 0;
    static const int ENCODING_1 = 1;
    static const int ENCODING_2 = 2;
    M3GKeyframeSequenceStruct ();
    ~M3GKeyframeSequenceStruct ();
    unsigned char  interpolation;
    unsigned char  repeat_mode;
    unsigned char  encoding;
    unsigned int   duration;
    unsigned int   valid_range_first;
    unsigned int   valid_range_last;
    unsigned int   component_count;
    unsigned int   keyframe_count;
    unsigned int*  time;
    float**        vector_value;
};
std::ostream& operator<< (std::ostream& out, const M3GKeyframeSequenceStruct& keyframe_sequence);


struct M3GLightStruct
{
    static const int AMBIENT     = 128;
    static const int DIRECTIONAL = 129;
    static const int OMNI        = 130;
    static const int SPOT        = 131;
    M3GLightStruct ();
    ~M3GLightStruct ();
    float          attenuation_constant;
    float          attenuation_linear;
    float          attenuation_quadratic;
    int            color;
    unsigned char  mode;
    float          intensity;
    float          spot_angle;
    float          spot_exponent;
};
std::ostream& operator<< (std::ostream& out, const M3GLightStruct& light);


struct M3GMaterialStruct
{
    M3GMaterialStruct ();
    ~M3GMaterialStruct ();
    int    ambient_color;
    int    diffuse_color;
    int    emissive_color;
    int    specular_color;
    float  shininess;
    bool   vertex_color_tracking_enabled;
};
std::ostream& operator<< (std::ostream& out, const M3GMaterialStruct& material);


struct M3GMeshStruct
{
    M3GMeshStruct ();
    ~M3GMeshStruct ();
    unsigned int  vertex_buffer_index;
    unsigned int  submesh_count;
    unsigned int* index_buffer_index;
    unsigned int* appearance_index;
};

std::ostream& operator<< (std::ostream& out, const M3GMeshStruct& mesh);


struct M3GMorphingMeshStruct
{
    M3GMorphingMeshStruct ();
    ~M3GMorphingMeshStruct ();
    unsigned int  morph_target_count;
    unsigned int* morph_target_index;
    float*        initial_weight;
};
std::ostream& operator<< (std::ostream& out, const M3GMorphingMeshStruct& mesh);


struct M3GObject3DStruct
{
    M3GObject3DStruct ();
    ~M3GObject3DStruct ();
    unsigned int   user_id;
    unsigned int   animation_tracks_count;
    unsigned int*  animation_tracks_index;
    unsigned int   user_parameter_count;
    unsigned int*  parameter_id;
    unsigned int*  parameter_value_length;
    char**         parameter_value;
};
std::ostream& operator<< (std::ostream& out, const M3GObject3DStruct& obj);


struct M3GNodeStruct
{
    M3GNodeStruct ();
    ~M3GNodeStruct ();
    bool           enable_rendering;
    bool           enable_picking;
    unsigned char  alpha_factor;
    int            scope;
    bool           has_alignment;
    unsigned char  z_target;
    unsigned char  y_target;
    unsigned int   z_reference_index;
    unsigned int   y_reference_index;
};
std::ostream& operator<< (std::ostream& out, const M3GNodeStruct& node);


struct M3GPolygonModeStruct
{
    M3GPolygonModeStruct ();
    ~M3GPolygonModeStruct ();
    unsigned char  culling;
    unsigned char  shading;
    unsigned char  winding;
    bool           two_sided_lighting_enabled;
    bool           local_camera_lighting_enabled;
    bool           perspective_correction_enabled;
};
std::ostream& operator<< (std::ostream& out, const M3GPolygonModeStruct& poly);


struct M3GSkinnedMeshStruct
{
    M3GSkinnedMeshStruct ();
    ~M3GSkinnedMeshStruct ();
    unsigned int   skeleton_index;
    unsigned int   transform_reference_count;
    unsigned int*  transform_node_index;
    unsigned int*  first_vertex;
    unsigned int*  vertex_count;
    int*           weight;
};
std::ostream& operator<< (std::ostream& out, const M3GSkinnedMeshStruct& mesh);


struct M3GSprite3DStruct
{
    M3GSprite3DStruct ();
    ~M3GSprite3DStruct ();
    unsigned int  image_index;
    unsigned int  appearance_index;
    bool          is_scaled;
    int           crop_x;
    int           crop_y;
    int           crop_width;
    int           crop_height;
};
std::ostream& operator<< (std::ostream& out, const M3GSprite3DStruct& sprite);


struct M3GTexture2DStruct
{
    M3GTexture2DStruct ();
    ~M3GTexture2DStruct ();
    unsigned int   image_index;
    int            blend_color;
    unsigned char  blending;
    unsigned char  wrapping_s;
    unsigned char  wrapping_t;
    unsigned char  level_filter;
    unsigned char  image_filter;
};
std::ostream& operator<< (std::ostream& out, const M3GTexture2DStruct& texture);


struct M3GTransformableStruct
{
    M3GTransformableStruct ();
    ~M3GTransformableStruct ();
    bool   has_component_transform;
    float  translation[3];
    float  scale[3];
    float  orientation_angle;
    float  orientation_axis[3];
    bool   has_general_transform;
    float  transform[16];
};
std::ostream& operator<< (std::ostream& out, const M3GTransformableStruct& trans);


struct M3GTriangleStripArrayStruct
{
    static const int ENCODING_0    = 0;
    static const int ENCODING_1    = 1;
    static const int ENCODING_2    = 2;
    static const int ENCODING_128  = 128;
    static const int ENCODING_129  = 129;
    static const int ENCODING_130  = 130;
    M3GTriangleStripArrayStruct ();
    ~M3GTriangleStripArrayStruct ();
    unsigned char   encoding;
    unsigned int    start_index;
    unsigned int    indices_count;
    unsigned int*   indices;
    unsigned int    strip_lengths_count;
    unsigned int*   strip_lengths;
};
std::ostream& operator<< (std::ostream& out, const M3GTriangleStripArrayStruct& tris);


struct M3GVertexArrayStruct
{
    static const int ENCODING_0 = 0;
    static const int ENCODING_1 = 1;
    M3GVertexArrayStruct ();
    ~M3GVertexArrayStruct ();
    char            component_size;
    char            component_count;
    unsigned char   encoding;
    unsigned short  vertex_count;
    union {
        char**      char_components;
        short**     short_components;
        float**     float_components;
    };
};
std::ostream& operator<< (std::ostream& out, const M3GVertexArrayStruct& varry);


struct M3GVertexBufferStruct
{
    M3GVertexBufferStruct ();
    ~M3GVertexBufferStruct ();
    int            default_color;
    unsigned int   positions_index;
    float          position_scale;
    float          position_bias[3];
    unsigned int   normals_index;
    unsigned int   colors_index;
    unsigned int   texcoord_array_count;
    unsigned int*  texcoords_index;
    float*         texcoord_scale;
    float**        texcoord_bias;
};
std::ostream& operator<< (std::ostream& out, const M3GVertexBufferStruct& vbuf);


struct M3GWorldStruct
{
    M3GWorldStruct ();
    ~M3GWorldStruct ();
    unsigned int active_camera_index;
    unsigned int background_index;
};
std::ostream& operator<< (std::ostream& out, const M3GWorldStruct& world);





#endif
