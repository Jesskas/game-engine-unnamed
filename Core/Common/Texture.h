//
// Texture.h
// 

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Common/Precomp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Common/EngMath.h"

typedef struct
{
	const char* name;
	const char* filename;
	const char* extension;
	unsigned int fourCC;	// for DDS file format
	unsigned int Width;
	unsigned int Height;
	unsigned int mipMapCount;
	const void* data;

	// OpenGL stuff, not to be initialized here.
	int TextureID;
} Texture;

#if defined(__cplusplus)
extern "C" {
#endif
Texture LoadTexture(const char*, const char*);
Texture LoadDDS(const char*);
Texture LoadTGA(char*); // This is untested!!
void ReleaseTexture();
#if defined(__cplusplus)
}
#endif

#endif // TEXTURE_H

