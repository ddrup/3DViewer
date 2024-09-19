#include "viewerwindow.h"

#include "ui_viewerwindow.h"

using namespace s21;

viewerwindow::viewerwindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::viewerwindow) {
  ui->setupUi(this);
  setFixedSize(1500, 1000);

  setWindowTitle("3D Viewer");
  elementsPrograms();
  setGeometry(QRect(200, 200, 1500, 1000));
  setCentralWidget(stackedWidget);

  settings = new QSettings(
      this);  // класс QSettings позволяет сохранять и загружать настройки
  loadSettings();
}

viewerwindow::~viewerwindow() {
  ScaledMinus->detach(glWidget);
  ScaledPlus->detach(glWidget);
  OrthoViewButton->detach(glWidget);
  FrustViewButton->detach(glWidget);
  colorButton->detach(glWidget);
  colorEdgeButton->detach(glWidget);
  colorVertexButton->detach(glWidget);
  saveSettings();

  delete settings;
  delete topToolBar;
  delete glWidget;
  delete stackedWidget;
  delete dockWidget;
  delete pushButton;
  delete pushButtonRotate;
  delete plainTextEdit;
  delete openFile;
  delete saveFile;
  delete openGlWidget;
  delete openTextEdit;
  // delete fileMenu;
  delete xRotate;
  delete yRotate;
  delete zRotate;
  delete xTranslated;
  delete yTranslated;
  delete zTranslated;
  delete ScaledMinus;
  delete ScaledPlus;
  delete Screenshot;
  delete Gif;
  delete thisFile;
  delete thisVertices;
  delete thisEdges;
  delete OrthoViewButton;
  delete FrustViewButton;
  delete colorButton;
  delete colorEdgeButton;
  delete colorVertexButton;
  delete thickness;
  delete typeEdgeComboBox;
  delete setChanges;
  delete sizeVertex;
  delete MethodDisplayVertexComboBox;

  delete ui;
}

