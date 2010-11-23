#ifndef __MY_WIDGET_HPP__
#define __MY_WIDGET_HPP__

#include "m3g/m3g.hpp"
#include <QtOpenGL/QGLWidget>
#include <QMouseEvent>

/**
 */
class MyWidget : public QGLWidget
{
public:
  MyWidget ();
  virtual ~MyWidget ();

  virtual void initializeGL ();
  virtual void paintGL ();
  virtual void resizeGL (int width, int height);
  virtual void mouseMoveEvent (QMouseEvent* event);
  virtual void mousePressEvent (QMouseEvent* event);

private:
  m3g::World* wld;
  m3g::Camera* cam;
  float cur_x;
  float cur_y;

  std::vector<m3g::Object3D*> objs;
};



#endif
