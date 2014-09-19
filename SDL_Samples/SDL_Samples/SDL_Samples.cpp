// SDL_Samples.cpp : Defines the entry point for the console application.
//

// Link statically with GLEW
#define GLEW_STATIC

#include <GL/glew.h>
#include <SDL.h>
#include <SOIL.h>
#include "Matrix4X4.h"
#include "Matrix4X1.h"
#include "Vector3D.h"
#include "Math.h"
#include "ShaderLoader.h"
#include "Screen.h"
#include "Camera.h"


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	Screen mainScreen(800, 600);
	SDL_Window* window = SDL_CreateWindow("Sample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mainScreen._Width, mainScreen._Height, SDL_WINDOW_OPENGL);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	ShaderLoader shader("VertexShader\\DefaultVertex.vs", "FragmentShader\\DefaultFragment.frag");


	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);

	GLfloat vertices[] = { 
							0.0f, 0.5f,		1.0f, 0.0f, 0.0f,	0.50f, 1.0f,
							0.5f,-0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
							-0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
						};

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Specify layout for vertex data
	int vertexDataCount = 0;//0-postion,1-Color,2-UV
	//Position
	glVertexAttribPointer(vertexDataCount, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(vertexDataCount);
	
	//Color
	vertexDataCount++;
	glVertexAttribPointer(vertexDataCount, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(vertexDataCount);

	//UV
	vertexDataCount++;
	glVertexAttribPointer(vertexDataCount, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(vertexDataCount);

	glBindVertexArray(0);

	//generate texture
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Load image
	int width, height;
	unsigned char* image = SOIL_load_image("Resources\\Textures\\wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	if (image == NULL)
		return 0;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	Uint32 curFrameTime = SDL_GetTicks();
	Uint32 prevFrameTime;
	float deltaTime = 0.0f;
	float gameTime = 0.0f;

	const int MAX_FPS = 60;
	const float MAX_FPS_DT = MAX_FPS / 1000.0f;
	
	SDL_Event windowEvent;
	while (true)
	{
		if(SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
		}

		//calculate time
		prevFrameTime = curFrameTime;
		curFrameTime = SDL_GetTicks();
		
		deltaTime = (curFrameTime - prevFrameTime)/1000.0f;
		gameTime += deltaTime;

		//clear screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//Draw triangle
		shader.Apply();

		//BindTexture
		glBindTexture(GL_TEXTURE_2D, texture);

		//Create Trasnformation

		float scale = 0.25f;
		Matrix4X4 modelMatrix;
		modelMatrix.Rotate(gameTime * 500.0f, Vector3D::forward);
		modelMatrix = modelMatrix * scale;
		modelMatrix.Transpose();
		
		GLint modelID = glGetUniformLocation(shader.m_programID, "model");
		glUniformMatrix4fv(modelID, 1, GL_FALSE, *modelMatrix.m_Matrix);

		Matrix4X4 viewMatrix;
		Vector3D pos(2.0f, -1.0f, -5.0f);
		//viewMatrix = viewMatrix * scale;
		viewMatrix.Translate(pos);
		
		viewMatrix.Transpose();
		GLint viewID = glGetUniformLocation(shader.m_programID, "view");
		glUniformMatrix4fv(viewID, 1, GL_FALSE, *viewMatrix.m_Matrix);

		Camera camera;
		camera.SetProjectionMatrix(45.0f, mainScreen, 0.1f, 1000.0f);
		Matrix4X4 perspectiveMatrix = camera.GetProjectionMatrix();
		GLint projectionID = glGetUniformLocation(shader.m_programID, "projection");
		glUniformMatrix4fv(projectionID, 1, GL_FALSE, *perspectiveMatrix.m_Matrix);


		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}