void viewerwindow::elementsPrograms() {
  openFile = new QAction(tr("Open File"), this);
  openFile->setShortcut(QKeySequence::New);
  openFile->setStatusTip(tr("Открыть файл"));
  connect(openFile, SIGNAL(triggered(bool)), this, SLOT(s21_openFileDialog()));

  stackedWidget = new QStackedWidget(this);  // create OpenGL widgets
  glWidget = new Viewer(this);
  stackedWidget->addWidget(glWidget);
  stackedWidget->setCurrentWidget(glWidget);

  topToolBar = new QToolBar(tr("&toBar"));
  addToolBar(Qt::TopToolBarArea, topToolBar);
  topToolBar->setAllowedAreas(Qt::TopToolBarArea);
  topToolBar->addAction(openFile);
  topToolBar->addSeparator();
  topToolBar->setStyleSheet("background-color: #303134;");

  QFrame *frame = new QFrame(this);  // создание правой панели
  frame->setGeometry(1200, 33, 300, 1000);
  frame->setStyleSheet("background-color: #303134;");
  QVBoxLayout *layout = new QVBoxLayout(this);

  xRotate = new QSlider(Qt::Horizontal, this);  // Slider X rotate
  xRotate->setRange(-360, 360);
  xRotate->setValue(0);
  xRotate->setGeometry(1240, 80, 200, 30);
  layout->addWidget(xRotate);

  yRotate = new QSlider(Qt::Horizontal, this);  // Slider Y rotate
  yRotate->setRange(-360, 360);
  yRotate->setValue(0);
  yRotate->setGeometry(1240, 110, 200, 30);
  layout->addWidget(yRotate);

  zRotate = new QSlider(Qt::Horizontal, this);  // Slider Z rotate
  zRotate->setRange(-360, 360);
  zRotate->setValue(0);
  zRotate->setGeometry(1240, 140, 200, 30);
  layout->addWidget(zRotate);

  xTranslated = new QSlider(Qt::Horizontal, this);  // Slider X transl
  xTranslated->setRange(-300, 300);
  xTranslated->setValue(0);
  xTranslated->setGeometry(1240, 220, 200, 30);
  layout->addWidget(xTranslated);

  yTranslated = new QSlider(Qt::Horizontal, this);  // Slider Y transl
  yTranslated->setRange(-300, 300);
  yTranslated->setValue(0);
  yTranslated->setGeometry(1240, 250, 200, 30);
  layout->addWidget(yTranslated);

  zTranslated = new QSlider(Qt::Horizontal, this);  // Slider Z transl
  zTranslated->setRange(-300, 300);
  zTranslated->setValue(0);
  zTranslated->setGeometry(1240, 280, 200, 30);
  layout->addWidget(zTranslated);

  ScaledPlus = new QCustomPushButton("+", this);  // pushbuttn Scaled
  ScaledPlus->setGeometry(1120, 400, 50, 50);
  ScaledPlus->setStyleSheet(
      "QPushButton {"
      "    border-radius: 25px;"
      "    color: white;"
      "    background-color: #303134;"
      "}"
      "QPushButton:hover {"
      "    background-color: #252427;"
      "}");
  ScaledPlus->attach(glWidget);

  ScaledMinus = new QCustomPushButton("-", this);
  ScaledMinus->setGeometry(1120, 560, 50, 50);
  ScaledMinus->setStyleSheet(
      "QPushButton {"
      "    border-radius: 25px;"
      "    color: white;"
      "    background-color: #303134;"
      "}"
      "QPushButton:hover {"
      "    background-color: #252427;"
      "}");
  ScaledMinus->attach(glWidget);

  Screenshot = new QPushButton("", this);  // pushbutton screenshot
  Screenshot->setGeometry(1160, 900, 30, 30);
  Screenshot->setStyleSheet(
      "QPushButton {"
      "    border-radius: 15px;"
      "    color: white;"
      "    background-color: #303134;"
      "}"
      "QPushButton:hover {"
      "}");
  QPixmap pixmap1(":/Screenshot.png");
  Screenshot->setIcon(QIcon(pixmap1));
  Screenshot->setIconSize(QSize(25, 25));

  connect(Screenshot, SIGNAL(clicked()), this, SLOT(s21_Screenshot()));

  Gif = new QPushButton("", this);  // pushbutton gif
  Gif->setGeometry(1160, 960, 30, 30);
  Gif->setStyleSheet(
      "QPushButton {"
      "    border-radius: 15px;"
      "    color: white;"
      "    background-color: #303134;"
      "}"
      "QPushButton:hover {"
      "}");
  QPixmap pixmap2(":/Gif.png");
  Gif->setIcon(QIcon(pixmap2));
  Gif->setIconSize(QSize(20, 20));

  connect(Gif, SIGNAL(clicked()), this, SLOT(s21_Gif()));

  QLabel *rotateLabel = new QLabel("Rotate", this);  // Label Rotate
  rotateLabel->setGeometry(1210, 30, 200, 30);
  QFont labelFont = rotateLabel->font();
  labelFont.setPointSize(20);
  rotateLabel->setFont(labelFont);
  rotateLabel->setStyleSheet("QLabel { color: grey;}");
  layout->addWidget(rotateLabel);

  QLabel *rotateLabelX = new QLabel("X:", this);  // Label X for rotate
  rotateLabelX->setGeometry(1215, 77, 25, 30);
  labelFont = rotateLabelX->font();
  labelFont.setPointSize(16);
  rotateLabelX->setFont(labelFont);
  rotateLabelX->setStyleSheet("QLabel { color: grey;}");
  layout->addWidget(rotateLabelX);

  QLabel *rotateLabelY = new QLabel("Y:", this);  // Label Y for rotate
  rotateLabelY->setGeometry(1215, 107, 25, 30);
  labelFont = rotateLabelY->font();
  labelFont.setPointSize(16);
  rotateLabelY->setFont(labelFont);
  rotateLabelY->setStyleSheet("QLabel { color: grey;}");
  layout->addWidget(rotateLabelY);

  QLabel *rotateLabelZ = new QLabel("Z:", this);  // Label Z for rotate
  rotateLabelZ->setGeometry(1215, 137, 25, 30);
  labelFont = rotateLabelZ->font();
  labelFont.setPointSize(16);
  rotateLabelZ->setFont(labelFont);
  rotateLabelZ->setStyleSheet("QLabel { color: grey;}");
  layout->addWidget(rotateLabelZ);

  QLabel *translatedLabel = new QLabel("Translate", this);  // Label Translate
  translatedLabel->setGeometry(1210, 170, 200, 30);
  labelFont = translatedLabel->font();
  labelFont.setPointSize(20);
  translatedLabel->setFont(labelFont);
  translatedLabel->setStyleSheet("QLabel { color: grey;}");
  layout->addWidget(translatedLabel);

  QLabel *translatedLabelX = new QLabel("X:", this);  // Label X for translate
  translatedLabelX->setGeometry(1215, 217, 25, 30);
  labelFont = translatedLabelX->font();
  labelFont.setPointSize(16);
  translatedLabelX->setFont(labelFont);
  translatedLabelX->setStyleSheet("QLabel { color: grey;}");
  layout->addWidget(translatedLabelX);

  QLabel *translatedLabelY = new QLabel("Y:", this);  // Label Y for translate
  translatedLabelY->setGeometry(1215, 247, 25, 30);
  labelFont = translatedLabelY->font();
  labelFont.setPointSize(16);
  translatedLabelY->setFont(labelFont);
  translatedLabelY->setStyleSheet("QLabel { color: grey;}");
  layout->addWidget(translatedLabelY);

  QLabel *translatedLabelZ = new QLabel("Z:", this);  // Label Z for translate
  translatedLabelZ->setGeometry(1215, 277, 25, 30);
  labelFont = translatedLabelZ->font();
  labelFont.setPointSize(16);
  translatedLabelZ->setFont(labelFont);
  translatedLabelZ->setStyleSheet("QLabel { color: grey;}");
  layout->addWidget(translatedLabelZ);

  QFrame *line1 = new QFrame(this);  // line
  line1->setGeometry(1200, 65, 300, 1);
  line1->setStyleSheet("background-color: grey;");

  QFrame *line2 = new QFrame(this);  // line2
  line2->setGeometry(1200, 205, 300, 1);
  line2->setStyleSheet("background-color: grey;");

  QLabel *name_file = new QLabel("Name File: ", this);  // Label Name File
  labelFont = name_file->font();
  labelFont.setPointSize(16);
  name_file->setFont(labelFont);
  name_file->setStyleSheet("QLabel { color: grey;}");
  name_file->adjustSize();
  name_file->move(1215, 900);
  layout->addWidget(name_file);

  thisFile = new QLabel("", this);  // Label thisFile
  thisFile->setGeometry(1215 + name_file->width(), 900, 200, 30);
  labelFont = thisFile->font();
  labelFont.setPointSize(16);
  thisFile->setFont(labelFont);
  thisFile->setStyleSheet("QLabel { color: grey;}");
  layout->addWidget(thisFile);

  QLabel *count_vertices =
      new QLabel("Vertices: ", this);  // Label Count Vertices
  labelFont = count_vertices->font();
  labelFont.setPointSize(16);
  count_vertices->setFont(labelFont);
  count_vertices->setStyleSheet("QLabel { color: grey;}");
  count_vertices->adjustSize();
  count_vertices->move(1215, 930);
  layout->addWidget(count_vertices);

  thisVertices = new QLabel("", this);  // Label thisVertices
  thisVertices->setGeometry(1215 + count_vertices->width(), 930, 200, 30);
  labelFont = thisVertices->font();
  labelFont.setPointSize(16);
  thisVertices->setFont(labelFont);
  thisVertices->setStyleSheet("QLabel { color: grey;}");
  layout->addWidget(thisVertices);

  QLabel *count_edges = new QLabel("Edges: ", this);  // Label Count Edges
  labelFont = count_edges->font();
  labelFont.setPointSize(16);
  count_edges->setFont(labelFont);
  count_edges->setStyleSheet("QLabel { color: grey;}");
  count_edges->adjustSize();
  count_edges->move(1215, 960);
  layout->addWidget(count_edges);

  thisEdges = new QLabel("", this);  // Label Count Edges
  thisEdges->setGeometry(1215 + count_edges->width(), 960, 200, 30);
  labelFont = thisEdges->font();
  labelFont.setPointSize(16);
  thisEdges->setFont(labelFont);
  thisEdges->setStyleSheet("QLabel { color: grey;}");
  layout->addWidget(thisEdges);

  QLabel *typeProjectionLabel =
      new QLabel("Type Projection", this);  // Label typeProjection
  typeProjectionLabel->setGeometry(1210, 310, 200, 30);
  labelFont = typeProjectionLabel->font();
  labelFont.setPointSize(20);
  typeProjectionLabel->setFont(labelFont);
  typeProjectionLabel->setStyleSheet("QLabel { color: grey;}");
  layout->addWidget(typeProjectionLabel);

  OrthoViewButton = new QCustomPushButton("Parallel", this);
  OrthoViewButton->setGeometry(1203, 350, 140, 50);
  OrthoViewButton->setStyleSheet(
      "QPushButton {"
      "    border-radius: 2px;"
      "    color: #a0a39e;"
      "    background-color: #252427;"
      "}");
  OrthoViewButton->attach(glWidget);

  FrustViewButton = new QCustomPushButton("Central", this);
  FrustViewButton->setGeometry(1347, 350, 150, 50);
  FrustViewButton->setStyleSheet(
      "QPushButton {"
      "    border-radius: 2px;"
      "    color: #a0a39e;"
      "    background-color: #616360;"
      "}");
  FrustViewButton->attach(glWidget);

  QLabel *backGroundColor =
      new QLabel("Background-color: ", this);  // Label Background-color
  labelFont = backGroundColor->font();
  labelFont.setPointSize(20);
  backGroundColor->setFont(labelFont);
  backGroundColor->setStyleSheet("QLabel { color: grey;}");
  backGroundColor->adjustSize();
  backGroundColor->move(1210, 420);
  layout->addWidget(backGroundColor);

  colorButton = new QCustomPushButton("", this);
  colorButton->setGeometry(1215 + backGroundColor->width(), 415, 35, 40);
  colorButton->setStyleSheet("QPushButton { color: grey;}");
  colorButton->attach(glWidget);
  QObject::connect(colorButton, &QPushButton::clicked, [&]() {
    color = QColorDialog::getColor();
    if (color.isValid()) {
      glWidget->red = color.red() / 255.0f;
      glWidget->green = color.green() / 255.0f;
      glWidget->blue = color.blue() / 255.0f;
      colorButton->setStyleSheet(
          "QPushButton { background-color: " + color.name() + ";}");
      colorButton->notify();
    }
  });
  layout->addWidget(colorButton);

  QFrame *line3 = new QFrame(this);  // line3
  line3->setGeometry(1200, 470, 300, 1);
  line3->setStyleSheet("background-color: grey;");

  QFrame *line4 = new QFrame(this);  // line4
  line4->setGeometry(1200, 890, 300, 1);
  line4->setStyleSheet("background-color: grey;");

  QFrame *frameEdge = new QFrame(this);  // create panel for Edge
  frameEdge->setGeometry(1210, 475, 280, 200);
  frameEdge->setStyleSheet(
      "background-color: #25272b;"
      "    border-radius: 20px;");
  QVBoxLayout *layout1 = new QVBoxLayout(this);

  QLabel *labelEdge = new QLabel("Edges", this);  // Label Edges
  labelEdge->setGeometry(1330, 480, 160, 30);
  labelFont = labelEdge->font();
  labelFont.setPointSize(20);
  labelEdge->setFont(labelFont);
  labelEdge->setStyleSheet("QLabel { color: grey;}");
  layout1->addWidget(labelEdge);

  QLabel *typeEdge = new QLabel("Type: ", this);  // Label Type Edge
  labelFont = typeEdge->font();
  labelFont.setPointSize(16);
  typeEdge->setFont(labelFont);
  typeEdge->setStyleSheet("QLabel { color: grey;}");
  typeEdge->adjustSize();
  typeEdge->move(1220, 520);
  layout1->addWidget(typeEdge);

  typeEdgeComboBox = new QComboBox(this);
  typeEdgeComboBox->setGeometry(1220 + typeEdge->width(), 520, 100, 30);
  typeEdgeComboBox->setStyleSheet(
      "QComboBox {"
      "border: 1px solid gray;"
      "color: white;"
      "border-radius: 3px;"
      "padding: 1px 18px 1px 3px;"
      "min-width: 6em;"
      "selection-background-color: #25272b;"
      "background: #25272b;}");
  typeEdgeComboBox->addItem("Solid");
  typeEdgeComboBox->addItem("Dotted");
  connect(typeEdgeComboBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(s21_typeEdge()));

  QLabel *colorEdge = new QLabel("Color: ", this);  // Label Color Edge
  labelFont = colorEdge->font();
  labelFont.setPointSize(16);
  colorEdge->setFont(labelFont);
  colorEdge->setStyleSheet("QLabel { color: grey;}");
  colorEdge->adjustSize();
  colorEdge->move(1220, 570);
  layout1->addWidget(colorEdge);

  colorEdgeButton = new QCustomPushButton("", this);
  colorEdgeButton->setGeometry(1220 + colorEdge->width(), 565, 35, 40);
  colorEdgeButton->setStyleSheet("QPushButton { color: grey;}");
  colorEdgeButton->attach(glWidget);
  QObject::connect(colorEdgeButton, &QPushButton::clicked, [&]() {
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
      glWidget->redEdge = color.red() / 255.0f;
      glWidget->greenEdge = color.green() / 255.0f;
      glWidget->blueEdge = color.blue() / 255.0f;
      colorEdgeButton->setStyleSheet(
          "QPushButton { background-color: " + color.name() + ";}");
    }
    colorEdgeButton->notify();
  });
  layout1->addWidget(colorEdgeButton);

  QLabel *thicknessEdge =
      new QLabel("Thickness: ", this);  // Label Thickness Edge
  labelFont = thicknessEdge->font();
  labelFont.setPointSize(16);
  thicknessEdge->setFont(labelFont);
  thicknessEdge->setStyleSheet("QLabel { color: grey;}");
  thicknessEdge->adjustSize();
  thicknessEdge->move(1220, 620);
  layout1->addWidget(thicknessEdge);

  thickness = new QLineEdit(this);
  thickness->setGeometry(1220 + thicknessEdge->width(), 620, 180, 30);
  thickness->setStyleSheet(
      "QLineEdit { background-color: #25272b;}"
      "QLineEdit { border: none;}"
      "QLineEdit { color: grey}");
  connect(thickness, &QLineEdit::textChanged, this,
          &viewerwindow::s21_textEditTextChanged);

  QFrame *frameVertex = new QFrame(this);  // create panel for Vertex
  frameVertex->setGeometry(1210, 680, 280, 200);
  frameVertex->setStyleSheet(
      "background-color: #25272b;"
      "    border-radius: 20px;");
  QVBoxLayout *layout2 = new QVBoxLayout(this);

  QLabel *labelVertex = new QLabel("Vertexes", this);  // Label Vertex
  labelVertex->setGeometry(1310, 690, 160, 30);
  labelFont = labelVertex->font();
  labelFont.setPointSize(20);
  labelVertex->setFont(labelFont);
  labelVertex->setStyleSheet("QLabel { color: grey;}");
  layout2->addWidget(labelVertex);

  QLabel *typeDisplayMethod =
      new QLabel("Display method: ", this);  // Label Display Method Vertex
  labelFont = typeDisplayMethod->font();
  labelFont.setPointSize(16);
  typeDisplayMethod->setFont(labelFont);
  typeDisplayMethod->setStyleSheet("QLabel { color: grey;}");
  typeDisplayMethod->adjustSize();
  typeDisplayMethod->move(1220, 730);
  layout2->addWidget(typeDisplayMethod);

  MethodDisplayVertexComboBox =
      new QComboBox(this);  // ComboBox for Dispaly Method
  MethodDisplayVertexComboBox->setGeometry(1220 + typeDisplayMethod->width(),
                                           730, 100, 30);
  MethodDisplayVertexComboBox->setStyleSheet(
      "QComboBox {"
      "border: 1px solid gray;"
      "color: white;"
      "border-radius: 3px;"
      "padding: 1px 18px 1px 3px;"
      "selection-background-color: #25272b;"
      "background: #25272b;}");
  MethodDisplayVertexComboBox->addItem("None");
  MethodDisplayVertexComboBox->addItem("Circle");
  MethodDisplayVertexComboBox->addItem("Square");
  connect(MethodDisplayVertexComboBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(s21_typeVertex()));

  QLabel *colorVertex = new QLabel("Color: ", this);  // Label Color Vertex
  labelFont = colorVertex->font();
  labelFont.setPointSize(16);
  colorVertex->setFont(labelFont);
  colorVertex->setStyleSheet("QLabel { color: grey;}");
  colorVertex->adjustSize();
  colorVertex->move(1220, 780);
  layout2->addWidget(colorVertex);

  colorVertexButton =
      new QCustomPushButton("", this);  // PushButton for change color button
  colorVertexButton->setGeometry(1220 + colorVertex->width(), 775, 35, 40);
  colorVertexButton->setStyleSheet("QPushButton { color: grey;}");
  colorVertexButton->attach(glWidget);
  QObject::connect(colorVertexButton, &QPushButton::clicked, [&]() {
    QColor color1 = QColorDialog::getColor();
    if (color1.isValid()) {
      glWidget->redVertex = color1.red() / 255.0f;
      glWidget->greenVertex = color1.green() / 255.0f;
      glWidget->blueVertex = color1.blue() / 255.0f;
      colorVertexButton->setStyleSheet(
          "QPushButton { background-color: " + color1.name() + ";}");
      colorVertexButton->notify();
    }
  });
  layout2->addWidget(colorVertexButton);

  QLabel *typeVertex = new QLabel("Size: ", this);  // Label Size Vertex
  labelFont = typeVertex->font();
  labelFont.setPointSize(16);
  typeVertex->setFont(labelFont);
  typeVertex->setStyleSheet("QLabel { color: grey;}");
  typeVertex->adjustSize();
  typeVertex->move(1220, 830);
  layout2->addWidget(typeVertex);

  sizeVertex = new QTextEdit(this);
  sizeVertex->setGeometry(1220 + typeVertex->width(), 830, 180, 30);
  sizeVertex->setStyleSheet(
      "QTextEdit { background-color: #25272b}"
      "QTextEdit { border-style: none}"
      "QTextEdit { color: grey}");

  connect(sizeVertex, SIGNAL(textChanged()), this,
          SLOT(s21_textEditSizeVertex()));

  layout->addWidget(frameVertex);
  layout->addWidget(frameEdge);

  connect(xRotate, &QSlider::valueChanged, this, &viewerwindow::s21_RotateX);
  connect(yRotate, &QSlider::valueChanged, this, &viewerwindow::s21_RotateY);
  connect(zRotate, &QSlider::valueChanged, this, &viewerwindow::s21_RotateZ);

  connect(xTranslated, &QSlider::valueChanged, this,
          &viewerwindow::s21_TranslatedX);
  connect(yTranslated, &QSlider::valueChanged, this,
          &viewerwindow::s21_TranslatedY);
  connect(zTranslated, &QSlider::valueChanged, this,
          &viewerwindow::s21_TranslatedZ);

  connect(ScaledPlus, SIGNAL(clicked()), this, SLOT(s21_ScaledPlus()));
  connect(ScaledMinus, SIGNAL(clicked()), this, SLOT(s21_ScaledMinus()));

  connect(OrthoViewButton, SIGNAL(clicked()), this, SLOT(s21_OrthoView()));
  connect(FrustViewButton, SIGNAL(clicked()), this, SLOT(s21_FrustView()));
}

