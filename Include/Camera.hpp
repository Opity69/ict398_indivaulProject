#pragma once

#include <Transform.hpp>
#include "UUID_Generator.hpp"


class Camera : public TransFormable
{
public:
	Camera(const Transform& trans, float near, float far, float fov, float aspect);


	[[nodiscard]] float get_near() const;
	void set_near(const float near);
	[[nodiscard]] float get_far() const;
	void set_far(const float far);
	[[nodiscard]] float get_fov() const;
	void set_fov(const float fov);
	[[nodiscard]] float get_aspect() const;
	void set_aspect(const float aspect);
private:
	UUID id;

	float near = 0.01;
	float far = 1000;
	float fov = 90;
	float aspect = 10;


	mutable glm::fmat4 ViewProjectionMatrix_Cache = {};
	mutable bool matrix_valid = false;


	void InvalidMatrix()
	{
		matrix_valid = false;
	}
	void ReCompute();

public:
	Camera();
	UUID getID() { return id; }

	float* matrixPtr();
};
