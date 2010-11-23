#include "M3GStruct.hpp"
#include <iostream>
using namespace std;

const int M3GFogStruct::EXPONENTIAL;
const int M3GFogStruct::LINEAR;

const int M3GCameraStruct::GENERIC;
const int M3GCameraStruct::PARALLEL;
const int M3GCameraStruct::PERSPECTIVE;

const int M3GImage2DStruct:: ALPHA;
const int M3GImage2DStruct:: LUMINANCE;
const int M3GImage2DStruct:: LUMINANCE_ALPHA;
const int M3GImage2DStruct:: RGB;
const int M3GImage2DStruct:: RGBA;

const int M3GKeyframeSequenceStruct:: ENCODING_0;
const int M3GKeyframeSequenceStruct:: ENCODING_1;
const int M3GKeyframeSequenceStruct:: ENCODING_2;

const int M3GLightStruct:: AMBIENT;
const int M3GLightStruct:: DIRECTIONAL;
const int M3GLightStruct:: OMNI;
const int M3GLightStruct:: SPOT;

const int M3GTriangleStripArrayStruct:: ENCODING_0;
const int M3GTriangleStripArrayStruct:: ENCODING_1;
const int M3GTriangleStripArrayStruct:: ENCODING_2;
const int M3GTriangleStripArrayStruct:: ENCODING_128;
const int M3GTriangleStripArrayStruct:: ENCODING_129;
const int M3GTriangleStripArrayStruct:: ENCODING_130;

const int M3GVertexArrayStruct:: ENCODING_0;
const int M3GVertexArrayStruct:: ENCODING_1;


M3GHeaderStruct:: M3GHeaderStruct ()
{
    version_major             = 0;
    version_minor             = 0;
    has_external_references   = false;
    total_file_size           = 0;
    approximate_content_size  = 0;
    authoring_field           = 0;
}

M3GHeaderStruct:: ~M3GHeaderStruct ()
{
    delete [] authoring_field;
}

std::ostream& operator<< (std::ostream& out, const M3GHeaderStruct& header)
{
    out << "M3GHeaderStruct: \n";
    out << "  version_major            = " << (int)header.version_major       << "\n";
    out << "  version_minor            = " << (int)header.version_minor       << "\n";
    out << "  has_external_references  = " << header.has_external_references  << "\n";
    out << "  total_file_size          = " << header.total_file_size          << "\n";
    out << "  approximate_content_size = " << header.approximate_content_size << "\n";
    out << "  authoring_field          = " << header.authoring_field;
    return out;
}

M3GExternalReferenceStruct:: M3GExternalReferenceStruct ()
{
    uri = 0;
}

M3GExternalReferenceStruct:: ~M3GExternalReferenceStruct ()
{
    delete [] uri;
}

std::ostream& operator<< (std::ostream& out, const M3GExternalReferenceStruct& ex_ref)
{
    out << "M3GExternalReferenceStruct: \n";
    out << "  uri = " << ex_ref.uri;
    return out;
}

M3GAnimationControllerStruct:: M3GAnimationControllerStruct ()
{
    speed                   = 0;
    weight                  = 0;
    active_interval_start   = 0;
    active_interval_end     = 0;
    reference_sequence_time = 0;
    reference_world_time    = 0;
}

M3GAnimationControllerStruct:: ~M3GAnimationControllerStruct ()
{
}

std::ostream& operator<< (std::ostream& out, const M3GAnimationControllerStruct& anim_ctr)
{
    out << "M3GAnimationControllerStruct: \n";
    out << "  speed                   = " << anim_ctr.speed                   << "\n";
    out << "  weight                  = " << anim_ctr.weight                  << "\n";
    out << "  active_interval_start   = " << anim_ctr.active_interval_start   << "\n";
    out << "  active_interval_end     = " << anim_ctr.active_interval_end     << "\n";
    out << "  reference_sequence_time = " << anim_ctr.reference_sequence_time << "\n";
    out << "  reference_world_time    = " << anim_ctr.reference_world_time;
    return out;
}


M3GAnimationTrackStruct:: M3GAnimationTrackStruct ()
{
    keyframe_sequence_index    = 0;
    animation_controller_index = 0;
    property_id                = 0;

}

M3GAnimationTrackStruct:: ~M3GAnimationTrackStruct ()
{

}