QString viewerwindow::ParsingFileName(QString fileName) {
  int flag = 0;
  for (int i = fileName.size() - 1; i >= 0; i--) {
    if (fileName[i] == '/') {
      flag = 1;
    }
    if (flag == 1) {
      fileName.erase(fileName.begin(), fileName.begin() + i + 1);
      break;
    }
  }
  return fileName;
}

void viewerwindow::s21_RotateX(int newValue) {
  if (fileIsOpen == 1) {
    glWidget->angleRotate = newValue;
    glWidget->xRotate = 1.0f;
    glWidget->yRotate = 0.0f;
    glWidget->zRotate = 0.0f;
    glWidget->update();
    xLastValueRotated = newValue;
  }
}

void viewerwindow::s21_RotateY(int newValue) {
  if (fileIsOpen == 1) {
    glWidget->angleRotate = newValue;
    glWidget->xRotate = 0.0f;
    glWidget->yRotate = 1.0f;
    glWidget->zRotate = 0.0f;
    glWidget->update();
    xLastValueRotated = newValue;
  }
}

void viewerwindow::s21_RotateZ(int newValue) {
  if (fileIsOpen == 1) {
    glWidget->angleRotate = newValue;
    glWidget->xRotate = 0.0f;
    glWidget->yRotate = 0.0f;
    glWidget->zRotate = 1.0f;
    glWidget->update();
    xLastValueRotated = newValue;
  }
}

