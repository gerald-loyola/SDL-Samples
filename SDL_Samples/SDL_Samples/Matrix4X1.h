#pragma once

#include "Vector3D.h"

class  Matrix4X1
{
public:
	 Matrix4X1();
	 Matrix4X1(Vector3D&, const float&w = 1.0f);
	~ Matrix4X1();

	Matrix4X1 operator*(const float&);
	Matrix4X1 operator*(Vector3D&);
	Matrix4X1 operator*(Matrix4X1&);

	Matrix4X1 Rotate(const float&, const Vector3D&);

	float m_Matrix[4];
};