std::ostream& operator<< (std::ostream& out, const M3GAnimationTrackStruct& anim_track)
{
    out << "M3GAnimationTrackStruct: \n";
    out << "  keyframe_sequence_index    = " << anim_track.keyframe_sequence_index    << "\n";
    out << "  animation_controller_index = " << anim_track.animation_controller_index << "\n";
    out << "  property_id                = " << anim_track.property_id;
    return out;
}


M3GAppearanceStruct:: M3GAppearanceStruct ()
{
    layer                  = 0;
    compositing_mode_index = 0;
    fog_index              = 0;
    polygon_mode_index     = 0;
    material_index         = 0;
    textures_count         = 0;
    textures_index         = 0;
}

M3GAppearanceStruct:: ~M3GAppearanceStruct ()
{
    delete [] textures_index;
}

std::ostream& operator<< (std::ostream& out, const M3GAppearanceStruct& app)
{
    out << "M3GAppearanceStruct: \n";
    out << "  layer                  = " << (int)app.layer             << "\n";
    out << "  compositing_mode_index = " << app.compositing_mode_index << "\n";
    out << "  polygon_mode_index     = " << app.polygon_mode_index     << "\n";
    out << "  material_index         = " << app.material_index         << "\n";
    out << "  textures_count         = " << app.textures_count         << "\n";
    out << "  textures_index         = [";
    for (int i = 0; i < (int)app.textures_count; i++) {
        out << app.textures_index[i] << ", ";
    }
    out << "]";
    return out;
}


M3GBackgroundStruct:: M3GBackgroundStruct     () : background_color(0), background_image_index(0), background_image_mode_x(0), background_image_mode_y(0), 
                                                   crop_x(0), crop_y(0), crop_width(0), crop_height(0), depth_clear_enabled(false), color_clear_enabled(false)
{
    background_color        = 0;
    background_image_index  = 0;
    background_image_mode_x = 0;
    background_image_mode_y = 0;
    crop_x                  = 0;
    crop_y                  = 0;
    crop_width              = 0;
    crop_height             = 0;
    depth_clear_enabled     = false;
    color_clear_enabled     = false;
}

M3GBackgroundStruct:: ~M3GBackgroundStruct ()
{
}

std::ostream& operator<< (std::ostream& out, const M3GBackgroundStruct& bg)
{
    out << "M3GBackgroundStruct: \n";
    out << "  background_color        = 0x" << hex << bg.background_color << dec << "\n";
    out << "  background_image_index  = "   << bg.background_image_index  << "\n";
    out << "  background_image_mode_x = "   << bg.background_image_mode_x << "\n";
    out << "  background_image_mode_y = "   << bg.background_image_mode_y << "\n";
    out << "  crop_x                  = "   << bg.crop_x                  << "\n";
    out << "  crop_y                  = "   << bg.crop_y                  << "\n";
    out << "  crop_width              = "   << bg.crop_width              << "\n";
    out << "  crop_height             = "   << bg.crop_height             << "\n";
    out << "  depth_clear_enabled     = "   << bg.depth_clear_enabled     << "\n";
    out << "  color_clear_enabled     = "   << bg.color_clear_enabled;
    return out;
}


M3GCameraStruct:: M3GCameraStruct () : projection_type(0), fovy(0), aspect_ratio(0), near(0), far(0)
{
    projection_type = 0;
    for (int i = 0; i < 16; i++) {
        matrix[i] = 0;
    }
    fovy          = 0;
    aspect_ratio  = 0;
    near          = 0;
    far           = 0;
}

M3GCameraStruct:: ~M3GCameraStruct ()
{
}

std::ostream& operator<< (std::ostream& out, const M3GCameraStruct& cam)
{
    out << "M3GCameraStruct: \n";
    out << "  projection_type = " << (int)cam.projection_type << "\n";
    out << "  matrix = [";
    for (int i = 0; i < 16; i++) {
        cout << cam.matrix[i] << ", ";
    }
    out << "]\n";
    out << " fovy          = " << cam.fovy         << "\n";
    out << "  aspect_ratio = " << cam.aspect_ratio << "\n";
    out << "  near         = " << cam.near         << "\n";
    out << "  far          = " << cam.far;
    return out;
}

