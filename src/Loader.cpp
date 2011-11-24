#include "m3g/m3g.hpp"
#include "m3g/stb_image_reader.hpp"
#include "m3g/Config.hpp"
#include "m3g/M3GReader.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;
using namespace m3g;

// M3G(JSR184) identifier
const unsigned char m3g_sig[12] = {0xab,0x4a,0x53,0x52,0x31,0x38,0x34,0xbb,0x0d,0x0a,0x1a,0x0a};

Loader:: Loader () : reader(NULL)
{
}

Loader:: ~Loader ()
{
    delete reader;
}


std::vector<Object3D*> Loader:: load (int length, const char* p, int offset)
{
    if (p == NULL) {
        throw NullPointerException (__FILE__, __func__, "Pointer is Null.");
    }
    if (length <= 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Length is invalid, len=%d.", length);
    }
    if (offset < 0 || offset >= length) {
        throw IllegalArgumentException (__FILE__, __func__, "Offset is invalid, offset=%d, len=%d.", offset, length);
    }

    p      += offset;
    length -= offset;
   
    Loader* loader = new Loader;
    vector<Object3D*> objs;

    if (memcmp (p, m3g_sig, sizeof(m3g_sig)) == 0) {
        objs = loader->load_m3g (p, length);
    } else {
        objs = loader->load_image (p, length);
    }


    delete loader;
    return objs;
}

std::vector<Object3D*> Loader:: load (const char* file_name)
{
    if (!file_name) {
        throw NullPointerException (__FILE__, __func__, "File name is Null.");
    }

    ifstream ifs (file_name);
    if (!ifs) {
        throw IOException (__FILE__, __func__, "Can't open the file, name=%s.", file_name);
    }

    ifs.seekg (0, std::ios::end);
    int size = ifs.tellg ();
    ifs.seekg (0, std::ios::beg);

    char* buf = new char[size];
    ifs.read (buf, size);

    vector<Object3D*> objs = load (size, buf, 0);

    delete [] buf;
    return objs;
}


std::vector<Object3D*> Loader:: load_m3g (const char* p, int size)
{
    // object indexは1から始まるので
    objs.push_back (0);

    int          object_type;
    unsigned int object_index;
    
    reader = new M3GReader (p, size);

    // M3G-ID
    reader->readID ();

    // Section 1 has Header object only.
    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    parseHeader          ();
    reader->endObject    ();
    reader->endSection   ();


    // Section 2～
    while (reader->startSection ()) {
        while (reader->startObject  (&object_type, &object_index)) {
            //cout << "Loader:: object_type = " << object_type << "\n";
            switch (object_type) {
            case M3G_TYPE_HEADER              : parseHeader ()             ; break;
            case M3G_TYPE_ANIMATION_CONTROLLER: parseAnimationController (); break;
            case M3G_TYPE_ANIMATION_TRACK     : parseAnimationTrack ()     ; break;
            case M3G_TYPE_APPEARANCE          : parseAppearance ()         ; break;
            case M3G_TYPE_BACKGROUND          : parseBackground ()         ; break;
            case M3G_TYPE_CAMERA              : parseCamera ()             ; break;
            case M3G_TYPE_COMPOSITING_MODE    : parseCompositingMode ()    ; break;
            case M3G_TYPE_FOG                 : parseFog ()                ; break;
            case M3G_TYPE_POLYGON_MODE        : parsePolygonMode ()        ; break;
            case M3G_TYPE_GROUP               : parseGroup ()              ; break;
            case M3G_TYPE_IMAGE2D             : parseImage2D ()            ; break;
            case M3G_TYPE_TRIANGLE_STRIP_ARRAY: parseTriangleStripArray () ; break;
            case M3G_TYPE_LIGHT               : parseLight ()              ; break;
            case M3G_TYPE_MATERIAL            : parseMaterial ()           ; break;
            case M3G_TYPE_MESH                : parseMesh ()               ; break;
            case M3G_TYPE_MORPHING_MESH       : parseMorphingMesh ()       ; break;
            case M3G_TYPE_SKINNED_MESH        : parseSkinnedMesh ()        ; break;
            case M3G_TYPE_TEXTURE2D           : parseTexture2D ()          ; break;
            case M3G_TYPE_SPRITE3D            : parseSprite3D ()           ; break;
            case M3G_TYPE_KEYFRAME_SEQUENCE   : parseKeyframeSequence ()   ; break;
            case M3G_TYPE_VERTEX_ARRAY        : parseVertexArray ()        ; break;
            case M3G_TYPE_VERTEX_BUFFER       : parseVertexBuffer ()       ; break;
            case M3G_TYPE_WORLD               : parseWorld ()              ; break;
            case M3G_TYPE_EXTERNAL_REFERENCE  : parseExternalReference ()  ; break;
            default: {
                throw IOException (__FILE__, __func__, "Unknown object type = %d", object_type);
            }
            }
            reader->endObject ();
        }
        reader->endSection ();
    }    

    objs.erase (remove(objs.begin(), objs.end(), (Object3D*)0), objs.end());

    return objs;
}

