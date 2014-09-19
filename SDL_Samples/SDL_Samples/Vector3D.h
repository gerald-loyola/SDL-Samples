#pragma once

#ifndef __VECTOR_3D__
#define __VECTOR_3D__

class Vector3D
{
public:
	Vector3D();
	Vector3D(float, float);
	Vector3D(float, float, float);

	float* GetDataInArray(float *); // for openGL

	Vector3D operator+ (const Vector3D&);
	Vector3D operator* (const Vector3D&);
	Vector3D operator- (const Vector3D&);
	Vector3D operator/ (const Vector3D&);
	Vector3D operator= (const Vector3D&);

	Vector3D operator+ (const float&);
	Vector3D operator* (const float&);
	Vector3D operator- (const float&);
	Vector3D operator/ (const float&);
	Vector3D operator= (const float&);
		
	
	float Vector3D::GetMagnitude();
	float GetSqrMagnitude();
	void Normalize();
	Vector3D GetNormalizedVector();

	Vector3D Cross(Vector3D);
	float Dot(Vector3D);
		
	~Vector3D();

	float x, y, z;

	static Vector3D right;
	static Vector3D up;
	static Vector3D forward;
};

#endif
