#include "Scene.hpp"
#include "Glew/include/GL/glew.h"

void Scene::register_Camera(std::shared_ptr<Camera>& camera)
{
	cameras_.insert({camera->getID(), camera});
}

void Scene::unregister_Camera(uint64_t id)
{
	cameras_.erase(id);
}

void Scene::SetCurrentCammera(uint64_t id)
{
	if (cameras_.count(id))
		currentCamera = cameras_.at(id);
}

void Scene::unregister_VissualObject(uint64_t id)
{
	objects_.erase(id);
}

void Scene::register_VissualObject(std::shared_ptr<IVissualObject> vsObject)
{
	objects_.insert({vsObject->getID(), vsObject});
}

void Scene::Draw()
{
	glPushMatrix();

	glClearColor(0000.1f, 00.1f, 0.2f, 1);

	

	glEnable(GL_DEPTH_TEST);

	

	
	glMatrixMode(GL_PROJECTION);
	if (!currentCamera.expired())
	{
		auto cam = currentCamera.lock();

		if (cam)
		{
			glLoadMatrixf(cam->matrixPtr());
		}
	}
	


	for (auto& l_object : objects_)
	{
		auto elm = l_object.second;
		if (elm)
		{
			elm->Draw();
		}
	}


	glPopMatrix();
}

void Scene::Update(float Timestep)
{
	phyics_world_.Update(Timestep);
}
