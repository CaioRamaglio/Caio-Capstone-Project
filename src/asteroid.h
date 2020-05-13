#ifndef ASTEROID_H
#define ASTEROID_H

#include <iostream>
#include <vector>
#include <memory>
#include <future>
#include <SDL.h>
#include "player.h"

class Asteroid{
  public:
    // Constructor
    Asteroid(float x, float y, SDL_Texture * texture);
    Asteroid(float x, float y, SDL_Texture * texture, float dirX, float dirY);
    
    // Getters/Setters
    std::vector<float *> GetPosition();
    bool IsAlive();
    void Dies();
    SDL_Texture * GetTexture();

    // Member Functions
    void Move(float x, float y);
    void PlayerCollision(Player * p);
    void BulletCollision(Bullet * b);

    // Public Member Variable
    bool hitByBullet;

  private:
    // Private Member Variables
    float _x;
    float _y;
    int _width;
    int _height;
    bool _alive;
    SDL_Texture * _texture;
    std::vector<std::future<void>> ftrs;
    std::mutex mtx;
};

#endif