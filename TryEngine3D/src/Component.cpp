#include "Component.h"

#include "Object.h"
#include "GameObject.h"
#include "Transform.h"

const RTTI Component::TYPE("Component", &Object::TYPE);

Component::Component():gameObject(NULL){
}

Component::~Component(){
}

GameObject* Component::getGameObject(){
    return gameObject;
}

GameObject const* const Component::getGameObject()const{
    return gameObject;
}

void Component::setGameObject(GameObject* obj){
    gameObject = obj;
}

Vec3f Component::getWorldPosition()const{
	return gameObject->getTransform()->getWorldPosition();
}

Vec3f Component::getPosition()const{
	return Vec3f(0);
}
