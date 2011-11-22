
#ifndef __M3G_READER_HPP__
#define __M3G_READER_HPP__

#include "M3GStruct.hpp"
#include <vector>


namespace m3g {

    class InMemoryStream;

   /**
    * @~Japanese  M3Gフォーマット形式のファイルリーダー.
    */
    class M3GReader
    {
    public:
        M3GReader (const char* file_name);
        M3GReader (const char* p, int size);
        ~M3GReader ();

        const unsigned char*    readID        ();
        bool startSection ();
        void endSection   ();
        bool startObject  (int* object_type, unsigned int* object_index);
        void endObject    ();

        void readHeader              (M3GHeaderStruct*              header           );
        void readExternalReference   (M3GExternalReferenceStruct*   ex_ref           );
        void readAnimationController (M3GAnimationControllerStruct* anim_controller  );
        void readAnimationTrack      (M3GAnimationTrackStruct*      anim_track       );
        void readAppearance          (M3GAppearanceStruct*          appearance       );
        void readBackground          (M3GBackgroundStruct*          background       );
        void readCamera              (M3GCameraStruct*              camera           );
        void readCompositingMode     (M3GCompositingModeStruct*     comp_mode        );
        void readFog                 (M3GFogStruct*                 fog              );
        void readGroup               (M3GGroupStruct*               group            );
        void readImage2D             (M3GImage2DStruct*             image            );
        void readIndexBuffer         (M3GIndexBufferStruct*         ibuf             );
        void readKeyframeSequence    (M3GKeyframeSequenceStruct*    keyframe_sequence);
        void readLight               (M3GLightStruct*               light            );
        void readMaterial            (M3GMaterialStruct*            material         );
        void readMesh                (M3GMeshStruct*                mesh             );
        void readMorphingMesh        (M3GMorphingMeshStruct*        morph_mesh       );
        void readNode                (M3GNodeStruct*                node             );
        void readObject3D            (M3GObject3DStruct*            object           );
        void readPolygonMode         (M3GPolygonModeStruct*         poly_mode        );
        void readSkinnedMesh         (M3GSkinnedMeshStruct*         skinned_mesh     );
        void readSprite3D            (M3GSprite3DStruct*            sprite           );
        void readTransformable       (M3GTransformableStruct*       transformable    );
        void readTriangleStripArray  (M3GTriangleStripArrayStruct*  tri_strip_array  );
        void readTexture2D           (M3GTexture2DStruct*           texture          );
        void readVertexArray         (M3GVertexArrayStruct*         vertex_array     );
        void readVertexBuffer        (M3GVertexBufferStruct*        vertex_buffer    );
        void readWorld               (M3GWorldStruct*               world            );
        void readString              (const char**                  str              );

        bool            getBoolean      ();
        unsigned char   getUByte        ();
        char            getByte         ();
        unsigned short  getUInt16       ();
        int             getInt32        ();
        unsigned int    getUInt32       ();
        float           getFloat32      ();
        unsigned int    getRGB          ();
        unsigned int    getRGBA         ();
        char*           getByteArray    (int size);
        unsigned char*  getUByteArray   (int size);
        unsigned short* getUInt16Array  (int size);
        float*          getFloat32Array (int size);
        char*           getString       ();

    private:
        m3g::InMemoryStream* stream;
    
        const char*    file_name;
        unsigned int   object_index;
        unsigned int   start_of_section;
        unsigned int   start_of_object;
        unsigned int   size_of_object;

        unsigned int   total_section_length;
        unsigned long  uncompressed_objects_length;  // must be 8 byte for zlib's uncompress
    };


    /**
     * @~Japanese  読み込み専用メモリストリームクラス.
     */
    class InMemoryStream
    {
    public:
        InMemoryStream  (const char* file_name);
        InMemoryStream  (const char* p, int size);
        ~InMemoryStream ();

        void read  (char* p, int size);
        void seekg (int pos);

        int          size  () const;
        unsigned int tellg () const;
        bool         eof   () const;

        void erase  (int pos, int size);
        void insert (int pos, const char* buf, int size);

        const unsigned char* pointer (int offset) const;

    private:
        std::vector<char> buf;
        int               cur;
    };

    

} // namespace m3g

#endif