/**
 * (注意) PNG画像は左上が(0,0)でM3Gは左下が(0,0)なので忘れずに上下をひっくり返すこと。
 */
std::vector<Object3D*> Loader:: load_image (const char* buffer, int size)
{
    int width, height, comp;
    unsigned char* pixels = stbi_load_from_memory ((unsigned char*)buffer, size,
                                                   &width, &height, &comp, 0);
    if (pixels == NULL) {
        throw IOException (__FILE__, __func__, "This file is not m3g or image (png, jpeg, ...).");
    }

    int format;
    switch (comp) {
    case 1 : format = Image2D::LUMINANCE;       break;
    case 2 : format = Image2D::LUMINANCE_ALPHA; break;
    case 3 : format = Image2D::RGB;             break;
    case 4 : format = Image2D::RGBA;            break;
    default: throw IOException (__FILE__, __func__, "Unknown image format=%d.", comp);
    }

    unsigned char* tmp = new unsigned char[width*comp];
    for (int y = 0; y < height/2; y++) {
        memswap ((char*)&pixels[y*width*comp],
                 (char*)&pixels[(height-1-y)*width*comp],
                 (char*)tmp,
                 width*comp);
    }
    delete[] tmp;

    objs.push_back (new Image2D (format, width, height, pixels));
    
    stbi_image_free (pixels);
    return objs;
}


void Loader:: parseHeader ()
{
    M3GHeaderStruct header;
    reader->readHeader   (&header);
    
    objs.push_back (0);
}


void Loader:: parseAnimationController ()
{
    M3GObject3DStruct               obj;
    M3GAnimationControllerStruct    ac;
    reader->readObject3D            (&obj);
    reader->readAnimationController (&ac);
            
    AnimationController* anim_ctr = new AnimationController ();
    setObject3D            (anim_ctr, obj);
    setAnimationController (anim_ctr, ac);

    objs.push_back (anim_ctr);
}

void Loader:: parseAnimationTrack ()
{
    M3GObject3DStruct          obj;
    M3GAnimationTrackStruct    atrack;
    reader->readObject3D       (&obj);
    reader->readAnimationTrack (&atrack);
            
    KeyframeSequence* key_seq  = dynamic_cast<KeyframeSequence*>(objs[atrack.keyframe_sequence_index]);
    unsigned int      property = atrack.property_id;

    AnimationTrack* anim_track = new AnimationTrack (key_seq, property);
    setObject3D       (anim_track, obj);
    setAnimationTrack (anim_track, atrack);

    objs.push_back (anim_track);
}

void Loader:: parseAppearance ()
{
    M3GObject3DStruct      obj;
    M3GAppearanceStruct    ap;
    reader->readObject3D   (&obj);
    reader->readAppearance (&ap);
            
    Appearance* app = new Appearance ();
    setObject3D   (app, obj);
    setAppearance (app, ap);

    objs.push_back (app);
}

void Loader:: parseBackground ()
{
    M3GObject3DStruct      obj;
    M3GBackgroundStruct    bgrnd;
    reader->readObject3D   (&obj);
    reader->readBackground (&bgrnd);
            
    Background* bg = new Background ();
    setObject3D   (bg, obj);
    setBackground (bg, bgrnd);

    objs.push_back (bg);
}

void Loader:: parseCamera ()
{
    M3GObject3DStruct         obj;
    M3GTransformableStruct    tra;
    M3GNodeStruct             node;
    M3GCameraStruct           cmr;
    reader->readObject3D      (&obj);
    reader->readTransformable (&tra);
    reader->readNode          (&node);
    reader->readCamera        (&cmr);
            
    Camera* cam = new Camera ();
    setObject3D      (cam, obj);
    setTransformable (cam, tra);
    setNode          (cam, node);
    setCamera        (cam, cmr);

    objs.push_back (cam);
}

void Loader:: parseCompositingMode ()
{
    M3GObject3DStruct           obj;
    M3GCompositingModeStruct    cmp;
    reader->readObject3D        (&obj);
    reader->readCompositingMode (&cmp);
            
    CompositingMode* cmode = new CompositingMode ();
    setObject3D        (cmode, obj);
    setCompositingMode (cmode, cmp);

    objs.push_back (cmode);
}

void Loader:: parseFog ()
{
    M3GObject3DStruct    obj;
    M3GFogStruct         fg;
    reader->readObject3D (&obj);
    reader->readFog      (&fg);
            
    Fog* fog = new Fog ();
    setObject3D (fog, obj);
    setFog      (fog, fg);

    objs.push_back (fog);
}

