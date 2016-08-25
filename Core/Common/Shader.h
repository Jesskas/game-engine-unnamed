//
// Shader.h
// Implementation of a Shader Helper Class.
//

#ifndef SHADER_H
#define SHADER_H

//
// Includes
//
#include "Common/Precomp.h"
#include <stdio.h>    // FILE*, etc
#include <stdlib.h>   // malloc, etc
#include <string.h>   // strcmp

#ifdef _WIN32
    #include "Common/GLExtLib.h"
#elif __linux__
	#include "GLExtLib.h"
#elif TARGET_OS_MAC
	#ifdef __OBJC__
		#import <OpenGL/OpenGL.h>
		#import <OpenGL/gl.h>
	#endif
#endif

typedef struct {
    const char* name;
    const int ProgramID;
} Shader;

#if defined(__cplusplus)
extern "C" {
#endif
Shader loadGLShader(const char* name, const char* vertexShaderPath, const char* fragmentShaderPath);
//Shader loadGLShader_s(char* name, char* shaderPath);
#if defined(__cplusplus)
}
#endif

#endif // SHADER_H

