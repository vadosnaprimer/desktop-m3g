#ifndef __M3G_TRANSFORMABLE_HPP__
#define __M3G_TRANSFORMABLE_HPP__

#include "m3g/Object3D.hpp"
#include "m3g/Quaternion.hpp"
#include "m3g/Transform.hpp"
#include <iosfwd>

namespace m3g {


    /**
     * @~English  An abstract base class for Node and Texture2D, defining common methods for manipulating node and texture.
     * @~Japanese ノードや2Dテクスチャーのための座標変換を扱う抽象クラス.
     */
    class Transformable : public Object3D
    {

        /**
         * @~English  Structure of scaling parameter, for inner use.
         * @~Japanese スケール乗数を保持する内部使用の構造体.
         */
        struct Scale {
            Scale (float x_, float y_, float z_) : x(x_), y(y_), z(z_) {};
            float x;
            float y;
            float z;
        };
        /**
         * @~English  Structure of translation parameter, for inner use.
         * @~Japanese 平行移動量を保持する内部使用の構造体.
         */
        struct Translation {
            Translation (float x_, float y_, float z_) : x(x_), y(y_), z(z_) {};
            float x;
            float y;
            float z;
        };


    public:

        /**
         * @~English  Construct a new Tranformable object.
         * @~Japanese このクラスは抽象クラスなので直接インスタンス化する事はできない.
         */
        Transformable ();

        /**
         * @~English  Destruct this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~Transformable ();

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         * @return 複製されたTransformableオブジェクト.
         */
        Transformable* duplicate () const;

        /**
         * @~English  Retrieves the composite transformation matrix of this Transformabls.
         * @~Japanese このクラスのコンポジット変換行列を取得する.
         * @param[out] transform 結果を書き込むTranformオブジェクト.
         * この関数は変換行列(TRSM)をすべてこの順で掛け合わせた行列を返す.
         */
        void getCompositeTransform (Transform* transform) const;

        /**
         * @~English  Retriees the orientation component of htis Transformable.
         * @~Japanese このクラスの回転要素(R)を取得する. 
         * @param[out] angle_axis  結果をangle-axis形式(angle,ax,ay,az)で書き込む領域.
         * 角度は[-180,180], 回転軸は(ax,ay,az)が必ず正規化されて書き込まれる.
         * @todo 戻り値の角度は本当にこれで正しいか（[0,360]とか180回転の扱いとか）？　あとで確認する。
         */
        void getOrientation (float* angle_aixs) const;

        /**
         * @~English  Retrieves the matrix component of this Transformable.
         * @~Japanese このクラスのスケーリング要素(S)を取得する.
         * @param[out] xyz  スケーリング要素(sx, sy, sz)を書き込む領域.
         */
        void getScale (float* xyz) const;

        /**
         * @~English  Retrieves the matrix component of this Transformable.
         * @~Japanese このクラスの行列要素(M)を取得する.
         * @param[out] transform  行列要素を書き込むTransformオブジェクト.
         */
        void getTransform (Transform* transform) const;

        /**
         * @~English  Retrieves the translation component of this Transformable.
         * @~Japanese このクラスの平行移動要素成分(T)を取得する.
         * @param[out] xyz  平行移動要素(tx, ty, tz)を書き込む領域.
         */
        void getTranslation (float* xyz) const;

        /**
         * @~English  Multiplies the current orientation component from the right by the given orientation.
         * @~Japanese 現在の回転要素(R)に指定された回転を右から乗算する.
         * （注意）この関数は「post」と名前がついているが右から乗算するので、
         *  実際には既存の回転行列の「前に」適応される。仕様通りの動作だが直感に反する。
         * @param[in] angle 角度[degree]
         * @param[in] ax    回転軸のx成分
         * @param[in] ay    回転軸のy成分
         * @param[in] az    回転軸のz成分
         * 回転軸が正規化されている必要はない。回転軸の長さが0の場合はエラーとなる.
         */
        void postRotate (float angle, float ax, float ay, float az);

