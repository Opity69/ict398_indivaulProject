#pragma once
#include "Camera.hpp"
#include "VissualObject.hpp"
#include "PhyicsWorld.hpp"


#include  <memory>
#include <string>

#include <unordered_map>
#include  <vector>


float FloatorZero(const std::string& s);


struct ProjectileData
{

	glm::fvec3 resetpos = {};
	glm::fvec3 dir ={0,-1,0};
	float scale =1;
	std::weak_ptr<Body> projectile = {};

private:
	bool fired =false;

public:
	[[nodiscard]] bool is_fired() const;
	
	ProjectileData()= default;

	ProjectileData(std::weak_ptr<Body> projectile):projectile(projectile)
	{
		if(!this->projectile.expired())
		{
			auto ptr =projectile.lock();
			if(ptr)
			{
				resetpos = ptr->state.postion_state.pos;
			}
		}
		
	};
	
	
	void Reset()
	{
		if(!projectile.expired())
		{
			auto ptr =projectile.lock();
			if(ptr)
			{
				ptr->state.linear_velocity = {};
				ptr->state.angualr_velocity = {};

				ptr->state.postion_state.pos= resetpos;
			}
		}
		fired =false;
		
	}

	void Fire()
	{
		if(!is_fired())
		{
			if(!projectile.expired())
		{
			auto ptr =projectile.lock();
			if(ptr)
			{
				ptr->state.linear_velocity = LinearVelocity(dir * scale);
			

				
			}
		}
		fired =true;
		}
		
	}

	
};


class Scene
{
	std::unordered_map<uint64_t, std::weak_ptr<Camera>> cameras_;

	std::weak_ptr<Camera> currentCamera = {};
	
	


	std::unordered_map<uint64_t, std::shared_ptr<IVissualObject>> objects_;
	PhyicsWorld phyics_world_;

public:
	// bit hacky
	ProjectileData projectile_data;
	
	void register_Camera(std::shared_ptr<Camera>& camera);
	void unregister_Camera(uint64_t id);;

	void loadFromTokens(std::vector<std::string>& tokens);


	void SetCurrentCammera(uint64_t id);

	void register_VissualObject(std::shared_ptr<IVissualObject> vsObject);;
	void unregister_VissualObject(uint64_t id);;

	void register_PhyiscObject(std::shared_ptr<Body>& body);
	void unregister_PhyiscObject(UUID id);

	void SetupProject()
	{
		
	}

	void LoadCsv(const std::string& file_Path);

	void Draw();

	void Update(float Timestep);
};
