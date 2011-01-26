#include "m3g/m3g-gl.hpp"
#include "m3g/Light.hpp"
#include "m3g/Exception.hpp"
#include "m3g/AnimationTrack.hpp"
#include "m3g/AnimationController.hpp"
#include "m3g/KeyframeSequence.hpp"
#include "m3g/RenderState.hpp"
#include <iostream>
using namespace std;
using namespace m3g;

const int Light:: AMBIENT;
const int Light:: DIRECTIONAL;
const int Light:: OMNI;
const int Light:: SPOT;

Light:: Light () :
    mode(DIRECTIONAL), color(0x00ffffff), intensity(1),
    attenuation(1,0,0), spot(45,0)
{
}

Light:: ~Light ()
{
}

Light* Light:: duplicate () const
{
    return duplicate_xxx (NULL);
}

Light* Light:: duplicate_xxx (Object3D* obj) const
{
    Light* lgh  = dynamic_cast<Light*>(obj); 
    if (lgh == NULL) {
        lgh = new Light;
    }
    Node:: duplicate_xxx (lgh);

    lgh->mode        = mode;
    lgh->color       = color;
    lgh->intensity   = intensity;
    lgh->attenuation = attenuation;
    lgh->spot        = spot;

    return lgh;
}


void Light:: addAnimationTrack_xxx (AnimationTrack* animation_track, bool accepted)
{
    int property = animation_track->getTargetProperty();
    if (property == AnimationTrack::COLOR         ||
        property == AnimationTrack::INTENSITY     ||
        property == AnimationTrack::SPOT_ANGLE    ||
        property == AnimationTrack::SPOT_EXPONENT) {
        accepted = true;
    }

    Node:: addAnimationTrack_xxx (animation_track, accepted);
}

int Light:: animate_xxx (int world_time)
{
    Node:: animate_xxx (world_time);

    bool  is_color_modefied         = false;
    bool  is_intensity_modefied     = false;
    bool  is_spot_angle_modefied    = false;
    bool  is_spot_exponent_modefied = false;
    float rgb[]         = {0,0,0};
    float new_intensity = 0;
    Spot  new_spot      = Spot(0,0);
  
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
        case AnimationTrack::INTENSITY: {
            float value[1] = {1};
            keyframe->sample (sequence_time, value);
            new_intensity += value[0] * weight;
            is_intensity_modefied = true;
            //cout << "Light: intensity --> " << new_intensity << "\n";
            break;
        }
        case AnimationTrack::SPOT_ANGLE: {
            float value[1] = {1};
            keyframe->sample (sequence_time, value);
            new_spot.angle += value[0] * weight;
            is_spot_angle_modefied = true;
            //cout << "Light: spot_angle --> " << new_spot.angle << "\n";
            break;
        }
        case AnimationTrack::SPOT_EXPONENT: {
            float value[1] = {1};
            keyframe->sample (sequence_time, value);
            new_spot.exponent += value[0] * weight;
            is_spot_exponent_modefied = true;
            //cout << "Light: spot_angle --> " << new_spot.exponent << "\n";
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
        color = (color & 0xff000000) | (r << 16) | (g << 8) | (b << 0);
    }
    if (is_intensity_modefied) {
        intensity = new_intensity;
    }
    if (is_spot_angle_modefied) {
        spot.angle = clamp (0, 90, new_spot.angle);
    }
    if (is_spot_exponent_modefied) {
        spot.exponent = clamp (0, 128, new_spot.exponent);
    }

    return 0;
}


int Light:: getColor () const
{
    return color;
}

float Light:: getConstantAttenuation () const
{
    return attenuation.constant;
}

float Light:: getIntensity () const
{
    return intensity;
}

float Light:: getLinearAttenuation () const
{
    return attenuation.linear;
}

int Light:: getMode () const
{
    return mode;
}

float Light:: getQuadraticAttenuation () const
{
    return attenuation.quadratic;
}

float Light:: getSpotAngle () const
{
    return spot.angle;
}

float Light:: getSpotExponent () const
{
    return spot.exponent;
}

void Light:: setAttenuation (float constant, float linear, float quadratic)
{
    if (constant < 0 || linear < 0 || quadratic < 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Attenuation parameters is invalid, constant=%f, linear=%f, quadratic=%f.", constant, linear, quadratic);
    }
    if (constant == 0 && linear == 0 && quadratic == 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Attenuation parameters is invalid, constant=%f, linear=%f, quadratic=%f.", constant, linear, quadratic);
    }
    attenuation.constant  = constant;
    attenuation.linear    = linear;
    attenuation.quadratic = quadratic;
}

void Light:: setColor (int rgb)
{
    color = rgb & 0x00ffffff;
}

void Light:: setIntensity (float i)
{
    intensity = i;
}

void Light:: setMode (int mod)
{
    if (mod != AMBIENT && mod != DIRECTIONAL && mod != OMNI && mod != SPOT) {
        throw IllegalArgumentException (__FILE__, __func__, "Mode is invalid, mode=%d.", mod);
    }
    mode = mod;
}

void Light:: setSpotAngle (float angle)
{
    if (angle < 0 || angle > 90) {
        throw IllegalArgumentException (__FILE__, __func__, "Spot angle is invalid, angle=%f.", angle);
    }
    spot.angle = angle;
}

void Light:: setSpotExponent (float exponent)
{
    if (exponent < 0 || exponent > 128) {
        throw IllegalArgumentException (__FILE__, __func__, "Spot exponent is invalid, exponent=%f.", exponent);
    }
    spot.exponent = exponent;
}


