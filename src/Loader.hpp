#ifndef __M3G_LOADER_HPP__
#define __M3G_LOADER_HPP__

#include <vector>
#include "m3g/m3g.hpp"
#include "m3g/M3GReader-fwd.hpp"


namespace m3g {

    class Object3D;

    /**
     * @~English  Download and deserializes scene graph nodes and node components, as well as entire scene graphs.
     * @~Japanese シーングラフとそのノード要素のダウンロード.
     */
    class Loader : public Object
    {

    public:

        /**
         * @~English  Deserializes Object3D instances form the given byte array.
         * @~Japanese 与えられたバイトストリームのオフセット位置からObject3Dのインスタンスを生成する.
         */
        static std::vector<Object3D*> load (int length, const char* p, int offset);

        /**
         * @~English  Deserializes Object3D instances from the named resource.
         * @~Japanese 与えられた名前のリソースからObject3Dのインスタンスを生成する.
         */
        static std::vector<Object3D*> load (const char* file_name);


    private:

        Loader ();

        ~Loader ();

        std::vector<Object3D*> load_m3g (const char* p, int size);


        std::vector<Object3D*> load_png (const char* p, int size);


        std::vector<Object3D*> load_jpg (const char* p, int size);


        void parseHeader ();
        void parseAnimationController ();
        void parseAnimationTrack ();
        void parseAppearance ();
        void parseBackground ();
        void parseCamera ();
        void parseCompositingMode ();
        void parseFog ();
        void parsePolygonMode ();
        void parseGroup ();
        void parseImage2D ();
        void parseTriangleStripArray ();
        void parseLight ();
        void parseMaterial ();
        void parseMesh ();
        void parseMorphingMesh ();
        void parseSkinnedMesh ();
        void parseTexture2D ();
        void parseSprite3D ();
        void parseKeyframeSequence ();
        void parseVertexArray ();
        void parseVertexBuffer ();
        void parseWorld ();
        void parseExternalReference ();

        void setObject3D           (Object3D*            obj       , const M3GObject3DStruct&            object               ) const;
        void setAppearance         (Appearance*          app       , const M3GAppearanceStruct&          appearance           ) const;
        void setAnimationController(AnimationController* anim_ctr  , const M3GAnimationControllerStruct& animation_controller ) const;
        void setAnimationTrack     (AnimationTrack*      anim_track, const M3GAnimationTrackStruct&      animation_track      ) const;
        void setBackground         (Background*          bg        , const M3GBackgroundStruct&          bground              ) const;
        void setCamera             (Camera*              cam       , const M3GCameraStruct&              cmr                  ) const;
        void setCompositingMode    (CompositingMode*     cmode     , const M3GCompositingModeStruct&     comp_mode            ) const;
        void setFog                (Fog*                 fog       , const M3GFogStruct&                 fg                   ) const;
        void setGroup              (Group*               grp       , const M3GGroupStruct&               group                ) const;
        void setImage2D            (Image2D*             img       , const M3GImage2DStruct&             image                ) const;
        void setIndexBuffer        (IndexBuffer*         ibuf      , const M3GIndexBufferStruct&         index_buffer         ) const;
        void setKeyframeSequence   (KeyframeSequence*    key_seq   , const M3GKeyframeSequenceStruct&    keyframe_sequence    ) const;
        void setLight              (Light*               lgh       , const M3GLightStruct&               light                ) const;
        void setMaterial           (Material*            mat       , const M3GMaterialStruct&            material             ) const;
        void setMesh               (Mesh*                mesh      , const M3GMeshStruct&                msh                  ) const;
        void setMorphingMesh       (MorphingMesh*        mesh      , const M3GMorphingMeshStruct&        msh                  ) const;
        void setNode               (Node*                nod       , const M3GNodeStruct&                node                 ) const;
        void setPolygonMode        (PolygonMode*         pmode     , const M3GPolygonModeStruct&         poly_mode            ) const;
        void setSkinnedMesh        (SkinnedMesh*         mesh      , const M3GSkinnedMeshStruct&         msh                  ) const;
        void setSprite3D           (Sprite3D*            spr       , const M3GSprite3DStruct&            sprite               ) const;
        void setTexture2D          (Texture2D*           tex       , const M3GTexture2DStruct&           texture              ) const;
        void setTransformable      (Transformable*       tra       , const M3GTransformableStruct&       transformable        ) const;
        void setTriangleStripArray (TriangleStripArray*  tris      , const M3GTriangleStripArrayStruct&  tri_strip            ) const;
        void setVertexArray        (VertexArray*         varry     , const M3GVertexArrayStruct&         vertex_array         ) const;
        void setVertexBuffer       (VertexBuffer*        vbuf      , const M3GVertexBufferStruct&        vertex_buffer        ) const;
        void setWorld              (World*               wld       , const M3GWorldStruct&               world                ) const;



    private:
        M3GReader*             reader;
        std::vector<Object3D*> objs;


    };


} // namespace m3g {

#endif






