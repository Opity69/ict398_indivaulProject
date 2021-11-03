#include "Scene.hpp"


#include <fstream>
#include <sstream>
#include <string>

#include "Glew/include/GL/glew.h"


float FloatorZero(const std::string& s)
{
	if (s.empty())
	{
		return 0;
	}

	return std::stof(s);
}

bool ProjectileData::is_fired() const
{
	return fired;
}


void Scene::register_Camera(std::shared_ptr<Camera>& camera)
{
	cameras_.insert({camera->getID(), camera});
}

void Scene::unregister_Camera(uint64_t id)
{
	cameras_.erase(id);
}

void Scene::loadFromTokens(std::vector<std::string>& tokens)
{
	BodyProps p;
	BodyState s;
	size_t index = 0;
	std::string tag = tokens[index++];
	std::string Type = tokens[index++];
	float posX = std::stof(tokens[index++]);
	float posy = std::stof(tokens[index++]);
	float posz = std::stof(tokens[index++]);

	float p1 = std::stof(tokens[index++]);
	float p2 = std::stof(tokens[index++]);
	float p3 = std::stof(tokens[index++]);

	float mass = std::stof(tokens[index++]);

	float r = std::stof(tokens[index++]);
	float g = std::stof(tokens[index++]);
	float b = std::stof(tokens[index++]);


	Transform trans = {};
	trans.set_translation({posX, posy, posz});
	glm::fvec4 color{r, g, b, 1};

	glm::fvec3 params = {p1, p2, p3};
	p.mass = Mass{mass};

	if (Type == "Box")
	{
		auto box = std::make_shared<Box>(trans, color, params);
		auto box_collison = std::make_shared<CBox>(trans, params);
		p.tensor = computeTensorBox(p.mass, params);
		s.postion_state.pos = box->get_translation();
		auto boxBody = std::make_shared<Body>(BodyMode::RIGID, p, s, box);
		boxBody->SetCollison(box_collison);
		boxBody->tag = tag;
		this->register_VissualObject(box);
		this->register_PhyiscObject(boxBody);
		if (tag == "Bullet")
		{
			this->projectile_data = {boxBody};
		}
	}
	else if (Type == "Sphere")
	{
		auto sphere = std::make_shared<Sphere>(trans, color, params.x);
		auto sphere_collison = std::make_shared<CSphere>(trans, params.x);
		p.tensor = computeTensorSphere(p.mass, params.x);
		s.postion_state.pos = sphere->get_translation();
		auto sphereBody = std::make_shared<Body>(BodyMode::RIGID, p, s, sphere);
		sphereBody->SetCollison(sphere_collison);
		sphereBody->tag = tag;
		this->register_VissualObject(sphere);
		this->register_PhyiscObject(sphereBody);

		if (tag == "Bullet")
		{
			this->projectile_data = {sphereBody};
		}
	}
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


void Scene::LoadCsv(const std::string& file_Path)
{
	std::ifstream fstream(file_Path);

	if (!fstream.is_open())
	{
		std::cout << "File not Found";
	}
	std::string line;
	//skip header line
	std::getline(fstream, line);
	std::vector<std::string> Tokens;
	while (std::getline(fstream, line))
	{
		std::stringstream stringstream(line);


		Tokens.clear();
		std::string token;
		while (std::getline(stringstream, token, ','))
		{
			Tokens.push_back(token);
		}
		this->loadFromTokens(Tokens);
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

	if (!projectile_data.projectile.expired())
	{
		auto ptr = projectile_data.projectile.lock();
		if (ptr)
		{
			if (!projectile_data.is_fired())
			{
				glBegin(GL_LINES);
					glColor4f(1, 1, 0, 1);
					glVertex3fv(glm::value_ptr(ptr->state.postion_state.pos));
					glm::fvec3 endpoint = ptr->state.postion_state.pos + projectile_data.dir * projectile_data.scale;
					glVertex3fv(glm::value_ptr(endpoint));
				glEnd();
			}
			
		}
	}


	glPopMatrix();
}

void Scene::Update(float Timestep)
{
	phyics_world_.Update(Timestep);
}
