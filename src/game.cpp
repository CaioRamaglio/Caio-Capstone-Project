#include "game.h"
#include <iostream>

void Game::Run(Controller controller, Renderer renderer)
{
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;

    // Initialize Textures
    char * playerTexturePath = (char *)"../gfx/player.png";
    char * bulletTexturePath = (char *)"../gfx/playerBullet.png";
    char * enemyTexturePath = (char *)"../gfx/asteroid.png";
    playerTexture = renderer.LoadTexture(playerTexturePath);
    bulletTexture = renderer.LoadTexture(bulletTexturePath);
    enemyTexture = renderer.LoadTexture(enemyTexturePath);

    // Initialize Player
    Player * player = new Player(100, 100, playerTexture);

    // Initialize Enemy Spawn Timer && Difficulty
    spawnTimer = 180;
    difficultyLevel = 1;
    difficultyMultiplier = 1;
    
    // main game loop
    while(true){
        frame_start = SDL_GetTicks();
        
        // check for game over
        if(gameOver){
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            delete player;
            renderer.PrepareScene();
            // display score
            renderer.PresentScene();
            break;
        }

        // clear the previous render
        renderer.PrepareScene();

        // check player input
        controller.Input();

        // game logic
        PlayerLogic(&controller, player);
        SpawnEnemies();
        ClearBulletsAndEnemies(player);

        //check collisions
        for(auto e : enemies){
            e->PlayerCollision(player);
            for(auto b : player->bullets){
                e->BulletCollision(b.get());
            }
        }

        // rendering
        // render player
        std::vector<float *> playerPosition = player->GetPosition();
        renderer.Blit(player->GetTexture(), playerPosition[0], playerPosition[1]);

        // render bullets
        if(player->bullets.size() > 0){
            for(auto b : player->bullets){
                renderer.Blit(b->GetTexture(), b->GetPosition()[0], b->GetPosition()[1]);
            }
        }

        // render enemies
        if(enemies.size() > 0){
            for(auto e : enemies){
                renderer.Blit(e->GetTexture(), e->GetPosition()[0], e->GetPosition()[1]);
            }
        }

        // display everything to the screen
        renderer.PresentScene();

        // time control
        frame_end = SDL_GetTicks();
        frame_duration = frame_end - frame_start;
        if (frame_duration < ::msPerFrame) {
            SDL_Delay(::msPerFrame - frame_duration);
        }
    }
}

void Game::PlayerLogic(Controller * controller, Player * player)
{
    // check if player is still alive
    if(player->GetHealth() == 0){
        gameOver = true;
    }

    // move player while clamping to the window boundaries
    if(controller->up == true){
        if(*player->GetPosition()[1] > 0){
            player->Move(0, -4);
        }else{
            player->Move(0, 0);
        }
    }
    if(controller->down == true){
        if(*player->GetPosition()[1] < screenHeight - player->GetHeight()){
            player->Move(0, 4);
        }else{
            player->Move(0, 0);
        }
    }
    if(controller->left == true){
        if(*player->GetPosition()[0] > 0){
            player->Move(-4, 0);
        }else{
            player->Move(0, 0);
        }
    }
    if(controller->right == true){
        if(*player->GetPosition()[0] < screenWidth - player->GetWidth()){
            player->Move(4, 0);
        }else{
            player->Move(0, 0);
        }
    }

    // fire a bullet
    if(controller->firing == true){
        player->Fire(bulletTexture);
    }
}

void Game::ClearBulletsAndEnemies(Player * player){
    // this function destroys one bullet and one asteroid each frame
    // but since two bullets/asteroids are never spawned in two consecutive
    // frames, it functions almost identically

    // clear bullets
    std::list<std::shared_ptr<Bullet>>::iterator bIt;
    for(bIt = player->bullets.begin(); bIt != player->bullets.end(); bIt++){
        if((*bIt)->IsAlive() == false){
            player->bullets.remove(*bIt);
            break;
        }
    }

    // clear enemies
    std::list<std::shared_ptr<Enemy>>::iterator eIt;
    for(eIt = enemies.begin(); eIt != enemies.end(); eIt++){
        if((*eIt)->IsAlive() == false){
            enemies.remove(*eIt);
            break;
        }
    }
}

void Game::SpawnEnemies(){
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
            enemies.emplace_back(
                new Enemy(::screenWidth, spawnHeightDistr(eng), enemyTexture)
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
            enemies.emplace_back(
                new Enemy(::screenWidth, spawnHeightDistr(eng), enemyTexture)
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
            enemies.emplace_back(
                new Enemy(::screenWidth, spawnHeightDistr(eng), enemyTexture)
            );
            enemies.emplace_back(
                new Enemy(spawnWidthDistr(eng), ::screenHeight, enemyTexture, 0, -4)
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
            enemies.emplace_back(
                new Enemy(::screenWidth, spawnHeightDistr(eng), enemyTexture)
            );
            enemies.emplace_back(
                new Enemy(spawnHeightDistr(eng), ::screenHeight, enemyTexture, 
                spawnDirectionDistr(eng), spawnDirectionDistr(eng))
            );
            enemies.emplace_back(
                new Enemy(spawnHeightDistr(eng), 0, enemyTexture, 
                spawnDirectionDistr(eng), spawnDirectionDistr(eng))
            );
            spawnTimer = (spawnTimerDistr(eng) * difficultyMultiplier) / 2;
            difficultyMultiplier -= 0.01;
            if(difficultyMultiplier <= 0.5){
                difficultyMultiplier = 1;
            }
        }
    }
}
