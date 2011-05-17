
#ifndef __M3G_GRAPHICS3D_HPP__
#define __M3G_GRAPHICS3D_HPP__

#include <vector>
#include <iosfwd>
#include <map>
#include "m3g/Object.hpp"

namespace m3g {

    class Light;
    class Transform;
    class Graphics;
    class Image2D;
    class Background;
    class Camera;
    class Node;
    class VertexBuffer;
    class IndexBuffer;
    class Appearance;
    class World;

    /**
     * @~English  A singleton 3D graphics context that can be bound to a rendering target.
     * @~Japanese 描画デバイス(GPU)を抽象化したクラス。全てのレンダリングはこのクラスを通して行われる.
     */
    class Graphics3D : public Object
    {
        /**
         * @internal
         * @~English  Struct of viewport setting, for inner use.
         * @~Japanese ビューポートを定義する内部使用の構造体.
         */
        struct Viewport {
            Viewport (float x_, float y_, float w_, float h_) : x(x_), y(y_), width(w_), height(h_) {};
            float x;
            float y;
            float width;
            float height;
        };


    public:


        /**
         * @~English  A parameter to bindTarget, specifying that antialiasing should be turned on.
         * @~Japanese bindTarget()で使用するアンチエイリアスを指定する定数.
         */
        static const int ANTIALIAS   = 1<<1;
        /**
         * @~English  A parameter to bindTarget, specifying that dither should be turned on.
         * @~Japanese bindTarget()で使用するディザーリングを指定する定数.
         */
        static const int DITHER      = 1<<2;
        /**
         * @~English  A parameter to bindTarget, specifying that existing contents of the rendering targte need not be preserved.
         * @~Japanese bindTarget()で使用するレンダリングターゲットの内容が書き換えられることを示す定数.
         */
        static const int OVERWRITE   = 1<<4;
        /**
         * @~English  A parameter to bindTarget, specifying that true color rendering should be turned on.
         * @~Japanese bindTarget()で使用するトゥルーカラー(1677万色)を指定する定数.
         */
        static const int TRUE_COLOR  = 1<<3;


        /**
         * @~English  Destruct this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        ~Graphics3D ();

        /**
         * @~English                           Binds a Light to use in subsequent immediate mode rendering.
         *                                     This function is not implemented.
         * @param[in]  light                   Light object to be added.
         * @param[in]  transform               the transformation from the lcoal coordinate sytem
         *                                     of light to world space, or null to indicate the indntity matrix.
         * @return                             the index at which the Light was inserted in the array.
         * @throw      NullPointerException    引数のlightがNULLの場合.
         * @throw      NotImplementedException この関数は実装されていない.
         *
         * This function is used only in immediate-mode and not implmented.
         * I have no plan to implement immediate-mode.
         *
         * @~Japanese  ライトを追加します。この関数はイミーディエイトモードでのみ使用します。
         *             この関数は実装されていません.
         * @param[in]  light      追加するLightオブジェクト.
         * @param[in]  transform  ライトのローカル座標からワールド座標への変換を表すTransformオブジェクト.
         *                        NULLの場合は単位行列を表します。
         * @return                後でこのライトを参照する時に使用するインデックスを返します. 
         * @throw      NotImplementedException この関数の呼び出しは常にこの例外を発生します.
         * @throw      NullPointerException    引数のlightがNULLの場合.
         *
         * この関数はイミーディエイトモードでのみ使用し、Destkop-M3Gでは実装されていません。
         * 現在イミーディエイトモードを実装する予定はありません。
         */
        int addLight (Light* light, const Transform& transform);

        /**
         * @~English  Binds the defualt (frame buffer) as the rendring ttarget of this Graphics3D.
         * @param[in]  target                the Image2D or Graphics object to receive the rendered image.
         * This function is not implmented.
         * I have no plan to implment this function.
         * 
         * @~Japanese  描画対象をこのGrapihcs3Dオブジェクトにバインドします。現在この関数は実装されていません。
         * @param[in]  target                描画対象を表すオブジェクト。現在では特に規定されていない。
         * この関数はDestkop-M3Gでは実装されていません。
         * 実装する予定はありません。
         */
        void bindTarget (void* target);


        /**
         * @~English  Binds the defualt (frame buffer) as the rendring ttarget of this Graphics3D.
         * @param[in]  target                the Image2D or Graphics object to receive the rendered image.
         * @param[in]  depth_buffer_enabled  true to enabled depth buffering; false to disable.
         * @param[in]  hints                 an integer bitmask specifying which rendering hints to enbale,
         *                                   or zero to disable all hints.
         * This function is not implmented.
         * I have no plan to implment this function.
         * 
         * @~Japanese  描画対象をこのGrapihcs3Dオブジェクトにバインドします。現在この関数は実装されていません。
         * @param[in]  target                描画対象を表すオブジェクト。現在では特に規定されていない。
         * @param[in]  depth_buffer_enabled  デプスバッファーを有功にするフラグです。trueの時有効にし、falseの時に無効化します。
         * @param[in]  hints                 レンダリングに使用する"ヒント"をビット演算のorで重ねて指定します。
         * この関数はDestkop-M3Gでは実装されていません。
         * 実装する予定はありません。
         */
        void bindTarget (void* target, bool depth_buffer_enabled, int hints);


