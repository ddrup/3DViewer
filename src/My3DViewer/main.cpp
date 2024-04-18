#include <QApplication>

#include "viewer.h"
#include "viewerwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  //    Viewer w;
  //    w.resize(200, 200);
  //    w.show();

  QApplication::setOrganizationName("3DViewer");
  QApplication::setApplicationName("Settings");

  viewerwindow win;
  win.resize(1500, 1000);
  win.show();
  return a.exec();
}