        /**
         * @~English  Multiplies the current orientation component from the left by the given orientation.
         * @~Japanese 現在の回転要素(R)に指定された回転を左から乗算する.
         * （注意）この関数は「pre」と名前がついているが左から乗算するので、
         *  実際には既存の回転行列の「後に」適応される。仕様通りの動作だが直感に反する。
         * @param[in] angle 角度[degree]
         * @param[in] ax    回転軸のx成分
         * @param[in] ay    回転軸のy成分
         * @param[in] az    回転軸のz成分
         * 回転軸が正規化されている必要はない。回転軸の長さが0の場合はエラーとなる.
         */
        void preRotate (float angle, float ax, float ay, float az);

        /**
         * @~English  Multiplies the current scale component by the given scale factors.
         * @~Japanese 現在のスケーリング要素(S)に指定されたスケール要素を乗算する.
         * @param[in] sx  x方向のスケーリング要素
         * @param[in] sy　y方向のスケーリング要素
         * @param[in] sz  z方向のスケーリング要素
         */
        void scale (float sx, float sy, float sz);

        /**
         * @~English  Sets the orientation component of this Transformable.
         * @~Japanese 現在の回転要素(R)を破棄し、引数の回転を新たな回転要素(R)に設定する.
         * @param[in] angle 回転角度[degree]
         * @param[in] ax    回転軸のx成分.
         * @param[in] ay    回転軸のy成分.
         * @param[in] az    回転軸のz成分.
         */
        void setOrientation (float angle, float ax, float ay, float az);

        /**
         * @~English  Sets the scale component of this Transformable.
         * @~Japanese 現在のスケーリング要素(S)を破棄し、引数のスケーリングを新たなスケーリング要素(S)に設定する.
         * @param[in] sx  x方向のスケーリング要素.
         * @param[in] sy  y方向のスケーリング要素.
         * @param[in] sz  z方向のスケーリング要素.
         */
        void setScale (float sx, float sy, float sz);

        /**
         * @~English  Sets the matrix component of this Transformable by copying in the given Transform.
         * @~Japanese 現在の行列要素(M)を破棄し、引数のTransformオブジェクトを新たな行列要素(M)に設定する.
         * @param[in] transform  設定したい行列を保持するTransformオブジェクト.
         */
        void setTransform (const Transform* transform);

        /**
         * @~English  Sets the translation component of this Transformable.
         * @~Japanese 現在の移動要素(T)を破棄し、引数の移動を新たな移動要素(T)に設定する.
         * @param[in] tx  x方向の移動要素.
         * @param[in] ty  y方向の移動要素.
         * @param[in] tz  z方向の移動要素.
         */
        void setTranslation (float tx, float ty, float tz);

        /**
         * @~English  Adds the given offset to the current translation component.
         * @~Japanese 現在の移動要素(T)に指定された移動を足す.
         * @param[in] tx  x方向の移動要素.
         * @param[in] ty  y方向の移動要素.
         * @param[in] tz  z方向の移動要素.
         */
        void translate (float tx, float ty, float tz);

        /**
         * @~English  Print out information this object, for debug only.
         * @~Japanese このTransformableオブジェクトの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

    protected:

        /**
         * @~English
         * @~Japanese
         */
        virtual void addAnimationTrack_xxx (AnimationTrack* animation_track, bool accepted);

        /**
         * @~English  
         * @~Japanese 
         */
        virtual int animate_xxx (int world_time);

        /**
         * @~English  
         * @~Japanese 
         */
        virtual void render_xxx (RenderState& state) const;

        /**
         * @~English  
         * @~Japanese 
         */
        virtual Transformable* duplicate_xxx (Object3D* obj) const;


    private:
        Transformable (const Transformable& trans);
        Transformable& operator= (const Transformable& trans);



    private:
        Scale       scaling;
        Translation translation;
        Quaternion  orientation;
        Transform   transform;
    };


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Transformable& t);

#endif
