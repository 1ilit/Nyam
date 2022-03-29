#include "Graphics.h"

Graphics* Graphics::instance = NULL;

bool Graphics::isInit = false;

Graphics::Graphics() {
	isInit = Init();
}

Graphics::~Graphics() {
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
}

Graphics* Graphics::Instance() {
	if (instance==NULL)
		instance = new Graphics();

	return instance;
}

void Graphics::Release() {
	delete instance;
	instance = NULL;

	isInit = false;
}

bool Graphics::Initialized() {
	return isInit;
}

bool Graphics::Init() {

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "init error: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow("Nyam v1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		std::cout << "window creation error: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cout << "render creation error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 255, 150, 129, 255);

	int flags = IMG_INIT_PNG;

	if (!(IMG_Init(flags) & flags)) {
		std::cout << "image init error: " << IMG_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() == -1) {
		std::cout << "ttf init error: " << TTF_GetError() << std::endl;
		return false;
	}

	backBuffer = SDL_GetWindowSurface(window);

	return true;
}

SDL_Texture* Graphics::LoadTexture(std::string path) {
	SDL_Texture* tex = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL) {
		std::cout << "image load path error: " << IMG_GetError() << " path: " << path<<std::endl;
		return tex;
	}

	tex = IMG_LoadTexture(renderer, path.c_str());
	if (tex == NULL) {
		std::cout << "texture creatiion error: " << SDL_GetError() << std::endl;
		return tex;
	}

	SDL_FreeSurface(surface);

	return tex;
}

SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

	if (surface == NULL) {
		std::cout << "text render error: " << TTF_GetError() << std::endl;
		return NULL;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);

	if (tex == NULL) {
		std::cout << "text texture error: " << SDL_GetError() << std::endl;
		return NULL;
	}

	SDL_FreeSurface(surface);
	return tex;

}

void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip) {

	SDL_RenderCopyEx(renderer, tex, clip, rend, angle, NULL, flip);
}

void Graphics::ClearBackBuffer() {
	SDL_RenderClear(renderer);
}

void Graphics::Render() {
	SDL_RenderPresent(renderer);
}



