#pragma once
#include "Camera.hpp"
#include "VissualObject.hpp"


#include  <memory>
#include  <vector>


class Scene
{
	std::vector<std::shared_ptr<Camera>> cameras_;

	std::vector<std::shared_ptr<IVissualObject>> objects_;

	void register_Camera(){};

	void register_VissualObject(){};




	
};