M3GCompositingModeStruct:: M3GCompositingModeStruct ()
{
    depth_test_enabled  = false;
    depth_write_enabled = false;
    color_write_enabled = false;
    alpha_write_enabled = false;
    blending            = 0;
    alpha_threshold     = 0;
    depth_offset_factor = 0;
    depth_offset_units  = 0;
}

M3GCompositingModeStruct:: ~M3GCompositingModeStruct ()
{
}

std::ostream& operator<< (std::ostream& out, const M3GCompositingModeStruct& comp)
{
    out << "M3GCompositiongModeStruct: \n";
    out << "  depth_test_enabled = "  << comp.depth_test_enabled  << "\n";
    out << "  depth_write_enabled = " << comp.depth_write_enabled << "\n";
    out << "  color_write_enabled = " << comp.color_write_enabled << "\n";
    out << "  alpha_write_enabled = " << comp.alpha_write_enabled << "\n";
    out << "  blending = "            << comp.blending            << "\n";
    out << "  alpha_threshold = "     << comp.alpha_threshold     << "\n";
    out << "  depth_offset_factor = " << comp.depth_offset_factor << "\n";
    out << "  depth_offset_units  = " << comp.depth_offset_units;
    return out;
}

M3GFogStruct:: M3GFogStruct ()
{
    color    = 0;
    mode     = 0;
    density  = 0;
    near     = 0;
    far      = 0;
}

M3GFogStruct:: ~M3GFogStruct ()
{
}

std::ostream& operator<< (std::ostream& out, const M3GFogStruct& fog)
{
    out << "M3GFogStruct: \n";
    out << "  color   = " << hex << (int)fog.color << dec << "\n";
    out << "  mode    = " << (int)fog.mode << "\n";
    out << "  density = " << fog.density  << "\n";
    out << "  near    = " << fog.near      << "\n";
    out << "  far     = " << fog.far;
    return out;
}

M3GGroupStruct:: M3GGroupStruct ()
{
    children_index_count = 0;
    children_index       = 0;
}

M3GGroupStruct:: ~M3GGroupStruct ()
{
    delete [] children_index;
}

std::ostream& operator<< (std::ostream& out, const M3GGroupStruct& grp)
{
    out << "M3GGroupStruct: \n";
    out << "  children_index_count = " << grp.children_index_count << "\n";
    out << "  children_index       = [";
    for (int i = 0; i < (int)grp.children_index_count; i++) {
        out << grp.children_index[i] << ", ";
    }
    out << "]";
    return out;
}

M3GImage2DStruct:: M3GImage2DStruct ()
{
    format        = 0;
    is_mutable    = false;
    width         = 0;
    height        = 0;
    palette_count = 0;
    palette       = 0;
    pixels_count  = 0;
    pixels        = 0;
}

M3GImage2DStruct:: ~M3GImage2DStruct ()
{
    delete [] palette;
    delete [] pixels;
}

std::ostream& operator<< (std::ostream& out, const M3GImage2DStruct& img)
{
    out << "M3GImage2DStruct: \n";
    out << "  format        = " << (int)img.format    << "\n";
    out << "  is_mutable    = " << img.is_mutable     << "\n";
    out << "  width         = " << img.width          << "\n";
    out << "  height        = " << img.height         << "\n";
    out << "  palette_count = " << img.palette_count  << "\n";
    out << "  palette       = " << (void*)img.palette << "\n";
    out << "  pixels_count  = " << img.pixels_count   << "\n";
    out << "  pixels        = " << (void*)img.pixels;
    return out;
}

int format_to_bpp (int format)
{
    switch (format) {
    case M3GImage2DStruct::ALPHA          : return 1;
    case M3GImage2DStruct::LUMINANCE      : return 1;
    case M3GImage2DStruct::LUMINANCE_ALPHA: return 2;
    case M3GImage2DStruct::RGB            : return 3;
    case M3GImage2DStruct::RGBA           : return 4;
    default: cout << "Format is invalid, f=" << format << "\n"; return 0;
    }
}



M3GIndexBufferStruct:: M3GIndexBufferStruct ()
{
}

M3GIndexBufferStruct:: ~M3GIndexBufferStruct ()
{
}

std::ostream& operator<< (std::ostream& out, const M3GIndexBufferStruct& ibuf)
{
    out << "M3GIndexBuffer: ";
    return out;
}


