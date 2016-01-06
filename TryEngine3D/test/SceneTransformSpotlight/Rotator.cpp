#include "Rotator.h"

Rotator::Rotator(float rotationSpeed){
	speed = rotationSpeed;
}

Rotator::~Rotator(){
}

void Rotator::update(){
	//gameObject->getTransform()->rotate(Vec3f(0,0,speed));
}
