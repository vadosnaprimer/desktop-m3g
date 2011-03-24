#include "m3g/m3g-gl.hpp"
#include "m3g/VertexBuffer.hpp"
#include "m3g/VertexArray.hpp"
#include "m3g/AnimationTrack.hpp"
#include "m3g/AnimationController.hpp"
#include "m3g/KeyframeSequence.hpp"
#include "m3g/Exception.hpp"
#include "m3g/RenderState.hpp"
#include <iostream>
#include <iomanip>
using namespace std;
using namespace m3g;


VertexBuffer:: VertexBuffer () :
    positions(0), normals(0), colors(0), positions_scale(1),
    default_color(0xffffffff), node_alpha(1)
{
    for (int i = 0; i < 3; i++) {
        positions_bias[i] = 0;
    }
    for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
        tex_coords[i] = 0;
        tex_coords_scale[i] = 1;
        for (int j = 0; j < 3; j++) {
            tex_coords_bias[i][j] = 0;
        }
    }
}

VertexBuffer:: ~VertexBuffer ()
{
}

VertexBuffer* VertexBuffer:: duplicate () const
{
    return duplicate_xxx (NULL);
}

VertexBuffer* VertexBuffer:: duplicate_xxx (Object3D* obj) const
{
    VertexBuffer* vbuf = dynamic_cast<VertexBuffer*>(obj);
    if (vbuf == NULL) {
        vbuf = new VertexBuffer;
    }
    Object3D:: duplicate_xxx (vbuf);

    vbuf->positions = positions;
    vbuf->normals   = normals;
    vbuf->colors    = colors;
    for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
        vbuf->tex_coords[i] = tex_coords[i];
    }
    vbuf->positions_scale   = positions_scale;
    vbuf->positions_bias[0] = positions_bias[0];
    vbuf->positions_bias[1] = positions_bias[1];
    vbuf->positions_bias[2] = positions_bias[2];
    for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
        vbuf->tex_coords_scale[i] = tex_coords_scale[i];
    }
    for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
        vbuf->tex_coords_bias[i][0] = tex_coords_bias[i][0];
        vbuf->tex_coords_bias[i][1] = tex_coords_bias[i][1];
        vbuf->tex_coords_bias[i][2] = tex_coords_bias[i][2];
    }
    vbuf->default_color = default_color;
    vbuf->node_alpha    = node_alpha;

    return vbuf;
}



int VertexBuffer:: getReferences_xxx (Object3D** references) const
{
    int n = Object3D:: getReferences_xxx (references);
    if (positions)
        references ? references[n] = positions, n++ : n++;
    if (normals)
        references ? references[n] = normals, n++ : n++;
    if (colors)
        references ? references[n] = colors, n++ : n++;
    for (int i = 0; i < (int)MAX_TEXTURE_UNITS; i++) {
        if (tex_coords[i])
            references ? references[n] = tex_coords[i], n++ : n++;
    }

    return n;
}

void VertexBuffer:: addAnimationTrack_xxx (AnimationTrack* animation_track, bool accepted)
{
    int property = animation_track->getTargetProperty();
    if (property == AnimationTrack::COLOR) {
        accepted = true;
    }
    Object3D:: addAnimationTrack_xxx (animation_track, accepted);
}

int VertexBuffer:: animate_xxx (int world_time)
{
    Object3D:: animate_xxx (world_time);

    bool  is_color_modefied = false;
    bool  is_alpha_modefied = false;
    float rgb[]  = {0,0,0};
    float new_alpha  = 0;

    for (int i = 0; i < getAnimationTrackCount(); i++) {
        AnimationTrack*      track      = getAnimationTrack (i);
        KeyframeSequence*    keyframe   = track->getKeyframeSequence();
        AnimationController* controller = track->getController();
        if (!controller || !controller->isActive(world_time)) {
            continue;
        }
        float weight        = controller->getWeight ();
        float sequence_time = controller->getPosition (world_time);
    
        switch (track->getTargetProperty()) {
        case AnimationTrack::COLOR: {
            float value[3] = {1,1,1};
            keyframe->sample (sequence_time, value);
            rgb[0] += value[0] * weight;
            rgb[1] += value[1] * weight;
            rgb[2] += value[2] * weight;
            is_color_modefied = true;
            //cout << "VertexBuffer: default color --> " << rgb[0] << ", " << rgb[1] << ", " << rgb[2] << "\n";
            break;
        }
        case AnimationTrack::ALPHA: {
            float value[1] = {1};
            keyframe->sample (sequence_time, value);
            new_alpha += value[0] * weight;
            is_alpha_modefied = true;
            //cout << "VertexBuffer: alpha --> " << alpha << "\n";
            break;
        }
        default: {
            // Unknown target should be ignored.
            // animate() of Base class (of Derived class) retrieve it.
        }
        }
    }

    if (is_color_modefied) {
        unsigned char r = clamp (0, 1, rgb[0]) * 255;
        unsigned char g = clamp (0, 1, rgb[1]) * 255;
        unsigned char b = clamp (0, 1, rgb[2]) * 255;
        default_color = (default_color & 0xff000000) | (r << 16) | (g << 8) | (b << 0);
    }
    if (is_alpha_modefied) {
        unsigned char a = clamp (0, 1, new_alpha) * 255;
        default_color = (default_color & 0x00ffffff) | (a << 24);
    }

    return 0;
}

