#include "PhyicsTypesSystem.hpp"

ScalarType::ScalarType(Scalar_t value): value_(value)
{
}

LinearVelocity& LinearVelocity::operator+=(const LinearVelocity& integrate)
{
	this->value_ += integrate.value_;
	return  *this;
}

AngualrVelocity::AngualrVelocity(const glm::fvec3& vec) :Velocity(vec)
{
}

LinearVelocity LinearAcceleration::Integrate(float timestep)
{
	return  LinearVelocity{this->Value() * timestep};
	
}
