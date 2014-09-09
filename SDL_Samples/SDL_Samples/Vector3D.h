#pragma once


class Vector3D
{
public:
	Vector3D();
	Vector3D(float, float);
	Vector3D(float, float, float);

	inline float* GetArray(); // for openGL

	inline Vector3D operator+ (const Vector3D&);
	inline Vector3D operator* (const Vector3D&);
	inline Vector3D operator- (const Vector3D&);
	inline Vector3D operator/ (const Vector3D&);
	inline Vector3D operator= (const Vector3D&);

	inline Vector3D operator+ (const float&);
	inline Vector3D operator* (const float&);
	inline Vector3D operator- (const float&);
	inline Vector3D operator/ (const float&);
	inline Vector3D operator= (const float&);
		
	inline float GetMagnitude();
	inline float GetSqrMagnitude();
	inline void Normalize();
	inline Vector3D GetNormalizedVector();

	inline Vector3D Cross(Vector3D);
	inline float Dot(Vector3D);
		
	~Vector3D();

	float x, y, z;

};
