//
// GLExtLib.c
// Implements GLExtLib.h for strictly
// Windows and Linux environments.
//

#include "GLExtLib.h"

// Program
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLDETACHSHADERPROC glDetachShader = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLUNIFORM1IPROC glUniform1i = NULL;
PFNGLUNIFORM1IVPROC glUniform1iv = NULL;
PFNGLUNIFORM2IVPROC glUniform2iv = NULL;
PFNGLUNIFORM3IVPROC glUniform3iv = NULL;
PFNGLUNIFORM4IVPROC glUniform4iv = NULL;
PFNGLUNIFORM1FPROC glUniform1f = NULL;
PFNGLUNIFORM1FVPROC glUniform1fv = NULL;
PFNGLUNIFORM2FVPROC glUniform2fv = NULL;
PFNGLUNIFORM3FVPROC glUniform3fv = NULL;
PFNGLUNIFORM4FVPROC glUniform4fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = NULL;
PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f = NULL;
PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv = NULL;
PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = NULL;
PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = NULL;
PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = NULL;

// Texture
#ifdef _WIN32
PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = NULL;
#else // "previous declaration of glActiveTexture was [gl.h]" workaround
#define glActiveTexture p_glActiveTexture
#define glCompressedTexImage2D p_glCompressedTexImage2D
PFNGLACTIVETEXTUREPROC p_glActiveTexture = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC p_glCompressedTexImage2D = NULL;
#endif
PFNGLGENERATEMIPMAPPROC glGenerateMipmap = NULL;

// Shader
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;

// VBO
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;

// VAO
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;

// TODO: Check to see if each is null/error case.
// TODO: Check every version on every function accordingly.
// I'm not doing it now because it's 3:55am.
void InitGLext()
{
// TODO: Place this in function header.
#ifdef _WIN32
#define glGetProcAddress(x) wglGetProcAddress(x)
#elif __linux__
#define glGetProcAddress(x) glXGetProcAddress((const GLubyte*)x)
#endif

#if defined(_WIN32) || defined(__linux__)
    // Program
    glCreateProgram = (PFNGLCREATEPROGRAMPROC)glGetProcAddress("glCreateProgram");
    glDeleteProgram = (PFNGLDELETEPROGRAMPROC)glGetProcAddress("glDeleteProgram");
    glUseProgram = (PFNGLUSEPROGRAMPROC)glGetProcAddress("glUseProgram");
    glAttachShader = (PFNGLATTACHSHADERPROC)glGetProcAddress("glAttachShader");
    glDetachShader = (PFNGLDETACHSHADERPROC)glGetProcAddress("glDetachShader");
    glLinkProgram = (PFNGLLINKPROGRAMPROC)glGetProcAddress("glLinkProgram");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC)glGetProcAddress("glGetProgramiv");
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)glGetProcAddress("glGetProgramInfoLog");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)glGetProcAddress("glGetShaderInfoLog");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)glGetProcAddress("glGetUniformLocation");
    glUniform1i = (PFNGLUNIFORM1IPROC)glGetProcAddress("glUniform1i");
    glUniform1iv = (PFNGLUNIFORM1IVPROC)glGetProcAddress("glUniform1iv");
    glUniform2iv = (PFNGLUNIFORM2IVPROC)glGetProcAddress("glUniform2iv");
    glUniform3iv = (PFNGLUNIFORM3IVPROC)glGetProcAddress("glUniform3iv");
    glUniform4iv = (PFNGLUNIFORM4IVPROC)glGetProcAddress("glUniform4iv");
    glUniform1f = (PFNGLUNIFORM1FPROC)glGetProcAddress("glUniform1f");
    glUniform1fv = (PFNGLUNIFORM1FVPROC)glGetProcAddress("glUniform1fv");
    glUniform2fv = (PFNGLUNIFORM2FVPROC)glGetProcAddress("glUniform2fv");
    glUniform3fv = (PFNGLUNIFORM3FVPROC)glGetProcAddress("glUniform3fv");
    glUniform4fv = (PFNGLUNIFORM4FVPROC)glGetProcAddress("glUniform4fv");
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)glGetProcAddress("glUniformMatrix4fv");
    glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)glGetProcAddress("glGetAttribLocation");
    glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)glGetProcAddress("glVertexAttrib1f");
    glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)glGetProcAddress("glVertexAttrib1fv");
    glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)glGetProcAddress("glVertexAttrib2fv");
    glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)glGetProcAddress("glVertexAttrib3fv");
    glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)glGetProcAddress("glVertexAttrib4fv");
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glGetProcAddress("glEnableVertexAttribArray");
    glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)glGetProcAddress("glBindAttribLocation");

	// Texture
	glActiveTexture = (PFNGLACTIVETEXTUREPROC)glGetProcAddress("glActiveTexture");
	glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)glGetProcAddress("glCompressedTexImage2D");
	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glGetProcAddress("glGenerateMipmap");

    // Shader
    glCreateShader = (PFNGLCREATESHADERPROC)glGetProcAddress("glCreateShader");
    glDeleteShader = (PFNGLDELETESHADERPROC)glGetProcAddress("glDeleteShader");
    glShaderSource = (PFNGLSHADERSOURCEPROC)glGetProcAddress("glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC)glGetProcAddress("glCompileShader");
    glGetShaderiv = (PFNGLGETSHADERIVPROC)glGetProcAddress("glGetShaderiv");

    // VBO
    glGenBuffers = (PFNGLGENBUFFERSPROC)glGetProcAddress("glGenBuffers");
    glBindBuffer = (PFNGLBINDBUFFERPROC)glGetProcAddress("glBindBuffer");
    glBufferData = (PFNGLBUFFERDATAPROC)glGetProcAddress("glBufferData");
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)glGetProcAddress("glVertexAttribPointer");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)glGetProcAddress("glDeleteBuffers");

    // VAO
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glGetProcAddress("glGenVertexArrays");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glGetProcAddress("glBindVertexArray");
    glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glGetProcAddress("glDeleteVertexArrays");
#endif
}


