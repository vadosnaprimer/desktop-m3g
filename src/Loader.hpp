#ifndef __LOADER_HPP__
#define __LOADER_HPP__

#include <vector>
#include <iosfwd>
#include <strstream>
#include "Object.hpp"

namespace m3g {

    class Object3D;
    class IndexBuffer;
    class Node;
    class Transformable;
    class Group;
    class Mesh;

    /**
     * @~English  Download and deserializes scene graph nodes and node components, as well as entire scene graphs.
     * @~Japanese シーングラフとそのノード要素のダウンロード.
     */
    class Loader : public Object
    {
        struct FileInfo {
            FileInfo () : version_major(0), version_minor(0), has_external_refference(false),
                          external_refference_uri(0), total_file_size(0), 
                          approximate_content_size(0), authoring_field(0) {};
            int          version_major;
            int          version_minor;
            bool         has_external_refference;
            const char*  external_refference_uri;
            unsigned int total_file_size;
            unsigned int approximate_content_size;
            const char*  authoring_field;
        };


    public:

        /**
         * @~English  Deserializes Object3D instances form the given byte array.
         * @~Japanese 与えられたバイトストリームのオフセット位置からObject3Dのインスタンスを生成する.
         */
        static std::vector<Object3D*> load (int length, const char* data, int offset);

        /**
         * @~English  Deserializes Object3D instances from the named resource.
         * @~Japanese 与えられた名前のリソースからObject3Dのインスタンスを生成する.
         */
        static std::vector<Object3D*> load (const char* name);

        /**
         * @~  直前にロードしたファイルの情報。取り扱い未定.
         */
        static FileInfo file_info;


    private:

        /**
         *
         */
        static void load_m3g ();


        /**
         *
         */
        static void load_png ();


        static void load_jpeg ();



        /**
         * @~English  Creat a new Loader object.
         * @~Japanese コンストラクタ.
         */
        Loader ();
        /**
         * @~English  Destruct this object.
         * @~Japanese コンストラクタ.
         */
        ~Loader ();

        static bool            isM3GSignature ();
        static bool            isPngSignature ();
        static bool            isJpegSignature ();
        static bool            getBoolean     ();
        static char            getByte        ();
        static short           getInt16       ();
        static unsigned short  getUInt16      ();
        static int             getInt32       ();
        static unsigned int    getUInt32      ();
        static float           getFloat32     ();
        static const char*     getString      ();
        static unsigned int    getObjectIndex ();
        static int             getColorRGBA   ();
        static int             getColorRGB    ();
        static bool            getM3GSignature();
        static bool            getPngSignature();
        static bool            getJpegSignature();
        static char*           getByteArray   (int n);
        static short*          getInt16Array  (int n);
        static unsigned short* getUInt16Array (int n);
        static int*            getInt32Array  (int n);
        static unsigned int*   getUInt32Array (int n);
        static float*          getFloat32Array(int n);

        static void            read_raw (char* buf, int length);
        static void            read_zlib (char* decoded_buf, int decoded_buf_length, int compressed_length);

        static unsigned int adler32 (const unsigned char* data, int len);

        static void parseHeader();
        static void parseExref();
        static void parseAnimationController ();
        static void parseAnimationTrack ();
        static void parseAppearance ();
        static void parseBackground ();
        static void parseCamera ();
        static void parseCompositingMode ();
        static void parseFog ();
        static void parseGroup ();
        static void parseGroup (Group* grp);
        static void parseImage2D ();
        static void parseIndexBuffer (IndexBuffer* ibuf);
        static void parseKeyframeSequence ();
        static void parseLight ();
        static void parseMaterial ();
        static void parseMesh ();
        static void parseMesh (Mesh* mesh);
        static void parseMorphingMesh ();
        static void parseNode (Node* node);
        static void parseObject3D (Object3D* obj);
        static void parsePolygonMode ();
        static void parseSkinnedMesh ();
        static void parseSprite3D ();
        static void parseTexture2D ();
        static void parseTransformable (Transformable* trns);
        static void parseTriangleStripArray ();
        static void parseVertexArray ();
        static void parseVertexBuffer ();
        static void parseWorld ();

        //static std::ifstream ifs;
        static std::istrstream* iss;
        static std::vector<Object3D*> objs;
    };


} // namespace m3g {

#endif






