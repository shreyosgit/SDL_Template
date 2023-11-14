#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "SDL\SDL.h"
#include "glm\glm.hpp"

namespace glm {
	typedef tvec4<uint8_t> ui8_tvec4;
}

enum struct WindowState {ACTIVE, EXIT};

class SDL_Template
{
public:
	SDL_Template();
	~SDL_Template();

	void sdl_CreateWindow(const char* w_title, int w_width, int w_height);
	void sdl_DrawTexture(int u, int v, std::vector<glm::ui8_tvec4>& PixelData);
	void sdl_RenderBegin();
	void sdl_RenderEnd();
	void sdl_InputEvent();

	WindowState sdl_WindowState;

private:
	const char* sdl_WindowTitle;
	int sdl_WindowWidth, sdl_WindowHeight;
	SDL_Window* sdl_WindowPtr;
	SDL_Renderer* sdl_RendererPtr;
	SDL_Texture* sdl_TexturePtr;
	SDL_Rect sdl_ScrrenSize;

	void sdl_Init();
	void sdl_PrintError(std::string ErrorList);
	void sdl_Quit();
};