void Loader:: parsePolygonMode ()
{
    M3GObject3DStruct            obj;
    M3GPolygonModeStruct         pm;
    reader->readObject3D         (&obj);
    reader->readPolygonMode      (&pm);
            
    PolygonMode* pmode = new PolygonMode ();
    setObject3D    (pmode, obj);
    setPolygonMode (pmode, pm);

    objs.push_back (pmode);
}

void Loader:: parseGroup ()
{
    M3GObject3DStruct         obj;
    M3GTransformableStruct    tra;
    M3GNodeStruct             node;
    M3GGroupStruct            group;
    reader->readObject3D      (&obj);
    reader->readTransformable (&tra);
    reader->readNode          (&node);
    reader->readGroup         (&group);
    
    Group* grp = new Group ();
    setObject3D      (grp, obj);
    setTransformable (grp, tra);
    setNode          (grp, node);
    setGroup         (grp, group);

    objs.push_back (grp);
}

void Loader:: parseImage2D ()
{
    M3GObject3DStruct        obj;
    M3GImage2DStruct         image;
    reader->readObject3D     (&obj);
    reader->readImage2D      (&image);
    
    int   format        = image.format;
    int   width         = image.width;
    int   height        = image.height;
    int   palette_count = image.palette_count;
    unsigned char* palette = image.palette;
    unsigned char* pixels  = image.pixels;

    Image2D* img;
    if (palette_count > 0) {
        img = new Image2D (format, width, height, pixels, palette);
    } else {
        img = new Image2D (format, width, height, pixels);
    }
    setObject3D (img, obj);
    setImage2D  (img, image);

    objs.push_back (img);
}

void Loader:: parseTriangleStripArray ()
{
    M3GObject3DStruct              obj;
    M3GIndexBufferStruct           ibuf;
    M3GTriangleStripArrayStruct    tri_strip;
    reader->readObject3D           (&obj);
    reader->readIndexBuffer        (&ibuf);
    reader->readTriangleStripArray (&tri_strip);
    
    int  start_index = tri_strip.start_index;
    int  num_indices = tri_strip.indices_count;
    int* indices     = (int*)tri_strip.indices;
    int  num_strips  = tri_strip.strip_lengths_count;
    int* strips      = (int*)tri_strip.strip_lengths;

    TriangleStripArray* tris;
    if (indices)
        tris = new TriangleStripArray (num_indices, indices, num_strips, strips);
    else
        tris = new TriangleStripArray (start_index, num_strips, strips);        

    setObject3D           (tris, obj);
    setIndexBuffer        (tris, ibuf);
    setTriangleStripArray (tris, tri_strip);

    objs.push_back (tris);
}

void Loader:: parseLight ()
{
    M3GObject3DStruct         obj;
    M3GTransformableStruct    tra;
    M3GNodeStruct             node;
    M3GLightStruct            light;
    reader->readObject3D      (&obj);
    reader->readTransformable (&tra);
    reader->readNode          (&node);
    reader->readLight         (&light);
            
    Light* lgh = new Light ();
    setObject3D      (lgh, obj);
    setTransformable (lgh, tra);
    setNode          (lgh, node);
    setLight         (lgh, light);

    objs.push_back (lgh);
}

void Loader:: parseMaterial ()
{
    M3GObject3DStruct        obj;
    M3GMaterialStruct        material;
    reader->readObject3D     (&obj);
    reader->readMaterial     (&material);
            
    Material* mat = new Material ();
    setObject3D (mat, obj);
    setMaterial (mat, material);

    objs.push_back (mat);
}

void Loader:: parseMesh ()
{
    M3GObject3DStruct         obj;
    M3GTransformableStruct    tra;
    M3GNodeStruct             node;
    M3GMeshStruct             msh;
    reader->readObject3D      (&obj);
    reader->readTransformable (&tra);
    reader->readNode          (&node);
    reader->readMesh          (&msh);
    
    VertexBuffer*        vertices       = dynamic_cast<VertexBuffer*>(objs[msh.vertex_buffer_index]);
    int                  num_submesh    = msh.submesh_count;  // ファイルフォーマットで両者が
    int                  num_appearance = msh.submesh_count;  // 等しいことが保証されている
    vector<IndexBuffer*> submeshs    (num_submesh);
    vector<Appearance*>  appearances (num_submesh);
    for (int i = 0; i < num_submesh; i++) {
        submeshs[i] = dynamic_cast<IndexBuffer*>(objs[msh.index_buffer_index[i]]);
    }
    for (int i = 0; i < num_appearance; i++) {
        appearances[i] = dynamic_cast<Appearance*>(objs[msh.appearance_index[i]]);
    }

    Mesh* mesh = new Mesh (vertices, num_submesh, &submeshs[0], num_appearance, &appearances[0]);
    setObject3D      (mesh, obj);
    setTransformable (mesh, tra);
    setNode          (mesh, node);
    setMesh          (mesh, msh);

    objs.push_back (mesh);
}