/**
 * メモ: ここからNode::render()を呼んではいけない。
 *       ライトの位置はglLight()で指定するので。
 */
/**
 * Note: Light should be rendered only at first rendering pass(pass=1).
 * In other cases, do nothing.
 */
void Light:: render_xxx (RenderState& state) const
{
    if (state.pass != 1) {
        return;
    }

    //cout << "Light: render ================\n";
  
    int index = state.light_index++;

    GLfloat black[4] = {0,0,0,1};
    GLfloat rgba[4];
    rgba[0] = intensity * ((color & 0x00ff0000) >> 16) / 255.f;
    rgba[1] = intensity * ((color & 0x0000ff00) >>  8) / 255.f;
    rgba[2] = intensity * ((color & 0x000000ff) >>  0) / 255.f;
    rgba[3] = intensity * ((color & 0xff000000) >> 24) / 255.f;
  
    Transform trans;
    getCompositeTransform (&trans);
    float m[16];
    trans.get (m);

    glEnable  (GL_LIGHTING);
    glEnable  (GL_LIGHT0+index);

    if (mode == AMBIENT) {
        //cout << "AMBIENT light\n";
        glLightfv (GL_LIGHT0+index, GL_AMBIENT,  rgba);
        glLightfv (GL_LIGHT0+index, GL_DIFFUSE,  black);
        glLightfv (GL_LIGHT0+index, GL_SPECULAR, black);
        glLightf  (GL_LIGHT0+index, GL_SPOT_CUTOFF, 180.0f);
    }
    else if (mode == DIRECTIONAL) {
        //cout << "DIRECTIOANL light\n";
        GLfloat xyzw[4] = {m[2], m[6], m[10], 0};
        glLightfv (GL_LIGHT0+index, GL_POSITION, xyzw);
        glLightfv (GL_LIGHT0+index, GL_AMBIENT,  black);
        glLightfv (GL_LIGHT0+index, GL_DIFFUSE,  rgba);
        glLightfv (GL_LIGHT0+index, GL_SPECULAR, rgba);
        glLightf  (GL_LIGHT0+index, GL_SPOT_CUTOFF, 180.0f);
    }
    else if (mode == OMNI) {
        GLfloat xyzw[4] = {m[3], m[7], m[11], 1.0f};
        //cout << "OMNI light: xyzw = " << xyzw[0] << ", "<< xyzw[1] << ", "<< xyzw[2] << ", "<< xyzw[3] << "\n";
        //cout << "OMNI light: color = " << rgba[0] << ", "<< rgba[1] << ", "<< rgba[2] << ", "<< rgba[3] << "\n";
        //cout << "index = " << index << "\n";
        glLightfv (GL_LIGHT0+index, GL_POSITION, xyzw);
        glLightfv (GL_LIGHT0+index, GL_AMBIENT,  black);
        glLightfv (GL_LIGHT0+index, GL_DIFFUSE,  rgba);
        glLightfv (GL_LIGHT0+index, GL_SPECULAR, rgba);
        glLightf  (GL_LIGHT0+index, GL_SPOT_CUTOFF, 180.f);
    }
    else if (mode == SPOT) {
        //cout << "-------------------------SPOT light----------\n";
        GLfloat pos[4] = {m[3], m[7], m[11], 1};
        GLfloat dir[4] = {-m[2], -m[6], -m[10], 0};
        glLightfv (GL_LIGHT0+index, GL_POSITION, pos);
        glLightfv (GL_LIGHT0+index, GL_AMBIENT,  black);
        glLightfv (GL_LIGHT0+index, GL_DIFFUSE,  rgba);
        glLightfv (GL_LIGHT0+index, GL_SPECULAR, rgba);
        glLightfv (GL_LIGHT0+index, GL_SPOT_DIRECTION, dir);
        glLightf  (GL_LIGHT0+index, GL_SPOT_EXPONENT, spot.exponent);
        glLightf  (GL_LIGHT0+index, GL_SPOT_CUTOFF,   spot.angle);
    }
    else {
        throw IllegalArgumentException (__FILE__, __func__, "Invalid light mode, mode=%d.", mode);
    }

    glLightf (GL_LIGHT0+index, GL_CONSTANT_ATTENUATION,  attenuation.constant);
    glLightf (GL_LIGHT0+index, GL_LINEAR_ATTENUATION,    attenuation.linear);
    glLightf (GL_LIGHT0+index, GL_QUADRATIC_ATTENUATION, attenuation.quadratic);

}


static
const char* mode_to_string (int mode)
{
    switch (mode) {
    case Light::AMBIENT    : return "AMBIENT";
    case Light::DIRECTIONAL: return "DIRECTIONAL";
    case Light::OMNI       : return "OMNI";
    case Light::SPOT       : return "SPOT";
    default: return "Unknown";
    }
}

std::ostream& Light:: print (std::ostream& out) const
{
    out << "Light: mode="   << mode_to_string(mode);
    out << ", color=0x"     << hex << color << dec;
    out << ", intensity="   << intensity;
    out << ", attenuation=" << attenuation.constant;
    out << ","              << attenuation.linear;
    out << ","              << attenuation.quadratic;
    out << ", spot="        << spot.angle;
    out << ","              << spot.exponent;
    return out;
}

std::ostream& operator<< (std::ostream& out, const Light& lig)
{
    return lig.print(out);
}
