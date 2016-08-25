#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <QMainWindow>
#include <QOpenGLWidget>

#include "Common/GLExtLib.h"
#include "Common/Shader.h"
#include "Common/EngMath.h"

// Problematic Ones
#include "Common/Model.h"
#include "Common/Texture.h"

//#include <vector>

#ifdef TARGET_OS_MAC
#import <OpenGL/gl.h>
#import <OpenGL/OpenGL.h>
#endif

namespace Ui {
class OpenGLView;
}

class OpenGLView: public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit OpenGLView(QWidget *parent = 0);
    //~OpenGLView();

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
private:
    float m_width, m_height, m_aspect;
    GLuint vertexArrayObject;
    GLint ProgramID;

    Model gModel;
    Texture gTexture;

    std::vector<Model> models;

    //
    // Wrapper and Etc Functions
    //
    void InitGLModel(Model* model);
    void InitGLTexture(Texture* texture);

#ifdef TARGET_OS_MAC
    GLuint vertexBuffer;
    GLint positionUniform;
    GLint colourAttribute;
    GLint positionAttribute;
#endif

};

#endif // MAINWINDOW_H
