#include "Behaviour.h"
#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"
#include <SDL.h>

const RTTI Behaviour::TYPE("Behaviour", &Component::TYPE);

Behaviour::Behaviour(){
	gameObject = NULL;
}

Behaviour::~Behaviour(){
}

void Behaviour::setGameObject(GameObject* object){
	if(!gameObject)
		gameObject = object;
	else
		std::cout<<"In Behaviour::setGameObject : gameObject allready set"<<std::endl;
}
const GameObject& Behaviour::getGameObject(){
	return *gameObject;
}

void Behaviour::onMouseMotion(const SDL_MouseMotionEvent & event){}
void Behaviour::onMouseButton(const SDL_Event & event){}
void Behaviour::onJoystickButton(const SDL_Event & event){}
void Behaviour::onKeyboard(const SDL_KeyboardEvent & event){}
void Behaviour::update(){}
void Behaviour::onCollisionEnter(const CollisionHit& hit){}