void Loader:: parseMorphingMesh ()
{
    M3GObject3DStruct         obj;
    M3GTransformableStruct    tra;
    M3GNodeStruct             node;
    M3GMeshStruct             msh;
    M3GMorphingMeshStruct     morph_msh;
    reader->readObject3D      (&obj);
    reader->readTransformable (&tra);
    reader->readNode          (&node);
    reader->readMesh          (&msh);
    reader->readMorphingMesh  (&morph_msh);
            
    VertexBuffer*         vertices       = dynamic_cast<VertexBuffer*>(objs[msh.vertex_buffer_index]);
    int                   num_submesh    = msh.submesh_count;
    int                   num_appearance = msh.submesh_count;
    vector<IndexBuffer*>  submeshs    (num_submesh);
    vector<Appearance*>   appearances (num_submesh);
    for (int i = 0; i < num_submesh; i++) {
        submeshs[i] = dynamic_cast<IndexBuffer*>(objs[msh.index_buffer_index[i]]);
    }
    for (int i = 0; i < num_appearance; i++) {
        appearances[i] = dynamic_cast<Appearance*>(objs[msh.appearance_index[i]]);
    }
    int                   num_target  = morph_msh.morph_target_count;
    vector<VertexBuffer*> targets (num_target);
    for (int i = 0; i < num_target; i++) { 
            targets[i] = dynamic_cast<VertexBuffer*>(objs[morph_msh.morph_target_index[i]]);
         }
    
    MorphingMesh* mesh = new MorphingMesh (vertices                       ,
                                           num_target    , &targets[0]    , 
                                           num_submesh   , &submeshs[0]   ,
                                           num_appearance, &appearances[0] );
    setObject3D      (mesh, obj);
    setTransformable (mesh, tra);
    setNode          (mesh, node);
    setMesh          (mesh, msh);
    setMorphingMesh  (mesh, morph_msh);

    objs.push_back (mesh);
}

void Loader:: parseSkinnedMesh ()
{
    M3GObject3DStruct         obj;
    M3GTransformableStruct    tra;
    M3GNodeStruct             node;
    M3GMeshStruct             msh;
    M3GSkinnedMeshStruct      skin_msh;
    reader->readObject3D      (&obj);
    reader->readTransformable (&tra);
    reader->readNode          (&node);
    reader->readMesh          (&msh);
    reader->readSkinnedMesh   (&skin_msh);

    VertexBuffer*        vertices       = dynamic_cast<VertexBuffer*>(objs[msh.vertex_buffer_index]);
    int                  num_submesh    = msh.submesh_count;
    int                  num_appearance = msh.submesh_count;
    vector<IndexBuffer*> submeshs    (num_submesh);
    vector<Appearance*>  appearances (num_submesh);
    Group*               skeleton    = dynamic_cast<Group*>(objs[skin_msh.skeleton_index]);

    for (int i = 0; i < num_submesh; i++) {
        submeshs[i] = dynamic_cast<IndexBuffer*>(objs[msh.index_buffer_index[i]]);
    }
    for (int i = 0; i < num_appearance; i++) {
        appearances[i] = dynamic_cast<Appearance*>(objs[msh.appearance_index[i]]);
    }
    
    SkinnedMesh* mesh = new SkinnedMesh (vertices, num_submesh, &submeshs[0], num_appearance, &appearances[0], skeleton);
    setObject3D      (mesh, obj);
    setTransformable (mesh, tra);
    setNode          (mesh, node);
    setMesh          (mesh, msh);
    setSkinnedMesh   (mesh, skin_msh);

    objs.push_back (mesh);
}

void Loader:: parseTexture2D ()
{
    M3GObject3DStruct         obj;
    M3GTransformableStruct    tra;
    M3GTexture2DStruct        texture;
    reader->readObject3D      (&obj);
    reader->readTransformable (&tra);
    reader->readTexture2D     (&texture);
    
    Image2D* image = dynamic_cast<Image2D*>(objs[texture.image_index]);

    Texture2D* tex = new Texture2D (image);
    setObject3D      (tex, obj);
    setTransformable (tex, tra);
    setTexture2D     (tex, texture);

    objs.push_back (tex);
}

void Loader:: parseSprite3D ()
{
    M3GObject3DStruct         obj;
    M3GTransformableStruct    tra;
    M3GSprite3DStruct         sprite;
    reader->readObject3D      (&obj);
    reader->readTransformable (&tra);
    reader->readSprite3D      (&sprite);
            
    bool        scaled = sprite.is_scaled;
    Image2D*    img    = dynamic_cast<Image2D*>(objs[sprite.image_index]);
    Appearance* app    = dynamic_cast<Appearance*>(objs[sprite.appearance_index]);

    Sprite3D* spr = new Sprite3D (scaled, img, app);
    setObject3D      (spr, obj);
    setTransformable (spr, tra);
    setSprite3D      (spr, sprite);

    objs.push_back (spr);
}

