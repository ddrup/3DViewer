#include <QApplication>

#include "viewer.h"
#include "viewerwindow.h"
using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QApplication::setOrganizationName("3DViewer");
  QApplication::setApplicationName("Settings");
  viewerwindow win;
  win.resize(1500, 1000);
  win.show();
  return a.exec();
}
