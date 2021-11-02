// App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "window.h"
#include  "Scene.hpp"

int main()
{
	float inf =INFINITY;
	VissaulEngine vs;
	BodyProps props = {};
	BodyState state = {};
	Transform CameraTras = {};
	CameraTras.set_translation({0,10,80});
	CameraTras.set_rotation(glm::angleAxis(-0.1f, glm::fvec3{1,0,0}));
	auto scene = std::make_shared<Scene>();
	auto camera = std::make_shared<Camera>(CameraTras,0.001,100,90,1);

	scene->register_Camera(camera);
	scene->SetCurrentCammera(camera->getID());
	
	
	//auto sphere = std::make_shared<Shpere>(Transform{{-10,10,0},{10,10,10},{1,0,0,0,}},glm::fvec4{1.0f,0.0f,0.f,0.f},1);
	


	// Setup Floor
	glm::fvec3 floor_extends = {100,0.1f,100};
	Transform floor_t =  {};
	floor_t.set_translation({0,0,0});
	auto floor =std::make_shared<Box>(floor_t,glm::fvec4{1,1,1,1},floor_extends);
	auto floorcollison = std::make_shared<CBox>(floor->getTransfrom(), floor_extends);
	props.mass = Mass(inf);
	props.tensor = InteriaTensor(inf,inf,inf);

	state.postion_state.pos = floor->get_translation();
	state.postion_state.rot  = floor->get_rotation();
	state.angualr_velocity = {0,0,0};
	state.linear_velocity = {0,0,0};	
	auto  floorbody = std::make_shared<Body>(BodyMode::STATIC,props,state,floor);
	floorbody->SetCollison(floorcollison);
	scene->register_VissualObject(floor);
	scene->register_PhyiscObject(floorbody);
	

	// Setup Box

	glm::fvec3 box_ext = {3,3,3};

	Transform box_t = {};
	box_t.set_translation({0,20,0});
	auto box =std::make_shared<Box>(box_t,glm::fvec4{0,1,0,1},box_ext);
	auto boxCollison = std::make_shared<CBox>(box->getTransfrom(), box_ext);
	props.mass = Mass(30);
	props.tensor = InteriaTensor(20,20,20);

	state.postion_state.pos = box->get_translation();
	state.postion_state.rot  = box->get_rotation();
	state.angualr_velocity = {0,0,0};
	state.linear_velocity = {0,-2.5,0};
	
	auto  boxbody = std::make_shared<Body>(BodyMode::RIGID,props,state,box);
	boxbody->SetCollison(boxCollison);
	scene->register_VissualObject(box);
	scene->register_PhyiscObject(boxbody);
	

	Transform sphere_trans = {};
	float radius = 4;
	sphere_trans.set_translation(glm::fvec3(0,60,0));
	auto sphere =std::make_shared<Shpere>(sphere_trans,glm::fvec4{0,1,1,1},radius);
	auto sphereCollison = std::make_shared<CSphere>(sphere->getTransfrom(), radius);
	props.mass = Mass(10);
	props.tensor = InteriaTensor(20,20,20);

	state.postion_state.pos = sphereCollison->get_translation();
	state.postion_state.rot  = sphereCollison->get_rotation();
	state.angualr_velocity = {0,0,0};
	state.linear_velocity = {0,-1.5,0};
	
	auto  sphereBody = std::make_shared<Body>(BodyMode::RIGID,props,state,sphere);
	sphereBody->SetCollison(sphereCollison);
	scene->register_VissualObject(sphere);
	scene->register_PhyiscObject(sphereBody);
	

	
	//scene->register_VissualObject(sphere);
	//scene->register_VissualObject(box);
	//scene->register_VissualObject(floor);

	

	props.mass = Mass{0};
	props.tensor = InteriaTensor{};
	BodyState bodyState = {};
	

	

	auto win =  vs.makeWindow({100,100},"Test");
	win->SetSceneToDraw(scene);

	while (!win->ShouldClose() && vs.MainLoop())
	{
		win->Draw();
		win->Update(0.1);
		
		auto size = win->GetFsize();
		camera->set_aspect((float)size.x / (float) size.y);
		
		
	}
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