void Loader:: parseKeyframeSequence ()
{
    M3GObject3DStruct            obj;
    M3GKeyframeSequenceStruct    keyframe_sequence;
    reader->readObject3D         (&obj);
    reader->readKeyframeSequence (&keyframe_sequence);

    int num_keyframes  = keyframe_sequence.keyframe_count;
    int num_components = keyframe_sequence.component_count;
    int interpolation  = keyframe_sequence.interpolation;

    KeyframeSequence* key_seq = new KeyframeSequence (num_keyframes, num_components, interpolation);
    setObject3D         (key_seq, obj);
    setKeyframeSequence (key_seq, keyframe_sequence);

    objs.push_back (key_seq);
}

void Loader:: parseVertexArray ()
{
    M3GObject3DStruct       obj;
    M3GVertexArrayStruct    varray;
    reader->readObject3D    (&obj);
    reader->readVertexArray (&varray);
            
    int num_vertices   = varray.vertex_count;
    int num_components = varray.component_count;
    int component_size = varray.component_size;

    VertexArray* varry = new VertexArray (num_vertices, num_components, component_size);
    setObject3D    (varry, obj);
    setVertexArray (varry, varray);

    objs.push_back (varry);
}

void Loader:: parseVertexBuffer ()
{
    M3GObject3DStruct       obj;
    M3GVertexBufferStruct   vbuffer;
    reader->readObject3D     (&obj);
    reader->readVertexBuffer (&vbuffer);
            
    VertexBuffer* vbuf = new VertexBuffer ();
    setObject3D     (vbuf, obj);
    setVertexBuffer (vbuf, vbuffer);

    objs.push_back (vbuf);
}

void Loader:: parseWorld ()
{
    M3GObject3DStruct         obj;
    M3GTransformableStruct    tra;
    M3GNodeStruct             node;
    M3GGroupStruct            grp;
    M3GWorldStruct            world;
    reader->readObject3D      (&obj);
    reader->readTransformable (&tra);
    reader->readNode          (&node);
    reader->readGroup         (&grp);
    reader->readWorld         (&world);

    World* wld = new World ();
    setObject3D      (wld, obj);
    setTransformable (wld, tra);
    setNode          (wld, node);
    setGroup         (wld, grp);
    setWorld         (wld, world);

    objs.push_back (wld);
}

void Loader:: parseExternalReference ()
{
    M3GExternalReferenceStruct ext;
    reader->readExternalReference (&ext);

    if (ext.uri) {
        vector<Object3D*> ext_objs = Loader:: load (ext.uri);
        if ((int)ext_objs.size() == 0)
            throw IOException (__FILE__, __func__, "ExternalReference has no M3G objects.");
        objs.push_back (ext_objs[0]);
    }
}


void Loader:: setObject3D (Object3D* obj, const M3GObject3DStruct& object) const
{
    int user_id              = object.user_id;
    int anim_track_count     = object.animation_tracks_count;
    int user_parameter_count = object.user_parameter_count;

    obj->setUserID (user_id);
    for (int i = 0; i < anim_track_count; i++) {
        AnimationTrack* anim_track = dynamic_cast<AnimationTrack*>(objs[object.animation_tracks_index[i]]);
        obj->addAnimationTrack (anim_track);
    }
    if (user_parameter_count > 0) {
        map<unsigned int, char*>* user_object = new map<unsigned int, char*>();
        for (int i = 0; i < user_parameter_count; i++) {
            user_object->insert (map<unsigned int, char*>::value_type(object.parameter_id[i], object.parameter_value[i]));
        }
        obj->setUserObject (user_object);
    }
}

void Loader:: setAppearance (Appearance* app, const M3GAppearanceStruct& appearance) const
{
    int              layer = appearance.layer;
    CompositingMode* cmode = dynamic_cast<CompositingMode*>(objs[appearance.compositing_mode_index]);
    PolygonMode*     pmode = dynamic_cast<PolygonMode*>(objs[appearance.polygon_mode_index]);
    Material*        mat   = dynamic_cast<Material*>(objs[appearance.material_index]);
    int              textures_count = appearance.textures_count;
    app->setLayer (layer);
    app->setCompositingMode (cmode);
    app->setPolygonMode (pmode);
    app->setMaterial (mat);
    for (int i = 0; i < textures_count; i++) {
        Texture2D* tex = dynamic_cast<Texture2D*>(objs[appearance.textures_index[i]]);
        app->setTexture (i, tex);
    }
}


