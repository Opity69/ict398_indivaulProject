#pragma once

#include<glm3/glm/glm.hpp>
#include <glm3/glm/gtc/quaternion.hpp>
#include <glm3/glm/gtc/type_ptr.hpp>

class Transform
{
private:

	glm::fvec3 Transliotn_;
	glm::fvec3 Scale_;
	glm::fquat Rotation_;

public:
	glm::fvec3 get_transliotn() const;
	void set_transliotn(const glm::fvec3& transliotn);
	glm::fvec3 get_scale() const;
	void set_scale(const glm::fvec3& scale_rotation);
	glm::fquat get_rotation() const;
	void set_rotation(const glm::fquat& rotation);

	void Translate(glm::fvec3 Translation)
	{
		this->Transliotn_ += Translation;
		InvalidMatrix();
	}

	void Scale(glm::fvec3 scale)
	{
		this->Scale_ *= scale;
		InvalidMatrix();
	}

	void Rotate(glm::fquat rotation)
	{
		//TODO() Transform Rotation;
		InvalidMatrix();
	}

private:
	mutable glm::fmat4 MatrixCache;
	mutable bool ValidMatrix = false;

public:
	void InvalidMatrix() const
	{
		ValidMatrix = false;
	};

	void RecomputeMatrix() const
	{
		//TODO() setup Matrix for Transfrom
		//ValidMatrix = true;
	}


	glm::fmat4 GetTrasform()
	{
		if (!ValidMatrix)
		{
			RecomputeMatrix();
		}
		return MatrixCache;
	}

	float* getMatrixPtr()
	{
		if (!ValidMatrix)
		{
			RecomputeMatrix();
		}
		return  glm::value_ptr(MatrixCache);
	}
};
