# Caio Ramaglio Capstone Project: Capstone Asteroid Shooter Game

This is a 

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.10
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * Linux: run `sudo apt install libsdl2-dev`
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
* SDL2_image >= 2.0
  * Linux: run `sudo apt install libsdl2-image-dev`
  * Windows and Linux installation instructions can be found [here](https://trenki2.github.io/blog/2017/07/04/using-sdl2-image-with-cmake/)
  * Libraries and binaries for Windows and MacOS can be found [here](https://www.libsdl.org/projects/SDL_image/)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./AsteroidShooter`

## Project Structure

* The project contains a `gfx` folder for pngs used in the game and `src` folder with the C++ code (7 cpp files and 7 header files).
  * In the globals.h header, we set a few `constexpr` to be used to define the window size and frame rate
  * In main.cpp, we have our main() function which initializes instances of a Renderer, a Controller and a Game class.
    * Controller constructor initializes all its bool values to false. These will be used later to determine which buttons have been pressed in a given frame and pass that information to the Game object.
    * Renderer constructor takes the screenWidth and screenHeight of the window as arguments. It initializes SDL, creates pointers to an SDL_Window object and an SDL_Renderer object, sets a value to hide the cursor on the window and initializes the use of pngs and jpgs as sprites.
    * Game is used to call Game.Run().
  * In game.h, we declare the Run() function which contains the main loop of the game, as well as various functions and private member variables to compute the game logic.
  * In game.cpp, we define Run():
    * first, the function declares a few Uint32 variables which will be used to control the duration of each frame.
    * next, 
