#version 330 core
in vec3 _Color;
in vec2 _TextureCoord;
out vec4 outColor;

uniform sampler2D _Texture;
void main() 
{
	outColor = texture(_Texture, _TextureCoord) * vec4(_Color, 1.0f);
}