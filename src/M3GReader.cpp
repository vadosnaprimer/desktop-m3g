#include "M3GReader.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <zlib.h>
using namespace std;



M3GReader:: M3GReader (const char* name) : stream(0), file_name(name), object_index(1), start_of_section(0), size_of_object(0),
                                           total_section_length(0), uncompressed_objects_length(0)
{
    stream = new InMemoryStream (name);
}

M3GReader:: M3GReader (const char* p, int size)
{
    stream = new InMemoryStream (p, size);
}

M3GReader::     ~M3GReader ()
{
    delete stream;
    stream = 0;
}

const unsigned char* M3GReader:: readID ()
{
    static unsigned char buf[12];
    stream->read ((char*)buf, 12);
    return buf;
}

/**
 * 
 */
bool M3GReader:: startSection ()
{
    if (stream->eof()) {
        return false;
    }

    start_of_section = stream->tellg ();

    char compression_scheme      = getByte();
    total_section_length         = getUInt32();
    uncompressed_objects_length  = getUInt32();
    //cout << "compression = " << (int)compression_scheme << "\n";
    //cout << "total_section_length = " << total_section_length << "\n";
    //cout << "uncompressed_length = " << uncompressed_length << "\n";
    if (compression_scheme != 0 && compression_scheme != 1) {
        cout << "M3GReader: first byte of section (compression_sceme) is invalid, comp=" <<  (int)compression_scheme << ")\n";
        cout << "  Maybe, invalid use of M3GReader.\n";
        abort ();
    }

    assert (compression_scheme == 0 || compression_scheme == 1);
    assert (total_section_length >= 13);
    assert (uncompressed_objects_length  >= 0);

    // チェックサム
    stream->seekg (start_of_section + total_section_length - 4);
    unsigned int file_checksum  = getUInt32();
    unsigned int checksum       = adler32 ((unsigned char*)stream->pointer() + start_of_section,
                                           total_section_length - 4);
    if (checksum != file_checksum) {
        cout << "M3GReader: Checksum error.\n";
        cout << " Perhaps, this file is broken.\n";
        abort ();
    }

    stream->seekg (start_of_section + 9);

    if (compression_scheme ==  1) {
        char* buf = new char [uncompressed_objects_length];
        uncompress ((Bytef*)buf,
                    (uLongf*)&uncompressed_objects_length,
                    (const Bytef*)stream->pointer() + start_of_section + 9,
                    (uLong)(total_section_length-13));
        stream->erase  (start_of_section + 9, total_section_length-13);
        stream->insert (start_of_section + 9, buf, uncompressed_objects_length);
        delete [] buf;
    }

    return true;
}


void M3GReader:: endSection ()
{
    // read checksum, 
    // because it is already tested, do nothing
    getUInt32();

}

bool M3GReader:: startObject  (int* object_type, unsigned int* object_index_out)
{
    if (stream->tellg() - (start_of_section + 9) >= uncompressed_objects_length) {
        return false;
    }

    start_of_object  = stream->tellg ();


    *object_type     = (unsigned char)getByte();
    size_of_object   = getUInt32();

    if (object_index_out) {
        *object_index_out   = object_index;
    }
    object_index += 1;
    
    return true;
}

void M3GReader:: endObject  ()
{
    unsigned int end_of_object = stream->tellg ();

    if (end_of_object - (start_of_object + 5) != size_of_object) {
        cout << "M3GReader: you don't read object collectry\n";
        cout << "           it should be your miss.\n";
        cout << "  file's size_of_object  = " << size_of_object  << "\n";
        cout << "  your   start_of_object = " << start_of_object << "\n";
        cout << "  your   end_of_object   = " << end_of_object   << "\n";
        abort ();
    }

}


void M3GReader:: readHeader (M3GHeaderStruct* header)
{
    header->version_major            = getByte ();
    header->version_minor            = getByte ();
    header->has_external_references  = getBoolean ();
    header->total_file_size          = getUInt32 ();
    header->approximate_content_size = getUInt32 ();
    header->authoring_field          = getString ();
}

void M3GReader:: readExternalReference (M3GExternalReferenceStruct* ex_ref)
{
    ex_ref->uri = getString ();
}