M3GKeyframeSequenceStruct:: M3GKeyframeSequenceStruct ()
{
    interpolation     = 0;
    repeat_mode       = 0;
    encoding          = 0;
    duration          = 0;
    valid_range_first = 0;
    valid_range_last  = 0;
    component_count   = 0;
    keyframe_count    = 0;
    time              = 0;
    vector_value      = 0;
}


M3GKeyframeSequenceStruct:: ~M3GKeyframeSequenceStruct ()
{
    delete [] time;
    for (int i = 0; i < (int)keyframe_count; i++) {
        delete [] vector_value[i];
    }
    delete [] vector_value;
}

std::ostream& operator<< (std::ostream& out, const M3GKeyframeSequenceStruct& key_seq)
{
    out << "M3GKeyframeSequenceStruct: ";
    out << "  interpolation     = " << (int)key_seq.interpolation << "\n";
    out << "  repeat_mode       = " << (int)key_seq.repeat_mode   << "\n";
    out << "  encoding          = " << (int)key_seq.encoding      << "\n";
    out << "  duration          = " << key_seq.duration           << "\n";
    out << "  valid_range_first = " << key_seq.valid_range_first  << "\n";
    out << "  valid_range_last  = " << key_seq.valid_range_last   << "\n";
    out << "  component_count   = " << key_seq.component_count    << "\n";
    out << "  keyframe_count    = " << key_seq.keyframe_count     << "\n";
    out << "  time              = [";
    for (int i = 0; i < (int)key_seq.keyframe_count; i++) {
        out << key_seq.time << ", ";
    }
    out << "]\n";
    out << "  vector_value      = [";
    for (int i = 0; i < (int)key_seq.keyframe_count; i++) {
        for (int j = 0; j < (int)key_seq.component_count; j++) {
            out << key_seq.vector_value[i][j] << ", ";
        }
    }
    out << "]";
    return out;
}


M3GLightStruct:: M3GLightStruct ()
{
    attenuation_constant   = 0;
    attenuation_linear     = 0;
    attenuation_quadratic  = 0;
    color                  = 0;
    mode                   = 0;
    intensity              = 0;
    spot_angle             = 0;
    spot_exponent          = 0;
}

std::ostream& operator<< (std::ostream& out, const M3GLightStruct& lgh)
{
    out << "M3GLightStruct: \n";
    out << "  attenuation_constant  = "   << lgh.attenuation_constant  << "\n";
    out << "  attenuation_linear    = "   << lgh.attenuation_linear    << "\n";
    out << "  attenuation_quadratic = "   << lgh.attenuation_quadratic << "\n";
    out << "  color                 = 0x" << hex << lgh.color << dec   << "\n";
    out << "  mode                  = "   << (int)lgh.mode             << "\n";
    out << "  intensity             = "   << lgh.intensity             << "\n";
    out << "  spot_angle            = "   << lgh.spot_angle            << "\n";
    out << "  spot_exponent         = "   << lgh.spot_exponent;
    return out;
}

M3GLightStruct:: ~M3GLightStruct ()
{
}

M3GMaterialStruct:: M3GMaterialStruct ()
{
    ambient_color   = 0;
    diffuse_color   = 0;
    emissive_color  = 0;
    specular_color  = 0;
    shininess       = 0;
    vertex_color_tracking_enabled = 0;
}

M3GMaterialStruct:: ~M3GMaterialStruct ()
{
}

std::ostream& operator<< (std::ostream& out, const M3GMaterialStruct& mat)
{
    out << "M3GMaterial: \n";
    out << "  ambient_color  = 0x" << hex << mat.ambient_color  << dec << "\n";
    out << "  diffuse_color  = 0x" << hex << mat.diffuse_color  << dec << "\n";
    out << "  emissive_color = 0x" << hex << mat.emissive_color << dec << "\n";
    out << "  specular color = 0x" << hex << mat.specular_color << dec << "\n";
    out << "  shininess      = "   << mat.shininess                    << "\n";
    out << "  vertex_color_tracking_enabled = " << mat.vertex_color_tracking_enabled;
    return out;
}

