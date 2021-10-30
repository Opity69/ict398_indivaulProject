#include <iostream>

#include <windows.h>




#include <iostream>
#include <memory>

#include <ccd/ccd.h>



int main(int argc, const char** argv)
{
	std::cout << "Thing\n";

	glfwInit();


	ccd_t t;
	CCD_INIT(&t);

	auto win_ptr = glfwCreateWindow(100, 100, "TEST", nullptr, nullptr);


	while (!glfwWindowShouldClose(win_ptr))
	{
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

