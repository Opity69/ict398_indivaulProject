#pragma once

#include<glm3/glm/glm.hpp>
#include <glm3/glm/gtc/quaternion.hpp>
#include <glm3/glm/gtc/type_ptr.hpp>

class Transform
{
private:

	glm::fvec3 translation_;
	glm::fvec3 scale_;
	glm::fquat rotation_;


	
public:

	static  const  glm::fvec3 WorldForward;
	static const  glm::fvec3 WorldRight ;
	static const  glm::fvec3 WorldUp;

	
	glm::fvec3 get_translation() const;
	void set_translation(const glm::fvec3& translation);
	glm::fvec3 get_scale() const;
	void set_scale(const glm::fvec3& scale);
	glm::fquat get_rotation() const;
	void set_rotation(const glm::fquat& rotation);


	void Translate(glm::fvec3 Translation)
	{
		this->translation_ += Translation;
		InvalidMatrix();
	}

	void Scale(glm::fvec3 scale)
	{
		this->scale_ *= scale;
		InvalidMatrix();
	}

	void Rotate(glm::fquat rotation)
	{
		this->rotation_ =  rotation * rotation_; //TODO() check this is  correct
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

	bool CacheValid()
	{

		return ValidMatrix;
	}
	void RecomputeMatrix() const
	{
		glm::fmat4 t = glm::translate({},translation_)	;
		glm::fmat4 s = glm::scale({},scale_);
		glm::fmat4 r = glm::mat4_cast(rotation_);
		
		MatrixCache = t * s*r;
		//ValidMatrix = true;
	}


	glm::fmat4 GetTrasformMat()
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

class TransFormable
{
public:


private:
	Transform transform_;
protected:
	TransFormable(const Transform& trans);
	TransFormable():transform_(){}
	~TransFormable();
public:

	glm::fvec3 get_translation() const;
	void set_translation(const glm::fvec3& translation);
	glm::fvec3 get_scale() const;
	void set_scale(const glm::fvec3& scale);
	glm::fquat get_rotation() const;
	void set_rotation(const glm::fquat& rotation);


	void Translate(glm::fvec3 Translation);

	void Scale(glm::fvec3 scale);

	void Rotate(glm::fquat rotation);

	
	glm::fmat4 GetTrasformMatrix()
	{
		return  transform_.GetTrasformMat();
	}

	float* getMatrixPtr()
	{
		return  transform_.getMatrixPtr();
	}

	bool  isTransMatrixCacheValid()
	{
		return  transform_.CacheValid();
	}

	static glm::fvec3 getWorldForward()
	{
		return Transform::WorldForward;
	}

	static glm::fvec3 getWorldUp()
	{

		return  Transform::WorldUp;
		
	}

	static  glm::fvec3 getWorldRight()
	{
		return  Transform::WorldRight;
	}

	glm::fvec3 localForward()
	{
		auto rot_mat = glm::mat4_cast(transform_.get_rotation());
		glm::fvec4 v = {TransFormable::getWorldForward(),1};
		return  v * rot_mat;
		
	}

	glm::fvec3 localUP()
	{
		auto rot_mat = glm::mat4_cast(transform_.get_rotation());
		glm::fvec4 v = {TransFormable::getWorldUp(),1};
		return  v * rot_mat;
		
	}

	glm::fvec3 localRight()
	{
		auto rot_mat = glm::mat4_cast(transform_.get_rotation());
		glm::fvec4 v = {TransFormable::getWorldRight(),1};
		return  v * rot_mat;
		
	}
	
};
