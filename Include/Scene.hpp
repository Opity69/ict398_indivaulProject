#pragma once
#include "Camera.hpp"
#include "VissualObject.hpp"
#include "PhyicsWorld.hpp"


#include  <memory>
#include <string>

#include <unordered_map>
#include  <vector>


class Scene
{
	std::unordered_map<uint64_t ,std::weak_ptr<Camera>> cameras_;

	std::weak_ptr<Camera> currentCamera = {};


	std::unordered_map<uint64_t,std::shared_ptr<IVissualObject>> objects_;
	PhyicsWorld phyics_world_;

public:
	void register_Camera(std::shared_ptr<Camera>& camera);;
	void unregister_Camera(uint64_t id);;


	

	void SetCurrentCammera(uint64_t id);

	void register_VissualObject(std::shared_ptr<IVissualObject> vsObject);;
	void unregister_VissualObject(uint64_t id);;

	void register_PhyiscObject(std::shared_ptr<Body>& body);
	void unregister_PhyiscObject(UUID id);

	void LoadBodyFromTokens(const std::vector<std::string> input,size_t index)
	{
		auto& next = input[index];

		auto BodyType = std::stoi(next);
		float r = std::stof(input[++index]);
		float g = std::stof(input[++index]);
		float b = std::stof(input[++index]);
		float a = std::stof(input[++index]);


		//pos
		float p_x = std::stof(input[++index]);
		float p_y = std::stof(input[++index]);
		float p_z = std::stof(input[++index]);

		float p1 = std::stof(input[++index]);
		float p2 = std::stof(input[++index]);
		float p3 = std::stof(input[++index]);

		
	}
	void LoadCsv(const std::string& file_Path);

	void LoadBodies(const std::string& file_Path);
	void Draw();;

	void Update(float Timestep);
};

