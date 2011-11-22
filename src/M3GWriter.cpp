#include "M3GWriter.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdarg>
#include <zlib.h>
#include <cassert>
using namespace std;
using namespace m3g;

// "JSR184"
const unsigned char id[12] = {0xab, 0x4a, 0x53, 0x52, 0x31, 0x38, 0x34, 0xbb, 0x0d, 0x0a, 0x1a, 0x0a};

M3GWriter:: M3GWriter (const char* name_) : name(name_), stream(0),
                                            compression_scheme(false),
                                            object_index(1),
                                            object_type(0),
                                            start_of_section(0),
                                            start_of_objects(0),
                                            start_of_object(0),
                                            position_of_header_section(0),
                                            position_of_header(0),
                                            position_of_header_checksum(0)
{
    stream = new OutMemoryStream (name);
}

M3GWriter:: ~M3GWriter ()
{
    if (position_of_header) {
        unsigned int file_size = stream->tellp ();

        stream->seekp (position_of_header+3);
        putUInt32 (file_size);   // total file size
        putUInt32 (file_size);   // aproximate content size (same as above)
        unsigned int init_value = adler32 (0, NULL, 0);
        unsigned int checksum   = adler32 (init_value, 
                                           stream->pointer(position_of_header_section),
                                           position_of_header_checksum - position_of_header_section);

        stream->seekp (position_of_header_checksum);
        putUInt32  (checksum);
    }

    delete stream;
    stream = 0;
}

void M3GWriter:: writeID ()
{
    stream->write ((char*)id, 12);
}

void M3GWriter:: startSection (int compression)
{
    start_of_section   = stream->tellp();
    start_of_objects   = stream->tellp() + 9;
    compression_scheme = compression;

    // dummy, section header
    putByte   (0);   // 0:uncompress, 1:comress
    putUInt32 (0);   // total section length
    putUInt32 (0);   // uncompressed objects length
}

void M3GWriter:: endSection ()
{
    int end_of_objects   = stream->tellp ();
    int objects_length   = end_of_objects - start_of_objects;
    int section_length   = objects_length + 13;

    // compress if needed
    if (compression_scheme == 1) {
        unsigned long compressed_length = compressBound (objects_length);
        char* buf = new char[compressed_length];
        int ret;
        ret = compress ((Bytef*)buf,
                        (uLongf*)&compressed_length, 
                        (const Bytef*)stream->pointer(start_of_objects),
                        objects_length);
        assert (ret == Z_OK);

        stream->erase  (start_of_objects, objects_length);
        stream->insert (start_of_objects, buf, compressed_length);

        end_of_objects = start_of_objects + compressed_length;
        section_length = compressed_length + 13;

        delete [] buf;
    }

    stream->seekp (start_of_section);
    putByte       (compression_scheme);   // 1:compress
    putUInt32     (section_length);       // total section length
    putUInt32     (objects_length);       // uncompressed objects length

    stream->seekp (end_of_objects);

    unsigned int init_value = adler32 (0, NULL, 0);
    unsigned int checksum   = adler32 (init_value,
                                        stream->pointer(start_of_section),
                                        section_length-4);
    putUInt32  (checksum);
    
}

void M3GWriter:: startObject (int type, unsigned int* index)
{
    start_of_object = stream->tellp ();
    object_type     = type;

    if (index)
        *index = object_index;

    // dummy, object header
    putByte   (0);    // object type
    putUInt32 (0);    // object length
}

void M3GWriter:: endObject ()
{
    int end_of_object = stream->tellp ();
    int object_size   = end_of_object - (start_of_object + 5);

    stream->seekp (start_of_object);
    putByte       (object_type);    // object type
    putUInt32     (object_size);    // object length (not including header)

    stream->seekp (end_of_object);

    object_index += 1;
}

void M3GWriter:: writeHeader (const M3GHeaderStruct& header)
{
    assert (!(header.version_major == 0 && header.version_minor == 0));
    assert (compression_scheme == 0);

    position_of_header_section = start_of_section;
    position_of_header         = stream->tellp ();

    putByte    (header.version_major);        // version major
    putByte    (header.version_minor);        // version minor
    putBoolean (header.has_external_references);  // external reference
    putUInt32  (0);                           // total file size
    putUInt32  (0);                           // approximate file size
    putString  (header.authoring_field);      // authoring fiels

    position_of_header_checksum = stream->tellp ();
}

