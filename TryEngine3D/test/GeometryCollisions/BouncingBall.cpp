#include "BouncingBall.h"

BouncingBall::BouncingBall(float dim, float Speed){
	dimension = dim;
	speed = (float)rand()/RAND_MAX;
	float vx = (-2*((float)rand()/RAND_MAX))+1;
	velocity = normalize(Vec3f(vx,0,0));

}

BouncingBall::~BouncingBall(){
}

void BouncingBall::update(){
	Vec3f target = gameObject->getTransform()->getPosition();
	target += speed*velocity;

	if(abs(target[0]) > dimension || abs(target[1]) > dimension){
		velocity[0] = -velocity[0];
	}else
		gameObject->getTransform()->translate(speed*velocity);
}

void BouncingBall::onCollisionEnter(){
	velocity[0] = -velocity[0];
	gameObject->getTransform()->translate(speed*velocity);
}