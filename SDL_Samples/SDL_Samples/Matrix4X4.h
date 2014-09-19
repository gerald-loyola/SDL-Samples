#pragma once

#ifndef __MATRIX4X4__
#define __MATRIX4X4__

#ifndef __VECTOR_3D__
#include "Vector3D.h"
#endif

class Matrix4X4
{

public:
	Matrix4X4();
	~Matrix4X4();

	Matrix4X4 operator*(const float&);
	Matrix4X4 operator*(Matrix4X4&);
	Matrix4X4 operator=(Matrix4X4&);

	Matrix4X4 Translate(Vector3D&);
	Matrix4X4 Transpose();
	void Rotate(const float& angleInDegrees, const Vector3D& inAxis);
	
	float m_Matrix[4][4];
};

#endif