void M3GWriter:: writeExternalReference   (const M3GExternalReferenceStruct&   external_reference )
{
    putString (external_reference.uri);
}

void M3GWriter:: writeAnimationController (const M3GAnimationControllerStruct& animation_controller)
{
    putFloat32 (animation_controller.speed);
    putFloat32 (animation_controller.weight);
    putInt32   (animation_controller.active_interval_start  );
    putInt32   (animation_controller.active_interval_end    );
    putFloat32 (animation_controller.reference_sequence_time);
    putInt32   (animation_controller.reference_world_time   );
}

void M3GWriter:: writeAnimationTrack (const M3GAnimationTrackStruct& animation_track)
{
    putUInt32 (animation_track.keyframe_sequence_index);
    putUInt32 (animation_track.animation_controller_index);
    putUInt32 (animation_track.property_id);
}

void M3GWriter:: writeAppearance (const M3GAppearanceStruct& appearance)
{
    putByte   (appearance.layer);
    putUInt32 (appearance.compositing_mode_index);
    putUInt32 (appearance.fog_index);
    putUInt32 (appearance.polygon_mode_index);
    putUInt32 (appearance.material_index);
    putUInt32 (appearance.textures_count);
    for (int i = 0; i < (int)appearance.textures_count; i++) {
        putUInt32 (appearance.textures_index[i]);
    }
}

void M3GWriter:: writeBackground (const M3GBackgroundStruct& background)
{
    putRGBA    (background.background_color);
    putUInt32  (background.background_image_index);
    putByte    (background.background_image_mode_x);
    putByte    (background.background_image_mode_y);
    putUInt32  (background.crop_x);
    putUInt32  (background.crop_y);
    putUInt32  (background.crop_width);
    putUInt32  (background.crop_height);
    putBoolean (background.depth_clear_enabled);
    putBoolean (background.color_clear_enabled);
}

void M3GWriter:: writeCamera (const M3GCameraStruct& camera)
{
    putByte (camera.projection_type);
    if (camera.projection_type == M3GCameraStruct::GENERIC) {
        for (int i = 0; i < 16; i++) {
            putFloat32 (camera.matrix[i]);
        }
    }
    else {
        putFloat32 (camera.fovy);
        putFloat32 (camera.aspect_ratio);
        putFloat32 (camera.near);
        putFloat32 (camera.far);
    }
}

void M3GWriter:: writeCompositingMode (const M3GCompositingModeStruct& comp_mode)
{
    putBoolean (comp_mode.depth_test_enabled);
    putBoolean (comp_mode.depth_write_enabled);
    putBoolean (comp_mode.color_write_enabled);
    putBoolean (comp_mode.alpha_write_enabled);
    putByte    (comp_mode.blending);
    putByte    (comp_mode.alpha_threshold);
    putFloat32 (comp_mode.depth_offset_factor);
    putFloat32 (comp_mode.depth_offset_units);
}


void M3GWriter:: writeFog (const M3GFogStruct& fog)
{
    putRGB    (fog.color);
    putByte   (fog.mode);
    if (fog.mode == M3GFogStruct::EXPONENTIAL) {
        putFloat32 (fog.density);
    }
    else if (fog.mode == M3GFogStruct::LINEAR) {
        putFloat32 (fog.near);
        putFloat32 (fog.far);
    }
}

void M3GWriter:: writeGroup (const M3GGroupStruct& group)
{
    putUInt32 (group.children_index_count);
    for (int i = 0; i < (int)group.children_index_count; i++) {
        putUInt32 (group.children_index[i]);
    }
}

void M3GWriter:: writeImage2D (const M3GImage2DStruct& image)
{
    int count;

    putByte    (image.format);
    putBoolean (image.is_mutable);
    putUInt32  (image.width);
    putUInt32  (image.height);
    putUInt32  (image.palette_count);

    count = image.palette_count;
    for (int i = 0; i < count; i++) {
        putByte (image.palette[i]);
    }
    
    putUInt32 (image.pixels_count);
    putByteArray ((char*)image.pixels, image.pixels_count);
}

void M3GWriter:: writeIndexBuffer (const M3GIndexBufferStruct& ibuf)
{
    // nothing to do.
}

void M3GWriter:: writeLight (const M3GLightStruct& light)
{
    putFloat32 (light.attenuation_constant);
    putFloat32 (light.attenuation_linear);
    putFloat32 (light.attenuation_quadratic);
    putRGB     (light.color);
    putByte    (light.mode);
    putFloat32 (light.intensity);
    putFloat32 (light.spot_angle);
    putFloat32 (light.spot_exponent);
}