VertexArray* VertexBuffer:: getColors (float* scale_bias) const
{
    if (colors) {
        if (scale_bias) {
            scale_bias[0] = 1/255.f;
            scale_bias[1] = 0;
            scale_bias[2] = 0;
            scale_bias[3] = 0;
        }
    }
    return colors;
}

int VertexBuffer:: getDefaultColor () const
{
    // argb
    return default_color;
}

VertexArray* VertexBuffer:: getNormals (float* scale_bias) const
{
    if (normals) {
        int component_size = normals->getComponentType();
        if (scale_bias) {
            scale_bias[0] = (component_size == 1) ? 2/255.f : (component_size == 2) ? 2/65535.f : 1.f;
            scale_bias[1] = (component_size == 1) ? 1/255.f : (component_size == 2) ? 1/65535.f : 0.f;
            scale_bias[2] = (component_size == 1) ? 1/255.f : (component_size == 2) ? 1/65535.f : 0.f;
            scale_bias[3] = (component_size == 1) ? 1/255.f : (component_size == 2) ? 1/65535.f : 0.f;
        }
    }
    return normals;
}

VertexArray* VertexBuffer:: getPositions (float* scale_bias) const
{
    if (positions) {
        if (scale_bias) {
            scale_bias[0] = positions_scale;
            scale_bias[1] = positions_bias[0];
            scale_bias[2] = positions_bias[1];
            scale_bias[3] = positions_bias[2];
        }
    }
    return positions;
}

VertexArray* VertexBuffer:: getTexCoords (int index, float* scale_bias) const
{
    if (index < 0 || index >= MAX_TEXTURE_UNITS) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Texture index is invalid.");
    }

    if (tex_coords[index] && scale_bias) {
        scale_bias[0] = tex_coords_scale[index];
        for (int i = 0; i < tex_coords[index]->getComponentCount(); i++) {
            scale_bias[i+1] = tex_coords_bias[index][i];
        }
    }
    return tex_coords[index];
}

int VertexBuffer:: getVertexCount () const
{
    if (positions != NULL) {
        return positions->getVertexCount ();
    } else {
        return 0;
    }
    
}


/**
 * x:[0,255] --> y:[0,1]
 */
void VertexBuffer:: setColors (VertexArray* colors_)
{
    if (colors_ == NULL) {
        colors = NULL;
        return;
    }
    int component_type  = colors_->getComponentType ();
    int component_count = colors_->getComponentCount ();
    if (component_type != 1) {
        throw IllegalArgumentException (__FILE__, __func__, "Component size must be 1, size=%d.", component_type);
    }
    if (component_count != 3 && component_count != 4) {
        throw IllegalArgumentException (__FILE__, __func__, "Component count must be 3 or 4, size=%d.", component_count);
    }
    #ifdef USE_GL_ES
    if (component_count == 3) {
        throw IllegalArgumentException (__FILE__, __func__, "OpenGL ES doesn't support 3 component counts as vertex color.");
    }
    #endif

    colors     = colors_;
    node_alpha = 1;
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

    int vertex_count    = normals_->getVertexCount ();
    int component_count = normals_->getComponentCount ();
    if (component_count != 3) {
        throw IllegalArgumentException (__FILE__, __func__, "Component count must be 3, count=%d.", component_count);
    }
    if (positions && positions->getVertexCount() != vertex_count) {
        throw IllegalArgumentException (__FILE__, __func__, "Vertex count is invalid, %d <--> %d.", positions->getVertexCount(), vertex_count);
    }
    if (colors && colors->getVertexCount() != vertex_count) {
        throw IllegalArgumentException (__FILE__, __func__, "Vertex count is invalid. %d <--> %d.", colors->getVertexCount(), vertex_count);
    }
    for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
        if (tex_coords[i] && tex_coords[i]->getVertexCount() != vertex_count) {
            throw IllegalArgumentException (__FILE__, __func__, "Vertex count is invalid. %d <--> %d.", tex_coords[i]->getVertexCount(), vertex_count);
        }
    }

    normals = normals_;
}

