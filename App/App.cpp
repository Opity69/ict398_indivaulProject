// App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "window.h"
#include  "Scene.hpp"

int main()
{

	VissaulEngine vs;
	auto scene = std::make_shared<Scene>();
	auto camera = std::make_shared<Camera>(Transform{},0.001,100,90,1);

	scene->register_Camera(camera);

	auto win =  vs.makeWindow({100,100},"Test");
	win->SetSceneToDraw(scene);

	while (!win->ShouldClose() && vs.MainLoop())
	{
		win->Draw();
		
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
