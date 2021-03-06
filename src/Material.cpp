#include "m3g/m3g-gl.hpp"
#include "m3g/Material.hpp"
#include "m3g/Exception.hpp"
#include "m3g/AnimationTrack.hpp"
#include "m3g/AnimationController.hpp"
#include "m3g/KeyframeSequence.hpp"
#include "m3g/RenderState.hpp"
#include <iostream>
#include <iomanip>
using namespace std;
using namespace m3g;

const int Material:: AMBIENT;
const int Material:: DIFFUSE;
const int Material:: EMISSIVE;
const int Material:: SPECULAR;


Material:: Material () : 
    vertex_color_tracking(false), 
    ambient_color(0x00333333), diffuse_color(0xffcccccc), 
    emissive_color(0), specular_color(0), 
    shininess(0)
{
}

Material:: ~Material ()
{
}

Material* Material:: duplicate () const
{
    return duplicate_xxx (NULL);
}

Material* Material:: duplicate_xxx (Object3D* obj) const
{
    Material* mat = dynamic_cast<Material*>(obj);
    if (mat == NULL) {
        mat = new Material;
    }
    Object3D:: duplicate_xxx (mat);

    mat->vertex_color_tracking = vertex_color_tracking;
    mat->ambient_color         = ambient_color;
    mat->diffuse_color         = diffuse_color;
    mat->emissive_color        = emissive_color;
    mat->specular_color        = specular_color;
    mat->shininess             = shininess;

    return mat;
}


void Material:: addAnimationTrack_xxx (AnimationTrack* animation_track, bool accepted)
{
    int property = animation_track->getTargetProperty();
    if (property == AnimationTrack::ALPHA          ||
        property == AnimationTrack::AMBIENT_COLOR  ||
        property == AnimationTrack::DIFFUSE_COLOR  ||
        property == AnimationTrack::EMISSIVE_COLOR ||
        property == AnimationTrack::SHININESS      || 
        property == AnimationTrack::SPECULAR_COLOR) {
        accepted = true;
    }

    Object3D:: addAnimationTrack_xxx (animation_track, accepted);
}

