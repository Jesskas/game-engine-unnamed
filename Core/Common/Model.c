//
//
// 

#include "Common/Model.h"

Model LoadModel(const char* name, const char* filepath)
{
	// For now, just LoadOBJ() this.
	// Later this will be sophisticated and auto-detect
	// the file format simply from the char*.
	// But for now, just three-char filenames work.
	int i = strlen(filepath) - 1;
	while (filepath[i] != '.') {
		if (filepath[i] == 'j') {
			i--;
			if (filepath[i] == 'b') {
				i--;
				if (filepath[i] == 'o') {
					i--;
					if (filepath[i] == '.') {
						// yup, it's an obj file.
					}
				}
			}
		}
	}

	Model model = LoadOBJ(filepath);
	model.name = name;

	getIdentityMatrix(model.model);

	return model;
}

//
// TODO/Remarks:
// So far, I am not using indices to draw my elements. I will probably revise that soon.
// In the meantime, I'm not using the ideal variable assignment for Model.vertexCount.
//
Model LoadOBJ(const char* filepath)
{
	// temp placeholders; TODO: Get a better max, how to detect?
	unsigned int vertexIndices[1024], uvIndices[1024], normalIndices[1024];
	unsigned int indicesCount = 0;
	Vector3* temp_vertices = (Vector3*)malloc(SIZEOF_VEC3 * 1024);
	Vector2* temp_uvs = (Vector2*)malloc(SIZEOF_VEC2 * 1024);
	Vector3* temp_normals = (Vector3*)malloc(SIZEOF_VEC3 * 1024);
    unsigned int temp_verticesCount = 0, temp_normalsCount = 0, temp_uvsCount = 0;

	// load file
	FILE* fp;
	char* filetext = NULL;
	fp = fopen(filepath, "r");
	if (fp) {
		fseek(fp, 0, SEEK_END);
		int count = ftell(fp);
		rewind(fp);
		if (count > 0) {
			filetext = (char*)malloc(sizeof(char)*(count + 1));
			count = fread(filetext, sizeof(char), count, fp);
			filetext[count] = '\0';

			// Load Model from @filetext
			char* line;
			line = strtok(filetext, "\n");
			while (line != NULL) {
				//fprintf(stdout, "%s\n", line);
				// TODO: Handle other ones. Only handling needed ones now.
				// TODO: Out of bounds exception possible.
				if (line[0] == 'v') {
					if (line[1] == ' ') {
						float vertX = 0, vertY = 0, vertZ = 0;
						sscanf(line, "v %f %f %f", &vertX, &vertY, &vertZ);
						Vector3 temp = { vertX, vertY, vertZ };
						temp_vertices[temp_verticesCount][0] = temp[0];
						temp_vertices[temp_verticesCount][1] = temp[1];
						temp_vertices[temp_verticesCount][2] = temp[2];
						temp_verticesCount++;
					} else if (line[1] == 't') {
						// TODO: This problem is difficult. If you use a DDS texture,
						// the y-values are flipped; multiplied by -1. Intelligently,
						// that can't be done here. Maybe when assigning a texture,
						// if DDS, real-time flip the y's then.
						float uvX = 0, uvY = 0;
						sscanf(line, "vt %f %f", &uvX, &uvY);
						Vector2 temp = { uvX, -uvY };
						temp_uvs[temp_uvsCount][0] = temp[0];
						temp_uvs[temp_uvsCount][1] = temp[1];
						temp_uvsCount++;
					} else if (line[1] == 'n') {
						float normX = 0, normY = 0, normZ = 0;
						sscanf(line, "vn %f %f %f", &normX, &normY, &normZ);
						Vector3 temp = { normX, normY, normZ };
						temp_normals[temp_normalsCount][0] = temp[0];
						temp_normals[temp_normalsCount][1] = temp[1];
						temp_normals[temp_normalsCount][2] = temp[2];
						temp_normalsCount++;
					} else {}
				} else if (line[0] == 'f') {
					if (line[1] == ' ') {
						int vertexIndex0 = 0, vertexIndex1 = 0, vertexIndex2 = 0;
						int uvIndex0 = 0, uvIndex1 = 0, uvIndex2 = 0;
						int normalIndex0 = 0, normalIndex1 = 0, normalIndex2 = 0;

						if (sscanf(line,
							"f %d/%d/%d %d/%d/%d %d/%d/%d\n",
							&vertexIndex0, &uvIndex0, &normalIndex0,
							&vertexIndex1, &uvIndex1, &normalIndex1,
							&vertexIndex2, &uvIndex2, &normalIndex2) == 9)
						{
							vertexIndices[indicesCount] = vertexIndex0;
							vertexIndices[indicesCount+1] = vertexIndex1;
							vertexIndices[indicesCount +2] = vertexIndex2;
							
							uvIndices[indicesCount] = uvIndex0;
							uvIndices[indicesCount +1] = uvIndex1;
							uvIndices[indicesCount +2] = uvIndex2;
							
							normalIndices[indicesCount] = normalIndex0;
							normalIndices[indicesCount +1] = normalIndex1;
							normalIndices[indicesCount +2] = normalIndex2;
							
							indicesCount += 3;
						}
						else {
							fprintf(stderr, "ERROR: Invalid format. Must be -d/-d/-d -d/-d/-d -d/-d/-d format.\n"); exit(1);
						}
					}
				} else if (line[0] == 'o') {

				} else if (line[0] == 's') {

				} else if (line[0] == '#') {

				}

				line = strtok(NULL, "\n");
			}

			free(filetext);
		}
		else {
			fprintf(stdout, "Invalid model file."); exit(-1);
		}
		fclose(fp);
	}

    // For each vertex of each triangle
    // NOTE: Current implementation allocates enough space for
    //       the number of indices, now how many verts/uvs/norms
    //       there are.
    unsigned int i;
    Model model;
    model.indexCount = indicesCount;
    model.vertices = (Vector3*)malloc(SIZEOF_VEC3 * indicesCount);
    model.uvs =      (Vector2*)malloc(SIZEOF_VEC2 * indicesCount);
    model.normals =  (Vector3*)malloc(SIZEOF_VEC3 * indicesCount);
    for (i = 0; i < indicesCount; i++) {
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        Vector3 vertex, normal; Vector2 uv;
        vertex[0] = temp_vertices[vertexIndex-1][0];
        vertex[1] = temp_vertices[vertexIndex-1][1];
        vertex[2] = temp_vertices[vertexIndex-1][2];
        uv[0] =     temp_uvs[uvIndex-1][0];
        uv[1] =     temp_uvs[uvIndex-1][1];
        normal[0] = temp_normals[normalIndex-1][0];
        normal[1] = temp_normals[normalIndex-1][1];
        normal[2] = temp_normals[normalIndex-1][2];

        memcpy(model.vertices[i], &vertex, SIZEOF_VEC3);
        memcpy(model.uvs[i], &uv, SIZEOF_VEC2);
        memcpy(model.normals[i], &normal, SIZEOF_VEC3);
    }
    free(temp_vertices);
    free(temp_uvs);
    free(temp_normals);

    return model;
}


void ReleaseModel()
{
	// free the malloc'd things like vertices* too
	//for (int i = 0; i < models.size(); i++)
	//{
	//	free((void*)models[i].name);
	//
	//}
}
