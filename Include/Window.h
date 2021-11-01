#pragma once




#include <memory>

#include <glm3/glm/glm.hpp>






class Scene;
struct GLFWwindow;



class Window
{
public:
	explicit Window(GLFWwindow* win_ptr);

private:
	std::weak_ptr<Scene> SceneToDraw;
	GLFWwindow* win_ptr =nullptr;
private:
	friend  class VissaulEngine;
	

public:
	~Window();

	bool ShouldClose();


	void Draw();
	void SetSceneToDraw(const std::shared_ptr<Scene>& scene);
	glm::uvec2 GetFsize();
	void Update(float x);
};

class VissaulEngine
{
	static bool Initailize();

	static bool GlewInit();


	static  GLFWwindow* sharewin;
public:
	VissaulEngine();

	std::unique_ptr<Window> makeWindow(const glm::uvec2& size, const char* title);


	bool MainLoop();


	~VissaulEngine();
};

