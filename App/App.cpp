// App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "window.h"
#include  "Scene.hpp"

int main()
{

	VissaulEngine vs;
	BodyProps props = {};
	BodyState state = {};
	auto scene = std::make_shared<Scene>();
	auto camera = std::make_shared<Camera>(Transform{{0,0,80},{},{1.0f,0.0f,0.0f,0.0f}},0.001,100,90,1);

	scene->register_Camera(camera);
	scene->SetCurrentCammera(camera->getID());
	
	
	//auto sphere = std::make_shared<Shpere>(Transform{{-10,10,0},{10,10,10},{1,0,0,0,}},glm::fvec4{1.0f,0.0f,0.f,0.f},1);
	


	// Setup Floor
	glm::fvec3 floor_extends = {100,0.1f,100};
	auto floor =std::make_shared<Box>(Transform{{0,-0.1,0},{1,1,1},(glm::angleAxis(-0.001f,glm::fvec3{1,0,0}))},glm::fvec4{1,1,1,1},floor_extends);
	auto floorcollison = std::make_shared<CBox>(floor->getTransfrom(), floor_extends);
	props.mass_inv = Mass(0);
	props.tensor_inv = InteriaTensor();

	state.postion_state.pos = floor->get_translation();
	state.postion_state.rot  = floor->get_rotation();
	state.angualr_velocity = {0,0,0};
	state.linear_velocity = {0,0,0};	
	auto  floorbody = std::make_shared<Body>(BodyMode::RIGID,props,state,floor);
	floorbody->SetCollison(floorcollison);
	scene->register_VissualObject(floor);
	scene->register_PhyiscObject(floorbody);
	

	// Setup Box

	glm::fvec3 box_ext = {3,3,3};

	Transform box_t = {};
	box_t.set_translation({0,20,0});
	auto box =std::make_shared<Box>(box_t,glm::fvec4{0,1,0,1},box_ext);
	auto boxCollison = std::make_shared<CBox>(box->getTransfrom(), box_ext);
	props.mass_inv = Mass(0);
	props.tensor_inv = InteriaTensor();

	state.postion_state.pos = box->get_translation() + glm::fvec3(20,20,20);
	state.postion_state.rot  = box->get_rotation();
	state.angualr_velocity = {0,0,0};
	state.linear_velocity = {0,-0.5,0};
	
	auto  boxbody = std::make_shared<Body>(BodyMode::RIGID,props,state,box);
	boxbody->SetCollison(boxCollison);
	scene->register_VissualObject(box);
	scene->register_PhyiscObject(boxbody);
	


	
	//scene->register_VissualObject(sphere);
	//scene->register_VissualObject(box);
	//scene->register_VissualObject(floor);

	

	props.mass_inv = Mass{0};
	props.tensor_inv = InteriaTensor{};
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
