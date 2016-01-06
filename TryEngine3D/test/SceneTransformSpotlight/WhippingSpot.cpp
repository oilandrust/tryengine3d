#include "WhippingSpot.h"

WhippingSpot::WhippingSpot(float dim, float Speed){
	dimension = dim;
	speed = Speed;
	float vx = (-2*((float)rand()/RAND_MAX))+1;
	float vy = (-2*((float)rand()/RAND_MAX))+1;
	velocity = normalize(Vec2f(vx,vy));

	target = Vec2f(0,0);
}

WhippingSpot::~WhippingSpot(){
}

void WhippingSpot::update(){
	target += speed*velocity;
	if(abs(target[0]) > dimension || abs(target[1]) > dimension){
		target -= speed*velocity;
		float vx = (-2*((float)rand()/RAND_MAX))+1;
		float vy = (-2*((float)rand()/RAND_MAX))+1;
		velocity = normalize(Vec2f(vx,vy));
	}

	gameObject->getTransform()->lookAt(Vec3f(target[0],target[1],0));
}