int Material:: animate_xxx (int world_time)
{
    Object3D:: animate_xxx (world_time);
  
    bool  is_alpha_modefied          = false;
    bool  is_ambient_color_modefied  = false;
    bool  is_diffuse_color_modefied  = false;
    bool  is_emissive_color_modefied = false;
    bool  is_shininess_modefied      = false;
    bool  is_specular_color_modefied = false;
    float ambient_rgb[]  = {0,0,0};
    float diffuse_rgb[]  = {0,0,0};
    float emissive_rgb[] = {0,0,0};
    float specular_rgb[] = {0,0,0};
    float alpha          = 0;
    float new_shininess  = 0;

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
        case AnimationTrack::ALPHA: {
            float value[1] = {1};
            keyframe->sample (sequence_time, value);
            alpha += value[0] * weight;
            is_alpha_modefied = true;
            //cout << "Material: alpha --> " << alpha << "\n";
            break;
        }
        case AnimationTrack::AMBIENT_COLOR: {
            float value[3] = {1,1,1};
            keyframe->sample (sequence_time, value);
            ambient_rgb[0] += value[0] * weight;
            ambient_rgb[1] += value[1] * weight;
            ambient_rgb[2] += value[2] * weight;
            is_ambient_color_modefied = true;
            //cout << "Material: ambient color --> " << ambient_rgb[0] << ", " << ambient_rgb[1] << ", " << ambient_rgb[2] << "\n";
            break;
        }
        case AnimationTrack::DIFFUSE_COLOR: {
            float value[3] = {1,1,1};
            keyframe->sample (sequence_time, value);
            diffuse_rgb[0] += value[0] * weight;
            diffuse_rgb[1] += value[1] * weight;
            diffuse_rgb[2] += value[2] * weight;
            is_diffuse_color_modefied = true;
            //cout << "Material: diffuse color --> " << diffuse_rgb[0] << ", " << ambient_rgb[1] << ", " << ambient_rgb[2] << "\n";
            break;
        }
        case AnimationTrack::EMISSIVE_COLOR: {
            float value[3] = {1,1,1};
            keyframe->sample (sequence_time, value);
            emissive_rgb[0] += value[0] * weight;
            emissive_rgb[1] += value[1] * weight;
            emissive_rgb[2] += value[2] * weight;
            is_emissive_color_modefied = true;
            //cout << "Material: emissive color --> " << emissive_rgb[0] << ", " << ambient_rgb[1] << ", " << ambient_rgb[2] << "\n";
            break;
        }
        case AnimationTrack::SHININESS: {
            float value[1] = {1};
            keyframe->sample (sequence_time, value);
            shininess += value[0] * weight;
            is_shininess_modefied = true;
            //cout << "Material: shininess --> " << shininess << "\n";
            break;
        }
        case AnimationTrack::SPECULAR_COLOR: {
            float value[3] = {1,1,1};
            keyframe->sample (sequence_time, value);
            specular_rgb[0] += value[0] * weight;
            specular_rgb[1] += value[1] * weight;
            specular_rgb[2] += value[2] * weight;
            is_specular_color_modefied = true;
            //cout << "Material: specular color --> " << specular_rgb[0] << ", " << ambient_rgb[1] << ", " << ambient_rgb[2] << "\n";
            break;
        }
        default: {
            // Unknown target should be ignored.
            // animate() of Base class handle it.
        }
        }
    }

    if (is_ambient_color_modefied) {
        unsigned char r = clamp (0, 1, ambient_rgb[0]) * 255;
        unsigned char g = clamp (0, 1, ambient_rgb[1]) * 255;
        unsigned char b = clamp (0, 1, ambient_rgb[2]) * 255;
        //cout << "Material: r,g,b = " << (int)r << ", " << (int)g << ", " << (int)b << "\n";
        ambient_color = (r << 16) | (g << 8) | (b << 0);
    }
    if (is_diffuse_color_modefied) {
        unsigned char r = clamp (0, 1, diffuse_rgb[0]) * 255;
        unsigned char g = clamp (0, 1, diffuse_rgb[1]) * 255;
        unsigned char b = clamp (0, 1, diffuse_rgb[2]) * 255;
        //cout << "Material: r,g,b = " << (int)r << ", " << (int)g << ", " << (int)b << "\n";
        diffuse_color = (diffuse_color & 0xff000000) | (r << 16) | (g << 8) | (b << 0);
    }
    if (is_emissive_color_modefied) {
        unsigned char r = clamp (0, 1, emissive_rgb[0]) * 255;
        unsigned char g = clamp (0, 1, emissive_rgb[1]) * 255;
        unsigned char b = clamp (0, 1, emissive_rgb[2]) * 255;
        //cout << "Material: r,g,b = " << (int)r << ", " << (int)g << ", " << (int)b << "\n";
        emissive_color = (r << 16) | (g << 8) | (b << 0);
    }
    if (is_alpha_modefied) {
        unsigned char a = clamp (0, 1, alpha) * 255;
        diffuse_color = (diffuse_color & 0x00ffffff) | (a << 24);
    }
    if (is_shininess_modefied) {
        shininess = clamp (0, 128, new_shininess);
    }
    if (is_specular_color_modefied) {
        unsigned char r = clamp (0, 1, specular_rgb[0]) * 255;
        unsigned char g = clamp (0, 1, specular_rgb[1]) * 255;
        unsigned char b = clamp (0, 1, specular_rgb[2]) * 255;
        //cout << "Material: r,g,b = " << (int)r << ", " << (int)g << ", " << (int)b << "\n";
        specular_color = (r << 16) | (g << 8) | (b << 0);
    }

    // don't delete this for quick debug.
    //cout << hex << "Material: ambient_color = 0x" << ambient_color << dec << "\n";
    //cout << hex << "Material: diffuse_color = 0x" << diffuse_color << dec << "\n";
    //cout << "Material: alpha = " << alpha << "\n";
    //cout << "Material: shininess = " << shininess << "\n";
    //cout << hex << "Material: specular_color = 0x" << specular_color << dec << "\n";

    return 0;
}

int Material:: getColor (int target) const
{
    switch (target) {
    case AMBIENT : return ambient_color;
    case DIFFUSE : return diffuse_color;
    case EMISSIVE: return emissive_color;
    case SPECULAR: return specular_color;
    default: throw IllegalArgumentException (__FILE__, __func__, "Target is invalid, target=%d.", target);
    }
}

float Material:: getShininess () const
{
    return shininess;
}

bool Material:: isVertexColorTrackingEnabled () const
{
    return vertex_color_tracking;
}