void M3GWriter:: writeMaterial (const M3GMaterialStruct& material)
{
    putRGB     (material.ambient_color);
    putRGBA    (material.diffuse_color);
    putRGB     (material.emissive_color);
    putRGB     (material.specular_color);
    putFloat32 (material.shininess);
    putBoolean (material.vertex_color_tracking_enabled);
}

void M3GWriter:: writeMesh (const M3GMeshStruct& mesh)
{
    putUInt32 (mesh.vertex_buffer_index);
    putUInt32 (mesh.submesh_count);
    for (int i = 0; i < (int)mesh.submesh_count; i++) {
        putUInt32 (mesh.index_buffer_index[i]);
        putUInt32 (mesh.appearance_index[i]);
    }
}

void M3GWriter:: writeMorphingMesh (const M3GMorphingMeshStruct& mesh)
{
    putUInt32 (mesh.morph_target_count);
    int count = mesh.morph_target_count;
    for (int i = 0; i < count; i++) {
        putUInt32  (mesh.morph_target_index[i]);
        putFloat32 (mesh.initial_weight[i]);
    }
}

void M3GWriter:: writeNode (const M3GNodeStruct& node)
{
    putBoolean (node.enable_rendering);
    putBoolean (node.enable_picking);
    putByte    (node.alpha_factor);
    putUInt32  (node.scope);
    putBoolean (node.has_alignment);
    if (node.has_alignment) {
        putByte (node.z_target);
        putByte (node.y_target);
        putUInt32 (node.z_reference_index);
        putUInt32 (node.y_reference_index);
    }
}


void M3GWriter:: writeObject3D (const M3GObject3DStruct& object3D)
{
    putUInt32 (object3D.user_id);
    putUInt32 (object3D.animation_tracks_count);
    for (int i = 0; i < (int)object3D.animation_tracks_count; i++) {
        putUInt32 (object3D.animation_tracks_index[i]);
    }
    putUInt32 (object3D.user_parameter_count);
    for (int i = 0; i < (int)object3D.user_parameter_count; i++) {
        putUInt32 (object3D.parameter_id[i]);
        putUInt32 (object3D.parameter_value_length[i]);
        putByteArray (object3D.parameter_value[i], object3D.parameter_value_length[i]);
    }
}

void M3GWriter:: writePolygonMode (const M3GPolygonModeStruct& poly_mode)
{
    putByte (poly_mode.culling);
    putByte (poly_mode.shading);
    putByte (poly_mode.winding);
    putBoolean (poly_mode.two_sided_lighting_enabled);
    putBoolean (poly_mode.local_camera_lighting_enabled);
    putBoolean (poly_mode.perspective_correction_enabled);
}


void M3GWriter:: writeSkinnedMesh (const M3GSkinnedMeshStruct& mesh)
{
    putUInt32 (mesh.skeleton_index);
    putUInt32 (mesh.transform_reference_count);
    int count = mesh.transform_reference_count;
    for (int i = 0; i < count; i++) {
        putUInt32 (mesh.transform_node_index[i]);
        putUInt32 (mesh.first_vertex[i]        );
        putUInt32 (mesh.vertex_count[i]        );
        putInt32  (mesh.weight[i]              );
    }
}


void M3GWriter:: writeSprite3D (const M3GSprite3DStruct& sprite)
{
    putUInt32  (sprite.image_index);
    putUInt32  (sprite.appearance_index);
    putBoolean (sprite.is_scaled);
    putInt32   (sprite.crop_x);
    putInt32   (sprite.crop_y);
    putInt32   (sprite.crop_width);
    putInt32   (sprite.crop_height);
}

void M3GWriter:: writeTexture2D (const M3GTexture2DStruct& texture)
{
    putUInt32 (texture.image_index);
    putRGB    (texture.blend_color);
    putByte   (texture.blending);
    putByte   (texture.wrapping_s);
    putByte   (texture.wrapping_t);
    putByte   (texture.level_filter);
    putByte   (texture.image_filter);

}

/**
 * (*1) 回転軸成分に-0.0fがあるとMascotCupsule V4のM3G ToolKit v4.5(update 2008/11/07)が強制終了するので
 *      その無理やりな回避コード。向こうが直したら消す。
 *      http://www.mascotcapsule.com/ja/alldata/tools/#tk_m3gtk
 */
