#include "World.hpp"
#include "Camera.hpp"
#include "Background.hpp"
#include "Light.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Exception.hpp"
#include "RenderState.hpp"
using namespace m3g;
using namespace std;
#include <iterator>


World:: World () :
    background(0), camera(0)
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
}


void World:: copy (World* wld) const
{
    wld->background = (background == NULL) ? NULL : background->duplicate ();
    wld->camera     = (camera     == NULL) ? NULL : dynamic_cast<Camera*>(camera->getDuplicatedNode());
}

int World:: animate (int world_time)
{
    //cout << "World: animate, time=" << world_time << "\n";

    Group:: animate (world_time);

    if (background) {
        background->animate (world_time);
    }
    if (camera) {
        camera->animate (world_time);
    }

    return 0;
}

Camera* World:: getActiveCamera () const
{
    return camera;
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
    camera = cam;
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
    if (camera == NULL) {
        throw IllegalStateException (__FILE__, __func__, "Active camera is NULL.");
    }
    
    //cout << "World render\n";
    
    state.camera = camera;

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
        camera->render (state);
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
        if (children[i] == camera) {
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
