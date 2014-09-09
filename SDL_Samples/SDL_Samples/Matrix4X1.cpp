#include "Matrix4X1.h"


Matrix4X1::Matrix4X1()
{
	for (int i = 0; i < 4; i++)
	{
		m_Matrix[i] = 1;
	}
}

Matrix4X1::Matrix4X1(Vector3D& inVector)
{
	float* vec3 = inVector.GetArray();
	for (int i = 0; i < 3; i++)
	{
		m_Matrix[i] = vec3[i];
	}

	m_Matrix[3] = 1;//Set the 'W' always to 1;
}

Matrix4X1::~Matrix4X1()
{
}
