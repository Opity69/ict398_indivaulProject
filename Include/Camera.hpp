#pragma once

#include <Transform.hpp>
#include <glm3/glm/gtc/type_ptr.hpp>
class Camera
{
	Transform transform_;
	float near = 0.01;
	float far  =1000;
	float ascept = 10;
	

	
	mutable  glm::fmat4 ViewProjectionMatrix_Cache;
	mutable  bool  matrix_valid = false;


public:
	float* matrixPtr()
	{

		return  glm::value_ptr(ViewProjectionMatrix_Cache);
	}

	

	
	

	
};