M3GMeshStruct:: M3GMeshStruct () : vertex_buffer_index(0), submesh_count(0), index_buffer_index(0), appearance_index(0)
{
    vertex_buffer_index = 0;
    submesh_count       = 0;
    index_buffer_index  = 0;
    appearance_index    = 0;
}

M3GMeshStruct:: ~M3GMeshStruct ()
{
    delete [] index_buffer_index;
    delete [] appearance_index;
}

std::ostream& operator<< (std::ostream& out, const M3GMeshStruct& mesh)
{
    out << "M3GMeshStruct: \n";
    out << "  vertex_buffer_index = " << mesh.vertex_buffer_index << "\n";
    out << "  submesh_count       = " << mesh.submesh_count       << "\n";
    out << "  index_buffer_index  = [" << mesh.index_buffer_index  << "\n";
    for (int i = 0; i < (int)mesh.submesh_count; i++) {
        out << mesh.index_buffer_index << ", ";
    }
    out << "\n";
    out << "  appearance_index    = [";
    for (int i = 0; i < (int)mesh.submesh_count; i++) {
        out << mesh.appearance_index    << ", ";
    }
    out << "]";
    return out;
}


M3GMorphingMeshStruct:: M3GMorphingMeshStruct () : morph_target_count(0), morph_target_index(0), initial_weight(0)
{
    morph_target_count = 0;
    morph_target_index = 0;
    initial_weight     = 0;
}

M3GMorphingMeshStruct:: ~M3GMorphingMeshStruct ()
{
    delete [] morph_target_index;
    delete [] initial_weight;
}

std::ostream& operator<< (std::ostream& out, const M3GMorphingMeshStruct& mesh)
{
    out << "MorhpingMesh: \n";
    out << "  morph_target_count = " << mesh.morph_target_count << "\n";
    out << "  morph_target_index = [";
    for (int i = 0; i < (int)mesh.morph_target_count; i++) {
        out << mesh.morph_target_index[i] << ", ";
    }
    out << "]\n";
    out << "  initial_weight     = [";
    for (int i = 0; i < (int)mesh.morph_target_count; i++) {
        out << mesh.initial_weight[i] << ", ";
    }
    out << "]\n";
    return out;
}


M3GObject3DStruct:: M3GObject3DStruct ()
{
    user_id                 = 0;
    animation_tracks_count  = 0;
    animation_tracks_index  = 0;
    user_parameter_count    = 0;
    parameter_id            = 0;
    parameter_value_length  = 0;
    parameter_value         = 0;

}

M3GObject3DStruct:: ~M3GObject3DStruct ()
{
    delete [] animation_tracks_index;
    delete [] parameter_id;
    delete [] parameter_value_length;
    for (int i = 0; i < (int)user_parameter_count; i++) {
        delete [] parameter_value[i];
    }
    delete [] parameter_value;

}

std::ostream& operator<< (std::ostream& out, const M3GObject3DStruct& obj)
{
    out << "M3GObject3DStruct: \n";
    out << "  user_id                = "  << obj.user_id                << "\n";
    out << "  animation_tracks_count = "  << obj.animation_tracks_count << "\n";
    out << "  animation_tarcks_index = [";
    for (int i = 0; i < (int)obj.animation_tracks_count; i++) {
        out << obj.animation_tracks_index[i] << ", ";
    }
    out << "]\n";
    out << "  user_parameter_count   = " << obj.user_parameter_count   << "\n";
    out << "  parameter_id           = [";
    for (int i = 0; i < (int)obj.user_parameter_count; i++) {
        out << obj.parameter_id[i]  << ", ";
    }
    out << "]\n";
    out << "  paramter_value_length  = [";
    for (int i = 0; i < (int)obj.user_parameter_count; i++) {
        out << obj.parameter_value_length << ", ";
    }
    out << "]\n";
    out << "  parameter_value        = [";
    for (int i = 0; i < (int)obj.user_parameter_count; i++) {
        out << (void*)obj.parameter_value[i] << ", ";
    }
    out << "]\n";

    return out;
}

M3GNodeStruct:: M3GNodeStruct ()
{
    enable_rendering   = false;
    enable_picking     = false;
    alpha_factor       = 0;
    scope              = 0;
    has_alignment      = false;
    z_target           = 0;
    y_target           = 0;
    z_reference_index  = 0;
    y_reference_index  = 0;
}
 
