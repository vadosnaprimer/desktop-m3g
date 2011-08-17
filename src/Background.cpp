#include "m3g/m3g-gl.hpp"
#include "m3g/Background.hpp"
#include "m3g/Image2D.hpp"
#include "m3g/Exception.hpp"
#include "m3g/AnimationTrack.hpp"
#include "m3g/AnimationController.hpp"
#include "m3g/KeyframeSequence.hpp"
#include "m3g/RenderState.hpp"
#include <iostream>
#include <iomanip>
using namespace std;
using namespace m3g;

const int Background:: BORDER;
const int Background:: REPEAT;

namespace {
    // 背景画像の表示に使う板ポリゴン.
    short positions[12] = {1, 0, 0,
                           1, 1, 0,
                           0, 0, 0,
                           0, 1, 0};
    float tex_coords[8] = {1, 0,
                           1, 1,
                           0, 0,
                           0, 1};
    unsigned short indices[4] = {0,1,2,3};
}



Background:: Background () :
    color_clear_enable(true), depth_clear_enable(true), color(0x00000000), 
    image(0), mode(BORDER,BORDER), crop(0,0,0,0), gl(0,0,0,0)
{
    glGenTextures   (1, &gl.tex_object);
    int err = glGetError ();
    if (err != GL_NO_ERROR) {
        throw OpenGLException (__FILE__, __func__, "Can't make texture object, err=%d.", err);
    }

    glGenBuffers (1, &gl.vbo_positions);
    glBindBuffer (GL_ARRAY_BUFFER, gl.vbo_positions);
    glBufferData (GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glGenBuffers (1, &gl.vbo_tex_coords);
    glBindBuffer (GL_ARRAY_BUFFER, gl.vbo_tex_coords);
    glBufferData (GL_ARRAY_BUFFER, sizeof(tex_coords), tex_coords, GL_STATIC_DRAW);

    glGenBuffers (1, &gl.vbo_indices);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, gl.vbo_indices);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    err = glGetError ();
    if (err != GL_NO_ERROR) {
        throw OpenGLException (__FILE__, __func__, "Can't make vertex buffer object, err=%d.", err);
    }

}

Background:: ~Background ()
{
    if (gl.tex_object > 0) {
        glDeleteTextures (1, &gl.tex_object);
    }
    if (gl.vbo_positions > 0) {
        glDeleteBuffers (1, &gl.vbo_positions);
    }
    if (gl.vbo_tex_coords > 0) {
        glDeleteBuffers (1, &gl.vbo_tex_coords);
    }
    if (gl.vbo_indices > 0) {
        glDeleteBuffers (1, &gl.vbo_indices);
    }
}


Background* Background:: duplicate () const
{
    return duplicate_xxx (NULL);
}

Background* Background:: duplicate_xxx (Object3D* obj) const
{
    Background* bg = dynamic_cast<Background*>(obj);
    if (bg == NULL) {
        bg = new Background;
    }
    Object3D:: duplicate_xxx (bg);

    bg->color_clear_enable = color_clear_enable;
    bg->depth_clear_enable = depth_clear_enable;
    bg->color              = color;
    bg->mode               = mode;
    bg->setImage (image);
    bg->crop               = crop;
    bg->gl                 = gl;

    return bg;
}



int Background:: getReferences_xxx (Object3D** references) const
{
    int n = Object3D:: getReferences_xxx (references);
    if (image)
        references ? references[n] = image, n++ : n++;

    return n;
}


void Background:: addAnimationTrack_xxx (AnimationTrack* animation_track, bool accepted)
{
    int property = animation_track->getTargetProperty();
    if (property == AnimationTrack::ALPHA ||
        property == AnimationTrack::COLOR ||
        property == AnimationTrack::CROP) {
        accepted = true;
    }
    Object3D:: addAnimationTrack_xxx (animation_track, accepted);
}