void Material:: setColor (int target, int argb)
{
    if (!(target & AMBIENT || target & DIFFUSE || target & EMISSIVE || target & SPECULAR)) {
        throw IllegalArgumentException (__FILE__, __func__, "Target color is invalid, target=%d\n", target);
    }
    
    if (target & AMBIENT) {
        ambient_color  = argb & 0x00ffffff;
    }
    if (target & DIFFUSE) {
        diffuse_color  = argb;
    }
    if (target & EMISSIVE) {
        emissive_color = argb & 0x00ffffff;
    }
    if (target & SPECULAR) {
        specular_color = argb & 0x00ffffff;
    }
  
}

void Material:: setShininess (float shi)
{
    if (shi < 0 || shi > 128) {
        throw IllegalArgumentException (__FILE__, __func__, "shininess is invalid, shi=%f.", shi);
    }
    shininess = shi;
}

void Material:: setVertexColorTrackingEnable (bool enable)
{
    vertex_color_tracking = enable;
}

/**
 * Note: Material should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void Material:: render_xxx (RenderState& state) const
{
    if (state.pass != 2) {
        return;
    }

    //cout << "Material: render\n";
    //cout << "Material: state.alpha = " << state.alpha << "\n";

    GLfloat ambient_rgb[4] = {((ambient_color & 0x00ff0000) >> 16) / 255.f,
                              ((ambient_color & 0x0000ff00) >> 8 ) / 255.f,
                              ((ambient_color & 0x000000ff) >> 0 ) / 255.f, 1};
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, ambient_rgb);

    GLfloat diffuse_rgba[4] = {((diffuse_color & 0x00ff0000) >> 16) / 255.f,
                               ((diffuse_color & 0x0000ff00) >> 8 ) / 255.f,
                               ((diffuse_color & 0x000000ff) >> 0 ) / 255.f,
                               ((diffuse_color & 0xff000000) >> 24) / 255.f * state.alpha};
    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_rgba);

    // Diffuse color is used as 'Color' too.
    glColor4f    (diffuse_rgba[0], diffuse_rgba[1], diffuse_rgba[2], diffuse_rgba[3]);

    GLfloat specular_rgb[4] = {((specular_color & 0x00ff0000) >> 16) / 255.f,
                               ((specular_color & 0x0000ff00) >> 8 ) / 255.f,
                               ((specular_color & 0x000000ff) >> 0 ) / 255.f, 1};
    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, specular_rgb);
    glMaterialf  (GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    GLfloat emissive_rgb[4] = {((emissive_color & 0x00ff0000) >> 16) / 255.f,
                               ((emissive_color & 0x0000ff00) >> 8 ) / 255.f,
                               ((emissive_color & 0x000000ff) >> 0 ) / 255.f, 1};
    glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, emissive_rgb);


    // 頂点カラーが有効なとき
    if (vertex_color_tracking) {
        glDisable (GL_LIGHTING);
        if (state.vertex_color_buffer_ready) {
            glEnableClientState (GL_COLOR_ARRAY);
        } else {
            GLfloat vertex_color_rgba[4] = {((state.default_vertex_color & 0x00ff0000) >> 16) / 255.f,
                                            ((state.default_vertex_color & 0x0000ff00) >> 8 ) / 255.f,
                                            ((state.default_vertex_color & 0x000000ff) >> 0 ) / 255.f,
                                            ((state.default_vertex_color & 0xff000000) >> 24) / 255.f * state.alpha};
            glColor4f  (vertex_color_rgba[0], vertex_color_rgba[1], vertex_color_rgba[2], vertex_color_rgba[3]);
        }
    }

}


void Material:: renderX ()
{
    GLfloat gray[4]  = {0.8,0.8,0.8,1};
    GLfloat dark[3]  = {0.2,0.2,0.2};
    GLfloat black[3] = {0,0,0};
    GLfloat zero     = 0;

    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT  , dark );
    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE  , gray );
    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR , black);
    glMaterialf  (GL_FRONT_AND_BACK, GL_SHININESS, zero );
    glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION , black);
    glColor4f    (gray[0], gray[1], gray[2], gray[3]);
}


std::ostream& Material:: print (std::ostream& out) const
{
    out << "Material: " << hex << setw(8) << setfill('0');
    out << "  ambient=0x"  << ambient_color;
    out << ", diffuse=0x"  << diffuse_color;
    out << ", emissive=0x" << emissive_color;
    out << ", specular=0x" << specular_color << dec;
    out << ", shininess="  << shininess;
    out << ", vertex_color_tracking=" << vertex_color_tracking;
    return out;
}


std::ostream& operator<< (std::ostream& out, const Material& mat)
{
    return mat.print(out);
}
