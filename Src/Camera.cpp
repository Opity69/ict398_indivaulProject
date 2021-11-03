#include "Camera.hpp"
#include <glm3/glm/gtc/type_ptr.hpp>

Camera::Camera(const Transform& trans, float near, float far, float fov, float aspect): TransFormable(trans),
	near(near),
	far(far),
	fov(fov),
	aspect(aspect)
{
}

float Camera::get_near() const
{
	return near;
	
}

void Camera::set_near(const float near)
{
	
	this->near = near;
	InvalidMatrix();
}

float Camera::get_far() const
{
	return far;
}

void Camera::set_far(const float far)
{
	this->far = far;
	InvalidMatrix();
}

float Camera::get_fov() const
{
	return fov;
}

void Camera::set_fov(const float fov)
{
	this->fov = fov;
}

float Camera::get_aspect() const
{
	return aspect;
}

void Camera::set_aspect(const float aspect)
{

	
	this->aspect = aspect;

	if(aspect < 0.01f || isfinite(aspect))
	{
		this->aspect =1;
	}
	
	InvalidMatrix();
}

void Camera::ReCompute()
{
	if (!matrix_valid || !isTransMatrixCacheValid())
	{
		if(aspect < 0.01)
		{
			aspect =1;
		}
		if(_isnanf(aspect))
		{
			aspect =1;
		}
		glm::fmat4 pro = glm::perspective<float>(glm::radians(fov), aspect, near, far);

		auto forward = this->localForward();
		auto eye = this->get_translation();
		auto up = this->localUP();

		glm::fmat4 view = glm::lookAt(eye, eye + forward, up);                          
		

		ViewProjectionMatrix_Cache = pro * view;
	}

	matrix_valid = true;
}

Camera::Camera() = default;

float* Camera::matrixPtr()
{
	ReCompute();
	return glm::value_ptr(ViewProjectionMatrix_Cache);
}
