#pragma once

class GLFWwindow;

class Context
{
private:
	GLFWwindow *handle;

public:
	bool init(size_t w = 800, size_t h = 600,
							  const char  *title = "Graphics");

	// determins the fps
	bool step();

	// tell window to close 
	bool term();

	bool getKey(int Key);
	bool getMouseButton(int button);
	void getMousePosition(double &x_out, double &y_out);
	double getTime();

};