void VertexBuffer:: setPositions (VertexArray* positions_, float scale, float* bias)
{
    if (positions_ == NULL) {
        positions = NULL;
        return;
    }
    if (bias == NULL) {
        throw NullPointerException (__FILE__, __func__, "Bias is NULL.");
    }
    int vertex_count    = positions_->getVertexCount ();
    int component_count = positions_->getComponentCount ();
    int component_type  = positions_->getComponentType ();
    if (component_count != 3) {
        throw IllegalArgumentException (__FILE__, __func__, "Component count must be 3, count=%d.", component_count);
    }
    if (component_type != 2 && component_type != 4) {
        throw IllegalArgumentException (__FILE__, __func__, "Component size must be 2 or 4, size=%d", component_type);
    }
    if (normals && normals->getVertexCount() != vertex_count) {
        throw IllegalArgumentException (__FILE__, __func__, "Vertex count is invalid, %d <--> %d.", normals->getVertexCount(), vertex_count);
    }
    if (colors && colors->getVertexCount() != vertex_count) {
        throw IllegalArgumentException (__FILE__, __func__, "Vertex count is invalid, %d <--> %d.", colors->getVertexCount(), vertex_count);
    }
    for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
        if (tex_coords[i] && tex_coords[i]->getVertexCount() != vertex_count) {
            throw IllegalArgumentException (__FILE__, __func__, "Vertex count is invalid, %d <--> %d.", tex_coords[i]->getVertexCount(), vertex_count);
        }
    }

    positions         = positions_;
    positions_scale   = scale;
    positions_bias[0] = bias[0];
    positions_bias[1] = bias[1];
    positions_bias[2] = bias[2];
}

void VertexBuffer:: setTexCoords (int index, VertexArray* tex_coords_, float scale, float* bias)
{
    if (index < 0 || index >= MAX_TEXTURE_UNITS) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, index=%d.", index);
    }
    if (tex_coords_ == NULL) {
        tex_coords[index] = NULL;
        return;
    }
    if (bias == NULL) {
        throw NullPointerException (__FILE__, __func__, "Bias is NULL.");
    }
    int vertex_count    = tex_coords_->getVertexCount ();
    int component_count = tex_coords_->getComponentCount ();
    int component_type  = tex_coords_->getComponentType ();

    if (component_count != 2 && component_count != 3) {
        throw IllegalArgumentException (__FILE__, __func__, "Component count must be 2 or 3, count=%d.", component_count);
    }
    if (component_type != 2 && component_type != 4) {
        throw IllegalArgumentException (__FILE__, __func__, "Component size must be 2 or 4, size=%d", component_type);
    }
    if (positions && positions->getVertexCount() != vertex_count) {
        throw IllegalArgumentException (__FILE__, __func__, "Vertex count is invalid. %d <--> %d.", positions->getVertexCount(), vertex_count);
    }
    if (normals && normals->getVertexCount() != vertex_count) {
        throw IllegalArgumentException (__FILE__, __func__, "Vertex count is invalid. %d <--> %d.", normals->getVertexCount(), vertex_count);
    }
    if (colors && colors->getVertexCount() != vertex_count) {
        throw IllegalArgumentException (__FILE__, __func__, "Vertex count is invalid. %d <--> %d.", colors->getVertexCount(), vertex_count);
    }
 
    tex_coords[index]         = tex_coords_;
    tex_coords_scale[index]   = scale;
    tex_coords_bias[index][0] = bias[0];
    tex_coords_bias[index][1] = bias[1];
    tex_coords_bias[index][2] = bias[2];
}

