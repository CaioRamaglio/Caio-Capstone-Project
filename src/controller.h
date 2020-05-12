#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL.h>
#include <vector>

class Controller{
  public:
    Controller();
    void Input(); // it will probably receive a player later
    void KeyDown(SDL_KeyboardEvent * e);
    void KeyUp(SDL_KeyboardEvent * e);

    bool up;
    bool down;
    bool left;
    bool right;
    bool firing;
    std::vector<bool *> buttons {&up, &down, &left, &right, &firing};
};

#endif