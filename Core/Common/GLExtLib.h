//
// OGL
// Essentially the manager for all OGL specific functions.
// For the time being, this is all assuming OpenGL 3.3.
// For higher compatibility, I may expand that into OpenGL 2.1,
// but I don't know how necessary that would be, considering there
// are machines online that can run OpenGL 3.3 that run for under $200,
// and 2.1 runs on a seemingly different paradigm entirely.
//
// For reference:
// - In MS Windows, <GL/gl.h> essentially contains
// every function in the OpenGL 1.1 API. The others must be grabbed
// in extensions.
//      (<GL/..> == "C: ... idk." Appears to be based on compiler/kit/something.)
// - In Linux, things appear to be the exact same way as Windows.
//      (<GL/..> = "/usr/include/GL..")
// - In Mac, things are done very differently. Doesn't seem like
// extensions are even necessary;
// (<OpenGL/...> = "/System/Library/Frameworks/OpenGL.framework/Headers/..."
//   - I'll detail more as I get it; it looks like gl.h contains
//     a lot of functions above 1.1; but there's also gl3.h?
//     and a glext.h, and a OpenGL.h. Wow.
// It does appear that gl.h there actually accounts for
// the GL_GLEXT_FUNCTION_POINTERS; which seems cool. So maybe
// this isn't necessary.
//
// Of interest:
// https://www.opengl.org/wiki/Load_OpenGL_Functions
//

#ifndef GLEXTLIB_H
#define GLEXTLIB_H

#pragma once

#include "Common/Precomp.h"
#include "Common/Shader.h"

#pragma once
#ifdef _WIN32
    #include <GL/gl.h>
    #include <GL/glext.h>
    //#include <GL/glu.h>
    #include <GL/wglext.h>
        #ifdef _MSC_VER
            #pragma comment (lib, "opengl32.lib")
        #endif
#elif __linux__
    #include <stdio.h>    // FILE*, etc
    #include <stdlib.h>   // malloc, etc
    #include <string.h>   // strcmp

    #include <GL/gl.h>
    #include <GL/glext.h>
    //#include <GL/glu.h>
    #include <GL/glx.h>
    #include <X11/X.h>
    #include <X11/Xlib.h>
    #include <GL/glxext.h>
#endif


//--------------------------
// Start Extension Loading
//--------------------------

// Program
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM1IVPROC glUniform1iv;
extern PFNGLUNIFORM2IVPROC glUniform2iv;
extern PFNGLUNIFORM3IVPROC glUniform3iv;
extern PFNGLUNIFORM4IVPROC glUniform4iv;
extern PFNGLUNIFORM1FPROC glUniform1f;
extern PFNGLUNIFORM1FVPROC glUniform1fv;
extern PFNGLUNIFORM2FVPROC glUniform2fv;
extern PFNGLUNIFORM3FVPROC glUniform3fv;
extern PFNGLUNIFORM4FVPROC glUniform4fv;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;
extern PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv;
extern PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;
extern PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;
extern PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;

// Texture
#ifdef _WIN32
PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = NULL;
#else // "previous declaration of glActiveTexture was [gl.h]" workaround
#define glActiveTexture p_glActiveTexture
#define glCompressedTexImage2D p_glCompressedTexImage2D
extern PFNGLACTIVETEXTUREPROC p_glActiveTexture;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC p_glCompressedTexImage2D;
#endif
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;

// Shader
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;

// VBO
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;

// VAO
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;

//
// Initialize the extensions to essentially begin post-2.1 version OpenGL.
//
#if defined(__cplusplus)
extern "C" {
#endif
void InitGLext();
#if defined(__cplusplus)
}
#endif

//--------------------------
// End Extension Loading
//--------------------------

#endif // GLEXTLIB_H

