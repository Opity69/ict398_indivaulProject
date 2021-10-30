#pragma once
#include <glm3/glm/glm.hpp>

typedef  int Transform;
class IVissualObject
{

	glm::fvec4 color;

	virtual void Draw() =0;
	virtual Transform get_transform_();
};



class Shpere : public  IVissualObject
{


	
};

class Box : public  IVissualObject
{


	
};

