//
//
// 

#include "Texture.h"

Texture LoadTexture(const char* name, const char* filepath)
{
	// For now, just LoadDDS() this.
	// Later this will be sophisticated and auto-detect
	// the file format simply from the char*.
	// But for now, just three-char filenames work.
	int i = strlen(filepath) - 1;
	while (filepath[i] != '.') {
		if (filepath[i] == 's' || filepath[i] == 'S') {
			i--;
			if (filepath[i] == 'd' || filepath[i] == 'D') {
				i--;
				if (filepath[i] == 'd' || filepath[i] == 'D') {
					i--;
					if (filepath[i] == '.') {
						// yup, it's an dds file.
					}
				}
			}
		}
		else { break; }
	}

	Texture texture = LoadDDS(filepath);
	texture.name = name;

	return texture;
}

//
// TODO/Remarks:
// So far, I am not using indices to draw my elements. I will probably revise that soon.
// In the meantime, I'm not using the ideal variable assignment for Model.vertexCount.
//
Texture LoadDDS(const char* filepath)
{
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
    #define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
    #define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII
    unsigned char header[124];
    FILE *fp;
    /* try to open the file */
    fp = fopen(filepath, "rb");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: Failed to open DDS file.\n\n"); exit(1);
    }
    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        fprintf(stderr, "ERROR: DDS strncmp failed...\n\n"); exit(1);
    }

    fread(&header, 124, 1, fp);
    unsigned int height = *(unsigned int*)&(header[8]);
    unsigned int width = *(unsigned int*)&(header[12]);
    unsigned int linearSize = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC = *(unsigned int*)&(header[80]);
    unsigned char * buffer;
    unsigned int bufsize;

    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);

    fclose(fp);
    //unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;

    Texture texture;
    texture.filename = filepath;
    texture.extension = "TGA";
    texture.fourCC = fourCC;
    texture.Width = width;
    texture.Height = height;
    texture.mipMapCount = mipMapCount;
    texture.data = buffer;

    return texture;
}

//Texture LoadTGA(char* filepath)
//{
//	// Looking here:
//	// http://duriansoftware.com/joe/An-intro-to-modern-OpenGL.-Chapter-2.2:-Shaders.html
//	// and so here:
//	// https://github.com/jckarter/hello-gl/blob/master/util.c


//	Texture texture = { 0 };

//	return texture;
//}

void ReleaseTexture()
{
	// Free the following things:
	// Texture.buffer variable containing texture data
}
