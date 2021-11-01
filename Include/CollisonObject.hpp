#pragma once

#include  <glm3/glm/glm.hpp>
#include  "Transform.hpp"
#include  <ccd/ccd.h>
#include  <testsuites/support.h>


class CollisonObject;

struct AABB
{
	glm::fvec3 min ={};
	glm::fvec3 max ={};


	bool intersect(const AABB& other)
	{
		// TODO()  intersect aabb
		
	}
	AABB Rotate(const glm::fquat& rot)
	{
		
	}

	AABB Scale(const glm::fvec3 scale)
	{
		
	}

	AABB Translate(const glm::fvec3 transLate)
	{
		
	}

	AABB Transform(const glm::fvec3 translate, const glm::fvec3 scale,const glm::fquat rot)
	{
	
	}
	
	
};



struct Contact
{
	glm::fvec3 pos;
	glm::fvec3 norm;
	float depth;
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

	bool Intersect(const CollisonObject& other, Contact&  contact)
	{
		if(this->GetAABB().intersect(other.GetAABB()))
		{
			if(InsectTest(*this,other,contact))
			{
				return true;
			}
		}
		
		return false;
	}

protected:
	
};


bool InsectTest(const  CollisonObject& objA, const CollisonObject& objB, Contact& contact)
{
	ccd_t ccd;
      CCD_INIT(&ccd); // initialize ccd_t struct

      // set up ccd_t struct
      ccd.support1       = ccdSupport; // support function for first object
      ccd.support2       = ccdSupport; // support function for second object
      ccd.max_iterations = 100;     // maximal number of iterations
      ccd.epa_tolerance  = 0.0001;  // maximal tolerance fro EPA part

      ccd_real_t depth;
      ccd_vec3_t dir, pos;
	 int intersect = ccdGJKPenetration(objA.getBaseType(), objB.getBaseType(), &ccd, &depth, &dir, &pos);


	contact.depth =depth;
	contact.norm = {dir.v[0],dir.v[1],dir.v[2]};
	contact.pos = {pos.v[0],pos.v[1],pos.v[2]};
	return (intersect  == 0);
}



struct Sphere :public  CollisonObject
{
	[[nodiscard]] float get_radius() const;
	void set_radius(const float radius);
	float radius = 1;

	 mutable  CCD_SPHERE(sphereData);
	

	

	void* getBaseType() const override;
protected:
	void OnTransform() override;
};

struct Box: public  CollisonObject
{
	glm::fvec3 extends;
	mutable  CCD_BOX(box_data);


	
};