void viewerwindow::s21_TranslatedX(int newValue) {
  if (fileIsOpen == 1) {
    glWidget->xTranslate = newValue;
    glWidget->update();
    xLastValueTranslated = newValue;
  }
}

void viewerwindow::s21_TranslatedY(int newValue) {
  if (fileIsOpen == 1) {
    glWidget->yTranslate = newValue;
    glWidget->update();
    xLastValueTranslated = newValue;
  }
}

void viewerwindow::s21_TranslatedZ(int newValue) {
  if (fileIsOpen == 1) {
    glWidget->zTranslate = newValue;
    glWidget->update();
    xLastValueTranslated = newValue;
  }
}

void viewerwindow::s21_ScaledPlus() {
  if (fileIsOpen == 1) {
    glWidget->allScale += 0.1;
    ScaledPlus->notify();
  }
}

void viewerwindow::s21_ScaledMinus() {
  if (fileIsOpen == 1) {
    if (glWidget->allScale > 0.1) {
      glWidget->allScale -= 0.1;
      ScaledMinus->notify();
    }
  }
}

void viewerwindow::s21_OrthoView() {
  if (glWidget->typeProjection == 1 && fileIsOpen == 1) {
    glWidget->typeProjection = 0;
    OrthoViewButton->setStyleSheet(
        "QPushButton {"
        "    border-radius: 2px;"
        "    color: #a0a39e;"
        "    background-color: #252427;"
        "}");
    FrustViewButton->setStyleSheet(
        "QPushButton {"
        "    border-radius: 2px;"
        "    color: #a0a39e;"
        "    background-color: #616360;"
        "}");
    OrthoViewButton->notify();
  }
}

