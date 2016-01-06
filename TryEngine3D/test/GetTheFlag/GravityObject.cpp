#include "GravityObject.h"

const float GravityObject::gravity = 15;

GravityObject::GravityObject(void):jumping(true),velocity(0),speed(10.0f)
{
}


GravityObject::~GravityObject(void)
{
}
void GravityObject::stayOnGround(){
	Vec3f position = getGameObject().getTransform()->getWorldPosition();

	Ray ray;
	ray.origine = position;
	ray.direction = Vec3f(0,0,-1);
	RayCastHit hit;
	bool overSomething = TREngine::getInstance()->rayCast(ray,hit,getGameObject().getCollider());
	bool onSomething = false;

	float dist;
	float size;
	if(overSomething && (hit.collider != getGameObject().getCollider())){
		dist = position[2] - hit.collider->getGameObject()->getTransform()->getWorldPosition()[2];
		if(hit.collider->getType().getName() == "SphereCollider"){
			SphereCollider* sphere = static_cast<SphereCollider*>(hit.collider);
			size = 2*sphere->getRadius()*sphere->getGameObject()->getTransform()->getScale()[2];
			onSomething = dist < size;
		}else if(hit.collider->getType().getName() == "BoxCollider"){
			BoxCollider* cube = static_cast<BoxCollider*>(hit.collider);
			size = cube->getSize()[2]*cube->getGameObject()->getTransform()->getScale()[2];
			onSomething = position[2] < size;
			//size -= 1;
		}
	}
 
	if(getGameObject().getTransform()->getWorldPosition()[2] < 0 || onSomething){
		if(onSomething){
			getGameObject().getTransform()->translate(0,0,size-position[2]);
			velocity[2] = 0;
		}else{
			getGameObject().getTransform()->translate(0,0,-position[2]);
			velocity[2] = 0;
		}
			
		jumping = false;
	}


}

void GravityObject::update(){
	
	Vec3f position = getGameObject().getTransform()->getWorldPosition();
	if( jumping ){
		getGameObject().getTransform()->translate(0,0,Timer::deltaTime()*velocity[2]);	
		//Gravity step
		velocity[2] -= Timer::deltaTime()*GravityObject::gravity;
		stayOnGround();
	}else if( position[2] > 1.5 ){
		Vec3f position = getGameObject().getTransform()->getWorldPosition();
		Ray ray;
		ray.origine = position;
		ray.direction = Vec3f(0,0,-1);
		RayCastHit hit;
		bool overSomething = TREngine::getInstance()->rayCast(ray,hit,getGameObject().getCollider());

		if(!overSomething){
			jumping = true;
		}else if(hit.collider->getType().getName()=="PlaneCollider")
			jumping = true;
	}

	if(getGameObject().getTransform()->getWorldPosition()[2] < 0 ){
		getGameObject().getTransform()->translate(0,0,-position[2]);
	}
}