        /**
         * @~English   Clears the viewport as specified in the given Background object.
         * @param[in]  background  a Background object defining which buffers to clear and how, or null to use the defualt settings.
         * @throw      NotImplementedException   allways rise this exception.
         * @throw      IllegalArgumentException  if the background image in background is not in the same format 
         *                                       as the currently bound rendering target.
         * @throw      IllegalStateException     if this Graphics3D does not have a rendeing target.
         *
         * @~Japanese  ビューポートを指定されたBackgroundオブジェクトでクリアします.
         * @param[in]  background  バッファーのクリアの有無とその方法を定義するBackgroundオブジェクト。
         *                         NULLの場合はデフォルトでクリアされます。
         * @throw      NotImplementedException   この関数の呼び出しは常にこの例外を発生します。
         * @throw      IllegalArgumentException  Backgoundオブジェクトに設定された背景画像のフォーマットが現在の
         *                                       レンダリングターゲットのフォーマットと異なる場合に発生します。
         * @throw      IllegalStateException     このGraphics3Dオブジェクトにレンダリングターゲットがバインドされていない場合に発生します。
         * 
         * この関数はイミーディエイトモードでのみ使用し、Destkop-M3Gでは実装されていません。
         * 現在イミーディエイトモードを実装する予定はありません。
         */
        void clear (Background* background);

        /**
         * @~English   Returns the current camera.
         * @param[out] transform  a Transorm to store the current camera transformation in, or null to only get the camera.
         * @return                カレントのCameraオブジェクト.
         * @throw      NotImplementedException   allways rise this exception.
         * @~Japanese  カレントのカメラを取得します.

         * @param[out] transform  カメラの変換行列を書き込むTransformオブジェクトへのポインター.NULLの場合はCameraオブジェクトのみ取得します。
         * @return                カレントのCameraオブジェクト.
         * @throw      NotImplementedException   この関数の呼び出しは常にこの例外を発生します。
         * 
         * この関数はイミーディエイトモードでのみ使用し、Destkop-M3Gでは実装されていません。
         * 現在イミーディエイトモードを実装する予定はありません。
         */
        Camera* getCamera (Transform* transform);

        /**
         * @~English  Returns the far distance of the depth range.
         * @return    distance to the far clipping plane, in window coordinates.
         * @~Japanese デプス範囲のファー距離を取得します。
         * @return    ファークリッピング面のウィンドウ座標での値を所得します.
         *
         * NDC座標系におけるファークリッピング面(z=1)が、ウィンドウ座標系に変換されたときのzの値を取得します。
         * デフォルトではz=1です。
         */
        float getDepthRangeFar () const;

        /**
         * @~English  Returns the near distance of the depth range.
         * @return    distance to the near clipping plane, in window coordinates.
         * @~Japanese デプス範囲のニア距離を取得します。
         * @return    ニアクリッピング面のウィンドウ座標での値を所得します.
         *
         * NDC座標系におけるニアクリッピング面(z=-1)が、ウィンドウ座標系に変換されたときのzの値を取得します。
         * デフォルトではz=0です。
         */
        float getDepthRangeNear () const;

        /**
         * @~English   Returns the rendering hints given for the current rendering target.
         * @return     the current renderig hint bitmask.
         * @throw      NotImplementedException   allways rise this exception.
         *
         * @~Japanese  カレントのレンダリングターゲットのレンダリングヒントを取得します.
         * @return     カレントのレンダリング・ヒントを返します。
         * @throw      NotImplementedException   この関数の呼び出しは常にこの例外を発生します。
         *
         * この関数はDestkop-M3Gでは実装されていません。
         * 実装する予定はありません。
         */
        int getHints () const;

        /**
         * @~English  Retrieves the singleton Graphics3D instance that is associated with this application.
         * @return    the Graphics3D instance associated with this application.
         *
         * @~Japanese このアプリケーションに関連づけれれたGraphics3Dクラスのシングルトンオブジェクトを取得します.
         * @return    Graphics3Dオブジェクトへのポインター
         * 
         * Graphics3Dクラスはシングルトン化されていてインスタンス化するにはこの関数を使用します。
         * Graphcis3Dオブジェクトはアプリケーションでただ1つ存在します。戻り値がNULLになる事はありません。
         */
        static Graphics3D* getInstance ();