void viewerwindow::s21_FrustView() {
  if (glWidget->typeProjection == 0 && fileIsOpen == 1) {
    glWidget->typeProjection = 1;
    FrustViewButton->setStyleSheet(
        "QPushButton {"
        "    border-radius: 2px;"
        "    color: #a0a39e;"
        "    background-color: #252427;"
        "}");
    OrthoViewButton->setStyleSheet(
        "QPushButton {"
        "    border-radius: 2px;"
        "    color: #a0a39e;"
        "    background-color: #616360;"
        "}");
    FrustViewButton->notify();
  }
}

void viewerwindow::s21_textEditTextChanged() {
  if (fileIsOpen == 1) {
    QString currentText = thickness->text();
    int flag = 0;
    for (int i = 0; i < currentText.size(); i++) {
      if ((currentText[i] < '0' || currentText[i] > '9') &&
          currentText[i] != '.') {
        flag = 1;
        break;
      }
    }
    if (flag == 0) {
      double thicknessNumber = currentText.toDouble();
      if (thicknessNumber > 30) thicknessNumber = 30;
      glWidget->widthEdge = thicknessNumber;
      glWidget->update();
    }
  }
}

void viewerwindow::s21_typeEdge() {
  if (fileIsOpen == 1) {
    if (typeEdgeComboBox->currentText() == "Solid") {
      glWidget->typeEdge = 0.0f;
    } else {
      glWidget->typeEdge = 3.0f;
    }
    glWidget->update();
  }
}