M3GNodeStruct:: ~M3GNodeStruct ()
{
}

std::ostream& operator<< (std::ostream& out, const M3GNodeStruct& node)
{
    out << "M3GNode: \n";
    out << "  enable_rendering  = " << node.enable_rendering  << "\n";
    out << "  enable_picking    = " << node.enable_picking    << "\n";
    out << "  alpha_factor      = " << (int)node.alpha_factor << "\n";
    out << "  scope             = " << node.scope             << "\n";
    out << "  has_alignment     = " << node.has_alignment     << "\n";
    out << "  z_target          = " << (int)node.z_target     << "\n";
    out << "  y_target          = " << (int)node.y_target     << "\n";
    out << "  z_reference_index = " << node.z_reference_index << "\n";
    out << "  y_reference_index = " << node.y_reference_index;
    return out;
}

M3GPolygonModeStruct:: M3GPolygonModeStruct ()
{
    culling                         = 0;
    shading                         = 0;
    winding                         = 0;
    two_sided_lighting_enabled      = false;
    local_camera_lighting_enabled   = false;
    perspective_correction_enabled  = false;
}

M3GPolygonModeStruct:: ~M3GPolygonModeStruct ()
{
}

std::ostream& operator<< (std::ostream& out, const M3GPolygonModeStruct& pmode)
{
    out << "M3GPolyMode: \n";
    out << "  culling = " << (int)pmode.culling << "\n";
    out << "  shading = " << (int)pmode.shading << "\n";
    out << "  windign = " << (int)pmode.winding << "\n";
    out << "  two_sided_lighting_enabled     = " << pmode.two_sided_lighting_enabled     << "\n";
    out << "  local_camera_lighting_enabled  = " << pmode.local_camera_lighting_enabled  << "\n";
    out << "  perspective_correction_enabled = " << pmode.perspective_correction_enabled;
    return out;
}

M3GSkinnedMeshStruct:: M3GSkinnedMeshStruct ()
{
    skeleton_index            = 0;
    transform_reference_count = 0;
    transform_node_index      = 0;
    first_vertex              = 0;
    vertex_count              = 0;
    weight                    = 0;

}

M3GSkinnedMeshStruct:: ~M3GSkinnedMeshStruct ()
{
    delete [] transform_node_index;
    delete [] first_vertex;
    delete [] vertex_count;
    delete [] weight;
}

std::ostream& operator<< (std::ostream& out, const M3GSkinnedMeshStruct& mesh)
{
    out << "M3GSkinnedMesh: \n";
    out << "  skeleton_index            = " << mesh.skeleton_index            << "\n";
    out << "  transform_reference_count = " << mesh.transform_reference_count << "\n";
    out << "  transform_node_index      = [";
    for (int i = 0; i < (int)mesh.transform_reference_count; i++) {
        out << mesh.transform_node_index    << ", ";
    }
    out << "]\n";
    out << "  first_vertex              = [";
    for (int i = 0; i < (int)mesh.transform_reference_count; i++) {
        out << mesh.first_vertex << ", ";
    }
    out << "]\n";
    out << "  vertex_count              = [";
    for (int i = 0; i < (int)mesh.transform_reference_count; i++) {
        out << mesh.vertex_count << ", ";
    }
    out << "]\n";
    out << "  weight                    = [";
    for (int i = 0; i < (int)mesh.transform_reference_count; i++) {
        out << mesh.weight      << ", ";
    }
    out << "]\n";
    return out;
}


M3GSprite3DStruct:: M3GSprite3DStruct ()
{
    image_index      = 0;
    appearance_index = 0;
    is_scaled        = 0;
    crop_x           = 0;
    crop_y           = 0;
    crop_width       = 0;
    crop_height      = 0;
}

M3GSprite3DStruct:: ~M3GSprite3DStruct ()
{
}


std::ostream& operator<< (std::ostream& out, const M3GSprite3DStruct& spr)
{
    out << "Sprite3D: \n";
    out << "  image_index      = " << spr.image_index     << "\n";
    out << "  appearance_index = " << spr.appearance_index << "\n";
    out << "  is_scaled        = " << spr.is_scaled       << "\n";
    out << "  crop_x           = " << spr.crop_x          << "\n";
    out << "  crop_y           = " << spr.crop_y          << "\n";
    out << "  crop_width       = " << spr.crop_width      << "\n";
    out << "  crop_height      = " << spr.crop_height;
    return out;
}

