#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "starfield.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void PrepareScene();
  void PresentScene();
  SDL_Texture * LoadTexture(char * filename);
  void Blit(SDL_Texture * texture, float * x, float * y);
  void DrawBackground(Starfield * starfield);
  void UpdateWindowTitle(int score);

 private:
  SDL_Renderer *sdl_renderer;
  SDL_Window *sdl_window;

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif