#ifndef __KEYFRAME_HPP__
#define __KEYFRAME_HPP__

#include <iostream>
#include <vector>


namespace m3g {

    /**
     * @internal
     * @~English  Represent 1 keyframe (time and data)
     * @~Japanese キーフレームを定義する内部使用のクラス.
     *            time=-1は無効データを表します。
     */
    class Keyframe
    {
    public:

        /**
         * @internal
         * @~English  Create a new empty Keyframe object
         * @~Japanese 空のKeyframeオブジェクトを作成するコンストラクタ.
         */
        Keyframe ();

        /**
         * @internal
         * @~English  Create a new Keyframe object.
         * @param[in] time   time of this keyframe.
         * @param[in] value  value of this keyframe.
         * @~Japanese 指定されたデータを持つKeyframeオブジェクトを作成するコンストラクタ.
         * @param[in] time   このキーフレームの時刻.
         * @param[in] value  このキーフレームの値.
         * 
         * 引数のvalueが指すメモリ領域は内部にコピーされません。
         * またdeleteは呼出側の責任で行います。
         */
        Keyframe (int time, float* value);

        /**
         * @internal
         * @~English  Destruct this Keyframe object.
         * @~Japanese このオブジェクトを破壊するデストラクタ.
         */
        ~Keyframe ();

        /**
         * @internal
         * @~English  Print out information of this object, for debug only.
         * @param[in] out  destination of output message.
         * @~Japanese このオブジェクトの情報を表示する内部使用の関数, デバッグ用.
         * @param[in] out  メッセージの出力先.
         */
        std::ostream& print (std::ostream& out) const;

    public:
        int    time;    ///< このキーフレームの時刻
        float* value;   ///< このキーフレームの値
    };

    /**
     * @internal
     * @~English  Perform step interpolation.  
     * @param[in]  s                Blending weight of keyframe k0 and keyframe k1.
     * @param[in]  k0               Keyframe k0.
     * @param[in]  k1               Kefyrame k1.
     * @param[in]  component_count  Component count of keyframe value.
     * @param[out] value            Output memory for writing interpolated value.
     * @~Japanese キーフレームのステップ補完を行う.
     * @param[in]  s                キーフレームk0とキーフレームk1のブレンド比率[0,1].
     * @param[in]  k0               キーフレームk0.
     * @param[in]  k1               キーフレームk1.
     * @param[in]  component_count  キーフレームの持つ値のコンポーネント数.
     * @param[out] value            補完した値を受け取るメモリ領域.
     *
     * s=0のときk0に等しく、s=1の時にk1に等しい。中間値は両者をステップ補完した値を返す。
     */
    void step   (float s, const Keyframe& k0, const Keyframe& k1, int component_count, float* value);

    /**
     * @internal
     * @~English  Perform linear interpolation.  
     * @param[in]  s                Blending weight of keyframe k0 and keyframe k1.
     * @param[in]  k0               Keyframe k0.
     * @param[in]  k1               Kefyrame k1.
     * @param[in]  component_count  Component count of keyframe value.
     * @param[out] value            Output memory for writing interpolated value.
     * @~Japanese キーフレームのステップ補完を行う.
     * @param[in]  s                キーフレームk0とキーフレームk1のブレンド比率[0,1].
     * @param[in]  k0               キーフレームk0.
     * @param[in]  k1               キーフレームk1.
     * @param[in]  component_count  キーフレームの持つ値のコンポーネント数.
     * @param[out] value            補完した値を受け取るメモリ領域.
     *
     * s=0のときk0に等しく、s=1の時にk1に等しい。中間値は両者を線形補完した値を返す。
     */
    void linear (float s, const Keyframe& k0, const Keyframe& k1, int component_count, float* value);

