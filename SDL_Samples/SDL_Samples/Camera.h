#pragma once

#ifndef __CAMERA__
#define __CAMERA__

#ifndef __MATRIX4X4__
#include "Matrix4X4.h"
#endif

#include "Screen.h"

class Camera
{
public:
	Camera();
	~Camera();

	
	void SetProjectionMatrix(float fov, Screen screen, float nearPlane, float farPlane);
	Matrix4X4 GetProjectionMatrix();

private:
	Matrix4X4 m_Matrix;
	float m_Fov;
	float m_aspectRatio;
	float m_nearPlane;
	float m_farPlane;

	Matrix4X4 GetProjectionMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane);
};

#endif