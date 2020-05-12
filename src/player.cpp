#include "player.h"
#include <iostream>

///////////////////////////
/* Player Implementation */
///////////////////////////
Player::Player(float x, float y, SDL_Texture * texture){
    _x = x;
    _y = y;
    _width = 40;
    _height = 48;
    _texture = texture;
    _health = 1;
}

std::vector<float *> Player::GetPosition(){
    std::vector<float *> position{&_x, &_y};
    return position;
}

int Player::GetWidth(){
    return _width;
}

int Player::GetHeight(){
    return _height;
}

int Player::GetHealth(){
    return _health;
}

void Player::SetHealth(int health){
    _health = health;
}

SDL_Texture * Player::GetTexture(){
    return _texture;
}

void Player::Move(float x, float y){
    _x += x;
    _y += y;
}

void Player::Fire(SDL_Texture * bulletTexture){
    if(reloadTimer > 0){ 
        reloadTimer -= 1;  
    }
    else{
        bullets.emplace_back(std::make_shared<Bullet>(_x + 48, _y + 16, bulletTexture));
        reloadTimer = 5;
    }
}

///////////////////////////
/* Bullet Implementation */
///////////////////////////
Bullet::Bullet(float x, float y, SDL_Texture * texture){
    _x = x;
    _y = y;
    _width = 9;
    _height = 26;
    _alive = true;
    _texture = texture;
    ftrs.emplace_back(std::async(std::launch::async, &Bullet::Move, this));
}

Bullet::~Bullet(){
    std::cout << "bullet destructor" << std::endl;
}

void Bullet::Move(){
    std::lock_guard lock(mtx);
    while(true){
        if(_alive == false){
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        _x += 12;
        if(_x > ::screenWidth){
            _alive = false;
            break;
        }
    }
}

std::vector<float *> Bullet::GetPosition(){
    std::vector<float *> position{&_x, &_y};
    return position;
}

int Bullet::GetWidth(){
    return _width;
}

int Bullet::GetHeight(){
    return _height;
}

bool Bullet::IsAlive(){
    return _alive;
}

void Bullet::Dies(){
    _alive = false;
}

SDL_Texture * Bullet::GetTexture(){
    return _texture;
}