void Loader:: setAnimationController (AnimationController* anim_ctr, const M3GAnimationControllerStruct& ac) const
{
    anim_ctr->setActiveInterval (ac.active_interval_start, ac.active_interval_end);
    anim_ctr->setPosition       (ac.reference_sequence_time, ac.reference_world_time);
    anim_ctr->setSpeed          (ac.speed, ac.reference_world_time);
    anim_ctr->setWeight         (ac.weight);
}

void Loader:: setAnimationTrack (AnimationTrack* anim_track, const M3GAnimationTrackStruct& at) const
{
    AnimationController* anim_ctr = dynamic_cast<AnimationController*>(objs[at.animation_controller_index]);
    anim_track->setController (anim_ctr);
}

void Loader:: setBackground (Background* bg, const M3GBackgroundStruct& bgr) const
{
    int      argb   = bgr.background_color;
    Image2D* img    = dynamic_cast<Image2D*>(objs[bgr.background_image_index]);
    int      mode_x = bgr.background_image_mode_x;
    int      mode_y = bgr.background_image_mode_y;
    int      crop_x = bgr.crop_x;
    int      crop_y = bgr.crop_y;
    int      width  = bgr.crop_width;
    int      height = bgr.crop_height;
    bool     depth_clear_enable = bgr.depth_clear_enabled;
    bool     color_clear_enable = bgr.color_clear_enabled;

    bg->setColor            (argb);
    bg->setColorClearEnable (color_clear_enable);
    bg->setCrop             (crop_x, crop_y, width, height);
    bg->setDepthClearEnable (depth_clear_enable);
    bg->setImage            (img);
    bg->setImageMode        (mode_x, mode_y);
}

void Loader:: setCamera (Camera* cam, const M3GCameraStruct& cmr) const
{
    int       projection_type = cmr.projection_type;
    float     fovy            = cmr.fovy;
    float     aspect_ratio    = cmr.aspect_ratio;
    float     near            = cmr.near;
    float     far             = cmr.far;
    Transform tra;
    tra.set (cmr.matrix);

    switch (projection_type) {
    case Camera::GENERIC    : cam->setGeneric (&tra)                             ; break;
    case Camera::PARALLEL   : cam->setParallel (fovy, aspect_ratio, near, far)   ; break;
    case Camera::PERSPECTIVE: cam->setPerspective (fovy, aspect_ratio, near, far); break;
    default: throw IOException (__FILE__, __func__, "Projection type of camera is illegal, type=%d", projection_type);
    }
}

void Loader:: setCompositingMode (CompositingMode* cmode, const M3GCompositingModeStruct& comp_mode) const
{
    bool  depth_test_enable  = comp_mode.depth_test_enabled;
    bool  depth_write_enable = comp_mode.depth_write_enabled;
    bool  color_write_enable = comp_mode.color_write_enabled;
    bool  alpha_write_enable = comp_mode.alpha_write_enabled;
    int   blending           = comp_mode.blending;
    float alpha_threshold    = comp_mode.alpha_threshold / 255.f;
    float factor             = comp_mode.depth_offset_factor;
    float units              = comp_mode.depth_offset_units;

    cmode->setAlphaThreshold   (alpha_threshold);
    cmode->setAlphaWriteEnable (alpha_write_enable);
    cmode->setBlending         (blending);
    cmode->setColorWriteEnable (color_write_enable);
    cmode->setDepthOffset      (factor, units);
    cmode->setDepthTestEnable  (depth_test_enable);
    cmode->setDepthWriteEnable (depth_write_enable);
}

void Loader:: setFog (Fog* fog, const M3GFogStruct& fg) const
{
    int   rgb     = fg.color;
    int   mode    = fg.mode;
    float density = fg.density;
    float near    = fg.near;
    float far     = fg.far;

    fog->setColor   (rgb);
    fog->setMode    (mode);
    switch (mode) {
    case Fog::EXPONENTIAL: fog->setDensity (density)  ; break;
    case Fog::LINEAR     : fog->setLinear  (near, far); break;
    default: throw IOException (__FILE__, __func__, "Fog mode is invalid, mode=%d.", mode);
    }
}

void Loader:: setGroup (Group* grp, const M3GGroupStruct& group) const
{
    int child_count = group.children_index_count;
    for (int i = 0; i < child_count; i++) {
        Node* node = dynamic_cast<Node*>(objs[group.children_index[i]]);
        if (node) {
            grp->addChild (node);
        }
    }
}

void Loader:: setImage2D (Image2D* img, const M3GImage2DStruct& image) const
{
    // nothing to do
}

void Loader:: setIndexBuffer (IndexBuffer* ibuf, const M3GIndexBufferStruct& index_buffer) const
{
    // nothing to do
}

