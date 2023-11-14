#include "Application.h"

Application::Application(): sdl_instance() {
	app_Title = "SDL Template";
	app_WindowWidth = 900;
	app_WindowHeight = 600;
}
Application::~Application() {

}

void Application::Init() {
	sdl_instance.sdl_CreateWindow(app_Title, app_WindowWidth, app_WindowHeight);
}

void Application::RenderLoop() {
	while (sdl_instance.sdl_WindowState == WindowState::ACTIVE) {
		sdl_instance.sdl_RenderBegin();
		sdl_instance.sdl_InputEvent();

		Draw();

		sdl_instance.sdl_RenderEnd();
	}
}

void Application::Run() {
	Init();
	Draw();
	RenderLoop();
}

void Application::Draw() {
	ImageData.resize(app_WindowWidth * app_WindowHeight);

	for (int y = 0; y < app_WindowHeight; ++y) {
		for (int x = 0; x < app_WindowWidth; ++x) {
			glm::vec4 color = glm::vec4(glm::vec3(0.5f * 255.0f, 0.2f * 255.0f, 0.1f * 255.0f), 1.0f * 255.0f);

			ImageData[x + y * app_WindowWidth] = color;
		}
	}

	sdl_instance.sdl_DrawTexture(app_WindowWidth, app_WindowHeight, ImageData);
}