#include "controller.h"
#include <iostream>

Controller::Controller(){
	// initialize all booleans to false
	for(bool * b : buttons){
		*b = false;
	}
}

void Controller::Input(){
	SDL_Event e;
	
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				KeyDown(&e.key);
				break;
			case SDL_KEYUP:
				KeyUp(&e.key);
				break;
            default:
                break;
		}
	}
}

void Controller::KeyDown(SDL_KeyboardEvent * e){
	if (e->keysym.scancode == SDL_SCANCODE_UP)
	{
		up = true;
	}
	if (e->keysym.scancode == SDL_SCANCODE_DOWN)
	{
		down = true;
	}
	if (e->keysym.scancode == SDL_SCANCODE_LEFT)
	{
		left = true;
	}
	if (e->keysym.scancode == SDL_SCANCODE_RIGHT)
	{
		right = true;
	}

	if (e->repeat == 0 && e->keysym.scancode == SDL_SCANCODE_LCTRL)
	{
		firing = true;
	}
}

void Controller::KeyUp(SDL_KeyboardEvent * e){
	if(e->repeat == 0){
		if (e->keysym.scancode == SDL_SCANCODE_UP)
		{
			up = false;
		}
		if (e->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			down = false;
		}
		if (e->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			left = false;
		}
		if (e->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			right = false;
		}

		if (e->keysym.scancode == SDL_SCANCODE_LCTRL)
		{
			firing = false;
		}
	}
}