void M3GWriter:: writeTransformable (const M3GTransformableStruct& transformable)
{
    putBoolean (transformable.has_component_transform);
    bool has = transformable.has_component_transform;
    if (has) {
        float* axis = const_cast<float*>(transformable.orientation_axis);
        for (int i = 0; i < 3; i++) {
            if (axis[i] == -0.0f) {
                axis[i] = +0.0f;  // (*1)
            }
        }
        putFloat32 (transformable.translation[0]);
        putFloat32 (transformable.translation[1]);
        putFloat32 (transformable.translation[2]);
        putFloat32 (transformable.scale[0]);
        putFloat32 (transformable.scale[1]);
        putFloat32 (transformable.scale[2]);
        putFloat32 (transformable.orientation_angle);
        putFloat32 (transformable.orientation_axis[0]);
        putFloat32 (transformable.orientation_axis[1]);
        putFloat32 (transformable.orientation_axis[2]);
    }
    putBoolean (transformable.has_general_transform);
    has = transformable.has_general_transform;
    if (has) {
        for (int i = 0; i < 16; i++) {
            putFloat32 (transformable.transform[i]);
        }
    }
}

void M3GWriter:: writeTriangleStripArray (const M3GTriangleStripArrayStruct& tris)
{
    putByte (tris.encoding);
    switch (tris.encoding) {
    case M3GTriangleStripArrayStruct::ENCODING_0: {
        putUInt32 (tris.start_index);
        break;
    }
    case M3GTriangleStripArrayStruct::ENCODING_1: {
        unsigned char start_index = tris.start_index;
        putByte (start_index);
        break;
    }
    case M3GTriangleStripArrayStruct::ENCODING_2: {
        unsigned short start_index = tris.start_index;
        putUInt16 (start_index);
        break;
    }    
    case M3GTriangleStripArrayStruct::ENCODING_128: {
        putUInt32 (tris.indices_count);
        int count = tris.indices_count;
        for (int i = 0; i < count; i++) {
            putUInt32 (tris.indices[i]);
        }
        break;
    }    
    case M3GTriangleStripArrayStruct::ENCODING_129: {
        putUInt32 (tris.indices_count);
        int count = tris.indices_count;
        for (int i = 0; i < count; i++) {
            unsigned char index = tris.indices[i];
            putByte (index);
        }
        break;
    }    
    case M3GTriangleStripArrayStruct::ENCODING_130: {
        putUInt32 (tris.indices_count);
        int count = tris.indices_count;
        for (int i = 0; i < count; i++) {
            unsigned short index = tris.indices[i];
            putUInt16 (index);
        }
        break;
    }    

    }

    putUInt32     (tris.strip_lengths_count);
    for (int i = 0; i < (int)tris.strip_lengths_count; i++) {
        putUInt32 (tris.strip_lengths[i]);
    }

    /*
    unsigned char   encoding;
    unsigned int    start_index;
    unsigned int*   indices;
    unsigned int    strip_length_count;
    unsigned int*   strip_length;
    */

}


void M3GWriter:: writeKeyframeSequence (const M3GKeyframeSequenceStruct& keyframe_sequence)
{
    int keyframe_count  = keyframe_sequence.keyframe_count;
    int component_count = keyframe_sequence.component_count;

    putByte   (keyframe_sequence.interpolation);
    putByte   (keyframe_sequence.repeat_mode);
    putByte   (keyframe_sequence.encoding);
    putUInt32 (keyframe_sequence.duration);
    putUInt32 (keyframe_sequence.valid_range_first);
    putUInt32 (keyframe_sequence.valid_range_last);
    putUInt32 (keyframe_sequence.component_count);
    putUInt32 (keyframe_sequence.keyframe_count);

    switch (keyframe_sequence.encoding) {
    case M3GKeyframeSequenceStruct::ENCODING_0: {
        for (int i = 0; i < keyframe_count; i++) {
            putUInt32 (keyframe_sequence.time[i]);
            for (int j = 0; j < component_count; j++) {
                putFloat32 (keyframe_sequence.vector_value[i][j]);
            }
        }
        break;
    }
    case M3GKeyframeSequenceStruct::ENCODING_1: {
        float* bias  = calcBias  (keyframe_sequence.vector_value, keyframe_count, component_count);
        float* scale = calcScale (keyframe_sequence.vector_value, keyframe_count, component_count);
        putFloat32Array (bias,  component_count);
        putFloat32Array (scale, component_count);
        for (int i = 0; i < keyframe_count; i++) {
            putUInt32 (keyframe_sequence.time[i]);
            for (int j = 0; j < component_count; j++) {
                unsigned char value = (keyframe_sequence.vector_value[i][j] - bias[j]) / scale[j] * 255;
                putByte (value);
            }
        }
        delete [] bias;
        delete [] scale;
        break;
    }
    case M3GKeyframeSequenceStruct::ENCODING_2: {
    }
        float* bias  = calcBias  (keyframe_sequence.vector_value, keyframe_count, component_count);
        float* scale = calcScale (keyframe_sequence.vector_value, keyframe_count, component_count);
        putFloat32Array (bias,  component_count);
        putFloat32Array (scale, component_count);
        for (int i = 0; i < keyframe_count; i++) {
            putUInt32 (keyframe_sequence.time[i]);
            for (int j = 0; j < component_count; j++) {
                unsigned short value = (keyframe_sequence.vector_value[i][j] - bias[j]) / scale[j] * 65535;
                putUInt16 (value);
            }
        }
        delete [] bias;
        delete [] scale;
        break;
    }

}

