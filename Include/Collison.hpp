#pragma once

#include  <glm3/glm/glm.hpp>
#include  "Transform.hpp"
class Collison
{
};



struct Sphere
{

	glm::fvec3 pos = {};
	float radius = 1;

	bool  intersect(const Sphere& other)
	{
		
	}
	
};

struct AABB
{
	glm::fvec3 min ={};
	glm::fvec3 max ={};


	bool intersect(const AABB& other)
	{
		// TODO()  intersect aabb
		
	}
	
};



class CollisonObject{

private:
	Transform transform_;


	
	// Cache

	mutable  AABB aabbCache;
	mutable  bool aabb_cachec_state =false;

	mutable  AABB RadiusCache;
	mutable  bool Radisu_cachec_state =false;

protected:
	void SetTransfrom(const Transform& t)
	{
		
		
	}

	Transform getTransform()const
	{

		return  transform_;
	}

public:

	virtual  AABB RecomputeAABB()
	{
		return  {};
	}

	virtual float  RecomputeRadius()
	{
		
	}
	
	virtual AABB  GetAABB()
	{
		return  {};
		
	}

	virtual Sphere ToSphere()
	{
		return  {};
	}


	virtual  glm::fvec3  SupportFunction(const glm::fvec3& dir) = 0;
	

	
};


class CollisonShpere : public  CollisonObject{
	float Radius;


};


class CollisonBox : public  CollisonObject{

	glm::fvec3 half_exents;


};

class Plane : public  CollisonObject
{
	glm::fvec3 points;

	mutable  glm::fvec3 normal_cache;
	mutable  bool normal_state = false;
	

	
};
