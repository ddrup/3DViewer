#ifndef VIEWERWINDOW_H
#define VIEWERWINDOW_H

#include <QColorDialog>
#include <QComboBox>
#include <QDockWidget>
#include <QFileDialog>
#include <QFrame>
#include <QImage>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPixmap>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSettings>
#include <QSlider>
#include <QStackedWidget>
#include <QStyleFactory>
#include <QTextBrowser>
#include <QTimer>
#include <QToolBar>
#include <QVBoxLayout>

#include "gifmaker/qgifimage.h"
#include "gifmaker/qgifimage_p.h"
#include "viewer.h"

extern "C" {
#include "Backend/s21_Viewer.h"
#include "Backend/s21_affine_transformation.h"
#include "gifmaker/gif_hash.h"
#include "gifmaker/gif_lib.h"
#include "gifmaker/gif_lib_private.h"
#include "gifmaker/qgifglobal.h"
}

namespace Ui {
class viewerwindow;
}

class viewerwindow : public QMainWindow {
  Q_OBJECT

 public:
  viewerwindow(QWidget *parent = nullptr);
  ~viewerwindow();

  void s21_convertQStringToCharPointer(QString str, char *array);
  void s21_help(QString line, s21_Object3D *object3D);
  QStackedWidget *stackedWidget;
  QDockWidget *dockWidget;
  QToolBar *topToolBar;
  QPushButton *pushButton;
  QPushButton *pushButtonRotate;
  QPlainTextEdit *plainTextEdit;
  Viewer *glWidget;
  QAction *openFile;
  QAction *saveFile;
  QAction *openGlWidget;
  QAction *openTextEdit;
  QMenu *fileMenu;

  QSlider *xRotate;
  QSlider *yRotate;
  QSlider *zRotate;
  double xLastValueRotated = 0;
  double yLastValueRotated = 0;
  double zLastValueRotated = 0;

  QSlider *xTranslated;
  QSlider *yTranslated;
  QSlider *zTranslated;
  double xLastValueTranslated = 0;
  double yLastValueTranslated = 0;
  double zLastValueTranslated = 0;

  QPushButton *ScaledPlus;
  QPushButton *ScaledMinus;
  double ratio = 1;
  double lastScaled = 1;

  QPushButton *Screenshot;
  QPushButton *Gif;

  QLabel *thisFile;
  QLabel *thisVertices;
  QLabel *thisEdges;

  QPushButton *OrthoViewButton;
  QPushButton *FrustViewButton;
  QPushButton *colorButton;
  QPushButton *colorEdgeButton;
  QPushButton *colorVertexButton;
  QTextEdit *thickness;
  QComboBox *typeEdgeComboBox;
  QPushButton *setChanges;
  QTextEdit *sizeVertex;
  QComboBox *MethodDisplayVertexComboBox;
  QColor color;

  int fileIsOpen = 0;
  int flaging = 0;

  void elementsPrograms();
  void writeSettings();
  void readSettings();
  void refreshValue();
  QString ParsingFileName(QString fileName);

  void saveSettings();  // метод для сохранения настроек
  void loadSettings();  // метод для загрузки настроек
  void s21_openFile(QString filename);
  QString fileSave;

  int FileFirstTimeIsOpen = 0;

 private:
  Ui::viewerwindow *ui;
  s21_Object3D *object3D;
  QSettings *settings;
  int flag = 0;

 public slots:
  // void s21_setGlWidget();
  // void s21_setTextEdit();
  void s21_openFileDialog();
  void s21_RotateX(int newValue);
  void s21_RotateY(int newValue);
  void s21_RotateZ(int newValue);

  void s21_TranslatedX(int newValue);
  void s21_TranslatedY(int newValue);
  void s21_TranslatedZ(int newValue);

  void s21_ScaledPlus();
  void s21_ScaledMinus();

  void s21_OrthoView();
  void s21_FrustView();
  void s21_textEditTextChanged();
  void s21_typeEdge();
  void s21_textEditSizeVertex();
  void s21_typeVertex();
  void s21_Screenshot();
  void s21_Gif();
};

#endif  // VIEWERWINDOW_H