    /**
     * @internal
     * @~English  Perform spherical linear interpolation.  
     * @param[in]  s                Blending weight of keyframe k0 and keyframe.
     * @param[in]  k0               Keyframe k0.
     * @param[in]  k1               Kefyrame k1.
     * @param[in]  component_count  Component count of keyframe value.
     * @param[out] value            Output memory for writing interpolated value.
     * @~Japanese キーフレームのステップ補完を行う.
     * @param[in]  s                キーフレームk0とキーフレームk1のブレンド比率[0,1].
     * @param[in]  k0               キーフレームk0.
     * @param[in]  k1               キーフレームk1.
     * @param[in]  component_count  キーフレームの持つ値のコンポーネント数.
     * @param[out] value            補完した値を受け取るメモリ領域.
     *
     * s=0のときk0に等しく、s=1の時にk1に等しい。中間値は両者を球面線形補完した値を返す。
     */
    void slerp  (float s, const Keyframe& k0, const Keyframe& k1, int component_count, float* value);

    /*
     * @internal
     * @~English  Perform spline interpolation.  
     * @param[in]  s                Blending weight of keyframe k1 and keyframe k2.
     * @param[in]  k0               Keyframe k0.
     * @param[in]  k1               Kefyrame k1.
     * @param[in]  k2               Keyframe k2.
     * @param[in]  k3               Kefyrame k3.
     * @param[in]  component_count  Component count of keyframe value.
     * @param[out] value            Output memory for writing interpolated value.
     * @~Japanese キーフレームのステップ補完を行う.
     * @param[in]  s                キーフレームk1とキーフレームk2のブレンド比率[0,1].
     * @param[in]  k0               キーフレームk0.
     * @param[in]  k1               キーフレームk1.
     * @param[in]  k2               キーフレームk2.
     * @param[in]  k3               キーフレームk3.
     * @param[in]  component_count  キーフレームの持つ値のコンポーネント数.
     * @param[out] value            補完した値を受け取るメモリ領域.
     *
     * s=0のときk0に等しく、s=1の時にk1に等しい。中間値は4つのキーフレームでスプライン補完した値を返す。
     * クォータニオンのスプライン補完はこの関数ではなくsquadを使用する。
     */
    void spline (float s, const Keyframe& k0, const Keyframe& k1, const Keyframe& k2, const Keyframe& k3, int component_count, float* value);

    /*
     * @internal
     * @~English  Perform spline interpolation of quaternions.  
     * @param[in]  s                Blending weight of keyframe k1 and keyframe k2.
     * @param[in]  k0               Keyframe k0.
     * @param[in]  k1               Kefyrame k1.
     * @param[in]  k2               Keyframe k2.
     * @param[in]  k3               Kefyrame k3.
     * @param[in]  component_count  Component count of keyframe value.
     * @param[out] value            Output memory for writing interpolated value.
     * @~Japanese キーフレームのステップ補完を行う.
     * @param[in]  s                キーフレームk1とキーフレームk2のブレンド比率[0,1].
     * @param[in]  k0               キーフレームk0.
     * @param[in]  k1               キーフレームk1.
     * @param[in]  k2               キーフレームk2.
     * @param[in]  k3               キーフレームk3.
     * @param[in]  component_count  キーフレームの持つ値のコンポーネント数.
     * @param[out] value            補完した値を受け取るメモリ領域.
     *
     * s=0のときk1に等しく、s=1の時にk2に等しい。中間値は4つのキーフレームでスプライン補完した値を返す。
     * この関数はクォータニオンのスプライン補完専用です。
     */
    void squad  (float s, const Keyframe& k0, const Keyframe& k1, const Keyframe& k2, const Keyframe& k3, int component_count, float* value);


} // namespace m3g {


/**
 * @internal
 * @~English  Print out information of this object, for debug only.
 * param[in]  out       Destination of output message.
 * param[in]  keyframe  Keyframe object to be displayed.
 * @~Japanese このオブジェクトの情報を表示する内部使用の関数, デバッグ用.
 * param[in]  out       メッセージの出力先.
 * param[in]  keyframe  情報を表示するKeyframeオブジェクト.
 */
std::ostream& operator<< (std::ostream& out, const m3g::Keyframe& keyframe);


#endif

