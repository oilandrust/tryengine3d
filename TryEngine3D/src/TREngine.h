#ifndef TRENGINE_H
#define TRENGINE_H

#include <vector>
#include <set>


class Scene;
class Behaviour;
class CollisionHandler;
class Camera;
class GameObject;
class Screen;
class Transform;
class Collider;
struct Ray;
struct RayCastHit;

using namespace std;


class TREngine{

	private:
		TREngine(void);
		
		static TREngine* instance;

		Scene* scene;
		vector<Behaviour*>* updateQueue;
		CollisionHandler* collisionHandler;
		vector<GameObject*> objects;

		set<GameObject*> deleteList;
		vector<GameObject*> addList;

		bool inDebug;
		GameObject* debugCamera;
		Camera* cam;
		Camera* mainCamera;

	public:
		~TREngine(void);
		static TREngine* getInstance(){
			if(!instance)
				instance = new TREngine();
			return instance;
		};

		const CollisionHandler* getCollisionHandler(){return collisionHandler;}

		void initialize(Scene* scene, vector<Behaviour*>* updateQueue, CollisionHandler* collisionHandler){
			this->scene = scene;
			this->updateQueue = updateQueue;
			this->collisionHandler = collisionHandler;
		}

		void shutDown();

		void setDebugMode(bool enable);
		bool inDebugMode(){return inDebug;}

		bool rayCast(const Ray& ray, RayCastHit& hit, Collider* ignore = NULL)const;

		void addGameObject(GameObject* gameObject);
		void deleteGameObject(GameObject* gameObject);

		vector<GameObject*>* getObjectList(){
			return &objects;
		}

		void endFrame();
};

#endif