void M3GReader:: readAnimationController (M3GAnimationControllerStruct* anim_controller)
{
    anim_controller->speed                   = getFloat32 ();
    anim_controller->weight                  = getFloat32 ();
    anim_controller->active_interval_start   = getInt32   ();
    anim_controller->active_interval_end     = getInt32   ();
    anim_controller->reference_sequence_time = getFloat32 ();
    anim_controller->reference_world_time    = getInt32   ();
}


void M3GReader:: readAnimationTrack (M3GAnimationTrackStruct* anim_track)
{
    anim_track->keyframe_sequence_index    = getUInt32 ();
    anim_track->animation_controller_index = getUInt32 ();
    anim_track->property_id                = getUInt32 ();
}

void M3GReader:: readAppearance (M3GAppearanceStruct* appearance)
{
    appearance->layer                  = getByte ();
    appearance->compositing_mode_index = getUInt32 ();
    appearance->fog_index              = getUInt32 ();
    appearance->polygon_mode_index     = getUInt32 ();
    appearance->material_index         = getUInt32 ();
    appearance->textures_count         = getUInt32 ();
    
    int count = appearance->textures_count;
    appearance->textures_index = new unsigned int[count];
    for (int i = 0; i < count; i++) {
        appearance->textures_index[i] = getUInt32 ();
    }
    
}

void M3GReader:: readBackground (M3GBackgroundStruct* background)
{
    background->background_color        = getRGBA   ();
    background->background_image_index  = getUInt32 ();
    background->background_image_mode_x = getByte   ();
    background->background_image_mode_y = getByte   ();
    background->crop_x                  = getUInt32 ();
    background->crop_y                  = getUInt32 ();
    background->crop_width              = getUInt32 ();
    background->crop_height             = getUInt32 ();
    background->depth_clear_enabled     = getBoolean ();
    background->color_clear_enabled     = getBoolean ();
}

void M3GReader:: readCamera (M3GCameraStruct* camera)
{
    camera->projection_type = getByte ();
    if (camera->projection_type == M3GCameraStruct::GENERIC) {
        for (int i = 0; i < 16; i++) {
            camera->matrix[i] = getFloat32 ();
        }
    }
    else {
        camera->fovy         = getFloat32 ();
        camera->aspect_ratio = getFloat32 ();
        camera->near         = getFloat32 ();
        camera->far          = getFloat32 ();
    }
}

void M3GReader:: readCompositingMode (M3GCompositingModeStruct* comp_mode)
{
    comp_mode->depth_test_enabled  = getBoolean ();
    comp_mode->depth_write_enabled = getBoolean ();
    comp_mode->color_write_enabled = getBoolean ();
    comp_mode->alpha_write_enabled = getBoolean ();
    comp_mode->blending            = getByte    ();
    comp_mode->alpha_threshold     = getByte    ();
    comp_mode->depth_offset_factor = getFloat32 ();
    comp_mode->depth_offset_units  = getFloat32 ();
}

void M3GReader:: readFog (M3GFogStruct* fog)
{
    fog->color = getRGB  ();
    fog->mode  = getByte ();
    if (fog->mode == M3GFogStruct::EXPONENTIAL) {
        fog->density = getFloat32 ();
    }
    else if (fog->mode == M3GFogStruct::LINEAR) {
        fog->near = getFloat32 ();
        fog->far  = getFloat32 ();
    }
}

void M3GReader:: readGroup (M3GGroupStruct* group)
{
    group->children_index_count = getUInt32 ();

    int count = group->children_index_count;
    group->children_index = new unsigned int[count];
    for (int i = 0; i < count; i++) {
        group->children_index[i] = getUInt32 ();
    }
}


void M3GReader:: readImage2D (M3GImage2DStruct* image)
{
    image->format        = getByte    ();
    image->is_mutable    = getBoolean ();
    image->width         = getUInt32  ();
    image->height        = getUInt32  ();

    if (!image->is_mutable) {
        image->palette_count = getUInt32     ();
        image->palette       = getUByteArray (image->palette_count);
        image->pixels_count  = getUInt32     ();
        image->pixels        = getUByteArray (image->pixels_count);
    }
}

void M3GReader:: readIndexBuffer (M3GIndexBufferStruct* ibuf)
{
    // nothing to do.
}

