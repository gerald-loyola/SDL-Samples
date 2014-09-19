#pragma once

#ifndef __TRANSFORM__
#define __TRANSFORM__

#ifndef __VECTOR_3D__
#include "Vector3D.h"
#endif

#ifndef __MATRIX4X4__
#include "Matrix4X4.h"
#endif

class Transform
{

public:
	Matrix4X4 GetTranslationMatrix();

	Vector3D position;
	Vector3D scale;
	Vector3D rotation;

private:
	Matrix4X4 transformationMatrix;
};

#endif