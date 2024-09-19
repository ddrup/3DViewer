#include "viewer.h"

using namespace s21;

Viewer::Viewer(QWidget *parent)
    : QOpenGLWidget(parent), mIndexBuffer(QOpenGLBuffer::IndexBuffer) {
  setWindowTitle("3D_Viewer");
}

Viewer::~Viewer() {}

void Viewer::setArrayVertex(const std::vector<float> &vertex) {
  arrayVertex.clear();
  for (size_t i = 0; i < vertex.size(); i += 3) {
    arrayVertex.append(QVector3D(vertex[i], vertex[i + 1], vertex[i + 2]));
  }
}

void Viewer::setArrayIndexes(const std::vector<unsigned int> &index) {
  arrayIndexes.clear();
  for (size_t i = 0; i < index.size(); ++i) {
    arrayIndexes.append(index[i]);
  }
}

void Viewer::updates() { update(); }

void Viewer::initializeGL() {
  initializeOpenGLFunctions();  // инициализация стандартных функция OpenGL_4_3
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  glEnable(GL_DEPTH_TEST);  // включает буфер глубины

  initShaders();  // загрузка вершинного и фрагментного шейдера
  initFigure();  // заполнения буверов VBA и IBO для хранения координат обьекта
}

void Viewer::resizeGL(int w, int h) {
  // Calculate aspect ratio
  qreal aspect = qreal(w) / qreal(h ? h : 1);
  mProjectionMatrixPerspect
      .setToIdentity();  // создание единичной матрицы проекции для
                         // перспективной проекции
  mProjectionMatrixOrtogon
      .setToIdentity();  // создание еденичной матрицы проекции для
                         // ортогональной проекции
  mProjectionMatrixPerspect.perspective(
      45.0f, aspect, 0.1f, 20.0f);  // задание матрици перспективной проекции
  mProjectionMatrixOrtogon.ortho(
      -(float)w / this->width(), (float)w / this->width(),
      -(float)h / this->width(), (float)h / this->width(), 0.1f, 20.0f);
  // задание матрици ортогональной проекции
}

void Viewer::paintGL() {
  glClearColor(red, green, blue, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT |
          GL_DEPTH_BUFFER_BIT);  // очистка буфера цвета и глубины

  glEnable(GL_PROGRAM_POINT_SIZE);  // включаем возможность изменять размер
                                    // вершин при отрисовке объекта
  glPolygonMode(GL_FRONT_AND_BACK,
                GL_LINE);  // отвечает за отрисовку только граней
  glLineWidth(widthEdge);  // отвечает за толщину граней

  mModelViewMatrix.setToIdentity();  // создание единичной матрицы поворота
                                     // (модельно-видовая матрица)
  mModelViewMatrix.translate(xTranslate / 100.0, yTranslate / 100.0,
                             (zTranslate - 105.0) / 100);
  mModelViewMatrix.rotate(mRotation);
  mModelViewMatrix.rotate(angleRotate, xRotate, yRotate, zRotate);
  mModelViewMatrix.scale(allScale, allScale, allScale);
  // эта функция поворота, в нее мы подаем объект Кваторион, который хранит
  // параметры поворота

  mProgram.bind();  // получаем доступ к нашей шейдерной программе, созданной в
                    // initShaders()

  if (typeProjection == 1) {
    mProgram.setUniformValue("mvp_matrix",
                             mProjectionMatrixPerspect *
                                 mModelViewMatrix);  // перспективная проекция
  } else {
    mProgram.setUniformValue(
        "mvp_matrix",
        mProjectionMatrixOrtogon * mModelViewMatrix);  // ортогональная проекция
  }

  mProgram.setUniformValue("u_dashSize",
                           5.0f);  // параметры для шейдера, размер пунктира
  mProgram.setUniformValue(
      "u_gapSize",
      typeEdge);  // параметры для шейдера, размер пробела между пунктирами
  mProgram.setUniformValue("u_pointSize",
                           sizeVertex);  // изменяет размер вершины
  mProgram.setUniformValue(
      "u_color", QVector3D(redEdge, greenEdge, blueEdge));  // цвет ребер
  mProgram.setUniformValue("u_shape", 1);  // вершины не отрисовываются

  mArrayBuffer.bind();  // получаем доступ к VBO - вершинному буферу
  mIndexBuffer.bind();  // получаем доступ к IBO - индексному буферу
  quintptr offset = 0;  // задаем позицию, с которой будет обрабатываться каждая
                        // вершина. В нашем случае в вершине содержится
  // QVector3D position затем QVector3D color, первое место в памяти начинается
  // с 0, значит для выбора QVector3D position нам надо указать offset = 0

  int vertexLocation = mProgram.attributeLocation(
      "a_position");  // берем индекс атрибута в шейдере - это layout(location =
                      // 0)
  if (vertexLocation == -1) {
    qWarning() << "Could not find attribute a_position";
  } else {
    mProgram.enableAttributeArray(
        vertexLocation);  // включаем массив атрибутов по этому индексу для
                          // шейдерной программы
    mProgram.setAttributeBuffer(
        vertexLocation, GL_FLOAT, offset, 3,
        sizeof(QVector3D));  // соединяем наш активный буфер mArrayBuffer.bind()
                             // с шейдерной программой через полученный индекс
  }
  glDrawElements(GL_TRIANGLES, mIndexBuffer.size(), GL_UNSIGNED_INT,
                 0);  // рисуем треугольники, используя VBO и IBO

  mProgram.setUniformValue(
      "u_color", QVector3D(redVertex, greenVertex, blueVertex));  // цвет вершин
  if (typeVertex == 1) {
    glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, arrayVertex.size());
    glDisable(GL_POINT_SMOOTH);
  } else if (typeVertex == 2) {
    mProgram.setUniformValue("u_shape", 0);  // отрисовка вершин
    mProgram.setUniformValue(
        "u_typeVertex",
        1);  // передаем тип вершины (1 - круглая, 0 - квадратная)
    glDrawElements(GL_POINTS, mIndexBuffer.size(), GL_UNSIGNED_INT,
                   0);  // условие на отрисовку вершин
  }
  mArrayBuffer.release();
  mIndexBuffer.release();
  mProgram.release();
}

