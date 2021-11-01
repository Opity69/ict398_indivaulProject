#pragma once
#include <glm3/glm/glm.hpp>
#include <glm3/glm/gtx/norm.hpp>


typedef glm::fvec3 Vector_t;
typedef float Scalar_t;


class VectorType
{
protected:
	Vector_t value_;

public:
	void SetValue(const Vector_t& value)
	{
		value_ = value;
	}

	Vector_t Value() const
	{
		return value_;
	}

	Vector_t Direction()
	{
		return normalize(value_);
	}

	Scalar_t Lenght()
	{
		return glm::length(value_);
	}


protected:
	VectorType(const Vector_t& value): value_(value)
	{
	};

	VectorType(Scalar_t x, Scalar_t y, Scalar_t z): value_(x, y, z)
	{
	};
	~VectorType() = default;
};


class ScalarType
{
protected:
	Scalar_t value_ = 0;


public:
	void SetValue(Scalar_t value)
	{
		value_ = value;
	}

	float GetValue() const
	{
		return value_;
	}

protected:
	explicit ScalarType(Scalar_t value);
	ScalarType() = default;
	~ScalarType() = default;
};

class Mass : public ScalarType
{
public:
	explicit Mass(Scalar_t val): ScalarType(val)
	{
	}

	Mass(): ScalarType(1)
	{
	};
};


class InteriaTensor
{
	glm::fvec3 tensor = {};
};

struct LinearSpeed : public ScalarType
{
	LinearSpeed(Scalar_t speed): ScalarType(speed)
	{
	};
};

struct AngularSpeed : public ScalarType
{
	AngularSpeed(Scalar_t speed): ScalarType(speed)
	{
	};
};


struct DeltaTime : public ScalarType
{
	explicit DeltaTime(Scalar_t dt)
		: ScalarType(dt)
	{
	}
};


class Postion
{
	Vector_t pos_;


public:
	explicit Postion(Scalar_t x, Scalar_t y, Scalar_t z): pos_(x, y, z)
	{
	}

	Vector_t getDisplacementVector()
	{
		return pos_;
	}
};


class Velocity : public VectorType
{
protected:
	explicit Velocity(const Vector_t& vec): VectorType(vec)
	{
	}

	~Velocity() = default;


public:
};

class Accelleration : public VectorType
{
protected:
	explicit Accelleration(Scalar_t x, Scalar_t y, Scalar_t z): VectorType(x, y, z)
	{
	}

	~Accelleration() = default;
};


class LinearVelocity : public Velocity
{
public:
	LinearVelocity(Scalar_t x, Scalar_t y, Scalar_t z): Velocity({x, y, z})
	{
	}

	LinearVelocity() : Velocity({0, 0, 0})
	{
	};

	explicit LinearVelocity(const Vector_t& lin_vel): Velocity(lin_vel)
	{
	};

	LinearSpeed ToSpeed()
	{
		return LinearSpeed(glm::length(value_));
	}

	Vector_t ToDirection()
	{
		return Direction();
	}

	LinearVelocity& operator+=(const LinearVelocity& integrate);
};

class AngualrVelocity : public Velocity
{
public:
	AngualrVelocity(Scalar_t x, Scalar_t y, Scalar_t z): Velocity({x, y, z})
	{
	}

	AngualrVelocity(): Velocity({0, 0, 0})
	{
	};

	AngularSpeed ToSpeed()
	{
		return AngularSpeed(glm::length(value_));
	}

	Vector_t Axis()
	{
		return Direction();
	}
};

class LinearAcceleration : public Accelleration
{
public:
	LinearAcceleration(): Accelleration(0, 0, 0)
	{
	}


	LinearAcceleration(Scalar_t x, Scalar_t y, Scalar_t z): Accelleration(x, y, z)
	{
	}

	LinearVelocity Integrate(float timestep);
};

class AngualrAcceleratiom : public Accelleration
{

public:
	AngualrAcceleratiom(Scalar_t x, Scalar_t y, Scalar_t z): Accelleration(x, y, z)
	{
	}

	AngualrAcceleratiom(): Accelleration(0, 0, 0)
	{
	};
};

class Force : VectorType
{
public:
	Force(): VectorType(0, 0, 0)
	{
	}

	Force(const LinearAcceleration& acceleration, const Mass& mass): VectorType(acceleration.Value() * mass.GetValue())
	{
	}
};

class Toruge : VectorType
{
public:
	Toruge(): VectorType(0, 0, 0)
	{
	};

	Scalar_t Strength() const
	{
		return glm::length(value_);
	}

	Vector_t Axis()
	{
		return Direction();
	}
};


class PointForce : public VectorType
{
	PointForce(const Postion& pos, const Vector_t& force);
	Postion pointOfAppliaction{0, 0, 0};


	Scalar_t Strenght()
	{
		return Lenght();
	}

	Vector_t ToDirection()
	{
		return Direction();
	}


	Toruge getToruge(int a, int b)
	{
		return {};
	}

	Force getForce(const Mass& mass)
	{
		return {};
	}
};
