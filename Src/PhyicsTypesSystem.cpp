#include "PhyicsTypesSystem.hpp"

LinearVelocity& LinearVelocity::operator+=(const LinearVelocity& integrate)
{
	this->value_ += integrate.value_;
	return  *this;
}

LinearVelocity LinearAcceleration::Integrate(float timestep)
{
	return  LinearVelocity{this->Value() * timestep};
	
}
