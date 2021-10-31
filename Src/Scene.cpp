#include "Scene.hpp"
#include "Glew/include/GL/glew.h"

void Scene::register_Camera(std::shared_ptr<Camera>& camera)
{
	cameras_.insert({camera->getID(),camera});
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

void Scene::register_VissualObject(std::shared_ptr<IVissualObject>& vsObject)
{
	objects_.insert({vsObject->getID(),vsObject});
}

void Scene::Draw()
{

	
	glClearColor(1,0,0,0);

	glBegin(GL_TRIANGLES);
	glColor4f(1,1,1,1);
	glVertex3f(-0.2,-0.2,0);
	glVertex3f(-0.1,0.1,0);
	glVertex3f(0.1,-0.1,0);
	glEnd();


	glPointSize(10);

	glBegin(GL_POINTS);
	glColor4f(0,0,1,1);
	glVertex3f(0,0,0);
	glEnd();
}
