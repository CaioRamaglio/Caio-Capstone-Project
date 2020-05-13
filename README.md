# Caio Ramaglio Capstone Project: Capstone Asteroid Shooter Game

This is a prototype of a sidescroller shooter game intended as a solution to the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213) Capstone project. This is partly based on the tutorials by Lazy Foo which can be found [here](https://www.parallelrealities.co.uk/tutorials/#ppp)

In this game, the player can move a space ship and fire bullets at asteroids that move randomly through the screen. Each asteroid destroys nets you 100 points and the game gets progressively harder the longer you play (there are 5 levels of difficulty). When the player is hit by an asteroid, the application ends and their score and level of difficulty reached are printed to the console. 

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

## Simplified Project Structure

* The project contains a `gfx` folder for pngs used in the game and `src` folder with the C++ code (7 cpp files and 7 header files).
* On a high level, the project is initiated by main.cpp, which instantiates objects defined in controller.cpp, game.cpp and renderer.cpp. These are responsible for taking player input, simulate game logic behavior and render the output respectively.
* Inside game.cpp, are pointers to classes defined in player.cpp, asteroid.cpp and starfield.cpp. These are the game actors that will be operated upon and printed to the application window.
* if the Player's health reaches 0, the infinite loop breaks and the program prints the user's score and level of difficulty reached to the console.

## Detailed Project Structure

* In the globals.h header, we set a few `constexpr` to be used to define the window size and frame rate
* In main.cpp, we have our `main()` function which initializes instances of a Renderer, a Controller and a Game object.
  * Controller constructor initializes all its bool values to false. These will be used later to determine which buttons have been pressed in a given frame and pass that information to the Game object.
  * Renderer constructor takes the `::screenWidth` and `::screenHeight` of the window as arguments. It initializes SDL, creates pointers to an SDL_Window object and an SDL_Renderer object, sets a value to hide the cursor on the window and initializes the use of pngs and jpgs as sprites.
  * Game is used to call `Game.Run()`.
* In game.h, we declare the Run() function which contains the main loop of the game, as well as various functions and private member variables to compute the game logic.
* In game.cpp, we define `Game::Run()`:
  * this function takes two arguments of types Renderer and Controller which are passed down for `main()` and assigned to private pointers of Game
  * the function declares a few `Uint32` variables which will be used to control the duration of each frame.
  * next, we initialize `SDL_Texture *` to the textures that will be used for the player, bullets and asteroids using `Renderer::LoadTexture()`.
    * `Renderer::LoadTexture()` takes `char *` describing the path to the png file that will be used as a texture and returns and `SDL_Texture *` to said texture.
  * next, we instantiate shared_ptrs for Player and Starfield.
    * The Player constructor takes a starting position in x,y float coordinates and a texture and assigns them to private member variables of the object. It also sets the player's health to 1 and the width/height of its 'hitbox' which will be used to check collisions later.
    * The Starfield constructor uses the `<random>` module and instantiates 250 Star objects in `std::vector<Star>` at random positions on the window and with random speeds. These random `int` parameters are passed as arguments to the Star constructor which assigns these values to private member variables of that class. (Star class in declared together with Starfield class in starfield.h)
  * last step before entering the game loop is to initialize variables related to the game's settings. gameOver is set to false, score is set to 0, difficulty modifiers are set to 1 and the spawnTimer, which counts the number of frames between spawning new asteroids is set to 180 frames (should be equal to three seconds).
* still inside `Game::Run()`, we enter an infinite while loop that repeats until gameOver is set to true.
  * first, we assign a value to frame_start which will be used to achieve our desired frame rate at the very end of the loop
  * then, there's a call to `Game::GameOver()`, which return a bool. if it evaluates to false we break from the loop and the program ends, else the execution continues like normal. 
    * If the gameOver variable changes to true, this function will get rid of the remaining asteroids and bullets on screen, print the player's score to the terminal and return true.
  * next, we call `Renderer::PrepareScene()` which draws the black background color and clears all the other things drawn on top of it from the last frame, so we draw their new positions on this new frame
  * the following call is to `Controller::Input()` which checks if any `SDL_Event` matches one the following: clicking the X on the window corner, pressing down a keyboard button and releasing a keyboard button.
    * if X is clicked on, the program terminates immediately.
    * when a button is pressed down, we call `Controller::KeyDown()` which checks which button has been pressed (left, right, up, down or left control) and sets the appropriate boolean  variable (left, right, up, down and fire respectively) to true.
    * when a button is released, we call `Controller::KeyUp()` which checks which button has been released (left, right, up, down or left control) and sets the appropriate boolean  variable (left, right, up, down and fire respectively) to false.
  * with these booleans from the Controller class set to reflect the user's input, we can call `Game::PlayerLogic()`
    * first we check if the player's health is equal to 0. If that's the case we set gameOver to true and the program will exit at the beginning of the next frame.
    * if any of the direction booleans have been set to true, we call `Player::Move()` which takes an x and a y float and increments the player's position by that amount.
    * if the fire boolean has been set to true, we call `Player::Fire()` which creates a `std::shared_ptr<Bullet>` and places it on a `std::list<Bullet>`. There's a reloadTimer integer that ensures a gap of five frames between each new Bullet. (Bullet is declared together with Player in player.h)
      * the Bullet constructor takes x,y coordinates as well as a texture, sets its width and height just like the player, and sets a boolean _alive to true. Lastly, it launches a new thread that calls `Bullet::Move()`.
      * this thread is sets up a `std::lock_guard<mutex>` and enters a infinite while loop which checks if _alive is true and continues to move the object to the right until it exceeds the `::screenWidth`. When that happens, _alive is set to false and the loop breaks.
  * the next step in the main loop calls `Game::SpawAsteroids()` which instantiates new Asteroids and places them in a `std::list<Asteroid>` similar to bullets, but this list is a member of Game instead of Player.
    * there are two Asteroid constructors. the first is similar to Player and Bullet constructors, it takes x,y coordinates and a texture. It sets width, heigth and _alive just like Bullet. The second constructor also takes two additional float for the directions the Asteroid should fly towards in the x and the y axis. Both constructors launch a thread in the end that calls `Asteroid::Move()`. (the direction values of the first constructor send the object in a straight line towards the left)
    * this thread works almost identically to the Bullet thread, but it takes the direction the Asteroid should fly towards into account. It checks if the direction values are both 0, and sets the direction of the X axis to -4 (left) to keep from spawning Asteroid that dont move. this function also checks if the object has hit any of the boundaries of the window, instead of just the right-most like in Bullet. 
    * `Game::SpawnAsteroids()` also checks difficultyLevel and difficultyMultiplier variables to determine how many Asteroids should be spawned after the spawnTimer has ran out. The game gradually gets more difficult as Asteoids start spawning in different directions and more frequently. This function uses `<random>` to vary the spawnTimer between 60 and 120 frames (between 1 and 2 seconds)
  * next is `Game::ClearBulletsAndAsteroids()` which loops through all Bullets stored in the Player class list and all Asteroids stored in the Game class list. It checks if any of the elements' _alive is set to false and removes them from the list. Because they are shared_ptrs, this destroys the instance of the object. (This function breaks after removing one Bullet and one Asteroid in a single frame to avoid errors in iterating through a list while removing multiple objects)
  * the last step before starting rendering the objects is to call `Game::CheckCollisions()` which loops through all Asteroids calling `Asteroid::PlayerCollision()` and `Asteroid::BulletCollision()`.
    * `Asteroid::PlayerCollision()` takes a pointer to the Player and uses the x,y coordinates combined with width and height of both objects to determine whether their sprites are overlaping. If that's the case, the player health is set to 0 and the Asteroid's _alive is set to false. They will both be destroyed when `Game::GameOver()` is called the next frame.
    * `Asteroid::BulletCollision()` uses the same methos to determine whether the sprites are overlaping. If that's the case, both Asteroid and Bullet will have their booleans _alive set to false by calling `Asteroid::Dies()` and `Bullet::Dies()`. Additionally the boolean hitByBullet is set to true for the Asteroid, so when `Game::ClearBulletsAndAsteroids()` goes to clear it, it will increment the score by 100 points.
  * With all the game logic out of the way, the loop calls the function `Game::Render()`, which draws the Stars, the Player, the Bullets and the Asteroids, in that order.
    * the background stars are drawn by calling `Renderer::DrawBackground()`. This sets the Star color depending on its speed variable (faster stars are bighter) and draw the object as a short line on the screen.
    * all other object on the game are drawn by calling `Renderer::Blit()` which takes a `SDL_Texture *` and `float *` for x and y coordinates. It queries the attributes of the texture and renders it to a rectangle placed on the coordinates on the window.
  * Finally, we call `Renderer::PresentScene()` to put all of the sprites inside the window.
  * the next step is to update the window title to display the current player score as they player. This is done by calling `Renderer::UpdateWindowTitle()`.
  * Lastly, we assign the value to frame_end and subtract frame_start from it to get the frame_duration. If frame_duration is less than `::msPerFrame` we're aiming for, we tell SDL to wait for the maining time. 
  * If we reach this point the frame is done and we're ready to start a new frame by loop back to the start of the infinite loop inside `Game::Run()`.

## Capstone Project Rubrics Met

Loop, Function, I/O
* The project demonstrates an understanding of C++ functions and control structures.
  * there are many examples throughout the project, the execution of class Game is split into many function being called by `Game::Run()` defined in game.cpp line 4.
* The project accepts user input and processes the input.
  * in controller.cpp, the function `Controller::Input()` defined on line 11 calls the function `SDL_PollEvent()` which queries user input to determine its type. Based on this information we can direct the program to perform specific actions.
Object Oriented Programming
* The project uses Object Oriented Programming techniques.
  * the whole project is built around classes. the files player.h and player.cpp declare and implement two classes Player and Bullet.
* Classes use appropriate access specifiers for class members.
  * again player.h is a good example of the use of access specifiers in the declaration of class Player.
* Class constructors utilize member initialization lists.
  * In player.cpp, the constructors for class Player and class Bullet make use of initilization lists on lines 7 and 57 respectively
Memory Management
* The project uses smart pointers instead of raw pointers.
  * game.h declares shared pointers to Player, Starfield and multiple Asteroids in a list on lines 25, 26 and 32 respectively
Concurrency
* The project uses multithreading.
  * In player.cpp on line 62, the constructor for Bullet launches a new task using the function `Bullet::Move()`
* A mutex or lock is used in the project.
  * Again in player.cpp line 66, the function `Bullet::Move()` instantiates a `std::lock_guard<mutex>` to protect the thread from data races.