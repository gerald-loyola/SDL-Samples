#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 _Color;
out vec2 _TextureCoord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() 
{
	gl_Position =  projection * view *  model * vec4(position, 0.0, 1.0);

	_Color = color;
	_TextureCoord = texCoord;
}