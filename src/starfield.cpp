#include "starfield.h"
///////////////////////
/*Star Implementation*/
///////////////////////
Star::Star(int x, int y, int speed) 
    : _x(x), _y(y), _speed(speed){}

std::vector<int> Star::GetPosition(){
    std::vector<int> pos{_x, _y};
    return pos;
}

int * Star::CurrentX(){
    return &_x;
}

int Star::GetSpeed(){
    return _speed;
}

void Star::Move(){
    _x -= _speed;

    if(_x < 0){
        _x += ::screenWidth;
    }
}

////////////////////////////
/*Starfield Implementation*/
////////////////////////////
Starfield::Starfield(){
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> heightDistr(0, ::screenHeight);
    std::uniform_int_distribution<> widthDistr(0, ::screenWidth);
    std::uniform_int_distribution<> speedDistr(1, 3);
    
    for(size_t i = 0; i < 250; i++){
        stars.emplace_back(std::make_shared<Star>
            (widthDistr(eng), heightDistr(eng), speedDistr(eng)));
    }
}

void Starfield::MoveStars(){
    for(auto s : stars){
        s->Move();
    }
}