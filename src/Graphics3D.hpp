
#ifndef __GRAPHICS3D_HPP__
#define __GRAPHICS3D_HPP__

#include <vector>
#include <iosfwd>
#include <map>
#include "Object.hpp"

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
   * @~Japanese レンダリングターゲットをバインドできるシングルトン3Dグラフィックスコンテキスト.
   */
  class Graphics3D : public Object
  {

    /**
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

    /**
     *
     */
    struct DepthRange {
      DepthRange (float n, float f) : near(n), far(f) {};
      float near;
      float far;
    };

  public:


    /**
     * @~Japanese bindTarget()で使用するアンチエイリアスを指定する定数.
     */
    static const int ANTIALIAS   = 1<<1;
    /**
     *
     * @~Japanese bindTarget()で使用するディザーリングを指定する定数.
     */
    static const int DITHER      = 1<<2;
    /**
     *
     * @~Japanese bindTarget()で使用するレンダリングターゲットの内容が書き換えられることを示す定数.
     */
    static const int OVERWRITE   = 1<<4;
    /**
     *
     * @~Japanese bindTarget()で使用するを指定する定数.
     */
    static const int TRUE_COLOR  = 1<<3;


    /**
     * @~English  Destruct this object.
     * @~Japanese このオブジェクトを削除するデストラクタ.
     */
    ~Graphics3D ();

    /**
     * @~English  Binds a Light to use in subsequent immediate mode rendering.
     * @~Japanese イミーディエイトモードで使用するライトのバインド.
     */
    int addLight (Light* light, Transform& transform);

    /**
     * @~English  Binds the given Graphics or mutable Image 2D as the rendring ttarget of this Graphics3D.
     * @~Japanese このGraphics3DクラスにGraphicsをバインドする.
     */
    void bindTarget (Graphics* g, bool depth_buffer_enabled=true, int hints=0);

    /**
     * @~English  Clears the viewport as specified in the given Background object.
     * @~Japanese 指定されたBackgroundオブジェクトでビューポートをクリアする.
     */
    void clear (Background* background);

    /**
     * @~English  Returns the current camera.
     * @~Japanese カレントのカメラを取得する.
     */
    Camera* getCamera (const Transform& transform);

    /**
     * @~English  Returns the far distance of the depth range.
     * @~Japanese 深度レンジのfar距離を所得する.
     */
    float getDepthRangeFar () const;

    /**
     * @~English  Returns the near distance of the depth range.
     * @~Japanese 深度レンジのnear距離を取得する.
     */
    float getDepthRangeNear () const;

    /**
     * @~English  Returns the rendering hints given for the current rendering target.
     * @~Japanese カレントのレンダリングターゲットのレンダリング品とを取得する.
     */
    int getHints () const;

    /**
     * @~English  Retrieves the singleton Graphics3D instance that is associated with this application.
     * @~Japanese このアプリケーションに関連づけれれたGraphics3Dクラスのシングルトンオブジェクトを取得する.
     */
    static Graphics3D* getInstance ();

    /**
     * @~English  Returns a light int he current light array.
     * @~Japanese カレントのライト配列からライトを取得する.
     */
    Light* getLight (int index, const Transform& transform) const;

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
     * @~Japanese 現在バウンドされているターゲットをレンダリングし、ターゲットを解放する.
     */
    void releaseTarget () const;

    /**
     * @~English  Renders the given Sprite3D, Mesh, or Group node with the given transformation from local coordinates to world coordinates.
     * @~Japanese 指定されたSprite3D,Mesh,Groupノードを指定された行列でローカル座用からワールド座標に変換してレンダリングする.
     */
    void render (Node* node, Transform* transform) const;

    /**
     * @~English  Renders the given submesh with the given transformation from local coordinates to world coordinates.
     * @~Japanese 指定されたsubmeshを指定された行列でローカル座標からワールド座標に変換してレンダリングする.
     */
    void render (VertexBuffer* vertices, IndexBuffer* triangles, Appearance* apperance, Transform& transform) const;

    /**
     * @~English  Renders 
     * @~Japanese 指定されたスコープのsubmeshを指定された行列でローカル座標からワールド座標に変換してレンダリングする.
     */
    void render (VertexBuffer* vertices, IndexBuffer* triangles, Appearance* apperance, Transform& transform, int scope) const;

    /**
     * @~English  Rnders a image of world as viewd by the active camera of that World.
     * @~Japanese ワールドのアクティブなカメラでワールドをレンダリングする.
     */
    void render (World* world) const;

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

  public:
    Viewport viewport;
    bool     depth_buffer_enable;
    int      hints;
    std::map<const char*, int> properties;
    DepthRange depth_range;
  };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Graphics3D& g3d);


#endif