void Loader:: setKeyframeSequence (KeyframeSequence* key_seq, const M3GKeyframeSequenceStruct& ks) const
{
    int duration = ks.duration;
    int mode     = ks.repeat_mode;
    int first    = ks.valid_range_first;
    int last     = ks.valid_range_last;
    int keyframe_count = ks.keyframe_count;

    key_seq->setDuration  (duration);
    key_seq->setRepeatMode (mode);
    key_seq->setValidRange (first, last);
    for (int i = 0; i < keyframe_count; i++) {
        int    time  = ks.time[i];
        float* value = ks.vector_value[i];
        key_seq->setKeyframe (i, time, value);
    }
}

void Loader:: setLight (Light* lgh, const M3GLightStruct& light) const
{
    float constant  = light.attenuation_constant;
    float linear    = light.attenuation_linear;
    float quadratic = light.attenuation_quadratic;
    int   rgb       = light.color;
    int   mode      = light.mode;
    float intensity = light.intensity;
    float angle     = light.spot_angle;
    float exponent  = light.spot_exponent;

    lgh->setAttenuation  (constant, linear, quadratic);
    lgh->setColor        (rgb);
    lgh->setIntensity    (intensity);
    lgh->setMode         (mode);
    lgh->setSpotAngle    (angle);
    lgh->setSpotExponent (exponent);
}

void Loader:: setMaterial (Material* mat, const M3GMaterialStruct& material) const
{
    int   ambient_color  = material.ambient_color;
    int   diffuse_color  = material.diffuse_color;  // argb
    int   emissive_color = material.emissive_color;
    int   specular_color = material.specular_color;
    float shininess      = material.shininess;
    bool  vertex_color_tracking_enable = material.vertex_color_tracking_enabled;
    
    mat->setColor     (Material::DIFFUSE,  diffuse_color);
    mat->setColor     (Material::AMBIENT,  ambient_color);
    mat->setColor     (Material::EMISSIVE, emissive_color);
    mat->setColor     (Material::SPECULAR, specular_color);
    mat->setShininess (shininess);
    mat->setVertexColorTrackingEnable (vertex_color_tracking_enable);
}

void Loader:: setMesh (Mesh* mesh, const M3GMeshStruct& msh) const
{
    // nothing to do
}

void Loader:: setMorphingMesh (MorphingMesh* mesh, const M3GMorphingMeshStruct& msh) const
{
    int    target_count = msh.morph_target_count;
    float* weights      = msh.initial_weight;
    mesh->setWeights (target_count, weights);
}

void Loader:: setNode (Node* node, const M3GNodeStruct& nod) const
{
    bool  rendering_enable = nod.enable_rendering;
    bool  picking_enable   = nod.enable_picking;
    float alpha_factor     = nod.alpha_factor / 255.f;
    int   scope            = nod.scope;
    bool  has_alignment    = nod.has_alignment;

    node->setAlphaFactor     (alpha_factor);
    node->setPickingEnable   (picking_enable);
    node->setRenderingEnable (rendering_enable);
    node->setScope           (scope);
    if (has_alignment) {
        int   z_target = nod.z_target;
        int   y_target = nod.y_target;
        Node* z_ref    = dynamic_cast<Node*>(objs[nod.z_reference_index]);
        Node* y_ref    = dynamic_cast<Node*>(objs[nod.y_reference_index]);
        node->setAlignment (z_ref, z_target, y_ref, y_target);
    }

}

void Loader:: setPolygonMode (PolygonMode* pmode, const M3GPolygonModeStruct& poly_mode) const
{
    int  culling_mode                  = poly_mode.culling;
    int  shading_mode                  = poly_mode.shading;
    int  winding_mode                  = poly_mode.winding;
    bool two_sided_lighting_enable     = poly_mode.two_sided_lighting_enabled;
    bool local_camera_lighting_enable  = poly_mode.local_camera_lighting_enabled;
    bool perspective_correction_enable = poly_mode.perspective_correction_enabled;

    pmode->setCulling                     (culling_mode);
    pmode->setLocalCameraLightingEnable   (local_camera_lighting_enable);
    pmode->setPerspectiveCorrectionEnable (perspective_correction_enable);
    pmode->setShading                     (shading_mode);
    pmode->setTwoSidedLightingEnable      (two_sided_lighting_enable);
    pmode->setWinding                     (winding_mode);
}

void Loader:: setSkinnedMesh (SkinnedMesh* mesh, const M3GSkinnedMeshStruct& msh) const
{
    int transform_reference_count = msh.transform_reference_count;
    for (int i = 0; i < transform_reference_count; i++) {
        Node* node         = dynamic_cast<Node*>(objs[msh.transform_node_index[i]]);
        int   weight       = msh.weight[i];
        int   first_vertex = msh.first_vertex[i];
        int   num_vertices = msh.vertex_count[i];
        mesh->addTransform (node, weight, first_vertex, num_vertices);
    }
}