M3GTexture2DStruct:: M3GTexture2DStruct () : image_index(0), blend_color(0), blending(0), wrapping_s(0), wrapping_t(0), level_filter(0), image_filter(0)
{
    image_index  = 0;
    blend_color  = 0;
    blending     = 0;
    wrapping_s   = 0;
    wrapping_t   = 0;
    level_filter = 0;
    image_filter = 0;
}


M3GTexture2DStruct:: ~M3GTexture2DStruct ()
{
}


std::ostream& operator<< (std::ostream& out, const M3GTexture2DStruct& tex)
{
    out << "M3GTexture2DStruct: \n";
    out << "  image_index = "   << tex.image_index        << "\n";
    out << "  blend_color = 0x" << hex << tex.blend_color << dec << "\n";
    out << "  blending    = "   << (int)tex.blending      << "\n";
    out << "  wrapping_s  = "   << (int)tex.wrapping_s    << "\n";
    out << "  wrapping_t  = "   << (int)tex.wrapping_t    << "\n";
    out << "  level_filter = "  << (int)tex.level_filter  << "\n";
    out << "  image_filter = "  << (int)tex.image_filter;
    return out;
}



M3GTransformableStruct:: M3GTransformableStruct () : has_component_transform(false), orientation_angle(0), has_general_transform(false)
{
    has_component_transform = false;
    translation[0]          = 0;
    translation[1]          = 0;
    translation[2]          = 0;
    scale[0]                = 0;
    scale[1]                = 0;
    scale[2]                = 0;
    orientation_angle       = 0;
    orientation_axis[0]     = 0;
    orientation_axis[1]     = 0;
    orientation_axis[2]     = 0;
    has_general_transform   = false;
    for (int i = 0; i < 16; i++) {
        transform[i] = 0;
    }

}

M3GTransformableStruct:: ~M3GTransformableStruct ()
{
}

std::ostream& operator<< (std::ostream& out, const M3GTransformableStruct& trans)
{
    out << "M3GTransformable: \n";
    out << "  has_component_transform = " << trans.has_component_transform << "\n";
    out << "  translation             = [" << trans.translation[0] << ", " << trans.translation[1]<< ", " << trans.translation[2] << "]\n";
    out << "  scale                   = [" << trans.scale[0] << ", " << trans.scale[1] << ", " << trans.scale[2] << "]\n";
    out << "  orientation_angle       = " << trans.orientation_angle << "\n";
    out << "  orientation_axis        = " << trans.orientation_axis  << "\n";
    out << "  has_general_transform   = " << trans.has_general_transform << "\n";
    out << "  transform               = [";
    for (int i = 0; i < 16; i++) {
        out << trans.transform[i] << ", ";
    }
    out << "]\n";
    return out;
}


M3GTriangleStripArrayStruct:: M3GTriangleStripArrayStruct () : encoding(0), start_index(0), indices(0), strip_lengths_count(0), strip_lengths(0)
{
    encoding            = 0;
    start_index         = 0;
    indices_count       = 0;
    indices             = 0;
    strip_lengths_count = 0;
    strip_lengths       = 0;
}


M3GTriangleStripArrayStruct:: ~M3GTriangleStripArrayStruct ()
{
    delete [] indices;
    delete [] strip_lengths;
}

std::ostream& operator<< (std::ostream& out, const M3GTriangleStripArrayStruct& tris)
{
    out << "M3GTriangleStripArrayStruct: \n";
    out << "  encoding      = " << (int)tris.encoding << "\n";
    out << "  start_index   = " << tris.start_index   << "\n";
    out << "  indices_count = " << tris.indices_count << "\n";
    out << "  indices       = " << tris.indices       << "\n";
    out << "  strip_lengths_count = " << tris.strip_lengths_count << "\n";
    out << "  strip_lengths = [";
    for (int i = 0; i < (int)tris.strip_lengths_count; i++) {
        out << tris.strip_lengths << ", ";
    }
    out << "]";
    return out;
}


M3GVertexArrayStruct:: M3GVertexArrayStruct () : component_size(0), component_count(0), encoding(0), vertex_count(0), char_components(0)
{
    component_size   = 0;
    component_count  = 0;
    encoding         = 0;
    vertex_count     = 0;
    char_components  = 0;
}


