#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <vector>
#include <map>
#include "includeGL.h"
#include <CGLA/Mat4x4f.h>

#include "Transform.h"
#include "GameObject.h"

class MeshRenderer;
class Renderable;
class GameObject;
class Transform;
class Material;
class Light;
class Camera;

using namespace CGLA;

class Scene{
	public: static GLuint shadowMap;
			const static int shadowMapSize = 1024;
			static Mat4x4f projShadowMatrix;
    protected:

        std::vector<Transform*> transforms;
		std::vector<Light*> lights;
		std::vector<Camera*> cameras;

		bool useShadows;

		//std::vector<Renderable*> renderQueue;
		std::map<Material*, vector<Renderable*> > matSortedBatches;
		std::vector<Renderable*> shadowCasters;

        Transform* sceneRoot;
		Camera* mainCamera;

		void traverseSceneGraph();
		void make_proj_shadow_texture(Light* light);

    public:
		Scene();
		void clear();

        void render();
		      
		void setRoot(Transform* root);
        Transform* getRoot();

		void addGameObject(GameObject * object);
		void removeGameObject(GameObject* object);

		void addLight(Light* light);
		void addMeshRenderer(MeshRenderer* renderer);
		void applyLightsStates()const;
		void useShadow(bool use);
		void addCamera(Camera * camera);

		void setMainCamera(Camera* camera);
		void updateRenderQueue();


		void Scene::printNode(Transform * trans, int level){
			string tab;
			for(int i = 0; i < level ; i++){
				tab += "    ";
			}
			if(!trans){
				std::cout<<"NULL Transform!!"<<std::endl;
				return;
			}
			
			std::cout<<tab + trans->getGameObject()->getName()<<std::endl;

			Transform::ChildrenIterator childIt = trans->getChildrenIteratorBegin();
			for(; childIt != trans->getChildrenIteratorEnd(); ++childIt){
				printNode(*childIt,level+1);			
			}
		}
		void Scene::printSceneInfo(Scene* scene){
			std::cout<<"*********Objects in scene***********"<<std::endl;
			printNode(scene->getRoot(),0);
			std::cout<<"************************************"<<std::endl;
		}
};

void drawAxis(double scale);


#endif // SCENE_H_INCLUDED
