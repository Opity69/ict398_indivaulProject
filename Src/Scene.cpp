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

	glBegin(GL_TRIANGLES);
	glColor4f(1, 1, 1, 1);
	glVertex3f(-0.2, -0.2, 0);
	glVertex3f(-0.1, 0.1, 0);
	glVertex3f(0.1, -0.1, 0);
	glEnd();

	glEnable(GL_DEPTH_TEST);

	glPointSize(10);

	glBegin(GL_POINTS);
	glColor4f(0, 0, 1, 1);
	glVertex3f(0, 0, 0);
	glEnd();
	glMatrixMode(GL_PROJECTION);
	if (!currentCamera.expired())
	{
		auto cam = currentCamera.lock();

		if (cam)
		{
			glLoadMatrixf(cam->matrixPtr());
		}
	}
	//Triangle
	glBegin(GL_TRIANGLES);
	glColor4f(0.5, 0.5, 0.5, 0.5);
	glVertex3f(0, -10, -10);
	glVertex3f(-10, 10, -10);
	glVertex3f(10, 10, -10);
	glEnd();

	// Floor
	glBegin(GL_TRIANGLES);
	glColor4f(0.1f, 0, 0.5, 0.5);
	glVertex3f(0, 0, -1000);
	glVertex3f(1000, -0.1, 1000);
	glVertex3f(-1000, -0.1, 1000);
	glEnd();
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
