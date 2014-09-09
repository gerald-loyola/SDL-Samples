#pragma once
#include "Vector3D.h"

class  Matrix4X1
{
public:
	 Matrix4X1();
	 Matrix4X1(Vector3D&);
	~ Matrix4X1();

	inline Matrix4X1 operator*(Vector3D&);
	inline Matrix4X1 operator*(Matrix4X1&);

	float m_Matrix[4];
};
