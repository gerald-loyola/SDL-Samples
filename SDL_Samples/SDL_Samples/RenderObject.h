#pragma once

#ifndef __RENDERER__
#define __RENDERER__

#ifndef __SHADER_LOADER__
#include "ShaderLoader.h"
#endif

class Renderer
{

public:
	Renderer(){ }
	virtual ~Renderer(){}
	virtual void Draw(float dt) = 0;

	ShaderLoader *_ShaderLoader;
};

#endif