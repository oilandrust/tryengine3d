#include "GameObject.h"
#include "Behaviour.h"
#include "Transform.h"
#include "Collider.h"
#include "Animation.h"
#include "MeshRenderer.h"
#include "ParticleSystem.h"

const RTTI GameObject::TYPE("GameObject", &Object::TYPE);

GameObject::GameObject():
transform(0),
meshRenderer(0),
behaviour(0),
collider(0),
particleSystem(0){
}

GameObject::~GameObject(){
	delete behaviour;
	delete transform;
	delete meshRenderer;
	delete particleSystem;
	delete collider;
}


void GameObject::addComponent(Component * comp){
	componentMap.insert( pair<std::string,Component*>(comp->getType().getName(),comp) );
    components.push_back(comp);
}

Transform* GameObject::getTransform()const{
    assert(this->transform != 0);
    return this->transform;

}
void GameObject::setTransform(Transform* trans){
    this->transform = trans;
}

Renderable* GameObject::getRenderer()const{
	return this->meshRenderer;
}
void GameObject::setRenderer(Renderable* renderer){
	this->meshRenderer = renderer;
}

void GameObject::setBehaviour(Behaviour* behav){
	//componentMap.insert( pair<std::string,Component*>(behav->getType().getName(),behav) );
	behaviour = behav;
}
Behaviour* GameObject::getBehaviour() const{
	return behaviour;
}

void GameObject::setCollider(Collider* coll){
	componentMap.insert( pair<std::string,Component*>(coll->getType().getName(),coll) );
	collider = coll;
}
Collider* GameObject::getCollider() const{
	return collider;
}

boost::shared_ptr<Animation> GameObject::getAnimation() const{
	return this->animation;
}
void GameObject::setAnimation(boost::shared_ptr<Animation> anim){
	this->animation = anim;
}

ParticleSystem* GameObject::getParticleSystem() const{
	return particleSystem;
}
void GameObject::setParticleSystem(ParticleSystem* partSys){
	particleSystem = partSys;
}


void GameObject::onCollisionEnter(){
	//if(behaviour)
	//	behaviour->onCollisionEnter();
}

