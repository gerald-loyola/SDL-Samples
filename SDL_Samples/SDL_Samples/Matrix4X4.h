#pragma once
#include "Vector3D.h"
#include "Matrix4X1.h"

class Matrix4X4
{

public:
	Matrix4X4();
	~Matrix4X4();

	Matrix4X4 operator*(const float&);
	Matrix4X1 operator*(Vector3D&);
	Matrix4X1 operator*(Matrix4X1&);
	Matrix4X4 operator=(Matrix4X1&);

	Matrix4X1 Translate(Vector3D&);
	Matrix4X4 Transpose();
	
	float m_Matrix[4][4];
};