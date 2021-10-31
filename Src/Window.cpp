#include "Window.h"

#include <Glew/include/GL/glew.h>
#include <Glfw/include/GLFW/glfw3.h>
#include <Scene.hpp>

Window::Window(GLFWwindow* win_ptr): win_ptr(win_ptr)
{
}

Window::~Window()
{
	glfwDestroyWindow(win_ptr);
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(win_ptr);
}

void Window::Draw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int w = 1,h = 1;
	if(win_ptr)
	{
		glfwGetFramebufferSize(win_ptr,&w,&h);
	}
	glViewport(0,0,w,h);
	if (!SceneToDraw.expired())
	{
		auto ptr = SceneToDraw.lock();
		if (ptr)
		{
			ptr->Draw();
		}
	}

	if(win_ptr)
	{
		glfwSwapBuffers(win_ptr);
	}
}

void Window::SetSceneToDraw(const std::shared_ptr<Scene>& scene)
{
	this->SceneToDraw =scene;
}


GLFWwindow* VissaulEngine::sharewin = nullptr;

bool VissaulEngine::Initailize()
{
	static bool isGlfwInit = false;
	if (!isGlfwInit)
	{
		isGlfwInit = glfwInit();
	}

	if (isGlfwInit)
	{
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		sharewin = glfwCreateWindow(1, 1, "", NULL, NULL);

		glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	}

	return isGlfwInit;
}

bool VissaulEngine::GlewInit()
{
	static bool isGlewInit = false;
	if (!isGlewInit)
	{
		if (glfwInit())
		{
			isGlewInit = false;
			return isGlewInit;
		}
		isGlewInit = true;
	}
	return isGlewInit;
}

VissaulEngine::VissaulEngine()
{
	Initailize();
}

std::unique_ptr<Window> VissaulEngine::makeWindow(const glm::uvec2& size, const char* title)
{
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_SAMPLES, 4);

	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	auto win_ptr = glfwCreateWindow(size.x, size.y, title, nullptr, sharewin);
	glfwMakeContextCurrent(win_ptr);
	GlewInit();

	return std::make_unique<Window>(win_ptr);
}

bool VissaulEngine::MainLoop()
{
	glfwPollEvents();
	return true;
}

VissaulEngine::~VissaulEngine()
{
	glfwTerminate();
}
