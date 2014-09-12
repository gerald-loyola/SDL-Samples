#pragma once

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