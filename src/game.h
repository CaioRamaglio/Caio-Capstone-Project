#ifndef GAME_H
#define GAME_H

#include <list>
#include <memory>
#include <random>
#include <SDL.h>
#include "controller.h"
#include "renderer.h"
#include "player.h"
#include "asteroid.h"
#include "starfield.h"

class Game{
  public:
    void Run(Controller controller, Renderer renderer);
    void PlayerLogic();
    void ClearBulletsAndAsteroids();
    void SpawnAsteroids();
    void CheckCollisions();
    bool GameOver(Starfield * starfield);

  private:
    Controller * _controller;
    Player * _player;
    Renderer * _renderer;
    SDL_Texture * playerTexture;
    SDL_Texture * bulletTexture;
    SDL_Texture * asteroidTexture;
    std::list<std::shared_ptr<Asteroid>> asteroids;
    int spawnTimer;
    int difficultyLevel;
    float difficultyMultiplier;
    bool gameOver;
    int score;
    double survived;
};

#endif