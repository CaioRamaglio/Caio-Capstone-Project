#include "renderer.h"
#include <iostream>

Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height)
    : screen_width(screen_width), screen_height(screen_height)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    if (nullptr == sdl_window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Initialize use of PNGs and JPGs for sprites
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

Renderer::~Renderer() 
{
    std::cout << "renderer destroyed" << std::endl;
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::PrepareScene() 
{
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 30, 30, 30, 255);
    SDL_RenderClear(sdl_renderer);
}

void Renderer::PresentScene()
{
    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}  

SDL_Texture * Renderer::LoadTexture(char * filename)
{
	SDL_Texture * texture = IMG_LoadTexture(sdl_renderer, filename);
	return texture;
}

void Renderer::Blit(SDL_Texture * texture, float * x, float * y)
{
	SDL_Rect dest;
	dest.x = *x;
	dest.y = *y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(sdl_renderer, texture, NULL, &dest);
}
