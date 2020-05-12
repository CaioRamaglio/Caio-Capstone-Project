#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
    Controller controller;
    Game game;
    Renderer renderer(::screenWidth, ::screenHeight); // Constructor initializes SDL

    game.Run(controller, renderer); // main loop
    return 0;
}