void M3GReader:: readKeyframeSequence (M3GKeyframeSequenceStruct* keyframe_sequence)
{
    keyframe_sequence->interpolation     = getByte ();
    keyframe_sequence->repeat_mode       = getByte ();
    keyframe_sequence->encoding          = getByte ();
    keyframe_sequence->duration          = getUInt32 ();
    keyframe_sequence->valid_range_first = getUInt32 ();
    keyframe_sequence->valid_range_last  = getUInt32 ();
    keyframe_sequence->component_count   = getUInt32 ();
    keyframe_sequence->keyframe_count    = getUInt32 ();

    int keyframe_count  = keyframe_sequence->keyframe_count;
    int component_count = keyframe_sequence->component_count;

    switch (keyframe_sequence->encoding) {
    case M3GKeyframeSequenceStruct::ENCODING_0: {
        keyframe_sequence->time         = new unsigned int[keyframe_count];
        keyframe_sequence->vector_value = new float*      [keyframe_count];
        for (int i = 0; i < keyframe_count; i++) {
            keyframe_sequence->time[i]         = getUInt32 ();
            keyframe_sequence->vector_value[i] = getFloat32Array (component_count);
        }
        break;
    }
    case M3GKeyframeSequenceStruct::ENCODING_1: {
        float* bias  = getFloat32Array (component_count);
        float* scale = getFloat32Array (component_count);
        keyframe_sequence->time         = new unsigned int[keyframe_count];
        keyframe_sequence->vector_value = new float*      [keyframe_count];
        for (int i = 0; i < keyframe_count; i++) {
            keyframe_sequence->time[i]            = getUInt32 ();
            keyframe_sequence->vector_value[i]    = new float[component_count];
            unsigned char* vector_value           = (unsigned char*)getByteArray (component_count);
            for (int j = 0; j < component_count; j++) {
                keyframe_sequence->vector_value[i][j] = (vector_value[j]/255.f * scale[j] + bias[j]);
            }
            delete [] vector_value;
        }
        delete [] bias;
        delete [] scale;
        break;
    }
    case M3GKeyframeSequenceStruct::ENCODING_2: {
        float* bias  = getFloat32Array (component_count);
        float* scale = getFloat32Array (component_count);
        keyframe_sequence->time         = new unsigned int[keyframe_count];
        keyframe_sequence->vector_value = new float*      [keyframe_count];
        for (int i = 0; i < keyframe_count; i++) {
            keyframe_sequence->time[i]            = getUInt32 ();
            keyframe_sequence->vector_value[i]    = new float[component_count];
            unsigned short* vector_value           = (unsigned short*)getUInt16Array (component_count);
            for (int j = 0; j < component_count; j++) {
                keyframe_sequence->vector_value[i][j] = (vector_value[j]/65535.f * scale[j] + bias[j]);
            }
            delete [] vector_value;
        }
        delete [] bias;
        delete [] scale;
        break;
    }
    }

}

void M3GReader:: readLight (M3GLightStruct* light)
{
    light->attenuation_constant  = getFloat32 ();
    light->attenuation_linear    = getFloat32 ();
    light->attenuation_quadratic = getFloat32 ();
    light->color                 = getRGB     ();
    light->mode                  = getByte    ();
    light->intensity             = getFloat32 ();
    light->spot_angle            = getFloat32 ();
    light->spot_exponent         = getFloat32 ();
}

void M3GReader:: readMaterial (M3GMaterialStruct* material)
{
    material->ambient_color           = getRGB  ();
    material->diffuse_color           = getRGBA ();
    material->emissive_color          = getRGB  ();
    material->specular_color          = getRGB  ();
    material->shininess               = getFloat32 ();
    material->vertex_color_tracking_enabled = getBoolean ();
}


void M3GReader:: readMesh (M3GMeshStruct* mesh)
{
    mesh->vertex_buffer_index = getUInt32 ();
    mesh->submesh_count = getUInt32 ();
    int count = mesh->submesh_count;
    mesh->index_buffer_index = new unsigned int[count];
    mesh->appearance_index   = new unsigned int[count];
    for (int i = 0; i < count; i++) {
        mesh->index_buffer_index[i] = getUInt32 ();
        mesh->appearance_index[i]   = getUInt32 ();
    }
}

void M3GReader:: readMorphingMesh (M3GMorphingMeshStruct* mesh)
{
    mesh->morph_target_count = getUInt32 ();
    int count = mesh->morph_target_count;
    mesh->morph_target_index = new unsigned int [count];
    mesh->initial_weight     = new float [count];
    for (int i = 0; i < count; i++) {
        mesh->morph_target_index[i]   = getUInt32 ();
        mesh->initial_weight[i] = getFloat32 ();
    }
}

