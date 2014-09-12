#include "Matrix4X1.h"


Matrix4X1::Matrix4X1()
{
	m_Matrix[0] = m_Matrix[1] = m_Matrix[2] = 0;
	m_Matrix[3] = 1;
}

Matrix4X1::Matrix4X1(Vector3D& inVector, const float& w)
{
	float vec3[3];
	inVector.GetDataInArray(vec3);
	for (int i = 0; i < 3; i++)
	{
		m_Matrix[i] = vec3[i];
	}
	m_Matrix[3] = w;
}

Matrix4X1::~Matrix4X1()
{
}


Matrix4X1 Matrix4X1::operator*(const float& value)
{
	for (int i = 0; i < 3; i++)
	{
		m_Matrix[i] *= value;
	}
	return *this;
}

Matrix4X1 Matrix4X1::Rotate(const float& angleInDegrees, const Vector3D& inAxis)
{
	/*float angleInRadians = DegreeToRadians(angleInDegrees);
	float x = this->m_Matrix[0];
	float y = this->m_Matrix[1];
	float z = this->m_Matrix[2];
	if (inAxis.x > 0.0f)
	{
		this->m_Matrix[0] = x;
		this->m_Matrix[1] = (cos(angleInRadians) * y) - (sin(angleInRadians) * z);
		this->m_Matrix[2] = (sin(angleInRadians) * y) + (cos(angleInRadians) * z);
	}
	else if (inAxis.y > 0.0f)
	{
		this->m_Matrix[0] = (cos(angleInRadians) * x) + (sin(angleInRadians) * z);
		this->m_Matrix[1] = y;
		this->m_Matrix[2] = (-sin(angleInRadians) * x) + (cos(angleInRadians) * z);
	}
	else if (inAxis.z > 0.0f)
	{
		this->m_Matrix[0] = (cos(angleInRadians) * x) - (sin(angleInRadians) * y);
		this->m_Matrix[1] = (sin(angleInRadians) * x) + (cos(angleInRadians) * y);
		this->m_Matrix[2] = z;
	}*/

	return *this;
}