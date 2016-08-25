#version 130

in vec3 vertexPosition;
in vec2 vertexUV;
out vec2 UV;

uniform mat4 MVP;

void main(void)
{
    gl_Position = MVP * vec4(vertexPosition, 1.0);

    UV = vertexUV;
}
