

#ifndef __M3G_GL_HPP__
#define __M3G_GL_HPP__

// メモ：
// OpenGLのOS毎の違いを吸収するヘッダーファイル
// とにかく微妙な差が多すぎる。

 
// =====  Ubuntu(Linux系） =====
// - nVIDIA系は GL_GLEXT_PROTOTYPES を定義して
//   gl.h と glext.h をインクルードする
// - ATI系は gl.h のみをインクルードすれば十分。
//   定義しても動作に問題はない
// - 2011.02.23 gluは必要無くなったのでコメントアウト.
#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#endif
#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/glext.h>


#endif
