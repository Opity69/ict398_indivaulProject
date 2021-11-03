#include "CollisonObject.hpp"

void VecCopy(ccd_vec3_t* vec, const glm::fvec3& in)
{
	for (int i = 0; i < 3; ++i)
	{
		vec->v[i] = in[i];
	}
}

void QuatCopy(ccd_quat_t* quat, const glm::fquat& rot)
{
	for (int i = 1; i < 4; ++i)
	{
		quat->q[i - 1] = rot[i];
	}
	quat->q[3] = rot[0];
}

std::string VecToString(const glm::fvec3& vec)
{
	std::string out;
	out += "v:";
	for (int i = 0; i < 3; ++i)
	{
		out += std::to_string(vec[i]);
		out += ",";
	}
	out += "\t";
	return out;
}

std::string Contact::ToString() const
{
	std::string out;
	out += "\nPos: ";
	out += VecToString(pos);
	out += "\nnorm: ";
	out += VecToString(norm);
	out += "\ndepth: ";
	out += std::to_string(depth);
	return out;
}

bool InsectTest(const CollisonObject& objA, const CollisonObject& objB, Contact& contact)
{
	ccd_t ccd;
	CCD_INIT(&ccd); // initialize ccd_t struct

	// set up ccd_t struct
	ccd.support1 = ccdSupport; // support function for first object
	ccd.support2 = ccdSupport; // support function for second object
	ccd.max_iterations = 100; // maximal number of iterations
	ccd.epa_tolerance = 0.0001; // maximal tolerance fro EPA part

	ccd_real_t depth;
	depth = 0;
	ccd_vec3_t dir, pos;

	// Init just in case
	for (int i = 0; i < 3; ++i)
	{
		pos.v[i] =0;
	}
	for (int i = 0; i < 3; ++i)
	{
		dir.v[i] =0;
	}
	
	ccd_t ccd2;
	CCD_INIT(&ccd2); // initialize ccd_t struct

	// set up ccd_t struct
	ccd2.support1 = ccdSupport; // support function for first object
	ccd2.support2 = ccdSupport; // support function for second object
	ccd2.max_iterations = 50; // maximal number of iterations
	ccd2.epa_tolerance = 0.001; // maximal tolerance fro EPA part
	ccd2.center1        = ccdObjCenter;  // center function for first object
      ccd2.center2        = ccdObjCenter;  // center function for second object
      ccd2.mpr_tolerance  = 0.0001;

	  //TODO() figure out why this does work for this edge case
	//int intersect = ccdGJKPenetration(objA.getBaseType(), objB.getBaseType(), &ccd2, &depth, &dir, &pos);
	
	int intersect = ccdGJKPenetration(objA.getBaseType(), objB.getBaseType(), &ccd2, &depth, &dir, &pos);

	if(intersect != 0)
	{
		return false;
	}

	
	contact.depth = depth;
	contact.norm = {dir.v[0], dir.v[1], dir.v[2]};
	contact.pos = {pos.v[0], pos.v[1], pos.v[2]};
	contact.norm = contact.norm * 1.0f;

	for (int i = 0; i < 3; ++i)
	{
		float val = contact.norm[i];
		if(isinf(val) || isnan(val))
		{
			contact.norm = {0,1,0};
			__debugbreak();
		}
	}
	
	return  intersect ==0;
}

bool CollisonObject::Intersect(const CollisonObject& other, Contact& contact) const
{
	//if (this->GetAABB().intersect(other.GetAABB()))
	//{
	
	return  InsectTest(*this, other, contact);
	

}

float CSphere::get_radius() const
{
	return radius;
}

void CSphere::set_radius(const float radius)
{
	this->radius = radius;
	Setup();
}

void* CSphere::getBaseType() const
{
	return &sphereData;
}

void CSphere::OnTransform()
{
	Setup();
}

void* CBox::getBaseType() const
{
	return &boxData;
}

void CBox::OnTransform()
{
	Setup();
}
