#include "enemy.h"

Enemy::Enemy(float x, float y, SDL_Texture * texture){
    _x = x;
    _y = y;
    _width = _height = 48; 
    _texture = texture;
    _alive = true;
    ftrs.emplace_back(std::async(std::launch::async, &Enemy::Move, this, -4, 0));
}

Enemy::Enemy(float x, float y, SDL_Texture * texture, float dirX, float dirY){
    _x = x;
    _y = y;
    _width = _height = 48; 
    _texture = texture;
    _alive = true;
    ftrs.emplace_back(std::async(std::launch::async, &Enemy::Move, this, dirX, dirY));
}

Enemy::~Enemy(){
    std::cout << "Asteroid destructor" << std::endl;
}

std::vector<float *> Enemy::GetPosition(){
    std::vector<float *> position{&_x, &_y};
    return position;
}

bool Enemy::IsAlive(){
    return _alive;
}

void Enemy::Dies(){
    _alive = false;
}

SDL_Texture * Enemy::GetTexture(){
    return _texture;
}

void Enemy::Move(float x, float y){
    std::lock_guard lock(mtx);
    while(true){
        if (_alive == false){ break; }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        _x += x;
        _y += y;
        if (_x < 0 || _y < 0 || 
            _x > ::screenWidth || _y > ::screenHeight)
        {
            _alive = false;
            break;
        }
    }
}

void Enemy::PlayerCollision(Player * p){
    float playerX = *p->GetPosition()[0];
    float playerY = *p->GetPosition()[1];
    
    float maxX = (playerX < _x) ? _x : playerX;
    float minX = (playerX + p->GetWidth() > _x + _width) ? 
        _x + _width : playerX + p->GetWidth();

    float maxY = (playerY < _y) ? _y : playerY;
    float minY = (playerY + p->GetHeight() > _y + _height) ? 
        _y + _height : playerY + p->GetHeight();

    if(maxX < minX && maxY < minY){
        this->Dies();
        p->SetHealth(0);
        std::cout << "player collision" << std::endl;
    }
}

void Enemy::BulletCollision(Bullet * b){
    float bulletX = *b->GetPosition()[0];
    float bulletY = *b->GetPosition()[1];

    float maxX = (bulletX < _x) ? _x : bulletX;
    float minX = (bulletX + b->GetWidth() > _x + _width) ? 
        _x + _width : bulletX + b->GetWidth();

    float maxY = (bulletY < _y) ? _y : bulletY;
    float minY = (bulletY + b->GetHeight() > _y + _height) ? 
        _y + _height : bulletY + b->GetHeight();

    if(maxX < minX && maxY < minY){
        std::cout << "bullet collision" << std::endl;
        b->Dies();
        this->Dies();
    }
}