        /**
         * @~English  Returns a light int he current light array.
         * @~Japanese カレントのライト配列からライトを取得する.
         */
        Light* getLight (int index, Transform* transform) const;

        /**
         * @~English  Returns the size of the current light array.
         * @~Japanese カレントのライト配列のサイズを取得する.
         */
        int getLightCount () const;

        /**
         * @~English  Retrieves implementation specific peoperties.
         * @~Japanese 実装依存のプロパティの取得.
         */
        std::map<const char*, int> getProperties () const;

        /**
         * @~English  Returns the current rendierng target.
         * @~Japanese カレントのレンダリングターゲットの取得.
         */
        void* getTarget () const;

        /**
         * @~English  Returns the height of the viewport.
         * @~Japanese ビューポートの高さの取得.
         */
        int getViewportHeight () const;

        /**
         * @~English  Returns the width of the viewport.
         * @~Japanese ビューポートの幅の取得.
         */
        int getViewportWidth () const;

        /**
         * @~English  Returns the horizontal position of the viewport.
         * @~Japanese ビューポートの水平方向の位置の取得.
         */
        int getViewportX () const;

        /**
         * @~English  Returns the vertical position of the viewport.
         * @~Japanese ビューポートの垂直方向の位置の取得.
         */
        int getViewportY () const;

        /**
         * @~English  Queries whether depth buffering is enalbed for the current rendering target.
         * @~Japanese カレントのレンダリングターゲットの深度バッファーが有効かどうかの問い合わせ.
         */
        bool isDepthBufferEnabled () const;

        /**
         * @~English  Flushes the renderd 3D image to the currently bound target and then releases the target.
         * @~Japanese 現在バインドされているターゲットをレンダリングし、ターゲットを解放する.
         */
        void releaseTarget ();

        /**
         * @~English  Render the given Sprite3D, Mesh, or Group node with the given transformation from local coordinates to world coordinates.
         * @~Japanese 指定されたSprite3D,Mesh,Groupノードを指定された行列でローカル座用からワールド座標に変換してレンダリングする.
         */
        void render (const Node* node, const Transform* transform) const;

        /**
         * @~English  Render the iven submesh with the given transformation from local coordinates to world coordinates.
         * @~Japanese 指定されたサブメッシュを指定された行列でローカル座標からワールド座標に変換してレンダリングする.
         */
        void render (const VertexBuffer* vertices, const IndexBuffer* triangles, const Appearance* apperance, const Transform* transform) const;

        /**
         * @~English  Render the iven submesh with the given transformation from local coordinates to world coordinates.
         * @~Japanese 指定されたスコープのサブメッシュを指定された行列でローカル座標からワールド座標に変換してレンダリングする.
         */
        void render (const VertexBuffer* vertices, const IndexBuffer* triangles, const Appearance* apperance, const Transform* transform, int scope) const;

        /**
         * @~English  Rnders a image of world as viewd by the active camera of that World.
         * @~Japanese 引数のworld以下をアクティブなカメラでレンダリングする.
         * @param[in]  world  レンダリングしたいシーン.
         */
        void render (const World* world) const;

        /**
         * @~English  Clears the array of current Lights.
         * @~Japanese カレントのライト配列のクリア.
         */
        void resetLights ();

        /**
         * @~English  Sets the Camera to use in subsequent immediate mode rendering.
         * @~Japanese イミーディエイトモードレンダリングで使用するカメラを設定する.
         */
        void setCamera (Camera* camera, const Transform& transform);

        /**
         * @~English  Specifies the mappin gof depth values from normalized device coordinates to window coordinates.
         * @~Japanese NDC座標系からウィンドウ座標系に変換するさいの深度値のマッピングの仕方を設定する.
         */
        void setDepthRange (float near, float far);

        /**
         * @~English  Replaces or modifies a Light currently bound for immediate mode rendering.
         * @~Japanese イミーディエイトモードレンダリング現在バウンドされているライトを置き換えるか修正する.
         */
        void setLight (int index, Light* light, const Transform& transform);

        /**
         * @~English  Specifies a rectangular viewport on the currently bound rendering target.
         * @~Japanese 現在バウンドされているレンダリングターゲットの矩形ビューポートを設定する.
         */
        void setViewport (int x, int y, int width, int height);


        /**
         * @~English  Print out information of this object, for debug only.
         * @~Japanese このオブジェクトの情報を表示する。デバッグ用.
         */
        std::ostream& print (std::ostream& out) const;

    private:
        /**
         * @~English  Forbiddened constructor of Graphics3D.
         * @~Japanese コンストラクタ。この関数はprivateなので直接は呼べないのでgetInstance()を使う.
         */
        Graphics3D ();


        void initOpenGL ();

    private:
        Viewport viewport;
        bool     depth_buffer_enable;
        int      hints;
        std::map<const char*, int> properties;

    };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Graphics3D& g3d);


#endif