void M3GReader:: readNode (M3GNodeStruct* node)
{
    node->enable_rendering = getBoolean ();
    node->enable_picking   = getBoolean ();
    node->alpha_factor     = getUByte   ();
    node->scope            = getUInt32  ();
    node->has_alignment    = getBoolean ();
    if (node->has_alignment) {
        node->z_target          = getByte ();
        node->y_target          = getByte ();
        node->z_reference_index = getUInt32 ();
        node->y_reference_index = getUInt32 ();
    }
}


void M3GReader:: readObject3D (M3GObject3DStruct* object3D)
{
    int count;

    object3D->user_id                = getUInt32 ();
    object3D->animation_tracks_count = getUInt32 ();

    count = object3D->animation_tracks_count;
    object3D->animation_tracks_index = new unsigned int[count];
    for (int i = 0; i < count; i++) {
        object3D->animation_tracks_index[i] = getUInt32 ();
    }

    object3D->user_parameter_count = getUInt32 ();

    count = object3D->user_parameter_count;
    object3D->parameter_id           = new unsigned int[count];
    object3D->parameter_value_length = new unsigned int[count];
    object3D->parameter_value        = new char*       [count];
    for (int i = 0; i < count; i++) {
        object3D->parameter_id[i]           = getUInt32 ();
        object3D->parameter_value_length[i] = getUInt32 ();
        object3D->parameter_value[i]        = getByteArray (object3D->parameter_value_length[i]);
    }
}


void M3GReader:: readPolygonMode (M3GPolygonModeStruct* poly_mode)
{
    poly_mode->culling = getByte ();
    poly_mode->shading = getByte ();
    poly_mode->winding = getByte ();
    poly_mode->two_sided_lighting_enabled     = getBoolean ();
    poly_mode->local_camera_lighting_enabled  = getBoolean ();
    poly_mode->perspective_correction_enabled = getBoolean ();

}


void M3GReader:: readSkinnedMesh (M3GSkinnedMeshStruct* mesh)
{
    mesh->skeleton_index            = getUInt32 ();
    mesh->transform_reference_count = getUInt32 ();
    int count = mesh->transform_reference_count;
    mesh->transform_node_index = new unsigned int [count];
    mesh->first_vertex         = new unsigned int [count];
    mesh->vertex_count         = new unsigned int [count];
    mesh->weight               = new int [count];
    for (int i = 0; i < count; i++) {
        mesh->transform_node_index[i] = getUInt32 ();
        mesh->first_vertex[i]         = getUInt32 ();
        mesh->vertex_count[i]         = getUInt32 ();
        mesh->weight[i]               = getInt32  ();
    }

}


void M3GReader:: readSprite3D (M3GSprite3DStruct* sprite)
{
    sprite->image_index       = getUInt32 ();
    sprite->appearance_index  = getUInt32 ();
    sprite->is_scaled   = getBoolean ();
    sprite->crop_x      = getInt32 ();
    sprite->crop_y      = getInt32 ();
    sprite->crop_width  = getInt32 ();
    sprite->crop_height = getInt32 ();
}

void M3GReader:: readTexture2D (M3GTexture2DStruct* texture)
{
    texture->image_index  = getUInt32 ();
    texture->blend_color  = getRGB    ();
    texture->blending     = getByte   ();
    texture->wrapping_s   = getByte   ();
    texture->wrapping_t   = getByte   ();
    texture->level_filter = getByte   ();
    texture->image_filter = getByte   ();
}

void M3GReader:: readTransformable (M3GTransformableStruct* transformable)
{
    transformable->has_component_transform = getBoolean ();
    bool has = transformable->has_component_transform;
    if (has) {
        transformable->translation[0]      = getFloat32 ();
        transformable->translation[1]      = getFloat32 ();
        transformable->translation[2]      = getFloat32 ();
        transformable->scale[0]            = getFloat32 ();
        transformable->scale[1]            = getFloat32 ();
        transformable->scale[2]            = getFloat32 ();
        transformable->orientation_angle   = getFloat32 ();
        transformable->orientation_axis[0] = getFloat32 ();
        transformable->orientation_axis[1] = getFloat32 ();
        transformable->orientation_axis[2] = getFloat32 ();
    }
    transformable->has_general_transform   = getBoolean ();
    has = transformable->has_general_transform;
    if (has) {
        for (int i = 0; i < 16; i++) {
            transformable->transform[i]    = getFloat32 ();
        }
    }

}


