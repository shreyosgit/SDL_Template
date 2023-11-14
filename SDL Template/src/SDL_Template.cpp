#include "SDL_Template.h"

SDL_Template::SDL_Template() {
	sdl_WindowPtr = nullptr;
	sdl_WindowTitle = "SDL Template";
	sdl_WindowWidth = 600;
	sdl_WindowHeight = 500;
	sdl_WindowState = WindowState::ACTIVE;
}
SDL_Template::~SDL_Template() {
	sdl_Quit();
}
// Output Errors
void SDL_Template::sdl_PrintError(std::string ErrorList) {
	std::cout << ErrorList << std::endl;
	std::cin.get();

	SDL_Quit();
}

void SDL_Template::sdl_Init() {
	// Setting Scaling as Nearest Pixel Sampling
	SDL_bool HintError = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	if (HintError != SDL_TRUE) {
		sdl_PrintError("SDL hint could not be set! " + std::string(SDL_GetError()));
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		sdl_PrintError("SDL Subsystems could not be initialized!" + std::string(SDL_GetError()));
	}

	sdl_WindowPtr = SDL_CreateWindow(sdl_WindowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sdl_WindowWidth, sdl_WindowHeight, SDL_WINDOW_SHOWN);
	if (sdl_WindowPtr == nullptr) {
		sdl_PrintError("SDL window could not be created!" + std::string(SDL_GetError()));
	}

	sdl_RendererPtr = SDL_CreateRenderer(sdl_WindowPtr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (sdl_RendererPtr == nullptr) {
		sdl_PrintError("SDL rendering context could not be created!" + std::string(SDL_GetError()));
	}
	// Using Alpha Blending for SDL_RenderCopy()*
	if (SDL_SetRenderDrawBlendMode(sdl_RendererPtr, SDL_BLENDMODE_BLEND) != 0) {
		sdl_PrintError("SDL Blendmode could not be applied!" + std::string(SDL_GetError()));
	}

	sdl_TexturePtr = SDL_CreateTexture(sdl_RendererPtr, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, sdl_WindowWidth, sdl_WindowHeight);

	// Setting up the destination rectangle
	sdl_ScrrenSize.x = 0;
	sdl_ScrrenSize.y = 0;
	sdl_ScrrenSize.w = sdl_WindowWidth;
	sdl_ScrrenSize.h = sdl_WindowHeight;
}

void SDL_Template::sdl_CreateWindow(const char* w_title, int w_width, int w_height) {
	sdl_WindowTitle = w_title;
	sdl_WindowWidth = w_width;
	sdl_WindowHeight = w_height;

	sdl_Init();
}

void SDL_Template::sdl_InputEvent() {
	SDL_Event sdl_Event;

	while (SDL_PollEvent(&sdl_Event)) {
		if (sdl_Event.type == SDL_QUIT) {
			sdl_WindowState = WindowState::EXIT;
			break;
		}
	}
}

void SDL_Template::sdl_DrawTexture(int u, int v, std::vector<glm::ui8_tvec4>& PixelData) {
	uint32_t* pixels;
	int pitch;
	int numofpixels = u * v;

	if (SDL_LockTexture(sdl_TexturePtr, NULL, (void**)&pixels, &pitch) != 0) {
		sdl_PrintError("The texture could not be locked!" + std::string(SDL_GetError()));
	}
	// Copy the buffer to the texture
	memcpy(pixels, PixelData.data(), numofpixels * sizeof(uint32_t));

	SDL_UnlockTexture(sdl_TexturePtr);
}

void SDL_Template::sdl_RenderBegin() {
	// Clearing the rendering context (in this case the backbuffers)
	if (SDL_RenderClear(sdl_RendererPtr) != 0) {
		sdl_PrintError("The rendering target could not be cleared!" + std::string(SDL_GetError()));
	}
}
void SDL_Template::sdl_RenderEnd() {
	// Copying the texture to the already cleared rendering target
	if (SDL_RenderCopy(sdl_RendererPtr, sdl_TexturePtr, NULL, &sdl_ScrrenSize) != 0) {
		sdl_PrintError("The texture data could not be copied to the rendering target!" + std::string(SDL_GetError()));
	}
	// Swap the buffer index and present the content to the user
	SDL_RenderPresent(sdl_RendererPtr);
}

void SDL_Template::sdl_Quit() {
	if (sdl_WindowState == WindowState::EXIT) {
		SDL_DestroyTexture(sdl_TexturePtr);
		SDL_DestroyRenderer(sdl_RendererPtr);
		SDL_DestroyWindow(sdl_WindowPtr);
		SDL_Quit();
	}
}