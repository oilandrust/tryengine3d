#include "GravityObject.h"


GravityObject::GravityObject():velocity(0),speed(10.0f),jumping(false)
{
	//getGameObject().getTransform()->lookAt(getGameObject().getTransform()->getWorldPosition() + aimDir);
}


GravityObject::~GravityObject(void)
{
}



void GravityObject::stayOnGround(const RayCastHit& hit, bool overSomething){
	Vec3f position = getGameObject().getTransform()->getWorldPosition();

	bool onSomething = false;

	float dist = 0;
	float trans = 0;
	if(overSomething){
		if(hit.collider->getType().getName() == "PlaneCollider"){
			PlaneCollider* sphere = static_cast<PlaneCollider*>(hit.collider);
			dist = position[2] - hit.intersection[2];
			trans = 1 - dist;
			onSomething = dist < 1;
		}else {
			if(hit.collider->getType().getName() == "BoxCollider"){
				dist = position[2] - hit.collider->getGameObject()->getTransform()->getWorldPosition()[2];
				BoxCollider* cube = static_cast<BoxCollider*>(hit.collider);
				float size = 0.5f*cube->getSize()[2]*cube->getGameObject()->getTransform()->getScale()[2];
				onSomething = dist < size + 1;
				trans = size + 1 - dist;
			}
		}
	}
	if(getGameObject().getTransform()->getWorldPosition()[2] < 1.5 || onSomething){
		if(onSomething){
			getGameObject().getTransform()->translate(0,0,trans);
			velocity[2] = 0;
		}else{
			getGameObject().getTransform()->translate(0,0,1-position[2]);
			velocity[2] = 0;
		}
			
		jumping = false;
	}

}

void GravityObject::update(){

	Transform * trans = getGameObject().getTransform();
	Vec3f position = trans->getWorldPosition();
	
	Ray ray;
	ray.origine = position;
	ray.direction = Vec3f(0,0,-1);
	RayCastHit hit;
	
	bool overSomething = TREngine::getInstance()->rayCast(ray,hit,getGameObject().getCollider());

	//Move
	
	if( jumping ){
		//Gravity step
		trans->translate(0,0,Timer::deltaTime()*speed*velocity[2]);
		velocity[2] -= Timer::deltaTime()*5.8f;
		stayOnGround(hit, overSomething);
	}else if(overSomething){
		stayOnGround(hit, overSomething);
		if(hit.collider->getType().getName() == "PlaneCollider")
			if(position[2] - hit.intersection[2] > 1.5){
				jumping = true;
			}

	}
}
