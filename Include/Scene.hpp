#pragma once
#include "Camera.hpp"
#include "VissualObject.hpp"


#include  <memory>

#include <unordered_map>
#include  <vector>


class Scene
{
	std::unordered_map<uint64_t ,std::weak_ptr<Camera>> cameras_;

	std::weak_ptr<Camera> currentCamera = {};


	std::unordered_map<uint64_t,std::shared_ptr<IVissualObject>> objects_;

public:
	void register_Camera(std::shared_ptr<Camera>& camera);;
	void unregister_Camera(uint64_t id);;


	void SetCurrentCammera(uint64_t id);

	void register_VissualObject(std::shared_ptr<IVissualObject> vsObject);;
	void unregister_VissualObject(uint64_t id
	);;


public:
	void Draw();;


	
};

