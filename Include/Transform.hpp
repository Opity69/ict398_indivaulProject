#pragma once

#include<glm3/glm/glm.hpp>
#include <glm3/glm/gtc/quaternion.hpp>
#include <glm3/glm/gtc/type_ptr.hpp>
#include <glm3/glm/gtx/quaternion.hpp>

class Transform
{
private:

	glm::fvec3 translation_  ={0,0,0}; 
	glm::fvec3 scale_ = {1,1,1};
	glm::fquat rotation_={1,0,0,0};


	
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
		this->rotation_ =  rotation * rotation_; //
		rotation_ = normalize(rotation_);
		InvalidMatrix();
	}

private:
	mutable glm::fmat4 MatrixCache;
	mutable bool ValidMatrix = false;

public:
	Transform(const glm::fvec3& trans ,const glm::fvec3& scale, const glm::fquat& rotation):translation_(trans),scale_(scale),rotation_(rotation)
	{
		
	}
	Transform(){};

	Transform& operator = (const  Transform& other)
	{
		translation_ = other.translation_;
		rotation_ = other.rotation_;
		scale_ = other.scale_;
		InvalidMatrix();
	} 
	
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
		glm::fmat4 id{1.0f};
		glm::fmat4 t = glm::translate(id,translation_)	;
		glm::fmat4 s = glm::scale(id,scale_);
		glm::fmat4 r = glm::mat4_cast(rotation_);
		
		MatrixCache = t*s*r ;
		ValidMatrix = true;
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


protected:
	Transform transform_;
protected:
	TransFormable(const Transform& trans);
	TransFormable():transform_(){}

	virtual  void OnTransform()
	{
		
	}
	
public:
    virtual  ~TransFormable(){};
	glm::fvec3 get_translation() const;
	void set_translation(const glm::fvec3& translation);
	glm::fvec3 get_scale() const;
	void set_scale(const glm::fvec3& scale);
	glm::fquat get_rotation() const;
	void set_rotation(const glm::fquat& rotation);


	void SetTransform(const Transform& transform)
	{
		this->transform_ =transform;
		OnTransform();
	}

	Transform getTransfrom() const
	{
		return  transform_;
	}

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
		glm::fvec4 v = {TransFormable::getWorldForward(),0};
		v =v*rot_mat;
		glm::fvec3 out ={ v.x,v.y,v.z};
		return  normalize(out);
		
	}

	glm::fvec3 localUP()
	{
	auto rot_mat = glm::mat4_cast(transform_.get_rotation());
		glm::fvec4 v = {TransFormable::getWorldUp(),0};
		v = v *rot_mat;
		glm::fvec3 out = v;
		return  normalize(out);
		
	}

	glm::fvec3 localRight()
	{
		auto rot_mat = glm::mat4_cast(transform_.get_rotation());
		
		glm::fvec4 v = {TransFormable::getWorldRight(),0};
		v = v*rot_mat;
		glm::fvec3 out = v;
		return  normalize(out);
		
		
	}
	
};
