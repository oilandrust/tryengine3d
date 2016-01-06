#include "TREngine.h"
#include "Scene.h"
#include "Behaviour.h"
#include "CollisionHandler.h"
#include "DebugCamera.h"
#include "CGLA\Vec3f.h"
#include "Screen.h"
#include "Camera.h"
#include "Transform.h"
#include "GameObject.h"

using namespace CGLA;



TREngine* TREngine::instance = NULL;

TREngine::TREngine():scene(NULL),updateQueue(NULL),collisionHandler(NULL),inDebug(false)
{
	cout<<"new engine"<<endl;
	debugCamera = new GameObject();
	cam = new Camera((float)800/600,1,1000,70);
	debugCamera->setName("Debug Camera");
	cam->setGameObject(debugCamera);
	Transform* cameraTransform = new Transform(Vec3f(6,6,6));
	debugCamera->setTransform(cameraTransform);
	cameraTransform->setGameObject(debugCamera);
	cameraTransform->lookAt(Vec3f(0,0,0));
	
	DebugCamera* controler = new DebugCamera();
	debugCamera->setBehaviour(controler);
	controler->setGameObject(debugCamera);
}

void TREngine::shutDown(){
	objects.clear();
	//collisionHandler->clear();
	//delete collisionHandler;
	//scene->clear();
	//delete scene;

	delete this;
}

TREngine::~TREngine()
{
	delete debugCamera;
	delete cam;
	TREngine::instance = 0;
}

void TREngine::addGameObject(GameObject* gameObject){
	addList.push_back(gameObject);
}

bool TREngine::rayCast(const Ray& ray, RayCastHit& hit,Collider* ignore)const{
	return collisionHandler->rayCast(ray,hit,ignore);
}

void TREngine::endFrame(){

	for(size_t i = 0; i < addList.size(); i++){
		scene->addGameObject(addList[i]);
		
		
		Transform* node = addList[i]->getTransform();
		vector<Transform*> openList;
		openList.push_back(node);
		while( !openList.empty() ){	
			node = openList.back();
			openList.pop_back();
			objects.push_back(node->getGameObject());
			Transform::ChildrenIterator childIt = node->getChildrenIteratorBegin();

			for(; childIt != node->getChildrenIteratorEnd(); ++childIt){
				openList.push_back(*childIt);				
			}
		}

		if(addList[i]->getBehaviour())
			updateQueue->push_back(addList[i]->getBehaviour());

		if(addList[i]->getCollider()){
			//cout<<"inserting collider"<<endl;
			collisionHandler->addCollider(addList[i]->getCollider());
		}
	}

	for(set<GameObject*>::iterator it = deleteList.begin(); it != deleteList.end(); ++it){
		//cout<<"remove from scene"<<endl;
		scene->removeGameObject(*it);

		//cout<<"remove collider"<<endl;
		if((*it)->getCollider())
			collisionHandler->removeCollider((*it)->getCollider());

		std::vector<GameObject*>::iterator jt;
		bool haso = false;
		for(jt = objects.begin(); jt != objects.end(); ++jt){
			if(*jt == *it){
				haso = true;
				break;
			}
		}
		if(haso)
			objects.erase(jt);

		//cout<<"remove behaviour"<<endl;
		if((*it)->getBehaviour()){
			std::vector<Behaviour*>::iterator jt;
			bool has = false;
			for(jt = updateQueue->begin(); jt != updateQueue->end(); ++jt){
				if(*jt == (*it)->getBehaviour()){
					has = true;
					break;
				}
			}
			if(has)
				updateQueue->erase(jt);
		}

		//cout<<"delete"<<endl;
		//delete *it;
		//cout<<"done"<<endl;
	}

	bool refresh = false;
	if(!addList.empty()){
		addList.clear();
		refresh = true;
	}
	if(!deleteList.empty()){
		deleteList.clear();
		refresh = true;
	}
	if(refresh)
		scene->updateRenderQueue();
}

void TREngine::deleteGameObject(GameObject* gameObject){
	deleteList.insert(gameObject);
}


void TREngine::setDebugMode(bool enable){
	if(enable && !inDebug){
		mainCamera = Camera::getMainCamera();
		Camera::setMainCamera(cam);
		addGameObject(debugCamera);
		inDebug = true;
	}else{
		Camera::setMainCamera(mainCamera);
		deleteGameObject(debugCamera);
		inDebug = false;
	}
}