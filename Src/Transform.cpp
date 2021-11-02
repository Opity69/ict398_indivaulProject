#include "Transform.hpp"



const glm::fvec3 Transform::WorldForward = {0,0,-1};
const glm::fvec3 Transform::WorldRight = {-1,0,0};
const glm::fvec3 Transform::WorldUp = {0,1,0};

glm::fvec3 Transform::get_translation() const
{
	return translation_;
}

void Transform::set_translation(const glm::fvec3& translation)
{
	translation_ = translation;
	InvalidMatrix();
}

glm::fvec3 Transform::get_scale() const
{
	return scale_;
}

void Transform::set_scale(const glm::fvec3& scale)
{
	scale_ = scale;
	InvalidMatrix();
}

glm::fquat Transform::get_rotation() const
{
	return rotation_;
	
}

void Transform::set_rotation(const glm::fquat& rotation)
{
	rotation_ = rotation;
	InvalidMatrix();
	
}

TransFormable::TransFormable(const Transform& trans): transform_(trans)
{
}

void TransFormable::Translate(glm::fvec3 Translation)
{
	transform_.Translate(Translation);
	OnTransform();
}

void TransFormable::Scale(glm::fvec3 scale)
{
	transform_.Scale(scale);
	OnTransform();
}

void TransFormable::Rotate(glm::fquat rotation)
{
	transform_.Rotate(rotation);
	OnTransform();
}

glm::fvec3 TransFormable::get_translation() const
{
	return  transform_.get_translation();
}

void TransFormable::set_translation(const glm::fvec3& translation)
{
	transform_.set_translation(translation);
	
	OnTransform();
}

glm::fvec3 TransFormable::get_scale() const
{
	return  transform_.get_scale();
}

void TransFormable::set_scale(const glm::fvec3& scale)
{
	 transform_.set_translation(scale);
	OnTransform();
}

glm::fquat TransFormable::get_rotation() const
{
	return  transform_.get_rotation();
}

void TransFormable::set_rotation(const glm::fquat& rotation)
{
	transform_.set_rotation(rotation);
	OnTransform();
}
