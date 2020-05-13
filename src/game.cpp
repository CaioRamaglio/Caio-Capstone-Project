#include "game.h"
#include <iostream>

void Game::Run(Controller controller, Renderer renderer)
{
    // Time control variables
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;

    // Initialize Player
    _player = new Player(100, 100, playerTexture);
    // Initialize Starfield background
    Starfield * starfield = new Starfield();

    _renderer = &renderer;
    _controller = &controller;

    // Initialize Textures
    char * playerTexturePath = (char *)"../gfx/player.png";
    char * bulletTexturePath = (char *)"../gfx/playerBullet.png";
    char * asteroidTexturePath = (char *)"../gfx/asteroid.png";
    playerTexture = _renderer->LoadTexture(playerTexturePath);
    bulletTexture = _renderer->LoadTexture(bulletTexturePath);
    asteroidTexture = _renderer->LoadTexture(asteroidTexturePath);

    // Initialize Game settings
    gameOver = false;
    spawnTimer = 180;
    difficultyLevel = 1;
    difficultyMultiplier = 1;
    score = 0;
    
    // Main Game Loop
    while(true){
        frame_start = SDL_GetTicks();
        
        // check for game over
        if(GameOver(starfield)){ break; }

        // clear the previous render
        renderer.PrepareScene();

        // check player input
        controller.Input();

        // game logic
        starfield->MoveStars();
        PlayerLogic();
        ClearBulletsAndAsteroids();
        SpawnAsteroids();
        CheckCollisions();

        // rendering
        // render background
        renderer.DrawBackground(starfield);

        // render player
        std::vector<float *> _playerPosition = _player->GetPosition();
        renderer.Blit(_player->GetTexture(), _playerPosition[0], _playerPosition[1]);

        // render bullets
        if(_player->bullets.size() > 0){
            for(auto b : _player->bullets){
                renderer.Blit(b->GetTexture(), b->GetPosition()[0], b->GetPosition()[1]);
            }
        }

        // render asteroids
        if(asteroids.size() > 0){
            for(auto a : asteroids){
                renderer.Blit(a->GetTexture(), a->GetPosition()[0], a->GetPosition()[1]);
            }
        }

        // display everything to the screen
        renderer.PresentScene();
        renderer.UpdateWindowTitle(score);

        // time control
        frame_end = SDL_GetTicks();
        frame_duration = frame_end - frame_start;
        if (frame_duration < ::msPerFrame) {
            SDL_Delay(::msPerFrame - frame_duration);
        }
    }
}

void Game::PlayerLogic()
{
    // check if player is still alive
    if(_player->GetHealth() == 0){
        gameOver = true;
    }

    // move player while clamping to the window boundaries
    if(_controller->up == true){
        if(*_player->GetPosition()[1] > 0){
            _player->Move(0, -4);
        }else{
            _player->Move(0, 0);
        }
    }
    if(_controller->down == true){
        if(*_player->GetPosition()[1] < screenHeight - _player->GetHeight()){
            _player->Move(0, 4);
        }else{
            _player->Move(0, 0);
        }
    }
    if(_controller->left == true){
        if(*_player->GetPosition()[0] > 0){
            _player->Move(-4, 0);
        }else{
            _player->Move(0, 0);
        }
    }
    if(_controller->right == true){
        if(*_player->GetPosition()[0] < screenWidth - _player->GetWidth()){
            _player->Move(4, 0);
        }else{
            _player->Move(0, 0);
        }
    }

    // fire a bullet
    if(_controller->firing == true){
        _player->Fire(bulletTexture);
    }
}

