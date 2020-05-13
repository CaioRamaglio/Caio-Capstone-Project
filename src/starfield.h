#ifndef STARFIELD_H
#define STARFIELD_H

#include <SDL.h>
#include <vector>
#include <random>
#include <memory>
#include "globals.h"

class Star{
  public:
    Star(int x, int y, int speed);
    std::vector<int> GetPosition();
    int * CurrentX();
    int GetSpeed();
    void Move();
  private:
    int _x;
    int _y;
    int _speed;
};

class Starfield{
  public:
    Starfield();
    void MoveStars();
    
    std::vector<std::shared_ptr<Star>> stars;

};

#endif