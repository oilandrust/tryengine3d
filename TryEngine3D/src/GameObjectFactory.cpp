#include "GameObjectFactory.h"
#include "Transform.h"
#include "GameObject.h"

GameObjectFactory* GameObjectFactory::instance = NULL;

GameObjectFactory::GameObjectFactory(){
}

GameObjectFactory::~GameObjectFactory(){
}

GameObject* GameObjectFactory::createGameObject(){
	GameObject* object = new GameObject();
	string name("GameObject");
	object->setName(name);

	Transform* trans = new Transform();
	trans->setGameObject(object);
	object->setTransform(trans);

	return object;
}
GameObject* GameObjectFactory::createGameObject(const string& name){
	GameObject* object = new GameObject();

	object->setName(name);

		Transform* trans = new Transform();
	trans->setGameObject(object);
	object->setTransform(trans);
	
	return object;
}
