#pragma once

#include <time.h>

#include "SDL_Template.h"

class Application

{
public:
	Application();
	~Application();

	void Run();
private:
	SDL_Template sdl_instance;
	std::vector<glm::ui8_tvec4> ImageData;

	const char* app_Title;
	int app_WindowWidth, app_WindowHeight;

	void Init();
	void Draw();
	void RenderLoop();
};

