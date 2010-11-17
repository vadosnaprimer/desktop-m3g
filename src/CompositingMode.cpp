#include <iostream>
#include "m3g/m3g-gl.hpp"
#include "m3g/CompositingMode.hpp"
#include "m3g/Exception.hpp"
#include "m3g/RenderState.hpp"
using namespace m3g;
using namespace std;

const int CompositingMode:: ALPHA;
const int CompositingMode:: ALPHA_ADD;
const int CompositingMode:: MODULATE;
const int CompositingMode:: MODULATE_X2;
const int CompositingMode:: REPLACE;

static
const char* mode_to_string (int mode);

CompositingMode:: CompositingMode () :
    blending_mode(REPLACE), alpha_threshold(0), depth_offset(0,0),
    depth_test(true), depth_write(true), color_write(true), alpha_write(true)
{
}

CompositingMode:: ~CompositingMode ()
{
}

CompositingMode* CompositingMode:: duplicate () const
{
    CompositingMode* cmode = new CompositingMode;
    this->Object3D       :: copy (cmode);
    this->CompositingMode:: copy (cmode);
    return cmode;
}

void CompositingMode:: copy (CompositingMode* cmode) const
{
    if (cmode == NULL) {
        throw NullPointerException (__FILE__, __func__, "CompositingMode is NULL.");
    }
    cmode->blending_mode   = blending_mode;
    cmode->alpha_threshold = alpha_threshold;
    cmode->depth_offset    = depth_offset;
    cmode->depth_test      = depth_test;
    cmode->depth_write     = depth_write;
    cmode->color_write     = color_write;
    cmode->alpha_write     = alpha_write;
}

float CompositingMode:: getAlphaThreshold () const
{
    return alpha_threshold;
}

int CompositingMode:: getBlending () const
{
    return blending_mode;
}

float CompositingMode:: getDepthOffsetFactor () const
{
    return depth_offset.factor;
}

float CompositingMode:: getDepthOffsetUnits () const
{
    return depth_offset.units;
}

bool CompositingMode:: isAlphaWriteEnabled () const
{
    return alpha_write;
}


bool CompositingMode:: isColorWriteEnabled () const
{
    return color_write;
}

bool CompositingMode:: isDepthTestEnabled () const
{
    return depth_test;
}

bool CompositingMode:: isDepthWriteEnabled () const
{
    return depth_write;
}

void CompositingMode:: setAlphaThreshold (float threashold)
{
    if (threashold < 0 || threashold > 1) {
        throw IllegalArgumentException (__FILE__, __func__, "Alpha threashold is invalid, th=%f.", threashold);
    }

    alpha_threshold = threashold;
}

void CompositingMode:: setAlphaWriteEnable (bool enable)
{
    alpha_write = enable;
}

void CompositingMode:: setBlending (int mode)
{
    if (mode < ALPHA || mode > REPLACE) {
        throw IllegalArgumentException (__FILE__, __func__, "Blending mode is invalid, mode=%d.", mode);
    }
    blending_mode = mode;
}

void CompositingMode:: setColorWriteEnable (bool enable)
{
    color_write = enable;
}

void CompositingMode:: setDepthOffset (float factor, float units)
{
    depth_offset = DepthOffset(factor, units);
}

void CompositingMode:: setDepthTestEnable (bool enable)
{
    depth_test = enable;
}

void CompositingMode:: setDepthWriteEnable (bool enable)
{
    depth_write = enable;
}

/**
 * Note: CompositingMode should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void CompositingMode:: render (RenderState& state) const
{
    if (state.pass != 2) {
        return;
    }
    if (this == NULL) {
        renderX ();
        return;
    }

    //cout << "CompositingMode: render\n";

    switch (depth_test) {
    case true  : glDepthFunc (GL_LESS); break;
    case false : glDepthFunc (GL_ALWAYS);
    }

    glDepthMask (depth_write);
    glColorMask (color_write, color_write, color_write, alpha_write);

    glEnable (GL_BLEND);
    switch (blending_mode) {
    case REPLACE    : glBlendFunc (GL_ONE, GL_ZERO)           ; break;
    case ALPHA_ADD  : glBlendFunc (GL_SRC_ALPHA, GL_ONE)      ; break;
    case ALPHA      : glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ; break;
    case MODULATE   : glBlendFunc (GL_DST_COLOR, GL_ZERO)     ; break;
    case MODULATE_X2: glBlendFunc (GL_DST_COLOR, GL_SRC_COLOR); break;
    default: throw InternalException (__FILE__, __func__, "Blending mode is invalid, mode=%d.", blending_mode);
    }

    // TODO: 完全にdisableにするのではなく0にした方が
    // ドライバーレベルで高速化してくれそう
    if (alpha_threshold > 0) {
        glEnable    (GL_ALPHA_TEST);
        glAlphaFunc (GL_GEQUAL, alpha_threshold);      
    } else {
        glDisable (GL_ALPHA_TEST);
    }

    if (depth_offset.factor || depth_offset.units) {
        glEnable (GL_POLYGON_OFFSET_FILL);
        glPolygonOffset (depth_offset.factor, depth_offset.units);
    } else {
        glDisable (GL_POLYGON_OFFSET_FILL);
    }

}

void CompositingMode:: renderX ()
{
    glDepthFunc (GL_LESS);
    glDepthMask (GL_TRUE);
    glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glBlendFunc (GL_ONE, GL_ZERO);
    glDisable   (GL_ALPHA_TEST);
    glDisable   (GL_POLYGON_OFFSET_FILL);
}



static
const char* mode_to_string (int mode)
{
    switch (mode) {
    case CompositingMode::ALPHA      : return "ALPHA";
    case CompositingMode::ALPHA_ADD  : return "ALPHA_ADD";
    case CompositingMode::MODULATE   : return "MODULATE";
    case CompositingMode::MODULATE_X2: return "MODULATE_X2";
    case CompositingMode::REPLACE    : return "REPLACE";
    default: return "Unknown";
    }
}

std::ostream& CompositingMode:: print (std::ostream& out) const
{
    out << "CompositingMode: ";
    out << "  blending_mode="    << mode_to_string(blending_mode);
    out << ", alpha_threashold=" << alpha_threshold;
    out << ", depth_offset="     << depth_offset.units << "," << depth_offset.factor;
    out << ", depth_test="       << depth_test;
    out << ", depth_write="      << depth_write;
    out << ", color_write="      << color_write;
    out << ", alpha_write="      << alpha_write;
    return out;
}

std::ostream& operator<< (std::ostream& out, const CompositingMode& cm)
{
    return cm.print(out);
}

