
#include "..\include\graphics\Context.h"

#include "glinc.h"


#ifdef DEBUG
#include <iostream>

void APIENTRY GL_errorCallback(GLenum, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar *message, const void *userParam)
{
	std::cerr << message << std::endl;
}
#endif // DEBUG


	bool Context::init(size_t w, size_t h,
		const char  *title)
	{
		glfwInit();
		handle = glfwCreateWindow(w, h, title, 0, 0);
		glfwMakeContextCurrent(handle);

		glewExperimental = true;
		glewInit();
		#ifdef  _ DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

			glDebugMessageCallback(glDebugMessageCallback, 0);
			glDebugMessageControl(GL_DONT_CARE; GL_DONT_CARE, GL_DONT_CARE, 0, 0, true);
		#endif //  _ DEBUG
		return true;
	}

	// determins the fps
	bool Context::step()
	{
		glfwPollEvents();

		glfwSwapBuffers(handle);

		return !glfwWindowShouldClose(handle);
	}

	// tell window to close 
	bool Context::term()
	{
		glfwTerminate();
		handle = nullptr;
		return true;
	}

	bool Context::getKey(int Key)
	{
		glfwGetKey(handle,Key);
		return false;
	}

	bool Context::getMouseButton(int button)
	{
		glfwGetMouseButton(handle, button);

		return false;
	}

	void Context::getMousePosition(double &x_out, double &y_out)
	{
		glfwGetCursorPos(handle, &x_out, &y_out);
		
	}

	double Context::getTime()
	{
		return glfwGetTime();
	}




