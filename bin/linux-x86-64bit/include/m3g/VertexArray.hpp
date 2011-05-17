#ifndef __M3G_VERTEX_ARRAY_HPP__
#define __M3G_VERTEX_ARRAY_HPP__


#include "m3g/Object3D.hpp"
#include "m3g/m3ginternal.hpp"
#include <iosfwd>


namespace m3g {

    class VertexBuffer;
    class Matrix;
    struct BoneWeight;

    /**
     * @~English  An array of integer vectors representing vertex positions, normals, colors, or texture coordinates.
     * @~Japanese 頂点座標、頂点法線、頂点カラー、テクスチャー座標データの配列を保持するコンテナクラス.
     */
    class VertexArray : public Object3D
    {

    public:
        /**
         * @~English  Constructs a new VertexArray with the given dimensions.
         * @~Japanese 指定されたサイズで新しいVertxArrayを作成する.
         * @param[in] num_vertices    頂点数
         * @param[in] num_components  コンポーネント数
         * @param[in] component_size  コンポーネントサイズ(型)
         */
        VertexArray (int num_vertices, int num_components, int component_size);

        /**
         * @~English  Destructs this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~VertexArray ();

        /**
         * @~English  Convert data to specified component size(type).
         * @~Japanese このVertexArrayクラスの保持する内部データを指定のコンポーネント型(サイズ)に変更する。
         * @param[in] component_size  変更するコンポーネント型(サイズ)の指定
         */
        void convert (int component_size);

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         * @return 複製されたVertexArrayオブジェクト.
         */
        VertexArray* duplicate () const;

        /**
         * @~English  Returns a range of 8-bit vertex attributes. 
         * @~Japanese 8bitレンジの頂点データの取得.
         * @param[in] first_vertex データを取得したい頂点の最初の番号.
         * @param[in] num_vertices 頂点数
         * @param[in] values       結果を書き込むchar型の配列.
         */
        void get (int first_vertex, int num_vertices, char* values) const;

        /**
         * @~English  Returns a range of 16-bit vertex attributes.
         * @~Japanese 16bitレンジの頂点データの取得.
         * @param[in] first_vertex データを取得したい頂点の最初の番号.
         * @param[in] num_vertices 頂点数
         * @param[in] values       結果を書き込むshort型の配列.
         */
        void get (int first_vertex, int num_vertices, short* values) const;

        /**
         * @~English  Returns a range of 32-bit float vertex attributes.
         * @~Japanese 32bit浮動小数点レンジの頂点データの取得.
         * @param[in] first_vertex データを取得したい頂点の最初の番号.
         * @param[in] num_vertices 頂点数.
         * @param[in] values       結果を書き込むfloat型の配列.
         */
        void get (int first_vertex, int num_vertices, float* values) const;

        /**
         * @~English  Returns a scale-biased range of 32-bit float vertex attributes.
         * @~Japanese 頂点データをscale,biasをかけた32bit浮動小数点で取得.
         * @param[in] first_vertex データを取得したい頂点の最初の番号.
         * @param[in] num_vertices 頂点数.
         * @param[in] scale        補正に使用するスケール値.
         * @param[in] bias         補正に使用するバイアス値.
         * @param[in] values       結果を書き込むfloat型の配列.
         */
        void get (int first_vertex, int num_vertices, float scale, float* bias, float* values) const;

        /**
         * @~English  Returns the number of components per vertex.
         * @~Japanese 1頂点当たりの要素数の取得.
         * @return コンポーネント数.
         */
        int getComponentCount () const;

        /**
         * @~English  Returns the data type (size) of vertex components.
         * @~Japanese 頂点要素のデータタイプ（サイズ）の取得.
         * @return コンポーネントタイプ(サイズ). 1,2,4のいずれか。
         */
        int getComponentType () const;


        /**
         * @~English  Returns the number of vertices in this array.
         * @~Japanese このVertexArrayオブジェクトの持つ頂点数の取得.
         * @return 頂点数
         */
        int getVertexCount () const;

        /**
         * @~English  Copies in an array of 8-bit vertex attributes.
         * @~Japanese 8bit頂点データの設定.
         * @param[in] first_vertex データを設定したい頂点の最初の番号.
         * @param[in] num_vertices 頂点数.
         * @param[in] values       設定したいデータを持つchar型の配列.
         */
        void set (int first_vertex, int num_vertices, const char* values);

        /**
         * @~English  Copies in an array of 16-bit vertex attributes.
         * @~Japanese 16bit頂点データの設定.
         * @param[in] first_vertex データを設定したい頂点の最初の番号.
         * @param[in] num_vertices 頂点数.
         * @param[in] values       設定したいデータを持つshort型の配列.
         */
        void set (int first_vertex, int num_vertices, const short* values);

        /**
         * @~English  Copies in an array of 32-bit float vertex attributes.
         * @~Japanese 32bit浮動小数点頂点データの設定.
         * @param[in] first_vertex データを設定したい頂点の最初の番号.
         * @param[in] num_vertices 頂点数.
         * @param[in] values       設定したいデータを持つfloat型の配列.
         */
        void set (int first_vertex, int num_vertices, const float* values);

        /**
         * @internal  
         * @~English  
         * @~Japanese 
         */
        void setMorphing (const VertexArray*                     base_positions,
                          const std::vector<const VertexArray*>& morph_target_positions,
                          const std::vector<float>&              morph_wegiths);

        /**
         * @internal  
         * @~English  
         * @~Japanese 
         */
        void setSkinning (const VertexArray*            base_positions,
                          const std::vector<std::vector<BoneWeight> >& bone_indices,
                          const std::vector<Matrix>&    matrix_palette);

        /**
         * @internal  
         * @~English  
         * @~Japanese 
         */
        void updateOpenGLData (const void* value) const;


        /**
         * @internal  
         * @~English  Retrieve OpenGL' vbo name.
         * @~Japanese OpenGLのvbo名を取得する.
         */
        unsigned int getOpenGLVBO () const;

        /**
         * @internal  
         * @~English  Retrieve OpenGL' type name.
         * @~Japanese OpenGLの型名を取得する.
         */
        unsigned int getOpenGLFormat () const;


        /**
         * @~English  Print out information of this object, for debug only.
         * @~Japanese このVertexArrayクラスの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

        /**
         * @~English  Print out raw data of this object, for debug only.
         * @~Japanese このVertexArrayクラスの保持しているデータを表示する。デバッグ用.
         */
        std::ostream& print_raw_data (std::ostream& out) const;

    protected:

        /**
         * @~English  
         * @~Japanese 
         */
        virtual VertexArray* duplicate_xxx (Object3D* obj) const;

    private:
        VertexArray (const VertexArray& varry);
        VertexArray& operator= (const VertexArray& varry);

    private:
        int   component_count;
        int   component_size;
        int   vertex_count;
        union {
            char*  char_values;
            short* short_values;
            float* float_values;
        };
        unsigned int vbo;
    };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::VertexArray& va);


#endif
