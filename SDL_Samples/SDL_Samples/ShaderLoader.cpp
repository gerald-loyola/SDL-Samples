#include "ShaderLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

ShaderLoader::ShaderLoader(const char* vertexShaderSrc, const char* fragmentShaderSrc)
{
	m_programID = -100;

	string shaderPath = "Resources\\Shaders\\";
	
	//open vertex file
	string vertexFilePath = shaderPath + vertexShaderSrc;
	ifstream vertexFile(vertexFilePath);
	if (vertexFile.fail())
		return;

	//open fragment file
	string fragmentFilePath = shaderPath + fragmentShaderSrc;
	ifstream fragmentFile(fragmentFilePath);
	if (fragmentFile.fail())
		return;

	stringstream vertexSrc, fragmentSrc;
	vertexSrc << vertexFile.rdbuf();
	fragmentSrc << fragmentFile.rdbuf();

	vertexFile.close();
	fragmentFile.close();

	GLuint vertexID, fragmentID;
	
	string vertexCode = vertexSrc.str();
	vertexID = glCreateShader(GL_VERTEX_SHADER);
	if (!CompileShader(vertexCode.c_str(), vertexID))
		return;

	string fragmentCode = fragmentSrc.str();
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	if (!CompileShader(fragmentCode.c_str(), fragmentID))
		return;
	
	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexID);
	glAttachShader(m_programID, fragmentID);
	glLinkProgram(m_programID);

	GLint sucess;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &sucess);
	if (!sucess)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

bool ShaderLoader::CompileShader(const GLchar* source, GLint shaderID)
{
	GLint success;
	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		//todo: Print the log

		return false;
	}
	return true;
}

void ShaderLoader::Apply()
{
	if (m_programID == -100)
	{
		//todo : print some error
		return;
	}
	glUseProgram(m_programID);
}


ShaderLoader::~ShaderLoader()
{

}