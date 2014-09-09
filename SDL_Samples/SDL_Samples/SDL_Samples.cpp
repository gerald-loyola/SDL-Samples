// SDL_Samples.cpp : Defines the entry point for the console application.
//

// Link statically with GLEW
#define GLEW_STATIC

#include <GL/glew.h>
#include <SDL.h>
#include <SOIL.h>

#define GLSL(src) "#version 330 core\n" # src

// Shader sources
const GLchar* vertexShaderSource = GLSL(
								layout (location = 0) in vec2 position;
								layout (location = 1) in vec3 color;
								layout (location = 2) in vec2 texCoord;
								out vec3 _Color;
								out vec2 _TextureCoord;
								void main() 
								{
									_Color = color;
									_TextureCoord = texCoord;
								   gl_Position = vec4(position.x, position.y, 0.0, 1.0);
								}
								);

const GLchar* fragmentShaderSource =  GLSL(
								in vec3 _Color;
								in vec2 _TextureCoord;
								out vec4 outColor;

								uniform sampler2D _Texture;
								void main() 
								{
									outColor = texture(_Texture, _TextureCoord) * vec4(_Color, 1.0f);
								}
								);

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_Window* window = SDL_CreateWindow("Sample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	//Create and compile Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Create and compile fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Link the shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	

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


	SDL_Event windowEvent;
	while (true)
	{
		if(SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
		}

		//clear screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//Draw triangle
		glUseProgram(shaderProgram);

		//BindTexture
		glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}

