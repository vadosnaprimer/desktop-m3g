


#ifndef __M3G_EXCEPT_HPP__
#define __M3G_EXCEPT_HPP__

#include <stdexcept>

namespace m3g {

/**
 * @~English  Exception of null point error.
 * @~Japanese JavaのNullPointExceptionに相当する例外クラス.
 */
class null_point_error : public std::logic_error
{
public:
  null_point_error (const std::string& what) : logic_error(what) {};
};

/**
 * @~English  Exception of divided by 0.
 * @~Japanese （整数の）0割で生じる例外クラス.
 */
class zero_division_error : public std::runtime_error
{
public:
  zero_division_error (const std::string& what) : runtime_error(what) {};
};

/**
 * @~English  Exception of OpenGL related error.
 * @~Japanese OpenGLの呼び出して生じたエラー例外クラス.
 */
class opengl_error : public std::runtime_error
{
public:
  opengl_error (const std::string& what) : runtime_error(what) {};
};

  /**
 * @~English  Exception of Input/Output related error.
   * @~Japanese IOまわりのエラー例外クラス.
   */
  class io_error : public std::runtime_error
  {
  public:
    io_error (const std::string& what) : runtime_error(what) {};
  };

/**
 * @~English  Exception of not implemented now!.
 * @~Japanese まだ実装していない機能を呼び出したときの例外クラス。ごめんなさい.
 */
class not_implemented_error : public std::runtime_error
{
public:
  not_implemented_error (const std::string& what) : runtime_error(what) {};
};

} // namespace m3g {

#endif
