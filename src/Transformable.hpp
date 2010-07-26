#ifndef __TRANSFORMABLE_HPP__
#define __TRANSFORMABLE_HPP__

#include "Object3D.hpp"
#include "Quaternion.hpp"
#include "Transform.hpp"
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
         */
        virtual Transformable* duplicate () const;

        /**
         * @~English  Copy this Object3D to specified Object3D, not defined by M3G. 
         * @~Japanese このオブジェクトのデータを引数で指定されたオブジェクトにコピーするM3G非標準の関数.
         */
        void copy (Transformable* trans) const;

        /**
         * @~English  Adds the given AnimationTrack to this Object3D, 
         *            potentially changing the order and indices of the previously added tracks.
         * @~Japanese このObject3Dに指定されたアニメーショントラックを追加する。
         *            既存のトラックの順番とインデックスは変更されるかもしれない.
         */
        virtual void addAnimationTrack (AnimationTrack* animation_track);

        /**
         * @~English  Updates all animated properties in this Object3D and all Object3Ds that are reachable from this Object3D.
         * @~Japanese このObject3D自身とここから到達できるObject3Dのアニメーテッドプロパティを更新する.
         */
        virtual int animate (int world_time);

        /**
         * @~English  Retrieves the composite transformation matrix of this Transformabls.
         * @~Japanese このクラスの複合変換行列を取得する.
         */
        void getCompositeTransform (Transform* transform) const;

        /**
         * @~English  Retriees the orientation component of htis Transformable.
         * @~Japanese このクラスの回転要素を取得する.
         */
        void getOrientation (float* angle_aixs) const;

        /**
         * @~English  Retrieves the matrix component of this Transformable.
         * @~Japanese このクラスのスケーリング要素を取得する.
         */
        void getScale (float* xyz) const;

        /**
         * @~English  Retrieves the matrix component of this Transofrmable.
         * @~Japanese このクラスの行列要素を取得する.
         */
        void getTransform (Transform* transform) const;

        /**
         * @~English  Retrieves the translation component of this Transformable.
         * @~Japanese このクラスの移動要素成分を取得する.
         */
        void getTranslation (float* xyz) const;

        /**
         * @~English  Multiplies the current orientation component from the right by the given orientation.
         * @~Japanese 指定された軸の回転を右から乗算する.
         */
        void postRotate (float angle, float ax, float ay, float az);

        /**
         * @~English  Multiplies the current orientation component from the left by the given orientation.
         * @~Japanese 指定された軸の回転を左から乗算する.
         */
        void preRotate (float angle, float ax, float ay, float az);

        /**
         * @~English  Multiplies the current scale component by the given scale factors.
         * @~Japanese 指定されたスケール要素でカレントのスケーリング要素に乗算する.
         */
        void scale (float sx, float sy, float sz);

        /**
         * @~English  Sets the orientation component of this Transformable.
         * @~Japanese このTransformableクラスのOrientation要素を設定する.
         */
        void setOrientation (float angle, float ax, float ay, float az);

        /**
         * @~English  Sets the scale component of this Transformable.
         * @~Japanese このTransformableクラスのスケーリング要素を設定する.
         */
        void setScale (float sx, float sy, float sz);

        /**
         * @~English  Sets the matrix component of this Transformable by copying in the given Transform.
         * @~Japanese 指定されたTransformでこのTransformableクラスを設定する.
         */
        void setTransform (const Transform& transform);

        /**
         * @~English  Sets the translation component of this Transformable.
         * @~Japanese このTransformableクラスの移動要素を設定する.
         */
        void setTranslation (float tx, float ty, float tz);

        /**
         * @~English  Adds the given offset to the current translation component.
         * @~Japanese カレントの移動要素に指定されたオフセットを足す.
         */
        void translate (float tx, float ty, float tz);

        /**
         * @~English  Print out information this object, for debug only.
         * @~Japanese このTransformableクラスの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

        /**
         * @~English  Render this object, for inner use.
         * @~Japanese このTransformableをレンダリングする内部使用の関数.
         */
        virtual void render (RenderState& state) const;

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