void viewerwindow::s21_textEditSizeVertex() {
  if (fileIsOpen == 1) {
    QString currentText = sizeVertex->toPlainText();
    int flag = 0;
    for (int i = 0; i < currentText.size(); i++) {
      if ((currentText[i] < '0' || currentText[i] > '9') &&
          currentText[i] != '.') {
        flag = 1;
        break;
      }
    }
    if (flag == 0) {
      double sizeVertexNumber = currentText.toDouble();
      if (sizeVertexNumber > 30) sizeVertexNumber = 30;
      glWidget->sizeVertex = sizeVertexNumber;
      glWidget->update();
    }
  }
}

void viewerwindow::s21_typeVertex() {
  if (fileIsOpen == 1) {
    if (MethodDisplayVertexComboBox->currentText() == "None") {
      glWidget->typeVertex = 0;
    } else if (MethodDisplayVertexComboBox->currentText() == "Circle") {
      glWidget->typeVertex = 1;
    } else {
      glWidget->typeVertex = 2;
    }
    glWidget->update();
  }
}

void viewerwindow::refreshValue() {
  xRotate->setValue(0);
  yRotate->setValue(0);
  zRotate->setValue(0);
  xTranslated->setValue(0);
  yTranslated->setValue(0);
  zTranslated->setValue(0);
  thickness->setText("1");
  sizeVertex->setText("1");
  MethodDisplayVertexComboBox->setCurrentText("None");
  typeEdgeComboBox->setCurrentText("Solid");
  colorEdgeButton->setStyleSheet("background-color: #fafafa");
  colorVertexButton->setStyleSheet("background-color: #fafafa");
  glWidget->typeEdge = 0;
  glWidget->sizeVertex = 1;
  glWidget->typeVertex = 0;
  glWidget->widthEdge = 1;
  glWidget->redEdge = 1;
  glWidget->greenEdge = 1;
  glWidget->blueEdge = 1;
  glWidget->redVertex = 1;
  glWidget->greenVertex = 1;
  glWidget->blueVertex = 1;

  glWidget->angleRotate = 0.0f;
  glWidget->xRotate = 0.0f;
  glWidget->yRotate = 0.0f;
  glWidget->zRotate = 0.0f;
  glWidget->xTranslate = 0.0f;
  glWidget->yTranslate = 0.0f;
  glWidget->zTranslate = 0.0f;
  glWidget->allScale = 0.5f;

  glWidget->red = 32.0f / 255.0f;
  glWidget->green = 33.0f / 255.0f;
  glWidget->blue = 36.0f / 255.0f;
  QString styleSheet = QString("background-color: rgb(%1, %2, %3);")
                           .arg(int(glWidget->red * 255))
                           .arg(int(glWidget->green * 255))
                           .arg(int(glWidget->blue * 255));
  colorButton->setStyleSheet(styleSheet);
}

