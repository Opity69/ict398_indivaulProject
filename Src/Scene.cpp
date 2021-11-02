#include "Scene.hpp"


#include <sstream>
#include <string>

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

void Scene::register_PhyiscObject(std::shared_ptr<Body>& body)
{
	phyics_world_.AddBody(body);
}

void Scene::register_VissualObject(std::shared_ptr<IVissualObject> vsObject)
{
	objects_.insert({vsObject->getID(), vsObject});
}


// copied from https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c

std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str)
{
	std::vector<std::string> result;
	std::string line;
	std::getline(str, line);

	std::stringstream lineStream(line);
	std::string cell;

	while (std::getline(lineStream, cell, ','))
	{
		result.push_back(cell);
	}
	// This checks for a trailing comma with no data after it.
	if (!lineStream && cell.empty())
	{
		// If there was a trailing comma then add an empty element.
		result.push_back("");
	}
	return result;
}


void Scene::LoadBodies(const std::string& file_Path)
{
	// Look operation map
	auto Operation = 0u;

	switch (Operation)
	{
	case 1:
		// Addvssual
		break;
	case 2:
		// AddBody
		break;

		
	default: ;
		
	}
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
