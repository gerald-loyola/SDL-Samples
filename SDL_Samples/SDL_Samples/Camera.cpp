#include "Camera.h"
#include <math.h>

#ifndef __UTILITY__
#include "Utilities.h";
#endif

Camera::Camera()
{

}

Camera::~Camera()
{

}

Matrix4X4 Camera::GetProjectionMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
	Matrix4X4 outMatrix;
	outMatrix.m_Matrix[0][0] = 2 * nearPlane / (right - left);
	outMatrix.m_Matrix[0][1] = 0;
	outMatrix.m_Matrix[0][2] = 0;
	outMatrix.m_Matrix[0][3] = 0;

	outMatrix.m_Matrix[1][0] = 0;
	outMatrix.m_Matrix[1][1] = 2 * nearPlane / (top - bottom);
	outMatrix.m_Matrix[1][2] = 0;
	outMatrix.m_Matrix[1][3] = 0;

	outMatrix.m_Matrix[2][0] = (right + left) / (right - left);
	outMatrix.m_Matrix[2][1] = (top + bottom) / (top - bottom);
	outMatrix.m_Matrix[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
	outMatrix.m_Matrix[2][3] = -1;

	outMatrix.m_Matrix[3][0] = 0;
	outMatrix.m_Matrix[3][1] = 0;
	outMatrix.m_Matrix[3][2] = -2 * farPlane * nearPlane / (farPlane - nearPlane);
	outMatrix.m_Matrix[3][3] = 1;
	return outMatrix;
}

void Camera::SetProjectionMatrix(float fov, Screen screen, float nearPlane, float farPlane)
{
	m_Fov = fov;
	m_aspectRatio = (float)screen._Width/ (float)screen._Height;
	m_farPlane = farPlane;
	m_nearPlane = nearPlane;

	float scale = tan(Utilities::DegreeToRadians(fov * 0.5f)) * nearPlane;
	float right = m_aspectRatio * scale;
	float left = -right;
	float top = scale;
	float bottom = -top;

	m_Matrix = GetProjectionMatrix(left, right, bottom, top, nearPlane, farPlane);
}

Matrix4X4 Camera::GetProjectionMatrix()
{
	return m_Matrix;
}