#ifndef GAMEOBJECTFACTORY_H_INCLUDED
#define GAMEOBJECTFACTORY_H_INCLUDED

#include <vector>
#include <string>

class GameObject;

using namespace std;

class GameObjectFactory{
	protected:
		std::vector<GameObject*> gameObjects;
		static GameObjectFactory* instance;
		GameObjectFactory();
		~GameObjectFactory();


	public:
		static GameObjectFactory* getInstance(){
			if(!instance)
				instance = new GameObjectFactory;

			return instance;
		};

		GameObject* createGameObject();
		GameObject* createGameObject(const string& name);
};

#endif