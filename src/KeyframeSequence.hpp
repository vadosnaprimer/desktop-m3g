#ifndef __KEYFRAME_SEQUENCE_HPP__
#define __KEYFRAME_SEQUENCE_HPP__

#include "Object3D.hpp"
#include "Keyframe.hpp"
#include <iosfwd>

namespace m3g {

/**
   * @~English  Encapsulates animatin data as a sequence of time-stamped, vector-valued keyframes.
 * @~Japanese アニメーションデータをキーフレームとして一連のタイムスタンプ付きベクトルデータで表す。
 */
class KeyframeSequence : public Object3D
{
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
   * @~Japanese （？）補間を表す定数
   */
    static const int SQUAD    = 179;
  /**
   * @~English  A constructor parameter that specifies stepping from one keyframe value to the next.
   * @~Japanese ステップ補間を表す定数
   */
    static const int STEP     = 180;

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
   * @~English  Constructs a new2 keyframe sequence with specified interpolation method,
   *            number of components per keyframe, and number of keyframes.
     * @~Japanese 指定された補間方法、キーフレーム構成、キーフレーム数でキーフレームシーケンスを作成する.
     */
    KeyframeSequence (int numKeyframes, int numComponents, int interpolation);

    /**
   * @~English  Destruct this object.
     * @~Japanese このオブジェクトを削除するデストラクタ.
     */
    virtual ~KeyframeSequence ();

    /**
   * @~English  Returns the number of components per keyframe in this ssequence.
     * @~Japanese このシーケンスの1キーフレーム当たりのコンポーネント数を取得.
     */
    int getComponentCount () const;

    /**
   * @~English  Gets the duration of this sequence.
     * @~Japanese このシーケンスの期間を取得.
     */
    int getDuration () const;

    /**
   * @~English  Returns the type of interpolation for this sequence.
     * @~Japanese このシーケンスの補完方式を取得.
     */
    int getInterpolationType () const;


    /**
   * @~English  Retrieves the time stamp and value of a single keyframe.
     * @~Japanese １キーフレームのタイムスタンプと値を取得.
     */
     int getKeyframe (int index, float* value) const;

     /**
   * @~English  Returns the total number of keyframes in this sequence.
     * @~Japanese このシーケンスのキーフレーム数を取得.
     */
    int getKeyframeCount () const;

    /**
   * @~English  Retrieves the current repeat mode of this Keyframe Sequence.
     * @~Japanese このキーフレームシーケンスのリピートモードの取得.
     */
    int getRepeatMode () const;

    /**
   * @~English  Return the first keyframe of the current valid rangle for this sequence.
     * @~Japanese このシーケンスの有効レンジの最初のフレーム番号の取得.
     */
    int getValidRangeFirst () const;

    /**
   * @~English  Return the last keyframe of the current valid rangle for this sequence.
     * @~Japanese このシーケンスの有効レンジの最後のフレーム番号の取得.
     */
    int getValidRangeLast () const;

    /**
   * @~English  Sets the duration of this sequence in sequence time units.
     * @~Japanese このシーケンスの期間を取得。単位はシーケンス単位.
     */
    void setDuration (int duration);

    /**
   * @~English
     * @~Japanese 指定されたindex番目のキーフレームのローカル時間と値を設定.
     */
    void setKeyframe (int index, int time, float* value);

    /** 
   * @~English  Sets the repeat mode of this KeyframeSequence.
     * @~Japanese このキーフレームシーケンスのリピートモードの指定.
     */
    void setRepeatMode (int mode);

    /**
   * @~English  Selects the range of keyframes that are included in the animation.
     * @~Japanese アニメーションを含むキーフレームのレンジを設定.
     */
    void setValidRange (int first, int last);

    /**
   * @~English  Print out information of this object, for debug only.
     * @~Japanese このKeyframeSequenceクラスの情報を表示する。デバッグ用.
     */
  virtual std::ostream& print (std::ostream& out) const;

PRIVATE:
  /**
   * @~English  Returns interpolated values at specified time, for inner use.
   * @~Japanese 指定された時刻のフレームを取得する内部使用の関数.
   */
  void getFrame (int local_time, float* value) const;

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
