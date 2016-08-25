#include "Shader.h"

Shader loadGLShader(const char* name, const char* vertexShaderPath, const char* fragmentShaderPath)
{
    //MakeContextCurrent();
	// Before ^^

    int vertShaderID = glCreateShader(GL_VERTEX_SHADER);
    int fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    FILE* fp; int count = 0;
    char* vertexShaderCode = NULL;
	fp = fopen(vertexShaderPath, "r");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        count = ftell(fp);
        rewind(fp);
        if (count > 0) {
            vertexShaderCode = (char*)malloc(sizeof(char)*(count+1));
            count = fread(vertexShaderCode, sizeof(char), count, fp);
            vertexShaderCode[count] = '\0';
        }
        fclose(fp);
	}
	else {
		fprintf(stderr, "Failed to open the shader: %s\nWill likely crash, enjoy.\n", vertexShaderPath);
	}
    fp = NULL; count = 0;
    char* fragmentShaderCode = NULL;
	fp = fopen(fragmentShaderPath, "r");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        count = ftell(fp);
        rewind(fp);
        if (count > 0) {
            fragmentShaderCode = (char*)malloc(sizeof(char)*(count+1));
            count = fread(fragmentShaderCode, sizeof(char), count, fp);
            fragmentShaderCode[count] = '\0';
        }
        fclose(fp);
    }
	else {
		fprintf(stderr, "Failed to open the shader: %s\nWill likely crash, enjoy.\n", fragmentShaderPath);
	}
    int Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader, Check Status
    char const * VertexSourcePointer = vertexShaderCode;
    glShaderSource(vertShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(vertShaderID);
    glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 1) {
        char* VertexShaderErrorMessage = (char*)malloc(InfoLogLength);
        glGetShaderInfoLog(vertShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        if (strcmp(&VertexShaderErrorMessage[0], ""))
            fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
        free(VertexShaderErrorMessage);
    }

    // Compile Fragment Shader, Check Status
    char const * FragmentSourcePointer = fragmentShaderCode;
    glShaderSource(fragShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(fragShaderID);
    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 1) {
        char* FragmentShaderErrorMessage = (char*)malloc(InfoLogLength);
        glGetShaderInfoLog(fragShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        if (strcmp(&FragmentShaderErrorMessage[0], ""))
            fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
        free(FragmentShaderErrorMessage);
    }

    // Link the program, Check Status
    int ProgramID = glCreateProgram();
    glAttachShader(ProgramID, vertShaderID);
    glAttachShader(ProgramID, fragShaderID);
    glLinkProgram(ProgramID);
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 1) {
        char* ProgramErrorMessage = (char*)malloc(InfoLogLength);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        if (strcmp(&ProgramErrorMessage[0], ""))
            fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
        free(ProgramErrorMessage);
    }

    glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);
	free(vertexShaderCode);
	free(fragmentShaderCode);

	// after vv
    //ClearContextCurrent();

    Shader shader = { name, ProgramID };

    return shader;
}

// Not implemented.
//Shader loadGLShader_s(char* name, char* shaderPath)
//{
//    shaderPath = 0;
//    Shader shader = { name, 0 };

//    // Not implemented yet. Requires special specifications.

//    return shader;
//}

Shader loadDX9Shader(char* name, char* vertexShaderPath, char* pixelShaderPath);
Shader loadDX11Shader(char* name, char* vertexShaderPath, char* pixelShaderPath);
