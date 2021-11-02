#include "PhyicsWorld.hpp"

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

	float masspart = p1.mass.getInv() + p2.mass.GetValue();

	float demoninator = masspart + tesnorpart1 + tesnorpart2;

	return numerator / demoninator;
}

void ImpluseApply(const Scalar_t& impluse, BodyState& state, const BodyProps& props, const Contact& c)
{
	auto& lin_vel = state.linear_velocity;
	auto& ang_vel = state.angualr_velocity;

	auto LamdaBig = impluse * c.norm;

	lin_vel = LinearVelocity(lin_vel.Value() + LamdaBig * props.mass.GetValue());


	auto r =  c.pos -state.postion_state.pos; //TODO() fix  aussming center of mass in center for now
	auto rxn = glm::cross(r, c.norm);

	ang_vel = AngualrVelocity(ang_vel.Value() + props.tensor.getInv() * rxn);
}