void Loader:: setSprite3D (Sprite3D* spr, const M3GSprite3DStruct& sprite) const
{
    int crop_x = sprite.crop_x;
    int crop_y = sprite.crop_y;
    int width  = sprite.crop_width;
    int height = sprite.crop_height;

    spr->setCrop (crop_x, crop_y, width, height);
}


void Loader:: setTexture2D (Texture2D* tex, const M3GTexture2DStruct& texture) const
{
    int rgb          = texture.blend_color;
    int blend_func   = texture.blending;
    int wrap_s       = texture.wrapping_s;
    int wrap_t       = texture.wrapping_t;
    int level_filter = texture.level_filter;
    int image_filter = texture.image_filter;

    tex->setBlendColor (rgb);
    tex->setBlending   (blend_func);
    tex->setFiltering  (level_filter, image_filter);
    tex->setWrapping   (wrap_s, wrap_t);
}

void Loader:: setTransformable (Transformable* trans, const M3GTransformableStruct& transformable) const
{
    float tx    = transformable.translation[0];
    float ty    = transformable.translation[1];
    float tz    = transformable.translation[2];
    float sx    = transformable.scale[0];
    float sy    = transformable.scale[1];
    float sz    = transformable.scale[2];
    float angle = transformable.orientation_angle;
    float ax    = transformable.orientation_axis[0];
    float ay    = transformable.orientation_axis[1];
    float az    = transformable.orientation_axis[2];
    float has_component_transform = transformable.has_component_transform;
    float has_general_transform   = transformable.has_general_transform;
    Transform tra;
    tra.set (transformable.transform);

    if (has_component_transform) {
        trans->setTranslation (tx, ty, tz);
        trans->setOrientation (angle, ax, ay, az);
        trans->setScale       (sx, sy, sz);
    }
    if (has_general_transform) {
        trans->setTransform (&tra);
    }

}

void Loader:: setTriangleStripArray (TriangleStripArray*  tris, const M3GTriangleStripArrayStruct&  tri_strip) const
{
    // nothing to do
}

void Loader:: setVertexArray (VertexArray* varry, const M3GVertexArrayStruct& varray) const
{
    int     component_size   = varray.component_size;
    int     vertex_count     = varray.vertex_count;
    char**  char_components  = varray.char_components;
    short** short_components = varray.short_components;
    float** float_components = varray.float_components;
    for (int i = 0; i < vertex_count; i++) {
        switch (component_size) {
        case 1: varry->set (i, 1, char_components[i]) ; break;
        case 2: varry->set (i, 1, short_components[i]); break;
        case 4: varry->set (i, 1, float_components[i]); break;
        }
    }
}

void Loader:: setVertexBuffer (VertexBuffer* vbuf, const M3GVertexBufferStruct& vbuffer) const
{
    int          default_color    = vbuffer.default_color;
    float        position_scale   = vbuffer.position_scale;
    float        position_bias[3] = {vbuffer.position_bias[0], vbuffer.position_bias[1], vbuffer.position_bias[2]};
    VertexArray* colors           = dynamic_cast<VertexArray*>(objs[vbuffer.colors_index]);
    VertexArray* normals          = dynamic_cast<VertexArray*>(objs[vbuffer.normals_index]);
    VertexArray* positions        = dynamic_cast<VertexArray*>(objs[vbuffer.positions_index]);
    int          texcoord_count   = vbuffer.texcoord_array_count;


    if (positions) {
        // OpenGL(Desktop-M3G)は1バイト型の座標値に対応していないのでここで変換.
        if (positions->getComponentType() == 1) {
            positions->convert (2);
        }
        vbuf->setPositions    (positions, position_scale, position_bias);
    }
    if (normals) {
        vbuf->setNormals      (normals);
    }
    if (colors) {
        vbuf->setColors       (colors);
    }
    vbuf->setDefaultColor (default_color);
    for (int i = 0; i < texcoord_count; i++) {
        VertexArray* tex_coords        = dynamic_cast<VertexArray*>(objs[vbuffer.texcoords_index[i]]);
        float        texcoord_scale    = vbuffer.texcoord_scale[i];
        float        texcoord_bias[3]  = {vbuffer.texcoord_bias[i][0], vbuffer.texcoord_bias[i][1], vbuffer.texcoord_bias[i][2]};
        if (tex_coords->getComponentType() == 1) {
            tex_coords->convert (2);
        }
        vbuf->setTexCoords (i, tex_coords, texcoord_scale, texcoord_bias);
    }
}

void Loader:: setWorld (World* wld, const M3GWorldStruct& world) const
{
    Camera*     cam = dynamic_cast<Camera*>(objs[world.active_camera_index]);
    Background* bg  = dynamic_cast<Background*>(objs[world.background_index]);

    if (cam) {
        wld->setActiveCamera (cam);
    }
    if (bg) {
        wld->setBackground   (bg);
    }
}