void M3GReader:: readTriangleStripArray (M3GTriangleStripArrayStruct* tris)
{
    tris->encoding = getByte ();
    switch (tris->encoding) {
    case M3GTriangleStripArrayStruct::ENCODING_0: {
        tris->start_index = getUInt32 ();
        break;
    }
    case M3GTriangleStripArrayStruct::ENCODING_1: {
        tris->start_index = getByte ();
        break;
    }
    case M3GTriangleStripArrayStruct::ENCODING_2: {
        tris->start_index = getUInt16 ();
        break;
    }
    case M3GTriangleStripArrayStruct::ENCODING_128: {
        tris->indices_count = getUInt32 ();
        int count = tris->indices_count;
        tris->indices = new unsigned int [count];
        for (int i = 0; i < count; i++) {
            tris->indices[i] = getUInt32 ();
        }
        break;
    }
    case M3GTriangleStripArrayStruct::ENCODING_129: {
        tris->indices_count = getUInt32 ();
        int count = tris->indices_count;
        tris->indices = new unsigned int [count];
        for (int i = 0; i < count; i++) {
            tris->indices[i] = getUByte ();
        }
        break;
    }
    case M3GTriangleStripArrayStruct::ENCODING_130: {
        tris->indices_count = getUInt32 ();
        int count = tris->indices_count;
        tris->indices = new unsigned int [count];
        for (int i = 0; i < count; i++) {
            tris->indices[i] = getUInt16 ();
        }
        break;
    }
    } // switch

    tris->strip_lengths_count = getUInt32 ();
    int count = tris->strip_lengths_count;
    tris->strip_lengths = new unsigned int [count];
    for (int i = 0; i < count; i++) {
        tris->strip_lengths[i] = getUInt32 ();
    }

}


void M3GReader:: readVertexArray (M3GVertexArrayStruct* varry)
{
    varry->component_size  = getByte ();
    varry->component_count = getByte ();
    varry->encoding        = getByte ();
    varry->vertex_count    = getUInt16 ();
    int vertex_count    = varry->vertex_count;
    int component_count = varry->component_count;
    int component_size  = varry->component_size;
    int encoding        = varry->encoding;
    switch (component_size) {
    case 1: varry->char_components  = new char*  [vertex_count]; break;
    case 2: varry->short_components = new short* [vertex_count]; break;
    case 4: varry->float_components = new float* [vertex_count]; break;
    }
    int   delta_base   = 0;
    float delta_base_f = 0;
    for (int i = 0; i < vertex_count; i++) {
        switch (component_size) {
        case 1: varry->char_components[i]  = new char  [component_count]; break;
        case 2: varry->short_components[i] = new short [component_count]; break;
        case 4: varry->float_components[i] = new float [component_count]; break;
        }
        for (int j = 0; j < component_count; j++) {
            switch (component_size) {
            case 1: 
                if (encoding == 0) {
                    varry->char_components[i][j] = getByte ();
                } else {
                    varry->char_components[i][j] = delta_base + getByte();
                    delta_base = varry->char_components[i][j];
                }
                break;
            case 2:
                if (encoding == 0) {
                    varry->short_components[i][j] = getUInt16 ();
                } else {
                    varry->short_components[i][j] = delta_base + getUInt16();
                    delta_base = varry->short_components[i][j];
                }
                break;
            case 4:
                if (encoding == 0) {
                    varry->float_components[i][j] = getFloat32 ();
                } else {
                    varry->float_components[i][j] = delta_base_f + getFloat32 ();
                    delta_base_f = varry->float_components[i][j];
                }
                break;
            }

        }
    }
}

