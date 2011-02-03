#include "m3g/m3g-gl.hpp"
#include "m3g/Sprite3D.hpp"
#include "m3g/Appearance.hpp"
#include "m3g/Image2D.hpp"
#include "m3g/Exception.hpp"
#include "m3g/Graphics3D.hpp"
#include "m3g/Vector.hpp"
#include "m3g/AnimationTrack.hpp"
#include "m3g/AnimationController.hpp"
#include "m3g/KeyframeSequence.hpp"
#include "m3g/RenderState.hpp"
#include "m3g/CompositingMode.hpp"
#include "m3g/Fog.hpp"
#include "m3g/Intersect.hpp"
#include "m3g/RayIntersection.hpp"
#include "m3g/Camera.hpp"
#include <iostream>
#include <cmath>
using namespace std;
using namespace m3g;


Sprite3D:: Sprite3D (bool scaled_, Image2D* image_, Appearance* appearance_) :
    scaled(false), image(0), appearance(0), crop(0,0,0,0),
    texobj(0)
{
    if (image_ == NULL) {
        throw NullPointerException (__FILE__, __func__, "Image is NULL.");
    }

    scaled      = scaled_;
    image       = image_;
    appearance  = appearance_;
    crop.x      = 0;
    crop.y      = 0;
    crop.width  = image->getWidth();
    crop.height = image->getHeight();

    glGenTextures   (1, &texobj);

    int err = glGetError ();
    if (err != GL_NO_ERROR) {
        throw OpenGLException (__FILE__, __func__, "Can't make texture object, err=%d.", err);
    }

    setImage (image);
}

Sprite3D:: ~Sprite3D ()
{
    if (texobj > 0)  {
        glDeleteTextures (1, &texobj);
    }
}

Sprite3D* Sprite3D:: duplicate () const
{
    return duplicate_xxx (NULL);
}

Sprite3D* Sprite3D:: duplicate_xxx (Object3D* obj) const
{
    Sprite3D* spr = dynamic_cast<Sprite3D*>(obj);
    if (spr == NULL) {
        spr = new Sprite3D (scaled, image, appearance);
    }

    Node:: duplicate_xxx (spr);

    spr->crop       = crop;

    return spr;
}



int Sprite3D:: getReferences_xxx (Object3D** references) const
{
    int n = Node:: getReferences_xxx (references);
    if (image)
        references ? references[n] = image, n++ : n++;
    if (appearance)
        references ? references[n] = appearance, n++ : n++;

    return n;
}

void Sprite3D:: addAnimationTrack_xxx (AnimationTrack* animation_track, bool accepted)
{
    int property = animation_track->getTargetProperty();
    if (property == AnimationTrack::CROP) {
        accepted = true;
    }
    Object3D:: addAnimationTrack_xxx (animation_track, accepted);
}

int Sprite3D:: animate_xxx (int world_time)
{
    Node:: animate_xxx (world_time);

    bool     is_crop_modefied = false;
    CropRect new_crop         = CropRect(0,0,0,0);
    
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
        case AnimationTrack:: CROP: {
            float value[4] = {0,0,0,0};
            keyframe->sample (sequence_time, value);
            if (keyframe->getComponentCount() == 4) {
                new_crop.x      += value[0] * weight;
                new_crop.y      += value[1] * weight;
                new_crop.width  += value[2] * weight;
                new_crop.height += value[3] * weight;
            }
            else {
                new_crop.x      += value[0] * weight;
                new_crop.y      += value[1] * weight;
                new_crop.width  += crop.width * weight;
                new_crop.height += crop.height * weight;
	
            }
            is_crop_modefied = true;
            //cout << "Sprite3D: crop --> " << crop.x << ", " << crop.y << ", " << crop.width << ", " << crop.height << "\n";
        }
        default: {
            // Unknown target should be ignored.
            // animate() of Base class (of Derived class) retrieve it.
        }
        }
    }

    if (is_crop_modefied) {
        crop = new_crop;
    }
  
    return 0;
}

