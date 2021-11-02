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


enum class BodyMode
{
	RIGID,
	STATIC
};

struct PostionState
{
	glm::fvec3 pos = {};
	glm::fquat rot = {1,0,0,0};
};


struct BodyProps
{
	Mass mass_inv {1.0f};
	InteriaTensor tensor_inv;
};

struct BodyState
{
	PostionState postion_state = {};
	LinearVelocity linear_velocity = {};
	AngualrVelocity angualr_velocity = {};

	LinearAcceleration linear_acceleration;
	AngualrAcceleratiom angualr_acceleratiom;

	Toruge total_Torgue = {};
	Force total_Force = {};
};


struct Body
{
	Body(BodyMode mode, const BodyProps& props, const BodyState& state, const std::weak_ptr<TransFormable>& object)
		: mode(mode),
		  props(props),
		  state(state),
		  object_(object)
	{
	}



	
	
	BodyMode mode = BodyMode::RIGID;
	BodyProps props;
	BodyState state;

	std::shared_ptr<CollisonObject> collison;

	std::weak_ptr<TransFormable> object_; // Thing to act on

	void IntergrateForce(float timestep)
	{

		if(mode == BodyMode::STATIC)
		{
			return;
		}
	}

	void IntergrateVelocity(float timestep)
	{
		//state.linear_velocity += state.linear_acceleration.Integrate(timestep);  // TODO() add forces
		//state.angualr_velocity += state.angualr_acceleratiom.Integrate(timestep);


		if(mode == BodyMode::STATIC)
		{
			return;
		}
		
		state.postion_state.pos += state.linear_velocity.Value() * timestep;

		auto axis =  state.angualr_velocity.Direction();
		auto angle =state.angualr_velocity.Lenght();

		angle  *= timestep;
		if(fabs(angle) >0.0)
		{
			glm::fquat q = glm::angleAxis(angle,axis);

			state.postion_state.rot = q * state.postion_state.rot;
		}
		

		
	};

	void Exchange(Body& other, const Contact& c)
	{
		state.linear_velocity.SetValue(state.linear_velocity.Value()*-1.0f);
		state.angualr_velocity.SetValue(state.angualr_velocity.Value()*-1.0f);

		other.state.linear_velocity.SetValue(other.state.linear_velocity.Value()*-1.0f);
		other.state.angualr_velocity.SetValue(other.state.angualr_velocity.Value()*-1.0f);
	}

	void SetCollison(const std::shared_ptr<CollisonObject>& colision)
	{
		this->collison = colision;
	}

	std::shared_ptr<CollisonObject>& GetCollison()
	{
		return  collison;
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
			bodies_[i]->IntergrateForce(TimeStep);
			bodies_[i]->IntergrateVelocity(TimeStep);
		}


		for (int i = 0; i < bodies_.size(); ++i)
		{
			bodies_[i]->WriteBack();
			bodies_[i]->CollisonSync();
		}
	}

public:
	PhyicsWorld()
	{
	}


	void  AddBody(std::shared_ptr<Body>& body)
	{
		bodies_.push_back(body);
	}

	void Update(float TimeStep)
	{
		SubStep(TimeStep);
	}
};
