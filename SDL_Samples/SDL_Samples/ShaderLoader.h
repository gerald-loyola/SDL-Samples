#pragma once

#ifndef __SHADER_LOADER__
#define __SHADER_LOADER__

#include <GL/glew.h>

class ShaderLoader
{

public:
	ShaderLoader(const char*, const char*);
	~ShaderLoader();

	void Apply();

	GLint m_programID;

private:
	bool CompileShader(const GLchar*, GLint shaderID);
};

#endif