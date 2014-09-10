#include "Vector3D.h"
#include <math.h>

Vector3D Vector3D::right = Vector3D(1.0f, 0.0f, 0.0f);
Vector3D Vector3D::up = Vector3D(0.0f, 1.0f, 0.0f);
Vector3D Vector3D::forward = Vector3D(0.0f, 0.0f, 1.0f);


Vector3D::Vector3D()
{
	x = y = z = 0.0f;
}

Vector3D::Vector3D(float X, float Y)
{
	x = X;
	y = Y;
	z = 0.0f;
}

Vector3D::Vector3D(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

float* Vector3D::GetDataInArray(float *arr)
{
	arr[0] = x;
	arr[1] = y;
	arr[2] = z;
	return arr;
}

Vector3D Vector3D::operator+(const Vector3D& inVector)
{
	return Vector3D(x + inVector.x, y + inVector.y, z + inVector.z);
}

Vector3D Vector3D::operator-(const Vector3D& inVector)
{
	return Vector3D(x - inVector.x, y - inVector.y, z - inVector.z);
}

Vector3D Vector3D::operator*(const Vector3D& inVector)
{
	return Vector3D(x * inVector.x, y * inVector.y, z * inVector.z);
}

Vector3D Vector3D::operator/(const Vector3D& inVector)
{
	return Vector3D(x / inVector.x, y / inVector.y, z / inVector.z);
}

Vector3D Vector3D::operator=(const Vector3D& inVector)
{
	this->x = inVector.x;
	this->y = inVector.y;
	this->z = inVector.z;
	return *this;
}

Vector3D Vector3D::operator+(const float& value)
{
	return Vector3D(x + value, y + value, z + value);
}

Vector3D Vector3D::operator-(const float& value)
{
	return Vector3D(x - value, y - value, z - value);
}

Vector3D Vector3D::operator*(const float& value)
{
	return Vector3D(x * value, y * value, z * value);
}

Vector3D Vector3D::operator/(const float& value)
{
	return Vector3D(x / value, y / value, z / value);
}

float Vector3D::GetMagnitude()
{
	return sqrt(GetSqrMagnitude());
}

float Vector3D::GetSqrMagnitude()
{
	return (x*x) + (y*y) + (z*z);
}

void Vector3D::Normalize()
{
	*this = GetNormalizedVector();
}

Vector3D Vector3D::GetNormalizedVector()
{
	return *this / this->GetMagnitude();
}

Vector3D Vector3D::Cross(Vector3D inVector)
{
	return Vector3D((y * inVector.z) - (z * inVector.y), (z * inVector.x) - (x * inVector.z), (x * inVector.y) - (y * inVector.x));
}

float Vector3D::Dot(Vector3D inVector)
{
	Vector3D firstVector = this->GetNormalizedVector();
	Vector3D secondVector = inVector.GetNormalizedVector();

	float value = (firstVector.x * secondVector.x) + (firstVector.y * secondVector.y) + (firstVector.z * secondVector.z);
	return acos(value);
}

Vector3D::~Vector3D()
{

}