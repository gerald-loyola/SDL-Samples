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

Matrix4X4::~Matrix4X4()
{

}

Matrix4X1 Matrix4X4::operator*(Vector3D& inVector)
{
	Matrix4X1 matrix4x1(inVector);
	return *this * matrix4x1;
}


Matrix4X1 Matrix4X4::operator*(Matrix4X1& inMatrix)
{
	Matrix4X1 outMatrix(Vector3D(0.0f, 0.0f, 0.0f), 0.0f);
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			outMatrix.m_Matrix[row] += (m_Matrix[row][col] * inMatrix.m_Matrix[col]);
		}
	}
	return outMatrix;
}

Matrix4X4 Matrix4X4::operator*(const float& value)
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			m_Matrix[row][col] *= value;
		}
	}
	m_Matrix[3][3] = 1.0f;
	return *this;
}

Matrix4X4 Matrix4X4::operator=(Matrix4X1& inMatrix)
{
	for (int row = 0; row < 4; row++)
	{
		m_Matrix[row][3] = inMatrix.m_Matrix[row];
	}
	return *this;
}


Matrix4X1 Matrix4X4::Translate(Vector3D& inVector)
{
	Matrix4X1 inMatrix(inVector);
	return *this * inMatrix;
}

Matrix4X4 Matrix4X4::Transpose()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = i+1; j < 4; j++)
		{
			float val = m_Matrix[i][j];
			m_Matrix[i][j] = m_Matrix[j][i];
			m_Matrix[j][i] = val;
		}
	}
	return *this;
}

