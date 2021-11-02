#pragma once

#include <string>
#include  <glm3/glm/glm.hpp>
#include  "Transform.hpp"
#include  <ccd/ccd.h>
#include  <support_imp.h>


class CollisonObject;

struct AABB
{
	glm::fvec3 min ={};
	glm::fvec3 max ={};


	bool intersect(const AABB& other)
	{
		// TODO()  intersect aabb
		// Just ignore Broadphase
		return true;
		
	}
	AABB Rotate(const glm::fquat& rot)
	{
		return  {};
	}

	AABB Scale(const glm::fvec3 scale)
	{
		return  {};
	}

	AABB Translate(const glm::fvec3 transLate)
	{
		return  {};
	}

	AABB Transform(const glm::fvec3 translate, const glm::fvec3 scale,const glm::fquat rot)
	{
		return  {};
	}
	
	
};


void VecCopy(ccd_vec3_t* vec, const glm::fvec3& in);

void QuatCopy(ccd_quat_t* quat, const glm::fquat& rot);

std::string VecToString( const  glm::fvec3& vec)
{
	std::string out;
	out +="v:";
	for (int i = 0; i < 3; ++i)
	{
		out+=vec.x;
		out+=",";
	}
	out +="\t";
	return  out;
}


struct Contact
{
	glm::fvec3 pos;
	glm::fvec3 norm;
	float depth;

	std::string ToString() const
	{
		std::string out;
		out += "Pos:";
		out += VecToString(pos);
		out +="\tnorm";
		out += VecToString(norm);
		out +="\tdepth";
		out += depth;
		return out;
	}
};

bool InsectTest(const  CollisonObject& objA, const CollisonObject& objB, Contact& contact);


class CollisonObject : public TransFormable
{


	
protected:
mutable  AABB aabb_cachec;
public:
	explicit CollisonObject(const Transform& trans)
		: TransFormable(trans)
	{
	}

	AABB GetAABB() const
	{
		return  aabb_cachec;
	}

	virtual  void* getBaseType() const =0;

bool Intersect(const CollisonObject& other, Contact& contact) const;

protected:
	
};





struct CSphere :public  CollisonObject
{
	CSphere(const Transform& trans, float radius)
		: CollisonObject(trans),
		  radius(radius)
		 
	{
		Setup();
	}
	CSphere():CollisonObject({})
	{
		Setup();
	}


	void Setup()
	{
		sphereData.type = CCD_OBJ_SPHERE;
		VecCopy(&sphereData.pos,this->get_translation());
		QuatCopy(&sphereData.quat,this->get_rotation());
		sphereData.radius =radius;
	}

	[[nodiscard]] float get_radius() const;
	void set_radius(const float radius);
	float radius = 1;

	mutable  ccd_sphere_t sphereData;
	

	

	void* getBaseType() const override;
protected:
	void OnTransform() override;
};

struct CBox: public  CollisonObject
{
	CBox(const Transform& trans, const glm::fvec3& extends)
		: CollisonObject(trans),
		  extends(extends)
	{
		Setup();
	}
	

	

	glm::fvec3 extends;

protected:
	mutable  ccd_box_t boxData;


	void Setup()
	{
		boxData.type = CCD_OBJ_BOX;
		boxData.x = extends.x;
		boxData.y = extends.y;
		boxData.z = extends.z;

		VecCopy(&boxData.pos,this->get_translation());
		QuatCopy(&boxData.quat,this->get_rotation());

		
	}


public:
	void* getBaseType() const override;
protected:
	void OnTransform() override;
};