void viewerwindow::s21_openFileDialog() {
  fileIsOpen = 0;
  glWidget->fileIsOpen = 0;
  QString fileName =
      QFileDialog::getOpenFileName(this, "Выберите файл", QDir::currentPath());
  if (fileName != "" && fileName[fileName.size() - 1] == 'j' &&
      fileName[fileName.size() - 2] == 'b' &&
      fileName[fileName.size() - 3] == 'o') {
    s21_openFile(fileName);
  }
}

void viewerwindow::s21_openFile(QString fileName) {
  std::unique_ptr<Controller> currentController;
  try {
    currentController = std::make_unique<Controller>(fileName.toStdString());
  } catch (const std::invalid_argument &e) {
    qDebug() << "File is not correct";
  }
  qDebug() << currentController->getVertexes().size();
  controller_ = std::move(currentController);
  if (FileFirstTimeIsOpen == 1) refreshValue();
  fileSave = fileName;
  fileIsOpen = 1;
  glWidget->fileIsOpen = 1;
  glWidget->setArrayIndexes(controller_->getIndexes());
  glWidget->setArrayVertex(controller_->getVertexes());
  glWidget->initFigure();
  glWidget->update();
  thisFile->setText(ParsingFileName(fileName));
  thisVertices->setText(QString::number(controller_->getVertexes().size()));
  thisEdges->setText(QString::number(controller_->getIndexes().size()));
  if (FileFirstTimeIsOpen == 1) refreshValue();
  FileFirstTimeIsOpen = 1;
}

void viewerwindow::saveSettings() {
  settings->setValue("fileName",
                     fileSave);  // Сохраняем путь к последнему открытому файлу
  settings->setValue("xRotate", xRotate->value());
  settings->setValue("yRotate", yRotate->value());
  settings->setValue("zRotate", zRotate->value());
  settings->setValue("xTranslated", xTranslated->value());
  settings->setValue("yTranslated", yTranslated->value());
  settings->setValue("zTranslated", zTranslated->value());
  settings->setValue("ratio", glWidget->allScale);
  settings->setValue("angel", glWidget->angleRotate);

  settings->setValue("typeProjection", glWidget->typeProjection);
  settings->setValue("backgroundColorRed", glWidget->red);
  settings->setValue("backgroundColorGreen", glWidget->green);
  settings->setValue("backgroundColorBlue", glWidget->blue);

  settings->setValue("EdgeColorRed", glWidget->redEdge);
  settings->setValue("EdgeColorGreen", glWidget->greenEdge);
  settings->setValue("EdgeColorBlue", glWidget->blueEdge);

  settings->setValue("VertexColorRed", glWidget->redVertex);
  settings->setValue("VertexColorGreen", glWidget->greenVertex);
  settings->setValue("VertexColorBlue", glWidget->blueVertex);

  settings->setValue("thickness", glWidget->widthEdge);
  settings->setValue("size", glWidget->sizeVertex);

  settings->setValue("typeEdge", glWidget->typeEdge);
  settings->setValue("typeVertex", glWidget->typeVertex);
}