void M3GWriter:: writeVertexArray (const M3GVertexArrayStruct& varry)
{
    putByte   (varry.component_size);
    putByte   (varry.component_count);
    putByte   (varry.encoding);
    putUInt16 (varry.vertex_count);
    int vertex_count    = varry.vertex_count;
    int component_count = varry.component_count;
    int component_size  = varry.component_size;
    int encoding        = varry.encoding;
    int delta_base      = 0;
    float delta_base_f  = 0;
    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < component_count; j++) {
            switch (component_size) {
            case 1:
                if (encoding == 0) {
                    putByte (varry.char_components[i][j]);
                } else {
                    putByte (varry.char_components[i][j] - delta_base);
                    delta_base = varry.char_components[i][j] - delta_base;
                }
                break;
            case 2:
                if (encoding == 0) {
                    putUInt16 (varry.short_components[i][j]);
                } else {
                    putUInt16 (varry.short_components[i][j] - delta_base);
                    delta_base = varry.short_components[i][j] - delta_base;
                }
                break;
            case 4:
                if (encoding == 0) {
                    putFloat32 (varry.float_components[i][j]);
                } else {
                    putFloat32 (varry.float_components[i][j] - delta_base_f);
                    delta_base_f = varry.float_components[i][j] - delta_base_f;
                }
                break;
            }
        }
    }

}

void M3GWriter:: writeVertexBuffer (const M3GVertexBufferStruct& vbuf)
{
    putRGBA    (vbuf.default_color);
    putUInt32  (vbuf.positions_index);
    putFloat32 (vbuf.position_bias[0]);
    putFloat32 (vbuf.position_bias[1]);
    putFloat32 (vbuf.position_bias[2]);
    putFloat32 (vbuf.position_scale);
    putUInt32  (vbuf.normals_index);
    putUInt32  (vbuf.colors_index);
    putUInt32  (vbuf.texcoord_array_count);
    int count = vbuf.texcoord_array_count;
    for (int i = 0; i < count; i++) {
        putUInt32 (vbuf.texcoords_index[i]);
        putFloat32 (vbuf.texcoord_bias[i][0]);
        putFloat32 (vbuf.texcoord_bias[i][1]);
        putFloat32 (vbuf.texcoord_bias[i][2]);
        putFloat32 (vbuf.texcoord_scale[i]);
    }
}

void M3GWriter:: writeWorld (const M3GWorldStruct& world)
{
    putUInt32 (world.active_camera_index);
    putUInt32 (world.background_index);
}

void M3GWriter:: writeString (const char* format, ...)
{
   char buf[256];
   va_list args;
   va_start (args, format);
   vsnprintf (buf, 256, format, args);
   va_end (args);
   
   putString (buf);
}

void M3GWriter:: putBoolean   (bool value)
{
    stream->write ((char*)&value, 1);
}

void M3GWriter:: putByte    (char value)
{
    stream->write (&value, 1);
}

void M3GWriter:: putUInt16  (unsigned short value)
{
    stream->write ((char*)&value, 2);
}

void M3GWriter:: putInt32  (int value)
{
    stream->write ((char*)&value, 4);
}