M3GVertexArrayStruct:: ~M3GVertexArrayStruct ()
{
    for (int i = 0; i < vertex_count; i++) {
        switch (component_size) {
        case 1: delete [] char_components[i]; break;
        case 2: delete [] short_components[i]; break;
        case 4: delete [] float_components[i]; break;
        }
    }
    switch (component_size) {
    case 1: delete [] char_components; break;
    case 2: delete [] short_components; break;
    case 4: delete [] float_components; break;
    }
}

std::ostream& operator<< (std::ostream& out, const M3GVertexArrayStruct& varry)
{
    out << "M3GVertexArrayStruct: \n";
    out << "  component_size  = " << varry.component_size  << "\n";
    out << "  component_count = " << varry.component_count << "\n";
    out << "  encoding        = " << varry.encoding        << "\n";
    out << "  vertex_count    = " << varry.vertex_count    << "\n";
    out << "  components      = [";
    for (int i = 0; i < varry.vertex_count; i++) {
        for (int j = 0; j < varry.component_count; j++) {
            switch (varry.component_size) {
            case 1: out << (int)varry.char_components[i][j] << ", "; break;
            case 2: out << varry.short_components[i][j]     << ", "; break;
            case 4: out << varry.float_components[i][j]     << ", "; break;
            }
        }
    }
    out << "]";
    return out;
}
 

M3GVertexBufferStruct:: M3GVertexBufferStruct () : default_color(0), positions_index(0), position_scale(0), normals_index(0), colors_index(0),
                                                   texcoord_array_count(0), texcoords_index(0), texcoord_scale(0)
{
    default_color        = 0;
    positions_index      = 0;
    position_scale       = 0;
    position_bias[0]     = 0;
    position_bias[1]     = 0;
    position_bias[2]     = 0;
    normals_index        = 0;
    colors_index         = 0;
    texcoord_array_count = 0;
    texcoords_index      = 0;
    texcoord_bias        = 0;
    texcoord_scale       = 0;
}


M3GVertexBufferStruct:: ~M3GVertexBufferStruct ()
{
    delete [] texcoords_index;
    delete [] texcoord_scale;
    for (int i = 0; i < (int)texcoord_array_count; i++) {
        delete [] texcoord_bias[i];
    }
    delete [] texcoord_bias;
}

std::ostream& operator<< (std::ostream& out, const M3GVertexBufferStruct& vbuf)
{
    out << "M3GVertexBufferStruct: \n";
    out << "  default_color        = 0x" << hex << vbuf.default_color << dec << "\n";
    out << "  positions_index      = "   << vbuf.positions_index      << "\n";
    out << "  position_scale       = "   << vbuf.position_scale       << "\n";
    out << "  position_bias        = ["  << vbuf.position_bias[0] << ", " << vbuf.position_bias[1] << ", " << vbuf.position_bias[2] << "]\n";
    out << "  normals_index        = "   << vbuf.normals_index        << "\n";
    out << "  colors_index         = "   << vbuf.colors_index         << "\n";
    out << "  texcoord_array_count = "   << vbuf.texcoord_array_count << "\n";
    for (int i = 0; i < (int)vbuf.texcoord_array_count; i++) {
        out << "  texcoords_index  = "   << vbuf.texcoords_index[i]   << "\n";
        out << "  texcoord_scale   = "   << vbuf.texcoord_scale[i]    << "\n";
        out << "  texcoord_bias    = ["  << vbuf.texcoord_bias[i][0]  << ", " << vbuf.texcoord_bias[i][1] << ", " << vbuf.texcoord_bias[i][2] << "]\n";
    }
    return out;
}


M3GWorldStruct:: M3GWorldStruct () : active_camera_index(0), background_index(0)
{
    active_camera_index = 0;
    background_index    = 0;

}

M3GWorldStruct:: ~M3GWorldStruct ()
{
}

std::ostream& operator<< (std::ostream& out, const M3GWorldStruct& wld)
{
    out << "M3GWorldStruct: \n";
    out << "  active_camera_index = " << wld.active_camera_index << "\n";
    out << "  background_index    = " << wld.background_index    << "\n";
    return out;
}
                        


