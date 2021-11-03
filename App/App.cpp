// App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>

#include "window.h"
#include  "Scene.hpp"
#include <sstream>
#include <Glfw/include/GLFW/glfw3.h>


auto scene = std::make_shared<Scene>(); //   any other way would have taken for ages

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (!scene->projectile_data.is_fired())
	{
		if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
			scene->projectile_data.dir.y -= 0.1f;
		if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
			scene->projectile_data.dir.y += 0.1f;
		if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
			scene->projectile_data.dir.x -= 0.1f;
		if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
			scene->projectile_data.dir.x += 0.1f;
		if (key == GLFW_KEY_Z && (action == GLFW_REPEAT || action == GLFW_PRESS))
			scene->projectile_data.dir.y -= 0.1f;
		if (key == GLFW_KEY_Q && (action == GLFW_REPEAT || action == GLFW_PRESS))
			scene->projectile_data.dir.x += 0.1f;

		if (key == GLFW_KEY_LEFT_BRACKET && (action == GLFW_REPEAT || action == GLFW_PRESS))
			scene->projectile_data.scale -= 0.1f;
		if (key == GLFW_KEY_RIGHT_BRACKET && (action == GLFW_REPEAT || action == GLFW_PRESS))
			scene->projectile_data.scale += 0.1f;
	}
	scene->projectile_data.dir = normalize(scene->projectile_data.dir);

	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		scene->projectile_data.Reset();
	}
	
	glm::fvec3 vel = scene->projectile_data.dir * scene->projectile_data.scale;
	if (key == GLFW_KEY_SPACE && GLFW_PRESS)
	{
		scene->projectile_data.Fire();
		
		std::cout << "Current Bullet Fire With:" << VecToString(vel) << "\n";
	}
	else
	{
		
		std::cout << "Current Bullet vel:" << VecToString(vel) << "\n";
	}
}

