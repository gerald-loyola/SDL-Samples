#include "Matrix4X4.h"

Matrix4X4::Matrix4X4()
{
	float identityMatrix[4][4] = {
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
	};

	//copy the matrix
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			m_Matrix[row][col] = identityMatrix[row][col];
		}
	}
}

Matrix4X1 Matrix4X4::operator*(Vector3D& inVector)
{
	Matrix4X1 matrix4x1(inVector);
	return *this * matrix4x1;
}


Matrix4X1 Matrix4X4::operator*(Matrix4X1& inMatrix)
{
	Matrix4X1 outMatrix(Vector3D(0.0f, 0.0f, 0.0f));
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			outMatrix.m_Matrix[row] += (m_Matrix[row][col] * inMatrix.m_Matrix[col]);
		}
	}
	return outMatrix;
}