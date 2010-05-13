#ifndef __KEYFRAME_HPP__
#define __KEYFRAME_HPP__

#include <iostream>
#include <vector>


namespace m3g {

/**
 * @~Japanese キーフレーム情報を定義する内部使用構造体.
 * time=-1は無効データを表す。
 */
class Keyframe
{
public:
  Keyframe ();
  Keyframe (int t, float* v);
  ~Keyframe ();

  /**
   * @~Japanese このオブジェクトの情報を表示する内部使用の関数, デバッグ用.
   */
  std::ostream& print (std::ostream& out) const;

  int    time;
  float* value;
};

  /**
   * @~Japanese キーフレームのステップ補完を行う.
   */
  void step   (float s, const Keyframe& k0, const Keyframe& k1, int component_count, float* value);

  /**
   * @~Japanese キーフレームの線形補完を行う.
   */
  void linear (float s, const Keyframe& k0, const Keyframe& k1, int component_count, float* value);

  /**
   * @~Japanese キーフレームの球面線形補完を行う.
   */

  void slerp  (float s, const Keyframe& k0, const Keyframe& k1, int component_count, float* value);

  /**
   * @~Japanese キーフレームのスプライン補完を行う.
   */
  void spline (float s, const Keyframe& k0, const Keyframe& k1, const Keyframe& k2, const Keyframe& k3, int component_count, float* value);

  /**
   * @~Japanese キーフレームのクォータニオンのスプライン補間を行う.
   */
  void squad  (float s, const Keyframe& k0, const Keyframe& k1, const Keyframe& k2, const Keyframe& k3, int component_count, float* value);

} // namespace m3g {


std::ostream& operator<< (std::ostream& out, const m3g::Keyframe& keyframe);


#endif

