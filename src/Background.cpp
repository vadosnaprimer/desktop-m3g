#include <iostream>
#include <cmath>
#include "m3g/m3g-gl.hpp"
#include "m3g/Background.hpp"
#include "m3g/Image2D.hpp"
#include "m3g/Exception.hpp"
#include "m3g/AnimationTrack.hpp"
#include "m3g/AnimationController.hpp"
#include "m3g/KeyframeSequence.hpp"
#include "m3g/RenderState.hpp"
using namespace std;
using namespace m3g;

const int Background:: BORDER;
const int Background:: REPEAT;

Background:: Background () :
    color_clear_enable(true), depth_clear_enable(true), color(0x00000000), 
    image(0), mode(BORDER,BORDER), crop(0,0,0,0),
    texobj(0)
{
    glGenTextures   (1, &texobj);
    int err = glGetError();
    if (err != GL_NO_ERROR) {
        throw OpenGLException (__FILE__, __func__, "Can't make texture object, err=%d.", err);
    }

}

Background:: ~Background ()
{
    if (texobj > 0) {
        glDeleteTextures(1, &texobj);
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
    if (image == NULL) 
        return;

    int fmt = img->getFormat ();
    if (fmt != Image2D::RGB && fmt != Image2D::RGBA) {
        throw IllegalArgumentException (__FILE__, __func__, "Image format is invalid, format=%d.", fmt);
    }


    int   width  = image->getWidth ();
    int   height = image->getHeight ();
    int   format = image->getOpenGLFormat ();
    void* data   = image->getOpenGLPointer ();

    crop    = CropRect (0, 0, width, height);

    glBindTexture   (GL_TEXTURE_2D, texobj);
    glPixelStorei   (GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D    (GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glTexParameteri (GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
}

void Background:: setImageMode (int mode_x, int mode_y)
{
    if ((mode_x != REPEAT && mode_x != BORDER) ||
        (mode_y != REPEAT && mode_y != BORDER)) {
        throw IllegalArgumentException (__FILE__, __func__, "Mode is invalid, x=%d, y=%d.\n", mode_x, mode_y);
    }

    mode = ImageMode (mode_x, mode_y);
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
    float rgba[4] = {r,g,b,a};

    glDepthMask (GL_TRUE);
    glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glClearColor (r,g,b,a);
    glClearDepth (1.f);

    if (color_clear_enable) {
        glClear (GL_COLOR_BUFFER_BIT);
    }
    if (depth_clear_enable) {
        glClear (GL_DEPTH_BUFFER_BIT);
    }
    if (image) {

        int width  = image->getWidth ();
        int height = image->getHeight ();

        glEnable (GL_TEXTURE_2D);

        glBindTexture    (GL_TEXTURE_2D , texobj);
        glTexParameteri  (GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri  (GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexEnvi        (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE  , GL_REPLACE);
        if (mode.x == BORDER) {
            glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameterfv (GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, (GLfloat*)&rgba);
        } else {
            glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        }
        if (mode.y == BORDER) {
            glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            glTexParameterfv (GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, (GLfloat*)&rgba);
        } else {
            glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }

        glMatrixMode   (GL_PROJECTION);
        glPushMatrix   ();
        glLoadIdentity ();
        glMatrixMode   (GL_MODELVIEW);
        glPushMatrix   ();
        glLoadIdentity ();

        float s0 = crop.x / width;
        float t0 = (height - crop.y) / height;
        float s1 = (crop.x + crop.width) / width;
        float t1 = (height - (crop.y + crop.height)) / height;

        glBegin      (GL_TRIANGLE_STRIP);
        glTexCoord2f (s1, t1);
        glVertex3f   (1, -1, 0.99999f);
        glTexCoord2f (s1, t0);
        glVertex3f   (1, 1,  0.99999f);
        glTexCoord2f (s0, t1);
        glVertex3f   (-1, -1, 0.99999f);
        glTexCoord2f (s0, t0);
        glVertex3f   (-1, 1,  0.99999f);
        glEnd        ();

        glMatrixMode (GL_PROJECTION);
        glPopMatrix  ();
        glMatrixMode (GL_MODELVIEW);
        glPopMatrix  ();
    }
}

void Background:: renderX ()
{
    glDepthMask  (GL_TRUE);
    glColorMask  (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glClearColor (0,0,0,0);   // r,g,b,a
    glClearDepth (1.0f);
    glClear      (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    out << ", color=0x"     << hex << color << dec;
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
