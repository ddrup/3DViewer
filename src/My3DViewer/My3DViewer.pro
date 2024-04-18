QT       += core gui
QT += opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Backend/s21_affine_transformation.c \
    Backend/s21_help_func.c \
    Backend/s21_matrix.c \
    Backend/s21_parse_obj_file.c \
    Backend/s21_vector.c \
    gifmaker/dgif_lib.c \
    gifmaker/egif_lib.c \
    gifmaker/gif_err.c \
    gifmaker/gif_font.c \
    gifmaker/gif_hash.c \
    gifmaker/gifalloc.c \
    gifmaker/qgifimage.cpp \
    gifmaker/quantize.c \
    main.cpp \
    viewer.cpp \
    viewerwindow.cpp

HEADERS += \
    gifmaker/gif_hash.h \
    gifmaker/gif_lib.h \
    gifmaker/gif_lib_private.h \
    gifmaker/qgifglobal.h \
    gifmaker/qgifimage.h \
    gifmaker/qgifimage_p.h \
    viewer.h \
    viewerwindow.h \
    Backend/s21_Viewer.h \
    Backend/s21_affine_transformation.h



FORMS += \
    viewer.ui \
    viewerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    gifmaker/gifimage.pro

DISTFILES += \
    gifmaker/AUTHORS \
    gifmaker/COPYING \
    gifmaker/Makefile \
    gifmaker/README \
    gifmaker/qdoc_wrapper.sh \
    gifmaker/qtgifimage.pri

RESOURCES += \
    Resource.qrc
