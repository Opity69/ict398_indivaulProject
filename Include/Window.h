#pragma once
#include <Glew/include/GL/glew.h>
#include <Glfw/include/GLFW/glfw3.h>

#include <Glfw/include/GLFW/glfw3.h>


class WindowSubsystem
{
	static bool init()
	{
		static bool intisalized =false;
		if(!intisalized)
		{
			intisalized =glfwInit();
		}
		return intisalized;

	}

};


class Widnow
{
	
};

