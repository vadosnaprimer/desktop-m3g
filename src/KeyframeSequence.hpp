#ifndef __M3G_KEYFRAME_SEQUENCE_HPP__
#define __M3G_KEYFRAME_SEQUENCE_HPP__

#include "m3g/Object3D.hpp"
#include "m3g/Keyframe.hpp"
#include <iosfwd>

namespace m3g {

    /**
     * @~English  Encapsulates animatin data as a sequence of time-stamped, vector-valued keyframes.
     * @~Japanese アニメーションに使用するキーフレームデータ(時刻とベクトルデータ）の保存.
     */
    class KeyframeSequence : public Object3D
    {

        /**
         * @~English  Struct of valid range, for inner use.
         * @~Japanese 有効時間を定義する内部使用構造体.
         */
        struct ValidRange {
            ValidRange (int first_, int last_) : first(first_), last(last_) {};
            int first;
            int last;
        };
  

    public:

        /**
         * @~English  A parameter to setRepeatMode, specifying that this sequence is to be played back just once and not repeated.
         * @~Japanese CONSTANTリピートモードを表す定数
         */
        static const int CONSTANT = 192;
        /**
         * @~English  A parameter to setRepeatMode, specifying that this sequence is to be repeated indefinitely.
         * @~Japanese LOOPリピートモードを表す定数
         */
        static const int LOOP     = 193;
        /**
         * @~English A constructor parameter that specifies linear interpolation between keyframes. 
         * @~Japanese 線形補間を表す定数
         */
        static const int LINEAR   = 176;
        /**
         * @~English  A constructor parameter that specifies sphereical linear interpolation of quaternions.
         * @~Japanese クォータニオンの球面線形補間を表す定数
         */
        static const int SLERP    = 177;
        /**
         * @~English  A constructor parameter that specifies spline interpolation between keyframes.
         * @~Japanese スプラインの球面線形補間を表す定数
         */
        static const int SPLINE   = 178;
        /**
         * @~English  A constructor parametr that specifies spline inteterpolation of quaternions.
         * @~Japanese クォータニオンのスプライン補間を表す定数
         */
        static const int SQUAD    = 179;
        /**
         * @~English  A constructor parameter that specifies stepping from one keyframe value to the next.
         * @~Japanese ステップ補間を表す定数
         */
        static const int STEP     = 180;


        /**
         * @~English  Constructs a new2 keyframe sequence with specified interpolation method,
         *            number of components per keyframe, and number of keyframes.
         * @~Japanese 指定された補間方法、キーフレーム構成、キーフレーム数でキーフレームシーケンスを作成する.
         */
        KeyframeSequence (int num_keyframes, int num_components, int interpolation);

        /**
         * @~English  Destruct this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~KeyframeSequence ();

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         * @return 複製されたキーフレーム・オブジェクト
         */
        KeyframeSequence* duplicate () const;

        /**
         * @~English  Returns the number of components per keyframe in this ssequence.
         * @~Japanese このシーケンスの1キーフレーム当たりのコンポーネント数を取得.
         * @return コンポーネント数。2,3,4のいずれか。
         */
        int getComponentCount () const;

        /**
         * @~English  Gets the duration of this sequence.
         * @~Japanese このシーケンスの持つ期間の取得.
         * @return シーケンス期間を返す.
         */
        int getDuration () const;

        /**
         * @~English  Returns the type of interpolation for this sequence.
         * @~Japanese このシーケンスの補完方式を取得.
         * @return 補完方法.　STEP, LINEAR, SQUAD, SLERP, SPLINEのいずれか。
         */
        int getInterpolationType () const;


        /**
         * @~English  Retrieves the time stamp and value of a single keyframe.
         * @~Japanese 引数で指定したキーフレームのデータ（時刻とその時の値）の取得.
         * @param[in] value 　キーフレームの値
         * @return キーフレームの時刻
         */
        int getKeyframe (int index, float* value) const;

        /**
         * @~English  Returns the total number of keyframes in this sequence.
         * @~Japanese このシーケンスが保持しているキーフレーム数を取得.
         */
        int getKeyframeCount () const;

        /**
         * @~English  Retrieves the current repeat mode of this Keyframe Sequence.
         * @~Japanese このキーフレームシーケンスのリピートモードの取得.
         * @return リピートモード。CONSTNATまたはLOOPが返る。
         */
        int getRepeatMode () const;

        /**
         * @~English  Return the first keyframe of the current valid rangle for this sequence.
         * @~Japanese このシーケンスの有効レンジの最初のフレーム番号の取得.
         * @return 有効レンジの開始インデックス
         */
        int getValidRangeFirst () const;

        /**
         * @~English  Return the last keyframe of the current valid rangle for this sequence.
         * @~Japanese このシーケンスの有効レンジの最後のフレーム番号の取得.
         * @return 有効レンジの終了インデックス（このインデックスも有効なキーフレームに含む）
         */
        int getValidRangeLast () const;

        /**
         * @~English  Sets the duration of this sequence in sequence time units.
         * @~Japanese このキーフレーム・シーケンスの期間を（シーケンス時間単位で）設定する.
         * @param[in] duration シーケンス期間
         */
        void setDuration (int duration);

        /**
         * @~English  Sets the time position and value of the specified keyframe.
         * @~Japanese 指定されたインデックスのキーフレーム・データ（時刻と値）を設定.
         * @param[in] index インデックス.
         * @param[in] time  時刻.
         * @param[in] value その時の値.
         */
        void setKeyframe (int index, int time, float* value);

        /** 
         * @~English  Sets the repeat mode of this KeyframeSequence.
         * @~Japanese このキーフレームシーケンスのリピートモードの指定.
         * @param[in] mode  リピートモード。CONSTANTもしくはLOOP.
         */
        void setRepeatMode (int mode);

        /**
         * @~English  Selects the range of keyframes that are included in the animation.
         * @~Japanese アニメーションを含むキーフレームの有効レンジを設定.firstとlastはどちらも有効レンジに含む[first,last].
         * @param[in] first  有効レンジの開始インデックス.
         * @param[in] first  有効レンジの終了インデックス.
         */
        void setValidRange (int first, int last);

        /**
         * @~English  Print out information of this object, for debug only.
         * @~Japanese このKeyframeSequenceクラスの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

        /**
         * @~English  Returns interpolated values at specified time.
         * @~Japanese 指定されたシーケンス時間の補完済みデータを取得する関数.
         * @param[in] sequence_time  サンプリングする時刻
         * @param[in] value          サンプリング結果を書き込む領域
         */
        void sample (int sequence_time, float* value) const;


    protected:

        /**
         * @~English  
         * @~Japanese 
         */
        virtual KeyframeSequence* duplicate_xxx (Object3D* obj) const;

    private:
        KeyframeSequence (const KeyframeSequence& key_seq);
        KeyframeSequence& operator= (const KeyframeSequence& key_seq);

    private:
        int        repeat_mode;
        int        interp_type;
        int        duration;
        ValidRange valid_range;
        int        component_count;
        int        keyframe_count;
        std::vector<Keyframe> keyframes;
    };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::KeyframeSequence& keys);


#endif