void Viewer::initShaders() {
  if (!mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                        ":/vshader.vsh")) {
    qWarning() << "Vertex shader error:" << mProgram.log();
    close();
  }
  if (!mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                        ":/fshader.fsh")) {
    qWarning() << "Fragment shader error:" << mProgram.log();
    close();
  }
  if (!mProgram.link()) {
    qWarning() << "Shader link error:" << mProgram.log();
    close();
  }
}

void Viewer::initFigure() {
  QVector<QVector3D> vertexes = arrayVertex;
  QVector<GLuint> indexes = arrayIndexes;

  mArrayBuffer.create();
  mArrayBuffer.bind();  // делаем буфер активным
  mArrayBuffer.allocate(
      vertexes.constData(),
      vertexes.size() * sizeof(QVector3D));  // заполняем буфер VBO
  mArrayBuffer.setUsagePattern(
      QOpenGLBuffer::DynamicDraw);  //Буфер будет изменяться и использоваться
                                    //много раз для отрисовки.
  mArrayBuffer.release();  // отсоиденяем буфер, делаем его не  активным

  mIndexBuffer.create();
  mIndexBuffer.bind();  // делаем буфер активным
  mIndexBuffer.allocate(
      indexes.constData(),
      indexes.size() * sizeof(GLuint));  // // заполняем буфер IBO
  mIndexBuffer.setUsagePattern(
      QOpenGLBuffer::DynamicDraw);  //Буфер будет изменяться и использоваться
                                    //много раз для отрисовки.
  mIndexBuffer.release();  // отсоиденяем буфер, делаем его не  активным

  update();
}

void Viewer::mousePressEvent(
    QMouseEvent *event)  // событие на нажатие клавиши на мыши
{
  if (event->buttons() & Qt::LeftButton) {
    mMousePosition =
        QVector2D(event->position());  // запоминаем позицию нажатия клавиши
  }
  event->accept();  // явно указываем, что event сработал
}

void Viewer::mouseMoveEvent(
    QMouseEvent *event)  // событие на движения указателя мыши
{
  if (!(event->buttons() & Qt::LeftButton))
    return;  // если нажата другая клавиша, то выходим

  QVector2D diff =
      QVector2D(event->position()) -
      mMousePosition;  // вычисляем разницу между местом нажатия клавиши и
                       // местом на которое мы перенесли указатель мыши
  mMousePosition =
      QVector2D(event->position());  // запоминаем новое положение мыши

  float angle = diff.length() /
                2.0;  // здесь вычисляем угол поворота. специально поделил на 2
                      // для того чтобы не так резко поворачивался обьект
  QVector3D axis =
      QVector3D(diff.y(), diff.x(), 0.0)
          .normalized();  // здесь задаем ось поворота оьекта, эта ось
                          // перпендикулярна вектору перемещения курсора мыши
  // в перпендикулярных векторах координаты (x) и (y) меняются местами и одна из
  // координат меняет знак, хнак нам менять не надо так как ось координат (y)
  // виджета направлена у нас вниз, а ось (y) в OpenGL направлена вверх
  mRotation = QQuaternion::fromAxisAndAngle(axis, angle) *
              mRotation;  //здесь задаем параметры нащего перемещения создавая
                          //оьект QQuaternion
  update();               // перерисовываем все
}
