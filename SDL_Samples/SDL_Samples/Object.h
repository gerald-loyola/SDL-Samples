#pragma once

#ifndef __OBJECT__
#define __OBJECT__

#include "ShaderLoader.h"

class Object
{

public:
	Object(){}
	virtual ~Object(){}
	virtual void Update(float dt) = 0;

	int _ObjectType = 0; 
};

#endif