void Game::SpawnAsteroids(){
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> spawnHeightDistr(0, ::screenHeight);
    std::uniform_int_distribution<> spawnWidthDistr(0, ::screenWidth);
    std::uniform_int_distribution<> spawnDirectionDistr(-4, 4);
    std::uniform_int_distribution<> spawnTimerDistr(60, 120);
    
    if(spawnTimer > 0){
        --spawnTimer;
    }
    else{
        //level 1
        if(difficultyLevel == 1){
            asteroids.emplace_back(
                new Asteroid(::screenWidth, spawnHeightDistr(eng), asteroidTexture)
            );
            spawnTimer = spawnTimerDistr(eng) * difficultyMultiplier;
            difficultyMultiplier -= 0.02;
            if(difficultyMultiplier <= 0.9){
                difficultyMultiplier = 1;
                difficultyLevel = 2;
            }
        }

        //level 2
        if (difficultyLevel == 2){
            asteroids.emplace_back(
                new Asteroid(::screenWidth, spawnHeightDistr(eng), asteroidTexture)
            );
            spawnTimer = (spawnTimerDistr(eng) * difficultyMultiplier) / 2;
            difficultyMultiplier -= 0.02;
            if(difficultyMultiplier <= 0.9){
                difficultyMultiplier = 1;
                difficultyLevel = 3;
            }
        }

        //level 3
        if (difficultyLevel == 3){
            asteroids.emplace_back(
                new Asteroid(::screenWidth, spawnHeightDistr(eng), asteroidTexture)
            );
            asteroids.emplace_back(
                new Asteroid(spawnWidthDistr(eng), ::screenHeight, asteroidTexture, 0, -4)
            );
            spawnTimer = (spawnTimerDistr(eng) * difficultyMultiplier) / 2;
            difficultyMultiplier -= 0.01;
            if(difficultyMultiplier <= 0.8){
                difficultyMultiplier = 1;
                difficultyLevel = 4;
            }
        }

        //level 4
        if (difficultyLevel == 4){
            asteroids.emplace_back(
                new Asteroid(::screenWidth, spawnHeightDistr(eng), asteroidTexture)
            );
            asteroids.emplace_back(
                new Asteroid(spawnWidthDistr(eng), ::screenHeight, asteroidTexture, 0, -4)
            );
            asteroids.emplace_back(
                new Asteroid(spawnWidthDistr(eng), -48, asteroidTexture, 
                spawnDirectionDistr(eng), spawnDirectionDistr(eng))
            );
            spawnTimer = (spawnTimerDistr(eng) * difficultyMultiplier) / 2;
            difficultyMultiplier -= 0.01;
            if(difficultyMultiplier <= 0.5){
                difficultyMultiplier = 1;
                difficultyLevel = 5;
            }
        }

        //level 5
        if (difficultyLevel == 5){
            asteroids.emplace_back(
                new Asteroid(::screenWidth, spawnHeightDistr(eng), asteroidTexture)
            );
            asteroids.emplace_back(
                new Asteroid(spawnWidthDistr(eng), ::screenHeight, asteroidTexture, 0, -4)
            );
            asteroids.emplace_back(
                new Asteroid(spawnWidthDistr(eng), ::screenHeight, asteroidTexture, 
                spawnDirectionDistr(eng), spawnDirectionDistr(eng))
            );
            asteroids.emplace_back(
                new Asteroid(spawnWidthDistr(eng), -48, asteroidTexture, 
                spawnDirectionDistr(eng), spawnDirectionDistr(eng))
            );
            spawnTimer = spawnTimerDistr(eng) / 2;
        }
    }
}

void Game::ClearBulletsAndAsteroids(){
    // this function destroys one bullet and one asteroid each frame
    // but since two bullets/asteroids are never spawned in two consecutive
    // frames, it functions almost identically

    // clear bullets
    std::list<std::shared_ptr<Bullet>>::iterator bIt;
    for(bIt = _player->bullets.begin(); bIt != _player->bullets.end(); bIt++){
        if((*bIt)->IsAlive() == false){
            _player->bullets.remove(*bIt);
            break;
        }
    }

    // clear asteroids
    std::list<std::shared_ptr<Asteroid>>::iterator eIt;
    for(eIt = asteroids.begin(); eIt != asteroids.end(); eIt++){
        if((*eIt)->IsAlive() == false){
            if((*eIt)->hitByBullet){ score += 100; }
            asteroids.remove(*eIt);
            break;
        }
    }
}

void Game::CheckCollisions(){
    for(auto a : asteroids){
        a->PlayerCollision(_player);
        for(auto b : _player->bullets){
            a->BulletCollision(b.get());
        }
    }
}

bool Game::GameOver(Starfield * starfield){
    if(gameOver){
        for(auto a : asteroids){
            a->Dies();
        }
       for(auto b : _player->bullets){
            b->Dies();
        }
        while(asteroids.size() > 0 && _player->bullets.size() > 0){
            ClearBulletsAndAsteroids();
        }
        delete _player;
        delete starfield;

        std::cout << "Game Over" << std::endl;
        std::cout << "Your scored " << score << " points!" << std::endl;
        std::cout << "You reached level " << difficultyLevel << " of difficulty" << std::endl;

        return true;
    }
    return false;
}