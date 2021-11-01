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
	ccd_vec3_t dir, pos;
	int intersect = ccdGJKPenetration(objA.getBaseType(), objB.getBaseType(), &ccd, &depth, &dir, &pos);


	contact.depth = depth;
	contact.norm = {dir.v[0], dir.v[1], dir.v[2]};
	contact.pos = {pos.v[0], pos.v[1], pos.v[2]};
	return (intersect == 0);
}

bool CollisonObject::Intersect(const CollisonObject& other, Contact& contact) const
{
	if (this->GetAABB().intersect(other.GetAABB()))
	{
		if (InsectTest(*this, other, contact))
		{
			return true;
		}
	}

	return false;
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

