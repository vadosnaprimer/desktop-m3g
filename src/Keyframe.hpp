#ifndef __KEYFRAME_HPP__
#define __KEYFRAME_HPP__

#include <iostream>
#include <vector>


namespace m3g {

/**
 * キーフレーム情報を定義する内部使用構造体.
 * time=-1は無効データを表す。
 */
class Keyframe
{
public:
  Keyframe ();
  Keyframe (int t, float* v);
  ~Keyframe ();

  int    time;
  float* value;
};

  /**
   * キーフレームのステップ補完を行う.
   */
  void step   (float s, const Keyframe& k0, const Keyframe& k1, int component_count, float* value);

  /**
   * キーフレームの線形補完を行う.
   */
  void linear (float s, const Keyframe& k0, const Keyframe& k1, int component_count, float* value);

  /**
   * キーフレームの球面線形補完を行う.
   */

  void slerp  (float s, const Keyframe& k0, const Keyframe& k1, int component_count, float* value);
  /**
   * キーフレームの？補完を行う.
   */
  void squad  (float s, const Keyframe& k0, const Keyframe& k1, int component_count, float* value);

  /**
   * キーフレームのスプライン補完を行う.
   */
  void spline (float s, const Keyframe& k0, const Keyframe& k1, const Keyframe& k2, const Keyframe& key_3, int component_count, float* value);

} // namespace m3g {


std::ostream& operator<< (std::ostream& out, const m3g::Keyframe& keyframe);


#endif

