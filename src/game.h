#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>
#include <memory>
#include <random>
#include <SDL.h>
#include "controller.h"
#include "renderer.h"
#include "player.h"
#include "enemy.h"

class Game{
  public:
    void Run(Controller controller, Renderer renderer);
    void PlayerLogic(Controller * controller, Player * player);
    void ClearBulletsAndEnemies(Player * player);
    void SpawnEnemies();
    void MoveEnemies();
    void MoveBullets(Player * player);

  private:
    SDL_Texture * playerTexture;
    SDL_Texture * bulletTexture;
    SDL_Texture * enemyTexture;
    std::list<std::shared_ptr<Enemy>> enemies;
    int spawnTimer;
    int difficultyLevel;
    float difficultyMultiplier;
    bool gameOver;
    int score;
};

#endif