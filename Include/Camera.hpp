#pragma once

#include <Transform.hpp>
#include "UUID_Generator.hpp"


class Camera : public TransFormable
{
public:
	Camera(const Transform& trans, float near, float far, float fov, float aspect);


private:
	UUID id;

	float near = 0.01;
	float far = 1000;
	float fov = 90;
	float aspect = 10;


	mutable glm::fmat4 ViewProjectionMatrix_Cache = {};
	mutable bool matrix_valid = false;


	void ReCompute();

public:
	Camera();
	UUID getID() { return id; }

	float* matrixPtr();
};
