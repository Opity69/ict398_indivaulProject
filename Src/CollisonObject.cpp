#include "CollisonObject.hpp"

float Sphere::get_radius() const
{
	return radius;
}

void Sphere::set_radius(const float radius)
{
	this->radius = radius;
	sphereData.radius = this->radius;
}

void* Sphere::getBaseType() const
{
	return &sphereData;
}

void Sphere::OnTransform()
{
	auto trans  = this->get_translation();
	for (int i = 0; i < 3; ++i)
	{
		sphereData.pos.v[i] =trans[i];
	}

	for (int i = 0; i < 3; ++i)
	{
		sphereData.pos.v[i] =trans[i];
	}

}