void viewerwindow::loadSettings() {
  fileSave = settings->value("fileName", "")
                 .toString();  // Загружаем путь к последнему открытому файлу
  if (fileSave != "") {
    double xRotateValue = settings->value("xRotate", 0).toDouble();
    double yRotateValue = settings->value("yRotate", 0).toDouble();
    double zRotateValue = settings->value("zRotate", 0).toDouble();
    double xTranslatedValue = settings->value("xTranslated", 0).toDouble();
    double yTranslatedValue = settings->value("yTranslated", 0).toDouble();
    double zTranslatedValue = settings->value("zTranslated", 0).toDouble();
    double ratioSave = settings->value("ratio", 0).toDouble();
    double angleValue = settings->value("angel", 0).toDouble();

    int typeProjection = settings->value("typeProjection", 0).toInt();
    double backColorRed = settings->value("backgroundColorRed", 0).toDouble();
    double backColorGreen =
        settings->value("backgroundColorGreen", 0).toDouble();
    double backColorBlue = settings->value("backgroundColorBlue", 0).toDouble();

    double edgeColorRed = settings->value("EdgeColorRed", 0).toDouble();
    double edgeColorGreen = settings->value("EdgeColorGreen", 0).toDouble();
    double edgeColorBlue = settings->value("EdgeColorBlue", 0).toDouble();

    double vertexColorRed = settings->value("VertexColorRed", 0).toDouble();
    double vertexColorGreen = settings->value("VertexColorGreen", 0).toDouble();
    double vertexColorBlue = settings->value("VertexColorBlue", 0).toDouble();

    double thicknessEdge = settings->value("thickness", 0).toDouble();
    thickness->setText(QString::number(thicknessEdge));
    double sizeVertex1 = settings->value("size", 0).toDouble();
    sizeVertex->setText(QString::number(sizeVertex1));

    double typeEdge1 = settings->value("typeEdge", 0).toDouble();
    glWidget->typeEdge = typeEdge1;
    typeEdgeComboBox->setCurrentIndex(typeEdge1);
    double typeVertex1 = settings->value("typeVertex", 0).toDouble();
    glWidget->typeVertex = typeVertex1;
    MethodDisplayVertexComboBox->setCurrentIndex(typeVertex1);

    xRotate->setValue(xRotateValue);
    yRotate->setValue(yRotateValue);
    zRotate->setValue(zRotateValue);
    xTranslated->setValue(xTranslatedValue);
    yTranslated->setValue(yTranslatedValue);
    zTranslated->setValue(zTranslatedValue);
    glWidget->red = backColorRed;
    glWidget->green = backColorGreen;
    glWidget->blue = backColorBlue;
    QString styleSheet = QString("background-color: rgb(%1, %2, %3);")
                             .arg(int(backColorRed * 255))
                             .arg(int(backColorGreen * 255))
                             .arg(int(backColorBlue * 255));
    colorButton->setStyleSheet(styleSheet);

    glWidget->redEdge = edgeColorRed;
    glWidget->greenEdge = edgeColorGreen;
    glWidget->blueEdge = edgeColorBlue;
    QString styleSheet1 = QString("background-color: rgb(%1, %2, %3);")
                              .arg(int(edgeColorRed * 255))
                              .arg(int(edgeColorGreen * 255))
                              .arg(int(edgeColorBlue * 255));
    colorEdgeButton->setStyleSheet(styleSheet1);

    glWidget->redVertex = vertexColorRed;
    glWidget->greenVertex = vertexColorGreen;
    glWidget->blueVertex = vertexColorBlue;
    QString styleSheet2 = QString("background-color: rgb(%1, %2, %3);")
                              .arg(int(vertexColorRed * 255))
                              .arg(int(vertexColorGreen * 255))
                              .arg(int(vertexColorBlue * 255));
    colorVertexButton->setStyleSheet(styleSheet2);

    glWidget->widthEdge = thicknessEdge;
    glWidget->sizeVertex = sizeVertex1;

    s21_openFile(fileSave);

    glWidget->angleRotate = angleValue;
    glWidget->xRotate = xRotateValue;
    glWidget->yRotate = yRotateValue;
    glWidget->zRotate = zRotateValue;
    glWidget->xTranslate = xTranslatedValue;
    glWidget->yTranslate = yTranslatedValue;
    glWidget->zTranslate = zTranslatedValue;
    glWidget->allScale = ratioSave;

    glWidget->update();
    if (typeProjection) s21_FrustView();
  }
}

void viewerwindow::s21_Screenshot() {
  QFileDialog dialogConnectImage(this);
  QString namePattern = "Screenshot";
  QString imageName = dialogConnectImage.getSaveFileName(
      this, tr("Save a screenshot"), namePattern, tr("image (*.jpeg *.bmp)"));
  if (!imageName.isEmpty()) {
    QImage screenShot =
        glWidget->grabFramebuffer();  // захват текущего изображения
    if (!imageName.contains(".jpeg") || !imageName.contains(".bmp"))
      imageName += ".jpeg";
    screenShot.save(imageName);
  }
}

void viewerwindow::s21_Gif() {
  QString namePattern = "ScreenCast";
  QString gifName = QFileDialog::getSaveFileName(
      this, tr("Save a screencast"), namePattern, tr("gif (*.gif)"));

  if (!gifName.isEmpty()) {
    Gif->setDisabled(true);

    QGifImage *gifImage = new QGifImage;
    gifImage->setDefaultDelay(100);  // Задержка для сохранения кадров

    int fps = 10;
    int duration = 5;

    int totalFrames = fps * duration;
    int framesCounter = 0;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() mutable {
      QImage frameImage = glWidget->grabFramebuffer();
      QSize imageSize(640, 480);
      QImage scaledImage = frameImage.scaled(imageSize);
      gifImage->addFrame(scaledImage);

      ++framesCounter;
      if (!Gif->isEnabled()) {
        Gif->setText(QString::number(framesCounter / 10) + "s");
      }

      if (framesCounter >= totalFrames) {
        timer->stop();
        gifImage->save(gifName);
        Gif->setEnabled(true);
        Gif->setText("");
        delete gifImage;
        delete timer;
      }
    });

    timer->start(1000 /
                 fps);  // Запускаем QTimer с интервалом, соответствующим fps
  }
}
