#include "Matrix4X4.h"

#include <math.h>

#ifndef __UTILITY__
#include "Utilities.h";
#endif



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

Matrix4X4 Matrix4X4::operator*(Matrix4X4& inMatrix)
{
	Matrix4X4 outMatrix;
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			float value = 0.0f;
			for (int j = 0; j < 4; j++)
			{
				value += m_Matrix[row][j] * inMatrix.m_Matrix[j][col];
			}
			outMatrix.m_Matrix[row][col] = value;
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


Matrix4X4 Matrix4X4::operator=(Matrix4X4& inMatrix)
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			m_Matrix[row][col] = inMatrix.m_Matrix[row][col];
		}
	}
	return *this;
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


void Matrix4X4::Rotate(const float& angleInDegrees, const Vector3D& inAxis)
{
	float angleInRadians = Utilities::DegreeToRadians(angleInDegrees);
	float cosT = cos(angleInRadians);
	float sinT = sin(angleInRadians);
	float T = 1 - cosT;
	
	float x = inAxis.x;
	float y = inAxis.y;
	float z = inAxis.z;

	float rotationData[4][4] = {
									{		 (T *x * x) + cosT,			(T * x * y) - (sinT * z),		(T * x * z) + (sinT * y),	0.0f },
									{ (T * x * y) + (sinT * z),				  (T * y * y) + cosT,		(T * y * z) - (sinT * x),	0.0f },
									{ (T * x * z) - (sinT * y),			(T * y * z) + (sinT * x),			  (T * z * z) + cosT,	0.0f },
									{					  0.0f,								0.0f,							0.0f,	1.0f }
								};


	Matrix4X4 rotMatrix;
	//copy the matrix
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			rotMatrix.m_Matrix[row][col] = rotationData[row][col];
		}
	}

	*this = rotMatrix * *this;
}
