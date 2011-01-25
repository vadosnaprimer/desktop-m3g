#include "m3g/m3g-gl.hpp"
#include "m3g/PolygonMode.hpp"
#include "m3g/Exception.hpp"
#include "m3g/RenderState.hpp"
#include <iostream>
using namespace std;
using namespace m3g;

const int PolygonMode:: CULL_BACK;
const int PolygonMode:: CULL_FRONT;
const int PolygonMode:: CULL_NONE;
const int PolygonMode:: SHADE_FLAT;
const int PolygonMode:: SHADE_SMOOTH;
const int PolygonMode:: WINDING_CCW;
const int PolygonMode:: WINDING_CW;

PolygonMode:: PolygonMode () :
    culling(CULL_BACK), winding(WINDING_CCW) ,shading(SHADE_SMOOTH),
    two_sided_lighting(false), local_camera_lighting(true), perspective_correction(true)
{
}

PolygonMode:: ~PolygonMode ()
{
}

PolygonMode* PolygonMode:: duplicate () const
{
    PolygonMode* pmode = new PolygonMode;
    this->Object3D   :: copy (pmode);
    this->PolygonMode:: copy (pmode);
    return pmode;
}

void PolygonMode:: copy (PolygonMode* pmode) const
{
    if (pmode == NULL) {
        throw NullPointerException (__FILE__, __func__, "PolyMode is NULL.");
    }
    pmode->culling                = culling;
    pmode->winding                = winding;
    pmode->shading                = shading;
    pmode->two_sided_lighting     = two_sided_lighting;
    pmode->local_camera_lighting  = local_camera_lighting;
    pmode->perspective_correction = perspective_correction;
}

int PolygonMode:: getCulling () const
{
    return culling;
}

int PolygonMode:: getShading () const
{
    return shading;
}

int PolygonMode:: getWinding () const
{
    return winding;
}

bool PolygonMode:: isLocalCameraLightingEnabled () const
{
    return local_camera_lighting;
}

bool PolygonMode:: isPerspectiveCorrectionEnabled () const
{
    return perspective_correction;
}

bool PolygonMode:: isTwoSidedLightingEnabled () const
{
    return two_sided_lighting;
}

void PolygonMode:: setCulling (int mode)
{
    if (mode != CULL_BACK && mode != CULL_FRONT && mode != CULL_NONE) {
        throw IllegalArgumentException (__FILE__, __func__, "Mode is invalid, mode=%d.", mode);
    }
    culling = mode;
}

void PolygonMode:: setLocalCameraLightingEnable (bool enable)
{
    local_camera_lighting = enable;
}

void PolygonMode:: setPerspectiveCorrectionEnable (bool enable)
{
    perspective_correction = enable;
}

void PolygonMode:: setShading (int mode)
{
    if (mode != SHADE_FLAT && mode != SHADE_SMOOTH) {
        throw IllegalArgumentException (__FILE__, __func__, "Mode is invalid, mode=%d.", mode);
    }
    shading = mode;
}

void PolygonMode:: setTwoSidedLightingEnable (bool enable)
{
    two_sided_lighting = enable;
}

void PolygonMode:: setWinding (int mode)
{
    if (mode != WINDING_CCW && mode != WINDING_CW) {
        throw IllegalArgumentException (__FILE__, __func__, "Mode is invalid, mode=%d.", mode);
    }
    winding = mode;
}

void PolygonMode:: render_xxx (RenderState& state) const
{
    if (state.pass != 2) {
        return;
    }

    //cout << "PolygonMode: render\n";

    switch (winding) {
    case WINDING_CCW: glFrontFace (GL_CCW); break;
    case WINDING_CW : glFrontFace (GL_CW) ; break;
    default : throw InternalException (__FILE__, __func__, "Winding mode is invalid, mode=%d\n", winding);
    }

    switch (culling) {
    case CULL_FRONT: glEnable (GL_CULL_FACE); glCullFace (GL_FRONT); break;
    case CULL_BACK : glEnable (GL_CULL_FACE); glCullFace (GL_BACK) ; break;
    case CULL_NONE : glDisable(GL_CULL_FACE); break;
    default : throw InternalException (__FILE__, __func__, "Culling mode is invalid, mode=%d\n", culling);
    }

    switch (two_sided_lighting) {
    case true : glLightModeli (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE) ; break;
    case false: glLightModeli (GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE); break;
    default : throw InternalException (__FILE__, __func__, "Two sided lighting is invalid, mode=%d\n", two_sided_lighting);
    }

    switch (shading) {
    case SHADE_FLAT  : glShadeModel (GL_FLAT)  ; break;
    case SHADE_SMOOTH: glShadeModel (GL_SMOOTH); break;
    default : throw InternalException (__FILE__, __func__, "Shading mode is invalid, mode=%d\n", shading);
    }

    switch (local_camera_lighting) {
    case true : glLightModeli (GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE) ; break;
    case false: glLightModeli (GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE); break;
    default: throw InternalException (__FILE__, __func__, "Local camera lighting is invalid, mode=%d\n", local_camera_lighting);
    }

    switch (perspective_correction) {
    case true : glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST) ; break;
    case false: glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST); break;
    default: throw InternalException (__FILE__, __func__, "Perspective correction is invalid, mode=%d\n", perspective_correction);
    }


}

void PolygonMode:: renderX ()
{
    glFrontFace   (GL_CCW);
    glCullFace    (GL_BACK);
    glEnable      (GL_CULL_FACE);
    glShadeModel  (GL_SMOOTH);
    glLightModeli (GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glLightModeli (GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glHint        (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}


static
const char* culling_to_string (int culling)
{
    switch (culling) {
    case PolygonMode::CULL_FRONT: return "CULL_FRONT";
    case PolygonMode::CULL_BACK : return "CULL_BACK";
    case PolygonMode::CULL_NONE : return "CULL_NONE";
    default: return "Unknown";
    }
}
static
const char* winding_to_string (int winding)
{
    switch (winding) {
    case PolygonMode::WINDING_CCW: return "WINDING_CCW";
    case PolygonMode::WINDING_CW : return "WINDING_CW";
    default: return "Unknown";
    }
}
static
const char* shading_to_string (int shading)
{
    switch (shading) {
    case PolygonMode::SHADE_FLAT   : return "SHADE_FLAT";
    case PolygonMode::SHADE_SMOOTH : return "SHADE_SMOOTH";
    default: return "Unknown";
    }
}

std::ostream& PolygonMode:: print (std::ostream& out) const
{
    out << "PolygonMode: ";
    out << "  culling="                << culling_to_string(culling);
    out << ", winding="                << winding_to_string(winding);
    out << ", shading="                << shading_to_string(shading);
    out << ", two_sided_lighting="     << two_sided_lighting;
    out << ", local_camera_lighting="  << local_camera_lighting;
    out << ", perspective_correction=" << perspective_correction;
    return out;
}

std::ostream& operator<< (std::ostream& out, const PolygonMode& pmode)
{
    return pmode.print(out);
}

