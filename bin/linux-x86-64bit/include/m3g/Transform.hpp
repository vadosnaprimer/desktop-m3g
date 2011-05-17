#ifndef __M3G_TRANSFORM_HPP__
#define __M3G_TRANSFORM_HPP__

#include <iosfwd>
#include "m3g/Matrix.hpp"
#include "m3g/Object.hpp"

namespace m3g {

    class VertexArray;
    class Vector;
    class Matrix;

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
         * @param[out] matrix  結果を書き込むfloat16個の領域.
         */
        void get (float* matrix) const;

        /**
         * @~English  
         * @~Japanese 
         * @return matrix.
         */
        Matrix getMatrix () const;

        /**
         * @~English  Invertes this matrix, if possible.
         * @~Japanese (可能なら)この行列の逆行列を計算し置き換える.
         */
        void invert ();

        /**
         * @~English  Multiplies this transformation from the right by the given transformation.  
         * @~Japanese この行列に、指定された変換行列を右から乗算する.
         * @param[in] transform  変換行列.
         */
        void postMultiply (const Transform& transform);

        /**
         * @~English  Multiplies this transformation from the right by the given rotation matrix, specified in axis-angle form.
         * @~Japanese この行列に、指定された回転軸と角度で回転する回転行列を右から乗算する。角度の単位はdegree.
         * @param[in] angle  角度[degree]
         * @param[in] ax     回転軸のx成分.
         * @param[in] ay     回転軸のy成分.
         * @param[in] az     回転軸のz成分.
         */
        void postRotate (float angle, float ax, float ay, float az);

        /**
         * @~English  Multiplies this transformation from the right by the given rotation matrix, specified in quaternion form.
         * @~Japanese この行列に、クォータニオン形式で指定された回転を行う回転行列を右から乗算する.
         * @param[in] qx  クォータニオンのベクター成分i
         * @param[in] qy  クォータニオンのベクター成分j
         * @param[in] qz  クォータニオンのベクター成分k
         * @param[in] qw  クォータニオンのスカラー成分
         */
        void postRotateQuat (float qx, float qy, float qz, float qw);

        /**
         * @~English  Multiplies this transformation from the right by the given scale matrix.
         * @~Japanese この行列に、指定されたスケーリング行列を右から乗算する.
         * @param[in] sx  x方向のスケーリング成分
         * @param[in] sy  y方向のスケーリング成分
         * @param[in] sz  z方向のスケーリング成分
         */
        void postScale (float sx, float sy, float sz);

        /**
         * @~English  Multiplies this transformation from the right by the given translation matrix.
         * @~Japanese 指定された移動行列を右から乗算する.
         * @param[in] tx  x方向の移動成分.
         * @param[in] ty  y方向の移動成分.
         * @param[in] tz  z方向の移動成分.
         */
        void postTranslate (float tx, float ty, float tz);

        /**
         * @~English  Sets this transformation by copying from the given 16-element float array.
         * @~Japanese 指定された16個のfloatの配列で変換行列を設定する.
         * @param[in] matrix  変換行列を表す16個の配列。row-major.
         */
        void set (const float* matrix);

        /**
         * @~English  Sets this transformation by copying the contents of the given Transform.
         * @~Japanese 指定されたTransformオブジェクトで変換行列を設定する.
         * @param[in] transform  変換行列を表すTransformオブジェクト.
         */
        void set (const Transform* transform);
        
        
        /**
         * @internal
         * @~English  set this tranformation bycopying from the contents of the given Matrix.
         * @~Japanese 指定されたMatrixオブジェクトで変換行列を設定する.
         */
        void set (const Matrix& matrix);

        /**
         * @~English  Replaces this transformation with the 4x4 identity matrix.
         * @~Japanese この変換行列を4x4の単位行列に設定する.
         */
        void setIdentity ();

        /**
         * @~English  Multiplies the given array of 4D vectors with this matrix.
         * @~Japanese float4要素のベクトルの集合をすべてこの変換行列で変換して書き換える.
         * @param[in]     vector_num  変換するデータの個数。かならず4の倍数になる.
         * @param[in,out] vectors     変換するデータの集合。値は変換後の値に書き換えられる.
         */
        void transform (int vector_num, float* vectors) const;

        /**
         * @~English  Multiplies the elements of the given VertexArray with this matrix, storeing the transformed values in a flloat array.
         * @~Japanese 指定されたVertexArrayの要素にこの変換行列を乗算する。
         *            結果はfloatの配列として収納する.
         */
        void transform (const VertexArray* in, float* out, bool w) const;

        /**
         *
         */
        Vector transform (const Vector& vector) const;

        /**
         *
         */
        Vector transform3x3 (const Vector& vector) const;

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