/**
 * Note: VertexBuffer should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void VertexBuffer:: render_xxx (RenderState& state) const
{
    if (state.pass != 2) {
        return;
    }

    if (positions) {
        //cout << "render position array\n";

        int component_count = positions->getComponentCount ();
        unsigned int format = positions->getOpenGLFormat ();
        unsigned int vbo    = positions->getOpenGLVBO();

        glTranslatef (positions_bias[0], positions_bias[1], positions_bias[2]);
        glScalef     (positions_scale, positions_scale, positions_scale);


        glBindBuffer        (GL_ARRAY_BUFFER, vbo);
        glEnableClientState (GL_VERTEX_ARRAY);
        glVertexPointer     (component_count, format, 0, 0);
 
    } else {
        glDisableClientState (GL_VERTEX_ARRAY);
    }

    if (normals) {
        //cout << "render normal array\n";
        unsigned int format = normals->getOpenGLFormat ();
        unsigned int vbo    = normals->getOpenGLVBO ();

        glBindBuffer        (GL_ARRAY_BUFFER, vbo);
        glEnableClientState (GL_NORMAL_ARRAY);
        glNormalPointer     (format, 0, 0);

    } else {
        glDisableClientState (GL_NORMAL_ARRAY);
    }

    if (colors) {
        //cout << "state.alpha = " << state.alpha << ", node_alpha = " << node_alpha << "\n";
        // 頂点カラーが有効でノードαが変更されていた場合は再度GPUに転送する.
        if (state.alpha != node_alpha) {
            int vertex_count    = colors->getVertexCount ();
            int component_count = colors->getComponentCount ();
            int component_num   = vertex_count*component_count;
            if (component_count == 4) {
                //cout << "VertexBuffer: update vertex color by node-alpha\n";
                unsigned char* values = new unsigned char[component_num];
                colors->get (0, vertex_count, (char*)values);
                for (int v = 0; v < vertex_count; v++) {
                    values[v*component_count + 3] *= state.alpha;
                }
                colors->updateOpenGLData (values);
                delete [] values;
            }
            node_alpha = state.alpha;
        }

        // 注意：頂点カラーを使うかどうかはMaterial::render()で決定される。
        // ここではデータをGPUに送るだけでdisableにしておく。
        int component_count = colors->getComponentCount();
        unsigned int vbo    = colors->getOpenGLVBO();
        glBindBuffer         (GL_ARRAY_BUFFER, vbo);
        glEnableClientState  (GL_COLOR_ARRAY);
        glColorPointer       (component_count, GL_UNSIGNED_BYTE, 0, 0);
        glDisableClientState (GL_COLOR_ARRAY);
        state.vertex_color_buffer_ready = true;
        state.default_vertex_color      = 0xffffffff;
    } else {
        glDisableClientState (GL_COLOR_ARRAY);
        state.vertex_color_buffer_ready = false;
        state.default_vertex_color      = default_color;
    }

    glMatrixMode (GL_TEXTURE);

    for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
        if (tex_coords[i]) {

            // テクスチャーユニットの選択
            glActiveTexture (GL_TEXTURE0+i);
            glEnable        (GL_TEXTURE_2D);

            // テクスチャーマトリックスの設定
            glLoadIdentity ();  // <-- この1行要らないか？？？
            glTranslatef (tex_coords_bias[i][0], tex_coords_bias[i][1], tex_coords_bias[i][2]);
            glScalef (tex_coords_scale[i], tex_coords_scale[i], tex_coords_scale[i]);

            //cout << "VertexBuffer: render " << i << "th texture coordinate array\n";

            int component_count = tex_coords[i]->getComponentCount();
            unsigned int format = tex_coords[i]->getOpenGLFormat ();
            unsigned int vbo    = tex_coords[i]->getOpenGLVBO ();

            // テクスチャー座標の頂点配列を使った設定
            glBindBuffer          (GL_ARRAY_BUFFER, vbo);    // VBOの選択
            glClientActiveTexture (GL_TEXTURE0+i);           // (クライアントを含む）テクスチャーユニットの選択
            glEnableClientState   (GL_TEXTURE_COORD_ARRAY);  // 頂点配列の有効化
            glTexCoordPointer (component_count, format, 0, 0);


        } else {
            // これ発行しなくても同じでは？
            glClientActiveTexture (GL_TEXTURE0+i);          // クライアント部分のテクスチャーユニット選択
            glDisableClientState  (GL_TEXTURE_COORD_ARRAY); // テクスチャー座標配列の無効化
        }
    }
  
    glMatrixMode (GL_MODELVIEW);
}

std::ostream& VertexBuffer:: print (std::ostream& out) const
{
    out << "VertexBuffer: ";
    if (positions) {
        out << "  positions = " << *positions << ",scale=" << positions_scale;
        out <<",bias=" << positions_bias[0] << "," << positions_bias[1] << "," << positions_bias[2];
    } else {
        out << "  positions = NOT FOUND";
    }
    if (normals)
        out << ", normals = " << *normals;
    else
        out << ", normals = NOT FOUND";
  
    if (colors)
        out << ", colors  = " << *colors;
    else
        out << ", colors  = NOT FOUND";
    out << ", default color = 0x" << hex << setw(8) << setfill('0') << default_color << dec;
    return out;
}

std::ostream& operator<< (std::ostream& out, const VertexBuffer& vbuf)
{
    return vbuf.print(out);
}