void M3GWriter:: putUInt32  (unsigned int value)
{
    stream->write ((char*)&value, 4);
}

void M3GWriter:: putFloat32 (float value)
{
    stream->write ((char*)&value, 4);
}

void M3GWriter:: putRGB (unsigned int value)
{
    unsigned char r = (value & 0x00ff0000) >> 16;
    unsigned char g = (value & 0x0000ff00) >> 8;
    unsigned char b = (value & 0x000000ff) >> 0;
    stream->write ((char*)&r, 1);
    stream->write ((char*)&g, 1);
    stream->write ((char*)&b, 1);
}

void M3GWriter:: putRGBA (unsigned int value)
{
    unsigned char a = (value & 0xff000000) >> 24;
    unsigned char r = (value & 0x00ff0000) >> 16;
    unsigned char g = (value & 0x0000ff00) >> 8;
    unsigned char b = (value & 0x000000ff) >> 0;
    stream->write ((char*)&r, 1);
    stream->write ((char*)&g, 1);
    stream->write ((char*)&b, 1);
    stream->write ((char*)&a, 1);
}


void M3GWriter:: putByteArray (const char* value, int size)
{
    stream->write (value, size);
}

void M3GWriter:: putUInt32Array (const unsigned int* value, int size)
{
    stream->write ((const char*)value, size*sizeof(unsigned int));
}

void M3GWriter:: putFloat32Array (const float* value, int size)
{
    stream->write ((const char*)value, size*sizeof(float));
}

void M3GWriter:: putString (const char* str)
{
    if (str)
        stream->write (str, strlen(str)+1);
    else
        stream->write ("", 1);
}


float* M3GWriter:: calcBias (float** vector_value, int keyframe_count, int component_count) const
{
    float* min   = new float[component_count];
    for (int j = 0; j < component_count; j++) {
        min[j] = vector_value[0][j];
        for (int i = 0; i < keyframe_count; i++) {
            min[j] = std::min (min[j], vector_value[i][j]);
        }
    }
    return min;
}

float* M3GWriter:: calcScale (float** vector_value, int keyframe_count, int component_count) const
{
    float* min   = new float[component_count];
    float* max   = new float[component_count];
    float* scale = new float[component_count];
    for (int j = 0; j < component_count; j++) {
        min[j] = vector_value[0][j];
        max[j] = vector_value[0][j];
        for (int i = 0; i < keyframe_count; i++) {
            min[j] = std::min (min[j], vector_value[i][j]);
            max[j] = std::max (max[j], vector_value[i][j]);
        }
    }
    for (int j = 0; j < component_count; j++) {
        scale[j] = max[j] - min[j];
    }
    delete [] min;
    delete [] max;
    return scale;
}


OutMemoryStream:: OutMemoryStream (const char* name_) : cur(0), name(name_)
{
    assert (name != 0);
}

OutMemoryStream:: ~OutMemoryStream ()
{
    if ((int)buf.size() > 0) {
        ofstream ofs (name, ios::out|ios::binary);
        assert (ofs != 0);
        ofs.write (&buf[0], buf.size());
    }
}

void OutMemoryStream:: write (const char* p, int size)
{
    assert (p != 0);
    assert (size > 0);

    if (cur + size > (int)buf.size()) {
        buf.resize (cur + size, 0);
    }

    copy (p, p+size, buf.begin()+cur);
    cur += size;
}

unsigned int OutMemoryStream:: tellp () const
{
    return cur;
}

void OutMemoryStream:: seekp (int pos)
{
    assert (pos >= 0 && pos <= (int)buf.size());

    cur = pos;
}

int OutMemoryStream:: size () const
{
    return buf.size();
}

void OutMemoryStream:: erase (int pos, int size)
{
    assert (pos >= 0 && pos < (int)buf.size());
    assert (size >= 0 && size <= (int)buf.size());
    assert (pos+size <= (int)buf.size());

    buf.erase (buf.begin()+pos, buf.begin()+pos+size);
}

void OutMemoryStream:: insert (int pos, const char* p, int size)
{
    assert (pos >= 0 && pos <= (int)buf.size());
    assert (p != 0);
    assert (size > 0);

    buf.insert (buf.begin()+pos, p, p+size);
}


const unsigned char* OutMemoryStream:: pointer (int offset) const
{
    assert (offset >= 0 && offset < (int)buf.size());
    return (const unsigned char*)&buf[offset];
}

