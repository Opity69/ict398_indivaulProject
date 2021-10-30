#pragma once
#include <glm3/glm/glm.hpp>


class VectorType
{

protected:
	glm::fvec3 value_;


public:
	void SetValue(const glm::fvec3& value )
	{
		value_ =value;
	}

	glm::fvec3 Value() const
	{
		return value_;
	}

protected:
	explicit  VectorType(glm::fvec3);
	~VectorType()= default;
};



class ScalarType
{
	protected:
	float value_;


public:
	void SetValue(float value )
	{
		value_ =value;
	}

	float GetValue() const
	{
		return value_;
	}

protected:
	explicit  ScalarType(float value);
	~ScalarType()= default;
};


class Velocity : public VectorType
{

protected:
	explicit Velocity(const glm::fvec3& vec): VectorType(vec)
	{
		
	}
	~Velocity() = default;
	
};

class Accelleration : public VectorType
{

protected:
	explicit Accelleration(const glm::fvec3& vec): VectorType(vec)
	{
		
	}
	~Accelleration() = default;
	
};


class LinearVelocity : public  Velocity
{

	
};

class AngualrVelocity : public  Velocity
{

	
};


