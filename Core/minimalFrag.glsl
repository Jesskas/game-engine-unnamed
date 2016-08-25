#version 130

in vec2 UV;
out vec4 out_Color;

uniform sampler2D diffuseTexture;

void main(void)
{
    out_Color = vec4( texture( diffuseTexture, UV ).rgb , 1.0 );
    //out_Color = vec4(0.0, 1.0, 1.0, 1.0);
}