int Background:: animate_xxx (int world_time)
{
    Object3D:: animate_xxx (world_time);

    bool     is_color_modefied = false;
    bool     is_alpha_modefied = false;
    bool     is_crop_modefied  = false;
    float    new_color[] = {0,0,0};
    float    new_alpha   = 0;
    CropRect new_crop    = CropRect(0,0,0,0);
    
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
        case AnimationTrack:: ALPHA: {
            float value[1] = {1};
            keyframe->sample (sequence_time, value);
            new_alpha += value[0] * weight;
            is_alpha_modefied = true;
            //cout << "Background: alpha --> " << new_alpha << "\n";
            break;
        }
        case AnimationTrack:: CROP: {
            float value[4] = {0,0,0,0};
            keyframe->sample (sequence_time, value);
            if (keyframe->getComponentCount() == 4) {
                new_crop.x      += value[0] * weight;
                new_crop.y      += value[1] * weight;
                new_crop.width  += value[2] * weight;
                new_crop.height += value[3] * weight;
            } else {
                new_crop.x      += value[0] * weight;
                new_crop.y      += value[1] * weight;
                new_crop.width  += crop.width * weight;
                new_crop.height += crop.height * weight;
	
            }
            is_crop_modefied = true;
            //cout << "Background: crop --> " << crop.x << ", " << crop.y << ", " << crop.width << ", " << crop.height << "\n";
        }
        case AnimationTrack:: COLOR: {
            float value[3] = {1,1,1};
            keyframe->sample (sequence_time, value);
            new_color[0] += value[0] * weight;
            new_color[1] += value[1] * weight;
            new_color[2] += value[2] * weight;
            is_color_modefied = true;
            //cout << "Background: color --> " << new_color[0] << ", " << new_color[1] << ", " << new_color[2]  << "\n";
            break;
        }
        default: {
            // Unknown target should be ignored.
            // animate() of Base class (of Derived class) retrieve it.
        }
        }
    }

    if (is_crop_modefied) {
        new_crop.width  = max(0.f, new_crop.width);
        new_crop.height = max(0.f, new_crop.height);
        crop  = CropRect(new_crop.x, new_crop.y, new_crop.width, new_crop.height);
    }
    if (is_color_modefied) {
        unsigned char r  = clamp(0, 1, new_color[0]) * 255;
        unsigned char g  = clamp(0, 1, new_color[1]) * 255;
        unsigned char b  = clamp(0, 1, new_color[2]) * 255;
        color = (color & 0xff000000) | (r << 16) | (g << 8) | (b << 0);
    }
    if (is_alpha_modefied) {
        unsigned char a  = clamp(0, 1, new_alpha) * 255;
        color = (color & 0x00ffffff) | (a << 24);
    }
  
    return 0;
}

int Background:: getColor () const
{
    return color;
}

int Background:: getCropHeight () const
{
    return crop.height;
}

int Background:: getCropWidth () const
{
    return crop.width;
}
    
int Background:: getCropX () const
{
    return crop.x;
}

int Background:: getCropY () const
{
    return crop.y;
}

Image2D* Background:: getImage () const
{
    return image;
}

int Background:: getImageModeX () const
{
    return mode.x;
}

int Background:: getImageModeY () const
{
    return mode.y;
}

bool Background:: isColorClearEnabled () const
{
    return color_clear_enable;
}


bool Background:: isDepthClearEnabled () const
{
    return depth_clear_enable;
}

void Background:: setColor (int argb)
{
    color = argb;
}

void Background:: setColorClearEnable (bool enable)
{
    color_clear_enable = enable;
}

void Background:: setCrop (int x, int y, int width, int height)
{
    crop = CropRect (x, y, width, height);
}

void Background:: setDepthClearEnable (bool enable)
{
    depth_clear_enable = enable;
}

