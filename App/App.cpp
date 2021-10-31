// App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "window.h"
#include  "Scene.hpp"

int main()
{

	VissaulEngine vs;
	auto scene = std::make_shared<Scene>();
	auto camera = std::make_shared<Camera>(Transform{{0,0,80},{},{1.0f,0.0f,0.0f,0.0f}},0.001,100,90,1);
	auto sphere = std::make_shared<Shpere>(Transform{{-10,10,0},{10,10,10},{1,0,0,0,}},glm::fvec4{1.0f,0.0f,0.f,0.f},1);
	auto box =std::make_shared<Box>(Transform{},glm::fvec4{0,1,0,1}, glm::fvec3{1,2,4});
	auto floor =std::make_shared<Box>(Transform{{0,-0.1,0},{1000,0.1,1000},(glm::angleAxis(-0.001f,glm::fvec3{1,0,0}))},glm::fvec4{1,1,1,1}, glm::fvec3{1,1,1});
	scene->register_Camera(camera);
	scene->SetCurrentCammera(camera->getID());
	scene->register_VissualObject(sphere);
	scene->register_VissualObject(box);
	scene->register_VissualObject(floor);
	

	auto win =  vs.makeWindow({100,100},"Test");
	win->SetSceneToDraw(scene);

	while (!win->ShouldClose() && vs.MainLoop())
	{
		win->Draw();
		//camera->Translate({0,0,1});
		//camera->Rotate(glm::angleAxis(0.1f, glm::fvec3(0.0f,1.0f,0.0f)));
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
