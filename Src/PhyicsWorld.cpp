#include "PhyicsWorld.hpp"

InteriaTensor computeTensorBox(const Mass& mass, const glm::fvec3& halfextends)
{
	auto extends = halfextends * 2.0f;
	
	float div = 1.0/12.0f;
	Scalar_t xx = div * mass.GetValue() *(extends.z *extends.z +  extends.x *extends.x);
	Scalar_t yy = div * mass.GetValue() *(extends.y *extends.y +  extends.x *extends.x);
	Scalar_t zz =  div * mass.GetValue() *(extends.z *extends.z +  extends.y *extends.y);
	return {xx, yy, zz};
}

InteriaTensor computeTensorSphere(const Mass& mass ,Scalar_t radius)
{
	float val = 2.0f/5.0f * mass.GetValue() *(radius* radius);
	return {val, val, val};
}

std::string BodyProps::ToString() const
{
	std::string out;
	out += "\nMass: ";
	out += std::to_string(mass.GetValue());
	out += "\n 1/mass: ";
	out += std::to_string(mass.getInv());

	out += "\nTesnor: ";
	out += VecToString(tensor.getTensor());
	out += "\n Tensor_inv: ";
	out += VecToString(tensor.getInv());

	return out;
}

std::string BodyState::ToString() const
{
	std::string out;
	out += "\nLinear Velocity: ";
	out += VecToString(linear_velocity.Value());
	out += "\nAngular Velocity: ";
	out += VecToString(angualr_velocity.Value());
	out += "\nPos: ";
	out += VecToString(postion_state.pos);


	return out;
}

float ComputeLamda(const BodyState& s1, const BodyProps& p1, const BodyState& s2, const BodyProps& p2, const Contact& c)
{
	float co_rest = 1;

	float epart = -(1 + co_rest);
	float linVelpart = dot(c.norm, (s1.linear_velocity.Value() - s2.linear_velocity.Value()));
	auto r1 =  c.pos - s1.postion_state.pos ;
	auto r2 =   c.pos  -s2.postion_state.pos;
	auto r1xn = cross(r1, c.norm);
	auto r2xn = cross(r2, c.norm);

	glm::fvec3 j1inv = p1.tensor.getInv();
	glm::fvec3 j2inv = p2.tensor.getInv();

	float angVel1 = dot(s1.angualr_velocity.Value(), r1xn);
	float angVel2 = dot(s2.angualr_velocity.Value(), r2xn);

	float numerator = epart * (linVelpart + (angVel1 - angVel2));

	float tesnorpart1 =
		dot((r1xn * j1inv), r1xn);
	float tesnorpart2 = dot((r2xn * j2inv), r2xn);

	float masspart = p1.mass.getInv() + p2.mass.getInv();

	float demoninator = masspart + tesnorpart1 + tesnorpart2;

	return numerator / demoninator;
}

void ImpluseApply(const Scalar_t& impluse, BodyState& state, const BodyProps& props, const Contact& c)
{
	auto& lin_vel = state.linear_velocity;
	auto& ang_vel = state.angualr_velocity;

	auto LamdaBig = impluse * c.norm;

	
	lin_vel = LinearVelocity(lin_vel.Value() + LamdaBig  * props.mass.getInv());


	auto r =  c.pos -state.postion_state.pos; //TODO() fix  aussming center of mass in center for now
	auto rxn = glm::cross(r, c.norm);

	ang_vel = AngualrVelocity(ang_vel.Value() + impluse*props.tensor.getInv() * rxn );
}
