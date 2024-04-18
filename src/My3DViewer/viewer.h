#ifndef VIEWER_H
#define VIEWER_H

#define GL_SILENCE_DEPRECATION

#include <QKeyEvent>
#include <QMainWindow>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
extern "C" {
#include "Backend/s21_Viewer.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class Viewer;
}
QT_END_NAMESPACE

class Viewer : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  Viewer(QWidget *parent = nullptr);
  ~Viewer();
  void s21_setObject3D(s21_Object3D *object3D);
  void s21_setPoligon(s21_Object3D *object3D);
  void s21_setBorders(s21_Object3D *object3D);
  void setVertex();
  void setEdge();
  int typeProjection = 0;
  float red = 32.0f / 255.0f;
  float green = 33.0f / 255.0f;
  float blue = 36.0f / 255.0f;
  float redEdge = 1;
  float greenEdge = 1;
  float blueEdge = 1;
  double widthEdge = 1;
  int typeEdge = 0;
  float redVertex = 1;
  float greenVertex = 1;
  float blueVertex = 1;
  double sizeVertex = 1;
  int typeVertex = 0;
  GLdouble left = 0;
  GLdouble right = 0;
  GLdouble bottom = 0;
  GLdouble top = 0;
  GLdouble near = 0;
  GLdouble far = 0;
  int fileIsOpen = 0;

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  Ui::Viewer *ui;

  double *arrayVertex;
  int *arrayIndexes;
  int edgeCounter = 0;
  int vertexCounter = 0;
};
#endif  // VIEWER_H
