#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
    Controller controller;
    Game game;
    Renderer renderer(::screenWidth, ::screenHeight);

    game.Run(controller, renderer);
    return 0;
}