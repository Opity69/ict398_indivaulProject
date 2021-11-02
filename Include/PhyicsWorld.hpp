#pragma once
#include <iostream>
#include <vector>
#include "Transform.hpp"
#include <memory>
#include  "PhyicsTypesSystem.hpp"
#include  <glm3/glm/glm.hpp>
#include  <glm3/glm/gtc/quaternion.hpp>
#include "CollisonObject.hpp"
#include <unordered_map>

#include "UUID_Generator.hpp"


enum class BodyMode
{
	RIGID,
	STATIC
};

struct PostionState
{
	glm::fvec3 pos = {0, 0, 0};
	glm::fquat rot = {1, 0, 0, 0};
};


struct BodyProps
{
	Mass mass{1.0f};
	InteriaTensor tensor = {1, 1, 1};

	std::string ToString() const
	{
		std::string out;
		out += "Mass: ";
		out += mass.GetValue();
		out += "\t Mass_inv: ";
		out += mass.getInv();

		out += "\tTesnor: ";
		out += VecToString(tensor.getTensor());
		out += "\t Tensor_inv: ";
		out += VecToString(tensor.getInv());

		return out;

		
		
	}
};

struct BodyState
{
	PostionState postion_state = {};
	LinearVelocity linear_velocity = {0, 0, 0};
	AngualrVelocity angualr_velocity = {0, 0, 0};

	LinearAcceleration linear_acceleration = {0, 0, 0};
	AngualrAcceleratiom angualr_acceleratiom = {0, 0, 0};

	Toruge total_Torgue = {};
	Force total_Force = {};
};


float ComputeLamda(const BodyState& s1, const BodyProps& p1, const BodyState& s2, const BodyProps& p2,
                   const Contact& c);


void ImpluseApply(const Scalar_t& impluse, BodyState& state, const BodyProps& props, const Contact& c);


struct Body
{


	std::string  tag= {"Empty"};
	UUID id;
	Body(BodyMode mode, const BodyProps& props, const BodyState& state, const std::weak_ptr<TransFormable>& object)
		: mode(mode),
		  props(props),
		  state(state),
		  object_(object)
	{
	}

	UUID BodyID() const
	{
		return  id;
	}
	
	void setState(const BodyState& state)
	{
		this->state = state;
	}

	BodyState& ModiftyState()
	{
		return this->state;
	}

	BodyState getState() const
	{
		return state;
	}


	BodyMode mode = BodyMode::RIGID;
	BodyProps props;
	BodyState state;

	std::shared_ptr<CollisonObject> collison;

	std::weak_ptr<TransFormable> object_; // Thing to act on

	void IntergrateForce(float timestep)
	{
		if (mode == BodyMode::STATIC)
		{
			return;
		}
	}

	void IntergrateVelocity(float timestep)
	{
		//state.linear_velocity += state.linear_acceleration.Integrate(timestep);  // TODO() add forces
		//state.angualr_velocity += state.angualr_acceleratiom.Integrate(timestep);


		if (mode == BodyMode::STATIC)
		{
			return;
		}

		state.postion_state.pos += state.linear_velocity.Value() * timestep;

		auto axis = state.angualr_velocity.Direction();
		auto angle = state.angualr_velocity.Lenght();

		angle *= timestep;
		if (fabs(angle) > 0.0 && !isinf(angle))
		{
			glm::fquat q = glm::angleAxis(angle, axis);

			state.postion_state.rot = q * state.postion_state.rot;
		}
	};

	void Exchange(Body& other, const Contact& c)
	{
		float fudge = 0.2f;

		std::cout << "Contact Between:" << this->tag << "::" << other.tag << "\tContact:" << c.ToString();
		
		

		float impluse = ComputeLamda(this->getState(), this->props, other.getState(), other.props, c);
		// Exchange

		if (mode != BodyMode::STATIC)
		{
			ImpluseApply(impluse, this->ModiftyState(), this->props, c);
		}


		if (other.mode != BodyMode::STATIC)
		{
			ImpluseApply(-impluse, other.ModiftyState(), other.props, c);
		}

		float wieghtA = 0.5, wieghtB = 0.5;


		if(this->mode == BodyMode::STATIC)
		{
			wieghtA =0;
			wieghtB =1;
		}else
		{
			if(other.mode == BodyMode::STATIC)
			{
				wieghtB = 0;
				wieghtA = 1;
			}
		}

		this->state.postion_state.pos += -c.norm * wieghtA * (c.depth + fudge);

		other.state.postion_state.pos += c.norm * wieghtB * (c.depth + fudge);
	}

	void SetCollison(const std::shared_ptr<CollisonObject>& colision)
	{
		this->collison = colision;
	}

	std::shared_ptr<CollisonObject>& GetCollison()
	{
		return collison;
	}

	bool CheckSuspend()
	{
		return false;
	}

	void WriteBack()
	{
		if (!object_.expired())
		{
			auto ptr = object_.lock();
			if (ptr)
			{
				ptr->set_translation(state.postion_state.pos);
				ptr->set_rotation(state.postion_state.rot);
			}
		}
	}

	void CollisonSync()
	{
		if (collison)
		{
			collison->set_translation(state.postion_state.pos);
			collison->set_rotation(state.postion_state.rot);
		}
	}
};


#define  MAX_CONTACTS  4

struct BodyPair
{
	Contact contact;
	std::shared_ptr<Body> A;
	std::shared_ptr<Body> B;

	void Solve()
	{
		if (A && B)
		{
			A->Exchange(*B.get(), contact);
		}
	}
};


class PhyicsWorld
{
	std::vector<std::shared_ptr<Body>> bodies_;
	std::vector<BodyPair> pairs_;


private:
	void SubStep(float TimeStep)
	{
		pairs_.clear();
		auto val = bodies_.size();

		Contact c;
		for (size_t i = 0; i < val; ++i)
		{
			bodies_[i]->CollisonSync();
			for (size_t k = i + 1; k < val; ++k)
			{
				if (bodies_[i]->GetCollison() && bodies_[k]->GetCollison())
				{
					if (bodies_[i]->GetCollison()->Intersect(*bodies_[k]->GetCollison(), c))
					{
						pairs_.push_back(BodyPair{c, bodies_[i], bodies_[k]});
					}
				}
			}
		}

		for (int i = 0; i < pairs_.size(); ++i)
		{
			pairs_[i].Solve();
		}

		for (int i = 0; i < bodies_.size(); ++i)
		{
			if (bodies_[i]->mode == BodyMode::STATIC)
			{
				continue;
			}
			bodies_[i]->IntergrateForce(TimeStep);
			bodies_[i]->IntergrateVelocity(TimeStep);
			bodies_[i]->WriteBack();
			bodies_[i]->CollisonSync();
		}
	}

public:
	PhyicsWorld()
	{
	}


	void AddBody(std::shared_ptr<Body>& body)
	{
		bodies_.push_back(body);
		bodies_.back()->WriteBack();
		bodies_.back()->CollisonSync();
	}

	void Update(float TimeStep)
	{
		SubStep(TimeStep);
	}
};
