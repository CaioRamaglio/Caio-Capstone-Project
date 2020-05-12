#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <list>
#include <memory>
#include <future>
#include <SDL.h>
#include "globals.h"

// forward declarations
class Renderer;

class Bullet{
  public:
    Bullet(float x, float y, SDL_Texture * texture);
    ~Bullet();
    void Move();
    std::vector<float *> GetPosition();
    int GetWidth();
    int GetHeight();
    bool IsAlive();
    void Dies();
    SDL_Texture * GetTexture();
  private:
    float _x;
    float _y;
    int _width;
    int _height;
    bool _alive;
    SDL_Texture * _texture;

    bool hitSomething;
    bool outOfBounds;

    std::vector<std::future<void>> ftrs;
    std::mutex mtx;
};

class Player{
  public:
    // Constructor
    Player(float x, float y, SDL_Texture * texture);
    
    // Getters/Setters
    std::vector<float *> GetPosition();
    int GetWidth();
    int GetHeight();
    int GetHealth();
    void SetHealth(int health);
    SDL_Texture * GetTexture();

    // Member Functions
    void Move(float x, float y);
    void Fire(SDL_Texture * bulletTexture);

    std::list<std::shared_ptr<Bullet>> bullets;
  private:
    // Private Member Variables
    float _x;
    float _y;
    int _width;
    int _height;
    int _health;
    SDL_Texture * _texture;
    int reloadTimer = 0; // number of frames between bullets
};

#endif