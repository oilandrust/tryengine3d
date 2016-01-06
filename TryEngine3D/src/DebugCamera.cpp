#include "DebugCamera.h"
#include "TryEngine.h"


DebugCamera::DebugCamera():velocity(0){
}


DebugCamera::~DebugCamera(){
}

void DebugCamera::onKeyboard(const SDL_KeyboardEvent & event){
	Transform* trans = gameObject->getTransform();
	if (event.type == SDL_KEYDOWN){
		SDLKey keyPressed = event.keysym.sym;
		switch (keyPressed){
			case SDLK_UP: 
			case SDLK_w:
				velocity[0] = 1;
				//trans->translate(trans->getForward());
                break;
            case SDLK_DOWN: 
			case SDLK_s:
				velocity[0] = -1;
                //trans->translate(-trans->getForward());
                break;
            case SDLK_RIGHT: 
			case SDLK_d:
				velocity[1] = -1;
                //trans->translate(-trans->getRight());
                break;
            case SDLK_LEFT: 
			case SDLK_a:
				velocity[1] = 1;
                //trans->translate(trans->getRight());
                break;
		}
	}else if (event.type == SDL_KEYUP){
		SDLKey keyPressed = event.keysym.sym;
		switch (keyPressed){
			case SDLK_UP: 
			case SDLK_w:
            case SDLK_DOWN: 
			case SDLK_s:
                velocity[0] = 0;
                break;
            case SDLK_RIGHT: 
			case SDLK_d:
            case SDLK_LEFT: 
			case SDLK_a:
				velocity[1] = 0;
                break;
		}
	}
}

void DebugCamera::onMouseMotion(const SDL_MouseMotionEvent & event){
	if( abs(event.xrel) > 0.40f*Screen::width || abs(event.yrel) > 0.40f*Screen::height )
		return;

	Vec3f rotation = gameObject->getTransform()->getRotation();
	float pitch = 0;

	if(abs(90-(rotation[0] + Timer::deltaTime()*6*(event.yrel))) < 90 )
		pitch = Timer::deltaTime()*6*event.yrel;
	
	gameObject->getTransform()->rotate(pitch,0,-Timer::deltaTime()*6*event.xrel);

	if( abs(event.x-Screen::width/2) > Screen::width*0.45f 
		|| 
		abs(event.y-Screen::height/2) > Screen::height*0.45f
	  ) 
	  SDL_WarpMouseInWindow(Screen::windowHandle,Screen::width/2,Screen::height/2);
}
void DebugCamera::update(){
	Transform* trans = gameObject->getTransform();
	trans->translate(.5f*velocity[0]*trans->getForward() + .5f*velocity[1]*trans->getRight());
}