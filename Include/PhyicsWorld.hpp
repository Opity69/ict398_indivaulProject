#pragma once
#include <iostream>
#include <vector>
#include "Transform.hpp"
#include <memory>
#include  "PhyicsTypesSystem.hpp"
#include  <glm3/glm/glm.hpp>
#include  <glm3/glm/gtc/quaternion.hpp>
#include "CollisonObject.hpp"


enum class BodyMode
{
	RIGID,
	STATIC
	
};

struct PostionState
{
	glm::fvec3 pos;
	glm::fquat rot;
	
};


struct BodyProps
{
	Mass mass;
	InteriaTensor tensor;
};

struct BodyState
{
	PostionState postion_state;
	LinearVelocity  linear_velocity;
	AngualrVelocity angualr_velocity;

	LinearAcceleration linear_acceleration;
	AngualrAcceleratiom angualr_acceleratiom;

	Toruge total_Torgue = {};
	Force  total_Force = {};
	
};


struct Body
{
	BodyProps props;
	BodyState state;

	std::shared_ptr<CollisonObject> collison;
	
	std::weak_ptr<TransFormable> object_; // Thing to act on
	
	void IntergrateForce(float timestep)
	{
		
	}
	void IntergrateVelocity(float  timestep){};

	std::shared_ptr<CollisonObject>& GetCollison()
	{
		
	}

	bool CheckSuspend()
	{
		return false;
	}

	void WriteBack()
	{
		if(!object_.expired())
		{
			auto ptr = object_.lock();
			if(ptr)
			{
				ptr->set_translation(state.postion_state.pos);
				ptr->set_rotation(state.postion_state.rot);
			}
		}
	}

	void CollisonSync()
	{
		if(collison)
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


	

	void Setup()
	{
		
	}

	void Solve()
	{
		
	}
	
};


class PhyicsWorld
{
	std::vector<std::shared_ptr<Body>> bodies_;
	//TODO() setup  sleeping
	//std::vector<std::shared_ptr<Body>> activeBodies;  //TOD() 
	std::vector<BodyPair> pairs_;
	

	



private:
	void SubStep(float TimeStep)
	{
		pairs_.clear();
		auto val =bodies_.size();

		Contact c;
		for (int i = 0; i < val; ++i)
		{
			for (int k = i+1; k < val; ++k)
			{

				//if(bodies_[i]->GetCollison()->Intersect(on_[k],c))
				//{
				//	//pairs_.push_back(BodyPair{c,collison_[i],collison_[k]})
				//}
			
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

		

		for (int i = 0; i <bodies_.size(); ++i)
		{

			bodies_[i]->WriteBack();
			bodies_[i]->CollisonSync();
		}
		
		
	}
public:
	PhyicsWorld()
	{
		
	}
	


	void Update(float TimeStep)
	{
		SubStep(TimeStep);
	}
	
	
};