void Background:: setImage (Image2D* img)
{
    image = img;
    if (image == NULL) {
        return;
    }

    int fmt = img->getFormat ();
    if (fmt != Image2D::RGB && fmt != Image2D::RGBA) {
        throw IllegalArgumentException (__FILE__, __func__, "Image format is invalid, format=%d.", fmt);
    }


    int   width  = image->getWidth ();
    int   height = image->getHeight ();
    int   format = image->getOpenGLFormat ();
    void* data   = image->getOpenGLPointer ();

    crop    = CropRect (0, 0, width, height);

    glActiveTexture (GL_TEXTURE0);
//    glClientActiveTexture (GL_TEXTURE0);
    glEnable        (GL_TEXTURE_2D);
    glBindTexture   (GL_TEXTURE_2D, gl.tex_object);
    glPixelStorei   (GL_UNPACK_ALIGNMENT, 1);
    glTexParameterf (GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);               //
    glTexImage2D    (GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
}

void Background:: setImageMode (int mode_x, int mode_y)
{
    if ((mode_x != REPEAT && mode_x != BORDER) ||
        (mode_y != REPEAT && mode_y != BORDER)) {
        throw IllegalArgumentException (__FILE__, __func__, "Mode is invalid, x=%d, y=%d.\n", mode_x, mode_y);
    }

    mode.x = mode_x;
    mode.y = mode_y;
}



/**
 * Note: Background should be rendered only at 0th rendering pass(pass=0).
 * In other cases, do nothing.
 */
void Background:: render_xxx (RenderState& state) const
{
    if (state.pass != 0) {
        return;
    }

    //cout << "Background: render\n";

    float r = ((color & 0x00ff0000) >> 16) / 255.f;
    float g = ((color & 0x0000ff00) >>  8) / 255.f;
    float b = ((color & 0x000000ff) >>  0) / 255.f;
    float a = ((color & 0xff000000) >> 24) / 255.f;

    glDepthMask   (GL_TRUE);
    glColorMask   (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glClearColor  (r,g,b,a);
    glClearDepth  (1.f);

    if (depth_clear_enable) {
        glClear (GL_DEPTH_BUFFER_BIT);
    }

    if (color_clear_enable) {
        glClear  (GL_COLOR_BUFFER_BIT);

        if (image) {
            float img_width  = image->getWidth ();
            float img_height = image->getHeight ();
            float scale_x    = (mode.x == BORDER) ? img_width  : ((crop.x + crop.width  - 1) / img_width  + 1) * img_width;
            float scale_y    = (mode.y == BORDER) ? img_height : ((crop.y + crop.height - 1) / img_height + 1) * img_height;
            float scale_s    = (mode.x == BORDER) ? 1          :  (crop.x + crop.width  - 1) / img_width  + 1;
            float scale_t    = (mode.y == BORDER) ? 1          :  (crop.y + crop.height - 1) / img_height + 1;

            glActiveTexture       (GL_TEXTURE0);
            glClientActiveTexture (GL_TEXTURE0);
            glEnable              (GL_TEXTURE_2D);
            glBindTexture         (GL_TEXTURE_2D , gl.tex_object);
            glTexEnvf             (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE  , GL_MODULATE);
            glTexParameterf       (GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameterf       (GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameterf       (GL_TEXTURE_2D , GL_TEXTURE_WRAP_S    , GL_REPEAT);
            glTexParameterf       (GL_TEXTURE_2D , GL_TEXTURE_WRAP_T    , GL_REPEAT);
            glDepthMask           (GL_FALSE);
            glDisable             (GL_LIGHTING);
            glDisable             (GL_CULL_FACE);
            glColor4f             (1,1,1,1);

            glMatrixMode   (GL_PROJECTION);
            glPushMatrix   ();
            glLoadIdentity ();
            glOrthof       (crop.x, crop.x + crop.width, crop.y + crop.height, crop.y , -1, 1);

            glMatrixMode   (GL_TEXTURE);
            glPushMatrix   ();
            glLoadIdentity ();
            glScalef       (scale_s, -scale_t, 1);
            
            glMatrixMode   (GL_MODELVIEW);
            glPushMatrix   ();
            glLoadIdentity ();
            glScalef       (scale_x, scale_y, 1);
            
            glEnableClientState (GL_VERTEX_ARRAY);
            glEnableClientState (GL_TEXTURE_COORD_ARRAY);

            // 頂点データ
            glBindBuffer    (GL_ARRAY_BUFFER, gl.vbo_positions);
            glVertexPointer (3, GL_SHORT, 0, 0);

            // テクスチャー座標データ
            glBindBuffer       (GL_ARRAY_BUFFER, gl.vbo_tex_coords);
            glTexCoordPointer  (2, GL_FLOAT, 0, 0);

            // インデックス
            glBindBuffer    (GL_ELEMENT_ARRAY_BUFFER, gl.vbo_indices);
            glDrawElements  (GL_TRIANGLE_STRIP, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_SHORT, 0);
            
            glDisableClientState (GL_VERTEX_ARRAY);
            glDisableClientState (GL_TEXTURE_COORD_ARRAY);

            glMatrixMode   (GL_PROJECTION);
            glPopMatrix    ();
            glMatrixMode   (GL_TEXTURE);
            glPopMatrix    ();
            glMatrixMode   (GL_MODELVIEW);
            glPopMatrix    ();

            glDepthMask   (GL_TRUE);
        }
    }

    

}

void Background:: renderX ()
{
    glDepthMask   (GL_TRUE);
    glColorMask   (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glClearColor  (0,0,0,0);   // r,g,b,a
    glClearDepth  (1.0f);
    glClear       (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


static
const char* mode_to_string (int mode)
{
    switch (mode) {
    case Background::BORDER: return "BORDER";
    case Background::REPEAT: return "REPEAT";
    default: return "Unknown";
    }
}

std::ostream& Background:: print (std::ostream& out) const
{
    out << "Background: ";
    out << "  color clear=" << color_clear_enable;
    out << ", depth clear=" << depth_clear_enable;
    out << ", color=0x"     << hex << setw(8) << setfill('0') << color << dec;
    out << ", image=0x"     << image;
    out << ", mode="        << mode_to_string(mode.x);
    out << ","              << mode_to_string(mode.y);
    out << ", crop="        << crop.x;
    out << ","              << crop.y;
    out << ","              << crop.width;
    out << ","              << crop.height;
    return out;
}

std::ostream& operator<< (std::ostream& out, const Background& bg)
{
    return bg.print (out);
}
