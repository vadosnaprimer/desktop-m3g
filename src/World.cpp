#include "m3g/World.hpp"
#include "m3g/Camera.hpp"
#include "m3g/Background.hpp"
#include "m3g/Light.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "m3g/Exception.hpp"
#include "m3g/RenderState.hpp"
using namespace m3g;
using namespace std;
#include <iterator>


World:: World () :
    background(0), active_camera(0)
{
}

World:: ~World ()
{
}

World* World:: duplicate () const
{
    World* wld   = new World;
    this->Object3D     :: copy (wld);
    this->Transformable:: copy (wld);
    this->Node         :: copy (wld);
    this->Group        :: copy (wld);
    this->World        :: copy (wld);
    return wld;
}

void World:: mark (void(*func)(void*)) const
{
    if (func == NULL)
        return;
    
    Group::mark (func);
    if (background) {
        background->mark (func);
    }
    if (active_camera) {
        active_camera->mark (func);
    }
}


void World:: copy (World* wld) const
{
    wld->background = (background == NULL) ? NULL : background->duplicate ();
    wld->active_camera     = (active_camera     == NULL) ? NULL : dynamic_cast<Camera*>(active_camera->getDuplicatedNode());
}

int World:: animate (int world_time)
{
    //cout << "World: animate, time=" << world_time << "\n";

    Group:: animate (world_time);

    if (background) {
        background->animate (world_time);
    }
    if (active_camera) {
        active_camera->animate (world_time);
    }

    return 0;
}

int World:: getReferences (Object3D** references) const
{
    int n  = Group:: getReferences (0);
    int n0 = n;
    if (background)
        n++;
    if (active_camera)
        n++;

    if (references) {
        int i = n0;
        Group:: getReferences (references);
        if (background)
            references[i++] = background;
        if (active_camera)
            references[i++] = active_camera;
    }
    
    return n;
}


Camera* World:: getActiveCamera () const
{
    return active_camera;
}

Background* World:: getBackground () const
{
    return background;
}

void World:: setActiveCamera (Camera* cam)
{
    if (cam == NULL) {
        throw NullPointerException (__FILE__, __func__, "Camera is NULL.");
    }
    active_camera = cam;
}

void World:: setBackground (Background* bg)
{
    if (bg == NULL) {
        throw NullPointerException (__FILE__, __func__, "Background is NULL.");
    }

    background = bg;
}

/**
 * Note: World should be rendered via all rendering pass.
 *   pass=-1: setup valid layers.
 *   pass=0: render background and camera.
 *   pass=1: render lights.
 *   pass=2: render objets.
 */
void World:: render (RenderState& state) const
{
    if (active_camera == NULL) {
        throw IllegalStateException (__FILE__, __func__, "Active camera is NULL.");
    }
    
    //cout << "World render\n";
    
    state.camera = active_camera;

    vector<int>& v = state.valid_layers;

    switch (state.pass) {
    case -1:
        // 使用するレイヤー番号の収集
        Group::render (state);
        sort (v.begin(), v.end());
        v.erase (unique(v.begin(), v.end()), v.end());
        break;
    case 0: {
        // バックグラウンドとカメラ
        if (background) {
            background->render (state);
        } else {
            Background:: renderX ();
        }
        active_camera->render (state);
        break;
    }
    case 1:
        // ライト
        state.light_index = 0;
        Group::render (state);
        break;
    case 2:
        // プリミティブ
        for (int i = 0; i < (int)state.valid_layers.size(); i++) {
            state.layer = state.valid_layers[i];
            Group::render (state);
        }
        break;
    default:
        throw IllegalStateException (__FILE__, __func__, "Render pass is invalid, pass=%d.", state.pass);
    }

}



std::ostream& World::print (std::ostream& out) const
{
    out << "World: \n";
    int index = -1;
    for (int i = 0; i < (int)children.size(); i++) {
        if (children[i] == active_camera) {
            index = i;
            break;
        }
    }
    if (index >= 0)
        out << "  active camera = [" << index << "]\n";
    else 
        out << "  active camera = NOT FOUND\n";
    if (background)
        out << "  background    = " << *background << "\n";
    else 
        out << "  background    = NOT FOUND\n";
    for (int i = 0; i < (int)children.size(); i++) {
        out << "  [" << i << "] : ";
        children[i]->print(out) << "\n";
    }

    return out;
}

std::ostream& operator<< (std::ostream& out, const m3g::World& wld)
{
    return wld.print(out);
}
