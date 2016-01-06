#ifndef FPSAPP_H
#define FPSAPP_h

#include <TryEngineApp.h>
#include <TryEngine.h>

#include "FirstPersonController.h"
#include "GravityObject.h"

class FPSApp : public TryEngineApp{
	public:
		FPSApp();
		virtual ~FPSApp();

		virtual void setupApp();

		virtual void close();

	private:
		/**GLOBAL BECAUSE NOT HANDLED BY THE RESSOURCE MANAGER YET*******/
		boost::shared_ptr<GLSLShader> fragLitShader;
		boost::shared_ptr<GLSLShader> fragLitShaderNoTex;
		boost::shared_ptr<TriMesh> planeMesh;
		boost::shared_ptr<TriMesh> cubeMesh;
		boost::shared_ptr<TriMesh> stairMesh;

		//FOR MATERIAL SORTED BATCHES, SHOULD BE HANDLED DIFFERENTLY BY THE SCENE
		Material* wallMat;
		Material* groundMat;
		Material* boxMat;
		Material* metalBoxMat;
		Material* stairMat ;


		void setupWorld();
		GameObject* createPlayer();
		GameObject* createStaticCube();
		GameObject* createCube();
		GameObject* createRamp();
		GameObject* createWall(int dir);
		GameObject* createPlane();
};

#endif
