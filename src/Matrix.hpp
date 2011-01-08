#ifndef __M3G_MATRIX_HPP__
#define __M3G_MATRIX_HPP__

#include <iosfwd>

namespace m3g {

    class Vector;

    /**
     * @internal
     * @~English  4x4 Matrix, for inner use.
     * @~Japanese 4x4行列クラス。内部使用専用.
     */
    class Matrix
    {
    public:
        /**
         * @internal
         * @~English  Create a new Indentity Matrix object.
         * @~Japanese このMatrixクラスのオブジェクト(単位行列)を作成するコンストラクタ.
         */
        Matrix ();

        /**
         * @internal
         * @~English  Create a new Materix object with specified transformation.
         * @~Japanese 指定された行列でMatrixクラスのオブジェクトを作成するコンストラクタ.
         */
        Matrix (float* m4x4);

        /**
         * @internal
         * @~English  Create a new Matrix object with specified transformation.
         * @~Japanese 指定された行列でMatrixクラスのオブジェクトを作成するコンストラクタ.
         */
        Matrix (float m00, float m01, float m02, float m03, 
                float m10, float m11, float m12, float m13, 
                float m20, float m21, float m22, float m23, 
                float m30, float m31, float m32, float m33);

        /**
         * @internal
         * @~English  Destruct this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        ~Matrix ();

        /**
         * @internal
         * @~English  Retrieves the invers matrix.
         * @exception IllegalArgumentException  If not able to calculate inverse.
         * @~Japanese このMatrixの逆行列を取得する.
         * @exception IllegalArgumentException  逆行列が計算できないとき.
         * @return    この行列の逆行列.
         */
        Matrix getInverse () const;

        /**
         * @internal
         * @~English  Retrives the 3x3 matrix from this 4x4 matrix.
         * @return    3x3 elements of this matrix.
         * @~Japanese この4x4の変換行列から3x3成分だけ取り出す.
         * @return    この行列の3x3成分.
         */
        Matrix get3x3 () const;

        /**
         * @internal
         * @~English  Set transformation 4x4 matrix.
         * @param[in]  matrix  Transformation matrix represented by 16 floats.
         * @~Japanese 指定の変換行列をこのMaterixオブジェクトに設定する.
         * @param[in]  matrix  変換行列を表す16個のfloat値.
         */
        void set(const float* matrix);

        /**
         * @internal
         * @~English  Replace transformation matrix as identity matrix.
         * @~Japanese 行列を単位行列で置き換える。
         */
        void setIdentity();

        /**
         * @internal
         * @~English  Replace transformation matrix as specified rotation.
         * @param[in]  angle  angle of rotation (degree).
         * @param[in]  ax     x element of rotation axis.
         * @param[in]  ay     y element of rotation axis.
         * @param[in]  az     z element of rotation axis.
         * @~Japanese 行列を指定の回転要素(angle,(ax,ay,az))があらわす回転行列で置き換える.
         * @param[in]  angle  回転角度(degree)
         * @param[in]  ax     回転軸のx成分
         * @param[in]  ay     回転軸のy成分
         * @param[in]  az     回転軸のz成分
         * 
         * 回転軸が正規化されている必要はない。回転軸の長さが0は例外を発生する。
         * ただし回転角度が0のときのみ、回転軸の長さが0でも受け入れる。
         */
        void setRotate (float angle, float ax, float ay, float az);

        /**
         * @internal
         * @~English   Replace transformation matrix as specified scaling.
         * @~Japanese  行列を指定のスケール要素(sx,sy,sz)があらわす拡大・縮小行列で置き換える.
         */
        void setScale (float sx, float sy, float sz);

        /**
         * @internal
         * @~English  Replace transformation matrix as specified tranlation.
         * @~Japanese 行列を指定の移動要素(tx,ty,tz)があらわす平行移動行列で置き換える.
         */
        void setTranslate (float tx, float ty, float tz);

        /**
         * @internal
         * @~English  Replace transformation matrix as inverted matrix.
         * @~Japanese 行列を逆行列で置き換える.
         */
        Matrix& invert ();

        /**
         * @internal
         * @~English  Replace transformation matrix as transposed matrix.
         * @~Japanese 行列を転置行列で置き換える.
         */
        Matrix& transpose ();

        /**
         * @internal
         * @~English  Multiplay matrix by right.
         * @~Japanese 指定の行列を右から乗算する.
         */
        Matrix& operator*= (const Matrix& rhs);

        /**
         * @internal
         * @~English  Retrives transformation matrix by index.
         * @~Japanese 4x4の変換行列に直接アクセスする.
         */
        float& operator[] (int n);

        /**
         * @internal
         * @~English  Retrives transformation matrix by index.
         * @~Japanese 4x4の変換行列に直接アクセスする.
         */
        const float& operator[] (int n) const;

        /**
         * @internal  
         * @~English  Print out information of this object.
         * @~Japanese このMarixオブジェクトの情報を表示する内部仕様の関数.
         */
        std::ostream& print (std::ostream& out) const;

    public:
        float m[16];    ///< 4x4行列を16個の配列で表現したもの
    };


    /**
     * @internal
     * @~English  Create a parallel projection matrix by specified parameters.
     * @~Japanese 指定のパラメーターから平行投影行列を作成する.
     */
    Matrix make_parallel_projection_matrix    (float height, float aspect_ratio, float near, float far);

    /**
     * @internal
     * @~English  Create a new perspective projection matrix by specified parameters.
     * @~Japanese 指定のパラメーターから透視投影行列を作成する.
     */
    Matrix make_perspective_projection_matrix (float fovy, float aspect_ratio, float near, float far);
    
} // namespace m3g {


/**
 * @internal
 * @~English  Binary operator of matrix-matrix multiply.
 * @~Japanese 行列の掛け算を行う2項演算子.
 */
m3g:: Matrix operator* (const m3g::Matrix& lhs, const m3g::Matrix& rhs);

/**
 * @internal   
 * @~English  Binary operator of matrix-vector multiply.
 * @~Japanese 行列とベクトルの掛け算を行う2項演算子.
 */
m3g:: Vector operator* (const m3g::Matrix& m, const m3g::Vector& v);

/**
 * @internal
 * @~English  Override of operator<< for print out information of Matrix object.
 * @~Japanese このMatrixオブジェクトの情報を表示する演算子<<のオーバーライド.
 */
std::ostream& operator<< (std::ostream& out, const m3g::Matrix& mat);


#endif
