#include "Transform.hpp"

glm::fvec3 Transform::get_transliotn() const
{
	return Transliotn;
}

void Transform::set_transliotn(const glm::fvec3& transliotn)
{
	Transliotn = transliotn;
	InvalidMatrix();
}

glm::fvec3 Transform::get_scale_rotation() const
{
	return ScaleRotation;
}

void Transform::set_scale_rotation(const glm::fvec3& scale_rotation)
{
	ScaleRotation = scale_rotation;
	InvalidMatrix();
}

glm::fquat Transform::get_rotation() const
{
	return Rotation;
}

void Transform::set_rotation(const glm::fquat& rotation)
{
	Rotation = rotation;
	InvalidMatrix();
}
