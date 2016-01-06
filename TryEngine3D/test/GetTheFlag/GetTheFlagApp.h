#ifndef GETTHEFLAGAPP_H
#define GETTHEFLAGAPP_H

#include <TryEngineApp.h>
#include <TryEngine.h>

#include "GravityObject.h"
#include "PlayerController.h"

class GetTheFlagApp : public TryEngineApp{
	public:
		GetTheFlagApp();
		virtual ~GetTheFlagApp();

		virtual void setupApp();

		virtual void close();

	private:
		/**GLOBAL BECAUSE NOT HANDLED BY THE RESSOURCE MANAGER YET*******/
		shared_ptr<Animation> shAnim;
		shared_ptr<GLSLShader> shFragLitShaderTex;
		shared_ptr<GLSLShader> shFragLitShader;
		shared_ptr<TR3D::TriMesh> shPlaneMesh;
		shared_ptr<TR3D::TriMesh> shCubeMesh;
		shared_ptr<TR3D::TriMesh> shSphereMesh;
		/****************************************************************/

		
		//FOR MATERIAL SORTED BATCHES, SHOULD BE HANDLED DIFFERENTLY BY THE SCENE
		Material* groundMat;
		Material* boxMat;
		Material* metalBoxMat;
		Material* playerMat;

		//Objects that have to be destroyed on shutdown and are not destroyed anywhere else
		Light* globalLight;
		Camera* mainCamera;

		GameObject* createPlane();
		GameObject* createCube();
		GameObject* createStaticCube();
		void setupWorld();
		GameObject* createLeg(const string& name);
		GameObject* createPlayer();


};

#endif
