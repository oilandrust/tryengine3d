#include "Rotator.h"

Rotator::Rotator(float rotationSpeed){
	speed = rotationSpeed;
	//gameObject = NULL;
}

Rotator::~Rotator(){
}

void Rotator::update(){
	gameObject->getTransform()->rotate(0,0,speed);
}