void M3GReader:: readVertexBuffer (M3GVertexBufferStruct* vbuf)
{
    vbuf->default_color    = getRGBA    ();
    vbuf->positions_index  = getUInt32  ();
    vbuf->position_bias[0] = getFloat32 ();
    vbuf->position_bias[1] = getFloat32 ();
    vbuf->position_bias[2] = getFloat32 ();
    vbuf->position_scale   = getFloat32 ();
    vbuf->normals_index    = getUInt32  ();
    vbuf->colors_index     = getUInt32  ();
    vbuf->texcoord_array_count = getUInt32 ();
    int count = vbuf->texcoord_array_count;
    vbuf->texcoords_index = new unsigned int [count];
    vbuf->texcoord_bias   = new float*       [count];
    vbuf->texcoord_scale  = new float        [count];
    for (int i = 0; i < count; i++) {
        vbuf->texcoords_index[i]    = getUInt32 ();
        vbuf->texcoord_bias  [i]    = new float [3];
        vbuf->texcoord_bias  [i][0] = getFloat32 ();
        vbuf->texcoord_bias  [i][1] = getFloat32 ();
        vbuf->texcoord_bias  [i][2] = getFloat32 ();
        vbuf->texcoord_scale [i]    = getFloat32 ();
    }

}

void M3GReader:: readWorld (M3GWorldStruct* world)
{
    world->active_camera_index = getUInt32 ();
    world->background_index    = getUInt32 ();
}

void M3GReader:: readString (const char** str)
{
    char* buf = new char[256];
    memset (buf, 256, 0);
    for (int i = 0; i < 255; i++) {
        buf[i] = getByte ();
        if (buf[i] == '\0') {
            break;
        }
    }
    *str = buf;
}

unsigned int M3GReader:: adler32 (const unsigned char* data, int len) const
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

unsigned int M3GReader:: adler32 (const char* file_name, int start, int end) const
{
    abort ();

    ifstream* ifs  = new ifstream (file_name);
    char*     buf  = new char [end-start];
    ifs->seekg (start);
    ifs->read  (buf, end-start);
    unsigned int checksum = adler32 ((const unsigned char*)buf, end-start);
    delete [] buf;
    delete ifs;

    return checksum;
}

bool           M3GReader:: getBoolean   ()
{
    bool ret;
    stream->read ((char*)&ret, 1);
    return ret;
}

unsigned char   M3GReader:: getUByte        ()
{
    unsigned char ret;
    stream->read ((char*)&ret, 1);
    return ret;
}

char           M3GReader:: getByte      ()
{
    char ret;
    stream->read ((char*)&ret, 1);
    return ret;
}

unsigned short M3GReader:: getUInt16    ()
{
    unsigned short ret;
    stream->read ((char*)&ret, 2);
    return ret;
}

int   M3GReader:: getInt32    ()
{
    int ret;
    stream->read ((char*)&ret, 4);
    return ret;
}

unsigned int   M3GReader:: getUInt32    ()
{
    unsigned int ret;
    stream->read ((char*)&ret, 4);
    return ret;
}


float          M3GReader:: getFloat32   ()
{
    float ret;
    stream->read ((char*)&ret, 4);
    return ret;
}

unsigned int   M3GReader:: getRGB       ()
{
    unsigned char r,g,b;
    stream->read ((char*)&r, 1);
    stream->read ((char*)&g, 1);
    stream->read ((char*)&b, 1);
    return (r << 16) | (g << 8) | (b << 0);
}

unsigned int   M3GReader:: getRGBA      ()
{
    unsigned char r,g,b,a;
    stream->read ((char*)&r, 1);
    stream->read ((char*)&g, 1);
    stream->read ((char*)&b, 1);
    stream->read ((char*)&a, 1);
    return (a << 24) | (r << 16) | (g << 8) | (b << 0);
}


char*          M3GReader:: getByteArray (int size)
{
    char* ret = new char[size];
    stream->read (ret, size);
    return ret;
}

unsigned char* M3GReader:: getUByteArray (int size)
{
    unsigned char* ret = new unsigned char[size];
    stream->read ((char*)ret, size);
    return ret;
}

unsigned short*          M3GReader:: getUInt16Array (int size)
{
    unsigned short* ret = new unsigned short[size];
    stream->read ((char*)ret, 2*size);
    return ret;
}

float*          M3GReader:: getFloat32Array (int size)
{
    float* ret = new float[size];
    stream->read ((char*)ret, 4*size);
    return ret;
}

char*    M3GReader:: getString    ()
{
    char* ret = new char[256];
    memset (ret, 0, 256);
    for (int i = 0; i < 255; i++) {
        char c;
        stream->read (&c, 1);
        if (c == '\0')
            break;
        ret[i] = c;
    }
    return ret;
}

