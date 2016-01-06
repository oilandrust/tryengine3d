
#include "GetTheFlagApp.h"
#define _CRTDBG_MAP_ALLOC


int main(int argc, char *argv[])
{
	GetTheFlagApp* app = new GetTheFlagApp();

	//Standard initialisation
	app->initializeOpenGLWindow(640,480,false);
	app->initializeEngine();

	//app specific setup
	app->setupApp();

	//enter main loop
	app->run();

	//close and destroy app
	app->close();
	delete app;

	/*
	//RELEASE RESSOURCES
	RessourceManager::getInstance()->releaseRessources();
	shAnim.reset();
	shFragLitShaderTex.reset();
	shFragLitShader.reset();
	shPlaneMesh.reset();
	shCubeMesh.reset();
	shSphereMesh.reset();
	shAnim.reset();

	
	//kill singletons
	RessourceManager::getInstance()->shutDown();
	TREngine::getInstance()->shutDown();
	LightManager::getInstance()->shutDown();
	*/

	cout<<"exit"<<endl;
	_CrtDumpMemoryLeaks();


    return 0;
}


