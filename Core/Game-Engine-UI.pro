#-------------------------------------------------
#
# Project created by QtCreator 2015-10-20T16:35:56
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game-Engine-UI
TEMPLATE = app

win32: {
    LIBS += -lopengl32 -lglu32 -lgdi32 -lkernel32 -luser32
}
unix:!macx {
    LIBS += -lX11 -GL -lGLU
}
macx: {
    LIBS += -framework Cocoa -framework OpenGL
}

SOURCES += main.cpp \
        mainwindow.cpp \
        Common/EngMath.c \
        Common/GLExtLib.c \
        Common/Model.c \
        Common/Shader.c \
        Common/Texture.c \
        openglview.cpp

HEADERS  += mainwindow.h \
        Common/EngMath.h \
        Common/GLExtLib.h \
        Common/Model.h \
        Common/Shader.h \
        Common/Texture.h \
        Common/Precomp.h \
        openglview.h

FORMS    += mainwindow.ui

OTHER_FILES += minimalVert.glsl \
               minimalFrag.glsl
