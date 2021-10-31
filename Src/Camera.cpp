#include "Camera.hpp"
#include <glm3/glm/gtc/type_ptr.hpp>
Camera::Camera(const Transform& trans, float near, float far, float fov, float aspect): TransFormable(trans),
	near(near),
	far(far),
	fov(fov),
	aspect(aspect)
{
}

void Camera::ReCompute()
{
	if (!matrix_valid)
	{
		glm::fmat4 pro = glm::perspective<float>(fov, aspect, near, far);

		glm::fmat4 view = glm::lookAt(this->get_translation(), this->get_translation() + this->localForward(),
		                              this->localUP());

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
