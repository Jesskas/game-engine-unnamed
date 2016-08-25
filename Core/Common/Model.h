//
// Model.h
// Written in C++ since the current math library
// is in C++ and C++ simplifies things for the short term.
// This will be simiplfied in time.
// 

#ifndef MODEL_H
#define MODEL_H

#include "Common/Precomp.h"
#include "Common/Texture.h"
#include "Common/EngMath.h"

typedef struct
{
	const char* name;
	Vector3* vertices;
	Vector2* uvs;
	Vector3* normals;
	//Vector3 tangents;
	//Vector3 bitangents;

	//unsigned int* indices;
	unsigned int* vertexIndices;
	unsigned int* uvIndices;
	unsigned int* normalIndices;
	//Vector3 indexed_tangents;
	//Vector3 indexed_bitangents;
	
    Texture* texture; // from Texture.h

	Matrix4 model;

	unsigned int vertexCount;
	unsigned int uvCount;
	unsigned int normalCount;
	unsigned int indexCount;

	int vertexBuffer;
	int uvBuffer;
	int normalBuffer;

} Model;

// Because the scope of this class does not exist
// when GraphicsHandler attempts to reference this,
// it gets absolutely nothing from this area. Consider
// actually moving Model data to there or somewhere else
// better.

#if defined(__cplusplus)
extern "C" {
#endif
Model LoadModel(const char*, const char*);
Model LoadOBJ(const char*);
void ReleaseModel();
#if defined(__cplusplus)
}
#endif

#endif // MODEL_H