int main()
{
	bool old = false;

	//std::cout << "Use Old y/n";
	//char option = 'n';
	//std::cin >> option;

	//old = option == 'y';

	if (old)
	{
		float inf = INFINITY;
		VissaulEngine vs;
		BodyProps props = {};
		BodyState state = {};
		Transform CameraTras = {};
		CameraTras.set_translation({0, 20, 80});
		CameraTras.set_rotation(glm::angleAxis(-0.2f, glm::fvec3{1, 0, 0}));

		auto camera = std::make_shared<Camera>(CameraTras, 0.001, 1000, 90, 1);

		scene->register_Camera(camera);
		scene->SetCurrentCammera(camera->getID());


		// Setup Floor
		glm::fvec3 floor_extends = {100, 20.f, 100};
		Transform floor_t = {};
		floor_t.set_translation({0, -40.0f, 0});
		auto floor = std::make_shared<Box>(floor_t, glm::fvec4{1, 1, 1, 1}, floor_extends);
		auto floorcollison = std::make_shared<CBox>(floor->getTransfrom(), floor_extends);
		props.mass = Mass(inf);
		props.tensor = InteriaTensor(inf, inf, inf);

		state.postion_state.pos = floor->get_translation();
		state.postion_state.rot = floor->get_rotation();
		state.angualr_velocity = {0, 0, 0};
		state.linear_velocity = {0, 0, 0};
		auto floorbody = std::make_shared<Body>(BodyMode::STATIC, props, state, floor);
		floorbody->SetCollison(floorcollison);
		floorbody->tag = "floor";
		scene->register_VissualObject(floor);
		scene->register_PhyiscObject(floorbody);


		// Setup Box

		glm::fvec3 box_halfext = {3, 3, 20};

		Transform box_t = {};
		box_t.set_translation({0, 0, 0});
		auto box = std::make_shared<Box>(box_t, glm::fvec4{0, 1, 0, 1}, box_halfext);
		auto boxCollison = std::make_shared<CBox>(box->getTransfrom(), box_halfext);
		props.mass = Mass(2);
		props.tensor = computeTensorBox(props.mass, box_halfext);

		state.postion_state.pos = box->get_translation();
		state.postion_state.rot = box->get_rotation();
		state.angualr_velocity = {0, 0, 0};
		state.linear_velocity = {0, 0, 0};

		auto boxbody = std::make_shared<Body>(BodyMode::RIGID, props, state, box);
		boxbody->tag = "Target1";
		boxbody->SetCollison(boxCollison);
		scene->register_VissualObject(box);
		scene->register_PhyiscObject(boxbody);


		Transform sphere_trans = {};
		float radius = 4;
		sphere_trans.set_translation(glm::fvec3(0, 60, 0));
		auto sphere = std::make_shared<Sphere>(sphere_trans, glm::fvec4{0, 1, 1, 1}, radius);
		auto sphereCollison = std::make_shared<CSphere>(sphere->getTransfrom(), radius);
		props.mass = Mass(10);
		props.tensor = InteriaTensor(3, 3, 3);


		state.postion_state.pos = sphereCollison->get_translation();
		state.postion_state.rot = sphereCollison->get_rotation();
		state.angualr_velocity = {0, 0, 0};
		state.linear_velocity = {0, -2.5, 0};

		auto sphereBody = std::make_shared<Body>(BodyMode::RIGID, props, state, sphere);
		sphereBody->SetCollison(sphereCollison);
		sphereBody->tag = "Sphere";
		scene->register_VissualObject(sphere);
		scene->register_PhyiscObject(sphereBody);


		//scene->register_VissualObject(sphere);
		//scene->register_VissualObject(box);
		//scene->register_VissualObject(floor);


		props.mass = Mass{0};
		props.tensor = InteriaTensor{};
		BodyState bodyState = {};


		auto win = vs.makeWindow({100, 100}, "Test");
		win->SetSceneToDraw(scene);

		while (!win->ShouldClose() && vs.MainLoop())
		{
			win->Draw();
			win->Update(0.1f);

			auto size = win->GetFsize();
			camera->set_aspect((float)size.x / (float)size.y);
		}
	}
	else
	{
		float inf = INFINITY;
		VissaulEngine vs;
		BodyProps props = {};
		BodyState state = {};
		Transform CameraTras = {};
		CameraTras.set_translation({0, 20, 80});
		CameraTras.set_rotation(glm::angleAxis(-0.2f, glm::fvec3{1, 0, 0}));

		auto camera = std::make_shared<Camera>(CameraTras, 0.001, 1000, 90, 1);

		scene->register_Camera(camera);
		scene->SetCurrentCammera(camera->getID());


		// Setup Floor
		glm::fvec3 floor_extends = {60, 10.f, 60};
		Transform floor_t = {};
		floor_t.set_translation({0, -30.0f, 0});
		auto floor = std::make_shared<Box>(floor_t, glm::fvec4{1, 1, 1, 1}, floor_extends);
		auto floorcollison = std::make_shared<CBox>(floor->getTransfrom(), floor_extends);
		props.mass = Mass(inf);
		props.tensor = InteriaTensor(inf, inf, inf);

		state.postion_state.pos = floor->get_translation();
		state.postion_state.rot = floor->get_rotation();
		state.angualr_velocity = {0, 0, 0};
		state.linear_velocity = {0, 0, 0};
		auto floorbody = std::make_shared<Body>(BodyMode::STATIC, props, state, floor);
		floorbody->SetCollison(floorcollison);
		floorbody->tag = "floor";
		scene->register_VissualObject(floor);
		scene->register_PhyiscObject(floorbody);


	

		std::string File_path = "Data/BodyProps.csv";

		scene->LoadCsv(File_path);
		scene->projectile_data.dir = {0.5,-0.5,0};


		auto win = vs.makeWindow({100, 100}, "new");
		glfwSetKeyCallback(win->getWinptr(), key_callback);
		win->SetSceneToDraw(scene);

		while (!win->ShouldClose() && vs.MainLoop())
		{
			win->Draw();
			win->Update(0.1);

			auto size = win->GetFsize();
			camera->set_aspect((float)size.x / (float)size.y);
		}
	}
}
