#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

/*
  Forrás:
    (1). http://sorj.de/?p=192
    (2). http://blog.lugru.com/2009/03/qtdesigner-and-qglwidget/
  Textura létrehozása: http://digitalfanatics.org/projects/qt_tutorial/chapter14.html
*/


#include <QtOpenGL>
#include <QGLWidget>

class MyGLWidget : public QGLWidget{

  Q_OBJECT // must include this if you use Qt signals/slots


public:
    MyGLWidget();
    //MyGLWidget(QWidget *parent = NULL)
      //  : QGLWidget(parent) {}


protected:
    // Set up the rendering context, define display lists etc.:
   void initializeGL();
   // draw the scene:
   void paintGL();
   // setup viewport, projection etc.:
   void resizeGL (int width, int height);

   //void mousePressEvent(QMouseEvent *event);
   //void mouseMoveEvent(QMouseEvent *event);
   void timerEvent(QTimerEvent *event);

public:
   void changeOrientation(float roll, float pitch, float yaw);

private:
   float roll_;
   float pitch_;
   float yaw_;
};



#endif // MYGLWIDGET_H
