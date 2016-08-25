// OpenGLView.cpp

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "openglview.h"

OpenGLView::OpenGLView(QWidget *parent) :
    QOpenGLWidget(parent)
{
    fprintf(stdout, "constructor called.\n");
}

void OpenGLView::initializeGL()
{
    // Enable GL extension functions
    InitGLext();

    // GL Ctxt Initialization
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    gModel = LoadModel("Cube", "../Assets/Models/pyramid-metal3.obj");
    gTexture = LoadTexture("Metal", "../Assets/Textures/scratchedmetal2.DDS");
    gModel.texture = &gTexture;
    InitGLModel(&gModel);
    InitGLTexture(gModel.texture);

    // Load Shader
    Shader shader = loadGLShader("Minimal", "Core/minimalVert.glsl", "Core/minimalFrag.glsl");
    ProgramID = shader.ProgramID;

    // Initialize before resizeGL
    m_height = this->height();
    m_width = this->width();
    m_aspect = m_width / m_height;
}

void OpenGLView::paintGL()
{
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(ProgramID);

    // VBOs and Uniforms
    glBindAttribLocation(ProgramID, 0, "vertexPosition");
    glBindAttribLocation(ProgramID, 1, "vertexUV");
    GLuint uniformMVP = glGetUniformLocation(ProgramID, "MVP");
    GLuint uniformDiffuseTexture = glGetUniformLocation(ProgramID, "diffuseTexture");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gModel.texture->TextureID);
    glUniform1i(uniformDiffuseTexture, 0);

    // Matrix manipulation
    Matrix4 gMVP = { 0 }, View = { 0 }, Projection = { 0 };
    scaleMatrix(gModel.model, 1.f, 1.f, 1.f);
    eulerRotateMatrix(gModel.model, true, 0, 0, 0);

    translateMatrix(gModel.model, 0.f, 0.f, 0.0f);
    getLookAtRH(View, 0.f, 2.f, -2.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
    getPerspectiveMatrixRH(Projection, 45.f, m_width / m_height, .01f, 100.f);
    mat4Mul(gMVP, Projection, View);
    mat4Mul(gMVP, gMVP, gModel.model);
    glUniformMatrix4fv(uniformMVP, 1, GL_FALSE, gMVP);

    GLuint vboBuffer1 = 0, vboBuffer2 = 0;
    glGenBuffers(1, &vboBuffer1);
    glGenBuffers(1, &vboBuffer2);

    glBindBuffer(GL_ARRAY_BUFFER, vboBuffer1);
    glBufferData(GL_ARRAY_BUFFER,
                 gModel.indexCount * SIZEOF_VEC3, gModel.vertices, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vboBuffer2);
    glBufferData(GL_ARRAY_BUFFER,
                 gModel.indexCount * SIZEOF_VEC2, gModel.uvs, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, gModel.indexCount * 3);


}

void OpenGLView::resizeGL(int w, int h)
{
    m_height = h;
    m_width = w;
    m_aspect = m_width / m_height;
}

//
//
// Wrapper functions
//
//
void OpenGLView::InitGLModel(Model* model)
{
    GLuint vertexBuffer, uvBuffer, normalBuffer, vertexIndexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &uvBuffer);
    glGenBuffers(1, &normalBuffer);
    glGenBuffers(1, &vertexIndexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, model->vertexCount * SIZEOF_VEC3, &model->vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, model->uvCount * SIZEOF_VEC2, &model->uvs[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, model->normalCount * SIZEOF_VEC3, &model->normals[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indexCount * sizeof(unsigned long), &model->vertexIndices[0], GL_STATIC_DRAW);
    model->vertexBuffer = vertexBuffer;
    model->uvBuffer = uvBuffer;
    model->normalBuffer = normalBuffer;
}


void OpenGLView::InitGLTexture(Texture* texture)
{
    if (!strcmp(texture->extension, "TGA")) {
        #define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
        #define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
        #define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII
        unsigned int format;

        switch (texture->fourCC)
        {
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            free((unsigned char*)texture->data);
            printf("In loading DDS, default case occurred; won't work.\n");
        }

        //MakeContextCurrent();
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        unsigned char* buffer = (unsigned char*)texture->data; // This may not be a necessary thing to do, consider changing texture.data to type unsigned char*.
        unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
        unsigned int offset = 0;
        for (unsigned int level = 0; level < texture->mipMapCount && (texture->Width || texture->Height); ++level)
        {
            unsigned int size = ((texture->Width + 3) / 4)*((texture->Height + 3) / 4)*blockSize;
            glCompressedTexImage2D(GL_TEXTURE_2D, level, format, texture->Width, texture->Height, 0, size, buffer + offset);
            offset += size;
            texture->Width /= 2;
            texture->Height /= 2;
        }
        free((unsigned char*)texture->data);

        texture->TextureID = textureID;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);

        //ClearContextCurrent();
    }
}

/*
 * The following was a temporary wall of code specific to my
 * aged 2009 macbook with its aged GPU.

    char* vertexShaderCode =      "#version 110\n\
    =======
    char* vertexShaderCode =      "#version 150\n\
    >>>>>>> origin/master
                                    uniform vec2 p;\
                                    in vec4 position;\
                                    in vec4 colour;\
                                    out vec4 colourV;\
                                    void main (void)\
                                    {\
                                    colourV = colour;\
                                    gl_Position = vec4(p, 0.0, 0.0) + position;\
                                    }";

    char* fragmentShaderCode =    "#version 150\n\
                                    in vec4 colourV;\
                                    out vec4 fragColour;\
                                    void main (void)\
                                    {\
                                    fragColour = colourV;\
                                    }";


    int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShaderID);
    int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShaderID);

    ProgramID = glCreateProgram();
    glAttachShader(ProgramID, vertexShaderID);
    glAttachShader(ProgramID, fragmentShaderID);
    glBindFragDataLocation(ProgramID, 0, "fragColour");
    glLinkProgram(ProgramID);
    printf("ProgramID: %d\n", ProgramID);

    // 5. Get pointers to uniforms and attributes
    positionUniform = glGetUniformLocation(ProgramID, "p");
    colourAttribute = glGetAttribLocation(ProgramID, "colour");
    positionAttribute = glGetAttribLocation(ProgramID, "position");
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    printf("positionUniform: %i, colourAttribute: %i, positionAttribute: %i\n",positionUniform,colourAttribute,positionAttribute);

  * And then in paintGL:
  *
    //GLfloat vertexData[]= { -0.5,-0.5,0.0,1.0,   1.0,0.0,0.0,1.0,
    //                            -0.5, 0.5,0.0,1.0,   0.0,1.0,0.0,1.0,
    //                             0.5, 0.5,0.0,1.0,   0.0,0.0,1.0,1.0,
    //                             0.5,-0.5,0.0,1.0,   1.0,1.0,1.0,1.0};

    //glGenBuffers(1, &vertexBuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    //glBufferData(GL_ARRAY_BUFFER, 4*8*sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

    //glEnableVertexAttribArray((GLuint)positionAttribute);
    //glEnableVertexAttribArray((GLuint)colourAttribute  );
    //glVertexAttribPointer((GLuint)positionAttribute, 4, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), 0);
    //glVertexAttribPointer((GLuint)colourAttribute  , 4, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (char*)0+4*sizeof(GLfloat));
    glClearColor(0.0, 0.0, 0.3, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    fprintf(stdout, "paintGL?\n");
*/
