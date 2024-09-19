#ifndef VIEWER_H
#define VIEWER_H

#include <QDebug>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QVector>

#include "observer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Viewer;
}
QT_END_NAMESPACE
namespace s21 {
class Viewer : public QOpenGLWidget,
               protected QOpenGLFunctions,
               public IObserver {
  Q_OBJECT

 public:
  Viewer(QWidget *parent = nullptr);
  ~Viewer();
  void initFigure();
  void setArrayVertex(const std::vector<float> &vertex);
  void setArrayIndexes(const std::vector<unsigned int> &index);
  void updates() override;

  // Type Projection
  int typeProjection = 0;

  // Background-color
  float red = 32.0f / 255.0f;
  float green = 33.0f / 255.0f;
  float blue = 36.0f / 255.0f;

  // Edge settings
  float redEdge = 1.0f;
  float greenEdge = 0.0f;
  float blueEdge = 0.0f;
  double widthEdge = 3.0f;
  float typeEdge = 0.0f;

  // Vertex settings
  float redVertex = 1;
  float greenVertex = 1;
  float blueVertex = 1;
  float sizeVertex = 1;
  int typeVertex = 0;

  GLdouble left = 0;
  GLdouble right = 0;
  GLdouble bottom = 0;
  GLdouble top = 0;
  GLdouble near = 0;
  GLdouble far = 0;
  int fileIsOpen = 0;

  QMatrix4x4 mModelViewMatrixAffineTransformation;

  float angleRotate = 0.0f;
  float xRotate = 0.0f;
  float yRotate = 0.0f;
  float zRotate = 0.0f;

  float xTranslate = 0.0f;
  float yTranslate = 0.0f;
  float zTranslate = 0.0f;

  float allScale = 0.5f;

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void initShaders();
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

 private:
  Ui::Viewer *ui;

  QVector<QVector3D> arrayVertex;
  QVector<GLuint> arrayIndexes;
  int edgeCounter = 0;
  int vertexCounter = 0;

  QOpenGLShaderProgram mProgram;
  QOpenGLBuffer mArrayBuffer;
  QOpenGLBuffer mIndexBuffer;
  QMatrix4x4 mModelViewMatrix;
  QMatrix4x4 mProjectionMatrixPerspect;
  QMatrix4x4 mProjectionMatrixOrtogon;
  QVector2D mMousePosition;
  QQuaternion mRotation;
};

}  // namespace s21

#endif  // VIEWER_H