Appearance* Sprite3D:: getAppearance () const
{
    return appearance;
}

int Sprite3D:: getCropHeight () const
{
    return crop.height;
}

int Sprite3D:: getCropWidth () const
{
    return crop.width;
}

int Sprite3D:: getCropX () const
{
    return crop.x;
}

int Sprite3D:: getCropY () const
{
    return crop.y;
}

Image2D* Sprite3D:: getImage () const
{
    return image;
}


/**
 * 注意1: org,dir,riはすべてNDC座標系
 * 注意2: NDC座標系はOpenGLで一般的な右手座標系ではなく「左手座標系」
 *        従って交差判定に渡す頂点は「時計回り」
 *        v3 -- v1
 *         | ／ |
 *        v2 -- v0
 * 注意3: M3Gの仕様ではピック出来るのはscaledのみ。
 */
bool Sprite3D:: intersect (const Vector& org, const Vector& dir, const Camera* cam, RayIntersection* ri) const
{
    if (!isGlobalPickingEnabled()) {
        return false;
    }

    //cout << "Sprite3D: intersect, scaled=" << scaled << "\n";
    //cout << "org = " << org << "\n";
    //cout << "dir = " << dir << "\n";

    Vector center = getCenterPoint (cam);
    float  width  = scaled ? getScaledWidth (cam)  : getUnscaledWidth ();
    float  height = scaled ? getScaledHeight (cam) : getUnscaledHeight ();

    //cout << "center = " << center << "\n";
    //cout << "width  = " << width   << "\n";
    //cout << "height = " << height  << "\n";
    
    Vector v0 = center + Vector(width/2, -height/2, 0);
    Vector v1 = center + Vector(width/2,  height/2, 0);
    Vector v2 = center + Vector(-width/2, -height/2, 0);
    Vector v3 = center + Vector(-width/2,  height/2, 0);
    
    float u,v,t;
    bool  hit;
    
    Vector* vertices[2][3] = {{&v2, &v1, &v0}, {&v2,&v3,&v1}};
    int     indices[2][3]  = {{2,1,0}, {2,3,1}};

    for (int i = 0; i < 2; i++) {
        hit = triangle_intersect (org, dir, 
                                  *vertices[i][0], *vertices[i][1], *vertices[i][2],
                                  &u, &v, &t);
        if (hit) {
            if (ri) {
                *ri = RayIntersection (const_cast<Sprite3D*>(this),
                                       org, dir, t,
                                       u, v,
                                       3, indices[i],
                                       0);
            }
            return true;
        }
    }

    return false;
}

bool Sprite3D:: isScaled () const
{
    return scaled;
}

void Sprite3D:: setAppearance (Appearance* appearance_)
{
    appearance = appearance_;
}

void Sprite3D:: setCrop (int crop_x, int crop_y, int crop_width, int crop_height)
{
    crop.x      = crop_x;
    crop.y      = crop_y;
    crop.width  = crop_width;
    crop.height = crop_height;
}



void Sprite3D:: setImage (Image2D* img)
{
    if (img == NULL) {
        throw NullPointerException (__FILE__, __func__, "Image is NULL.");
    }
    int width  = img->getWidth ();
    int height = img->getHeight ();
    if ((width & (width-1)) || (height & (height-1))) {
        throw IllegalArgumentException (__FILE__, __func__, "Image size must be power of 2. w=%d,h=%d", width, height);
    }
    if (texobj == 0) {
        throw OpenGLException (__FILE__, __func__, "Texture object is not ready.");
    }

    image       = img;
    crop.x      = 0;
    crop.y      = 0;
    crop.width  = image->getWidth();
    crop.height = image->getHeight();

    int   format = image->getOpenGLFormat ();
    void* data   = image->getOpenGLPointer ();

    glBindTexture   (GL_TEXTURE_2D, texobj);
    glPixelStorei   (GL_UNPACK_ALIGNMENT, 1);

    gluBuild2DMipmaps (GL_TEXTURE_2D, GL_RGBA, image->getWidth(), image->getHeight(), format, GL_UNSIGNED_BYTE, data);
}

