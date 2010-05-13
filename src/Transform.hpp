#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__

#include <iosfwd>
#include "Matrix.hpp"
#include "Object.hpp"

namespace m3g {

    class VertexArray;

    /**
     * @~English  A generic 4x4 floating point matrix, representing a transformation.
     * @~Japanese 座標変換を表す汎用の4x4行列.
     */
    class Transform : public Object
    {
    public:
        /**
         * @~English  Constructs a new Transform object and intitializes it to the 4x4 identity matrix.
         * @~Japanese デフォルトの値のTransformオブジェクトの生成.
         */
        Transform ();

        /**
         * @~English  Consyructs a new Transform object and initializes it by copying in the contents of the given Transform.
         * @~Japanese 指定されたTransformをコピーしてTransformオブジェクトを生成.
         */
        Transform (const Transform& t);

        /**
         * @~English  Destructs this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        ~Transform ();

        /**
         * @~English  Retrieves the contents of this tarnsformation as a 16-element float array.
         * @~Japanese この変換を16個のfloatの配列として取り出す.
         */
        void get (float* matrix) const;

        /**
         * @~English  Invertes this matrix, if possible.
         * @~Japanese (可能なら)この行列の逆行列を計算し置き換える.
         */
        void invert ();

        /**
         * @~English  Multiplies this transformation from the right by the given transformation.  
         * @~Japanese 指定された変換行列を右から乗算する.
         */
        void postMultiply (const Transform& transform);

        /**
         * @~English  Multiplies this transformation from the right by the given rotation matrix, specified in axis-angle form.
         * @~Japanese 指定された回転軸と角度で回転する回転行列を右から乗算する。角度の単位はdegree.
         */
        void postRotate (float angle, float ax, float ay, float az);

        /**
         * @~English  Multiplies this transformation from the right by the given rotation matrix, specified in quaternion form.
         * @~Japanese クォータニオン形式で指定された回転を行う回転行列を右から乗算する.
         */
        void postRotateQuat (float qx, float qy, float qz, float qw);

        /**
         * @~English  Multiplies this transformation from the right by the given scale matrix.
         * @~Japanese 指定されたスケーリング行列を右から乗算する.
         */
        void postScale (float sx, float sy, float sz);

        /**
         * @~English  Multiplies this transformation from the right by the given translation matrix.
         * @~Japanese 指定された移動行列を右から乗算する.
         */
        void postTranslate (float tx, float ty, float tz);

        /**
         * @~English  Sets this transformation by copying from the given 16-element float array.
         * @~Japanese 指定された16個のfloatの配列をコピーして変換を設定する.
         */
        void set (const float* matrix);

        /**
         * @~English  Sets this transformation by copying the cvontents of the given Transform.
         * @~Japanese 指定されたTransformをコピーして変換を設定する.
         */
        void set (const Transform& transform);

        /**
         * @~English  Replaces this transformation with the 4x4 identity matrix.
         * @~Japanese この変換を4x4の単位行列に設定する.
         */
        void setIdentity ();

        /**
         * @~English  Multiplies the given array of 4D vectors with this matrix.
         * @~Japanese 指定された4要素のfloatのベクトルにこの変換行列を乗算する.
         */
        void transform (float* vectors) const;

        /**
         * @~English  Multiplies the elements of the given VertexArray with this matrix, storeing the transformed values in a flloat array.
         * @~Japanese 指定されたVertexArrayの要素にこの変換行列を乗算する。
         *            結果はfloatの配列として収納する.
         */
        void transform (VertexArray* in, float* out, bool w) const;

        /**
         * @~English  Transpose this matrix.
         * @~Japanese 転置を取りこの行列と入れ替える.
         */
        void transpose ();

        /**
         * @~English  Print out information of this object, for only debug.
         * @~Japanese このTransformクラスの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

    private:
        Matrix matrix;
    };



} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Transform& t);

#endif
