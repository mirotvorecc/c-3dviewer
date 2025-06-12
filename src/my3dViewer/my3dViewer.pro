QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix:!macx {
    LIBS += -lGL
}

macx: {
    LIBS += -framework OpenGL
}

# LIBS += -lGL
# LIBS += -framework OpenGL

TARGET = my3dViewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG +=c11
SOURCES += \
   ima/giflib/dgif_lib.c \
   ima/giflib/egif_lib.c \
   ima/giflib/gif_err.c \
   ima/giflib/gif_font.c \
   ima/giflib/gif_hash.c \
   ima/giflib/gifalloc.c \
   ima/giflib/quantize.c \
   ima/qgifimage.cpp \
    affine.c \
    main.cpp \
    mainwindow.cpp \
    glview.cpp \
    parser.c \

HEADERS += \
   ima/giflib/gif_hash.h \
   ima/giflib/gif_lib.h \
   ima/giflib/gif_lib_private.h \
   ima/qgifglobal.h \
   ima/qgifimage.h \
   ima/qgifimage_p.h \
    affine.h \
    mainwindow.h \
    glview.h \
    parser.h \

SUBDIRS += \
  ima/gifimage.pro

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
