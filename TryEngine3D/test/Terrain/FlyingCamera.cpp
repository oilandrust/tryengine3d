#include "FlyingCamera.h"
#include "TryEngine.h"


FlyingCamera::FlyingCamera():velocity(0){
}


FlyingCamera::~FlyingCamera(){
}

void FlyingCamera::onKeyboard(const SDL_KeyboardEvent & event){
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

void FlyingCamera::onMouseMotion(const SDL_MouseMotionEvent & event){
	//Transform* trans = gameObject->getTransform();
	//trans->rotate(-event.xrel,event.yrel,0);
	Vec3f rotation = getGameObject().getTransform()->getRotation();
	float pitch = 0;
	int x = event.x-Screen::width/2;
	int y = event.y-Screen::height/2;
	
	if(abs(90-(rotation[0] + 0.1f*y)) < 90 )
		pitch = 0.1f*y;
	 getGameObject().getTransform()->rotate(pitch,0,-0.1f*x);
	SDL_WarpMouse(Screen::width/2,Screen::height/2);
}
void FlyingCamera::update(){
	Transform* trans = gameObject->getTransform();
	trans->translate(velocity[0]*trans->getForward() + velocity[1]*trans->getRight());
}