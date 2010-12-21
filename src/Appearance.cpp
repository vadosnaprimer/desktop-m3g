#include <iostream>
#include "m3g/m3g-gl.hpp"
#include "m3g/Appearance.hpp"
#include "m3g/CompositingMode.hpp"
#include "m3g/Fog.hpp"
#include "m3g/Material.hpp"
#include "m3g/PolygonMode.hpp"
#include "m3g/Texture2D.hpp"
#include "m3g/CompositingMode.hpp"
#include "m3g/Exception.hpp"
#include "m3g/RenderState.hpp"
using namespace std;
using namespace m3g;


Appearance:: Appearance () :
    layer(0), polygon_mode(0), compositing_mode(0),
    material(0), fog(0)
{
    for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
        textures.push_back (0);
    }
}

Appearance:: ~Appearance ()
{
}

Appearance* Appearance:: duplicate () const
{
    Appearance* app = new Appearance;
    this->Object3D  :: copy (app);
    this->Appearance:: copy (app);
    return app;
}

int Appearance:: getReferences (Object3D** references) const
{
    int n = 0;
    if (polygon_mode)
        n++;
    if (compositing_mode)
        n++;
    if (material)
        n++;
    for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
        if (textures[i])
            n++;
    }
    if (fog)
        n++;

    if (references) {
        int i = 0;
        if (polygon_mode)
            references[i++] = polygon_mode;
        if (compositing_mode)
            references[i++] = compositing_mode;
        if (material)
            references[i++] = material;
        for (int j = 0; j < MAX_TEXTURE_UNITS; j++) {
            if (textures[j])
                references[i++] = textures[j];
        }
        if (fog)
            references[i++] = fog;
    }

    return n;
}

void Appearance:: mark (void(*func)(void*)) const
{
    if (func == NULL)
        return;

    Object::mark (func);
    if (polygon_mode) {
        polygon_mode->mark (func);
    }
    if (compositing_mode) {
        compositing_mode->mark (func);
    }
    if (material) {
        material->mark (func);
    }
    if (fog) {
        fog->mark (func);
    }
    for (int i = 0; i < (int)textures.size(); i++) {
        if (textures[i]) {
            textures[i]->mark (func);
        }
    }
}

void Appearance:: copy (Appearance* app) const
{
    if (app == NULL) {
        throw NullPointerException (__FILE__, __func__, "Appearance is NULL.");
    }
    app->layer            = layer;
    app->polygon_mode     = polygon_mode;
    app->compositing_mode = compositing_mode;
    app->material         = material;
    app->textures         = textures;
    app->fog              = fog;
}

int Appearance:: animate (int world_time)
{
    //cout << "Appearance: animate, time=" << world_time << "\n";

    Object3D:: animate (world_time);

    if (polygon_mode) {
        polygon_mode->animate (world_time);
    }
    if (compositing_mode) {
        compositing_mode->animate (world_time);
    }

    for (int i = 0; i < (int)textures.size(); i++) {
        if (textures[i])
            textures[i]->animate (world_time);
    }
    if (material) {
        material->animate (world_time);
    }
    if (fog) {
        fog->animate (world_time);
    }

    return 0;
}




CompositingMode* Appearance:: getCompositingMode () const
{
    return compositing_mode;
}

Fog* Appearance:: getFog () const
{
    return fog;
}

int Appearance:: getLayer () const
{
    return layer;
}

int Appearance:: getLayer2 () const
{
    int layer2 = layer*2;
    if (compositing_mode && compositing_mode->getBlending() != CompositingMode::REPLACE) {
        layer2 += 1;
    }
    return layer2;
}

Material* Appearance:: getMaterial () const
{
    return material;
}

PolygonMode* Appearance:: getPolygonMode () const
{
    return polygon_mode;
}

Texture2D* Appearance:: getTexture (int index) const
{
    if (index < 0 || index >= (int)textures.size()) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Texture index is inalid, index=%d", index);
    }
    return textures[index];
}

void Appearance:: setCompositingMode (CompositingMode* mode)
{
    // null is ok, use default.
    compositing_mode = mode;
}

void Appearance:: setFog (Fog* f)
{
    if (f == NULL) {
        throw NullPointerException (__FILE__, __func__, "Null fog is specified.");
    }
    fog = f;
}

void Appearance:: setLayer (int layer_)
{
    if (layer_ < -63 || layer_ > 64) {
        throw IllegalArgumentException (__FILE__, __func__, "Lyaer is invalid, layer=%d.", layer_);
    }
    layer = layer_;
}

void Appearance:: setMaterial (Material* mat)
{
    // null is ok, use default.
    material = mat;
}

void Appearance:: setPolygonMode (PolygonMode* mode)
{
    // null is ok, use default.
    polygon_mode = mode;
}

void Appearance:: setTexture (int index, Texture2D* texture)
{
    if (index < 0 || index >= (int)textures.size()) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Texture unit index is invalid, i=%d in [0,%d).", index, textures.size());
    }
    if (texture == NULL) {
        throw NullPointerException (__FILE__, __func__, "Null texture is specified.");
    }

    textures[index] = texture;
}


/**
 * Note: Appearance should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void Appearance:: render (RenderState& state) const
{
    if (state.pass != 2) {
        return;
    }

    //cout << "Appearance: render\n";

    if (fog)
        fog->render (state);
    else
        Fog:: renderX ();

    if (material)
        material->render (state);
    else
        Material:: renderX ();

    if (compositing_mode)
        compositing_mode->render (state);
    else
        CompositingMode:: renderX ();

    if (polygon_mode)
        polygon_mode->render (state);
    else
        PolygonMode:: renderX ();

    // ここのgl関数はTexture2Dの中に移動しようか？
    // 注意：テクスチャーマトリックスは独立に複数あるので
    // それぞれについて初期化が必要。

    glMatrixMode (GL_TEXTURE);

    glEnable (GL_TEXTURE_2D);
    for (int i = 0; i < (int)textures.size(); i++) {
        if (textures[i]) {
            glActiveTexture       (GL_TEXTURE0+i);           // テクスチャーユニットの選択     
            glEnable              (GL_TEXTURE_2D);           // テクスチャーユニットの有効化
            textures[i]->render (state);
        } else {
            glActiveTexture       (GL_TEXTURE0+i);            // テクスチャーユニットの選択     
            glDisable             (GL_TEXTURE_2D);            // テクスチャーユニットの無効化
            Texture2D:: renderX ();
        }
    }

    glMatrixMode (GL_MODELVIEW);
}


void Appearance:: renderX ()
{
    PolygonMode:: renderX ();
    CompositingMode:: renderX ();
    Material:: renderX ();
    Texture2D:: renderX ();
    Fog:: renderX ();
}

std::ostream& Appearance:: print (std::ostream& out) const
{
    out << "Appearance: ";
    out << "  layer=" << layer;
    if (polygon_mode)
        out << ", polygon_mode=" << *polygon_mode;
    else
        out << ", polygon_mode=DEFAULT";
    if (compositing_mode)
        out << ", compositing_mode=" << *compositing_mode;
    else
        out << ", compositing_mode=DEFAULT";
    if (material)
        out << ", material=" << *material;
    else
        out << ", mterial=DEFAULT";
    for (int i = 0; i < (int)textures.size(); i++) {
        if (textures[i])
            out << ", textures[" << i << "]=" << *textures[i];
        else
            out << ", textures[" << i << "]=NOT FOUND";
    }
    if (fog) 
        out << ", fog=" << *fog;
    else
        out << ", fog=DEFAULT";
    return out;
}


ostream& operator<< (ostream& out, const Appearance& app)
{
    return app.print(out);
}

