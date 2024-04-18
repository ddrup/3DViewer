#include "viewer.h"
//#include "./ui_viewer.h"

Viewer::Viewer(QWidget *parent) : QOpenGLWidget(parent) {
  setWindowTitle("3D_Viewer");
}

Viewer::~Viewer() {
  // delete ui;
}

void Viewer::s21_setObject3D(s21_Object3D *object3D) {
  if (!object3D->v->coord->matrix || !object3D->p->polygons) return;
  vertexCounter = object3D->v->amountVert;
  this->arrayVertex = new double[object3D->v->amountVert * 3];
  for (int i = 0, s = 0; i < object3D->v->amountVert; i++) {
    for (int j = 0; j < 3; j++) {
      this->arrayVertex[s++] = object3D->v->coord->matrix[i][j];
    }
  }
}

void Viewer::s21_setPoligon(s21_Object3D *object3D) {
  edgeCounter = 0;

  for (int i = 0; i < object3D->p->amountPolyg; i++) {
    edgeCounter += object3D->p->polygons[i]->size * 2;
  }
  this->arrayIndexes = new int[edgeCounter];
  int s = 0;
  for (int i = 0; i < object3D->p->amountPolyg; i++) {
    int first_index = s21_vectorGet(object3D->p->polygons[i], 0);
    this->arrayIndexes[s++] = first_index - 1;
    for (int j = 1; j < object3D->p->polygons[i]->size; j++) {
      this->arrayIndexes[s++] = s21_vectorGet(object3D->p->polygons[i], j) - 1;
      this->arrayIndexes[s++] = s21_vectorGet(object3D->p->polygons[i], j) - 1;
    }
    this->arrayIndexes[s++] = first_index - 1;
  }
}

void Viewer::s21_setBorders(s21_Object3D *object3D) {
  left = object3D->v->minMaxX[0];
  right = object3D->v->minMaxX[1];
  bottom = object3D->v->minMaxY[0];
  top = object3D->v->minMaxY[1];
  near = object3D->v->minMaxZ[1];
  far = object3D->v->minMaxZ[0];
}

void Viewer::setVertex() {
  if (typeVertex == 1) glEnable(GL_POINT_SMOOTH);
  glColor3d(redVertex, greenVertex, blueVertex);
  glPointSize(sizeVertex);
  glDrawArrays(GL_POINTS, 0, vertexCounter);
  if (typeVertex == 1) glDisable(GL_POINT_SMOOTH);
}

void Viewer::setEdge() {
  glColor3d(redEdge, greenEdge, blueEdge);
  glLineWidth(widthEdge);
  if (typeEdge == 0) {
    glLineStipple(1, 0x3333);
  } else {
    glLineStipple(1, 0x00FF);
  }
  glDrawElements(GL_LINES, edgeCounter, GL_UNSIGNED_INT, arrayIndexes);
}

void Viewer::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_STIPPLE);
}

void Viewer::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void Viewer::paintGL() {
  glClearColor(red, green, blue, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glVertexPointer(3, GL_DOUBLE, 0, arrayVertex);
  //проекции
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (typeProjection == 0) {
    float fov = 60.0 * M_PI / 180;  // 60 угол в градусах
    float heapHeight = fmax(bottom, top) / (2 * tan(fov / 2));
    glFrustum(-fmax(left, right), fmax(left, right), -fmax(bottom, top),
              fmax(bottom, top), heapHeight, far + 10);
    glTranslated(0, 0, -heapHeight * 10);
  } else {
    glOrtho(left * 10, right * 10, bottom * 10, top * 10, near, far * 10);
  }
  if (fileIsOpen == 1) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(redEdge, greenEdge, blueEdge);
    setEdge();
    if (typeVertex != 0) setVertex();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}