/**
 * Note: Sprite3D should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void Sprite3D:: render_xxx (RenderState& state) const
{
    if (!isGlobalRenderingEnabled()) {
        return;
    }
    if (appearance == NULL)
        return;

    if (state.pass == -1) {
        state.valid_layers.push_back (appearance->getLayer2());
    }
    if (state.pass != 2) {
        return;
    }
    if (appearance->getLayer2() != state.layer) {
        return;
    }

    // cout << "Sprite3D: render \n";

    Node:: render_xxx (state);

    // メモ：規格でCompositingModeとFog以外はデフォルトを使用する。
    Appearance:: renderX ();
    CompositingMode* cmp = appearance->getCompositingMode ();
    if (cmp) {
        cmp->render (state);
    }
    Fog* fog = appearance->getFog ();
    if (fog) {
        fog->render (state);
    }


    GLfloat border_color[4] = {1,1,1,0};
    glActiveTexture  (GL_TEXTURE0);
    glEnable         (GL_TEXTURE_2D);
    glBindTexture    (GL_TEXTURE_2D, texobj);
    glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameterfv (GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
    glTexEnvi        (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable         (GL_ALPHA_TEST);
    glAlphaFunc      (GL_GREATER, 0);

    const Camera* cam = state.camera;

    Vector center = getCenterPoint (cam);
    float  tx     = center.x;
    float  ty     = center.y;
    float  tz     = center.z;

    Vector tex_coord0 = getTexCoord0 ();
    Vector tex_coord1 = getTexCoord1 ();
    float  s0         = tex_coord0.x;
    float  t0         = tex_coord0.y;
    float  s1         = tex_coord1.x;
    float  t1         = tex_coord1.y;

    float width  = scaled ? getScaledWidth(cam)  : getUnscaledWidth();
    float height = scaled ? getScaledHeight(cam) : getUnscaledHeight();

    glMatrixMode   (GL_PROJECTION);
    glPushMatrix   ();
    glLoadIdentity ();
    glMatrixMode   (GL_MODELVIEW);
    glPushMatrix   ();
    glLoadIdentity ();
    
    glBegin      (GL_TRIANGLE_STRIP);
    glColor4f    (1,1,1,1);
    glTexCoord2f (s1, t1);
    glVertex3f   (tx+width/2.f, ty-height/2.f, tz);
    glTexCoord2f (s1, t0);
    glVertex3f   (tx+width/2.f, ty+height/2.f, tz);
    glTexCoord2f (s0, t1);
    glVertex3f   (tx-width/2.f, ty-height/2.f, tz);
    glTexCoord2f (s0, t0);
    glVertex3f   (tx-width/2.f, ty+height/2.f, tz);
    glEnd        ();
    
    glMatrixMode (GL_PROJECTION);
    glPopMatrix  ();
    glMatrixMode (GL_MODELVIEW);
    glPopMatrix  ();
    
}

Vector Sprite3D:: getCenterPoint (const Camera* cam) const
{
    Transform tr;

    getTransformTo (cam, &tr);
    Matrix model_view = tr.getMatrix ();

    cam->getProjection (&tr);
    Matrix projection = tr.getMatrix ();


    Vector o_mdl = Vector(0,0,0);
    Vector o_cam = (model_view * o_mdl).divided_by_w();
    Vector o_ndc = (projection * o_cam).divided_by_w();
    
    return o_ndc;
}


Vector Sprite3D:: getTexCoord0 () const
{
    float width  = image->getWidth ();
    float height = image->getHeight ();

    // s,t = 0〜1
    float s = (crop.width  >= 0) ? crop.x/width  : (crop.x - crop.width)/width;
    float t = (crop.height >= 0) ? crop.y/height : (crop.y - crop.height)/height;
    
    // テクスチャー座標は左下が(0,0)
    return Vector (s,1-t,0);
}

Vector Sprite3D:: getTexCoord1 () const
{
    float width  = image->getWidth ();
    float height = image->getHeight ();

    // s,t = 0〜1
    float s = (crop.width  >= 0) ? (crop.x + crop.width) /width  : crop.x/width;
    float t = (crop.height >= 0) ? (crop.y + crop.height)/height : crop.y/height;
    
    // テクスチャー座標は左下が(0,0)
    return Vector (s,1-t,0);
}

float Sprite3D:: getScaledHeight (const Camera* cam) const
{
    Transform tr;

    getTransformTo (cam, &tr);
    Matrix model_view = tr.getMatrix ();

    cam->getProjection (&tr);
    Matrix projection = tr.getMatrix ();

    //cout << "Sprite3D:: model_view = " << model_view << "\n";
    //cout << "Sprite3D:: projection = " << projection << "\n";

    // カメラ空間
    Vector o_cam  = (model_view * Vector(0,0,0)).divided_by_w();
    Vector px_cam = (model_view * Vector(0,1,0)).divided_by_w();
    float  dy_cam = fabsf(px_cam.y - o_cam.y);
    //cout << "Sprite3D: dy_cam = " << dy_cam << "\n";

    // NDC空間
    Vector o_ndc  = (projection * o_cam                       ).divided_by_w();
    Vector px_ndc = (projection * (o_cam + Vector(0,dy_cam,0))).divided_by_w();
    float  dy_ndc = fabsf(px_ndc.y - o_ndc.y);
    //cout << "Sprite3D: dy_cam = " << dy_cam << "\n";

    return dy_ndc;
}

float Sprite3D:: getScaledWidth (const Camera* cam) const
{
    Transform tr;

    getTransformTo (cam, &tr);
    Matrix model_view = tr.getMatrix ();

    cam->getProjection (&tr);
    Matrix projection = tr.getMatrix ();

    //cout << "Sprite3D:: model_view = " << model_view << "\n";
    //cout << "Sprite3D:: projection = " << projection << "\n";

    // カメラ空間
    Vector o_cam  = (model_view * Vector(0,0,0)).divided_by_w();
    Vector px_cam = (model_view * Vector(1,0,0)).divided_by_w();
    float  dx_cam = fabsf(px_cam.x - o_cam.x);
    //cout << "Sprite3D: dx_cam = " << dx_cam << "\n";

    // NDC空間
    Vector o_ndc  = (projection * o_cam                       ).divided_by_w();
    Vector px_ndc = (projection * (o_cam + Vector(dx_cam,0,0))).divided_by_w();
    float  dx_ndc = fabsf(px_ndc.x - o_ndc.x);
    //cout << "Sprite3D: dx_ndc = " << dx_ndc << "\n";

    return dx_ndc;
}

float Sprite3D:: getUnscaledWidth () const
{
    Graphics3D* g3d      = Graphics3D::getInstance();
    float image_width    = image->getWidth ();
    float viewport_width = g3d->getViewportWidth ();
    float dx_ndc         = 2*image_width/viewport_width;

    return dx_ndc;
}

float Sprite3D:: getUnscaledHeight () const
{
    Graphics3D* g3d       = Graphics3D::getInstance();
    float image_height    = image->getHeight ();
    float viewport_height = g3d->getViewportHeight ();
    float dy_ndc          = 2*image_height/viewport_height;

    return dy_ndc;
}



std::ostream& Sprite3D:: print (std::ostream& out) const
{
    int width  = image ? image->getWidth() : 0;
    int height = image ? image->getHeight() : 0;
    out << "Sprite3D: ";
    out << "  scaled=" << scaled;
    out << ", image=" << image << "(" << width << "x" << height << ")";
    out << ", appearance=" << appearance;
    out << ", crop=" << crop.x << "," << crop.y << "," << crop.width << "," << crop.height;
    return out;
}

std::ostream& operator<< (std::ostream& out, const Sprite3D& spr)
{
    return spr.print(out);
}


