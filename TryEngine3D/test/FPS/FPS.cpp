#include <SDL.h>
#include <SDL_mouse.h>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>

#include <TryEngine.h>

#include "FPSApp.h"
#include <map>
#include <sstream>

#define _CRTDBG_MAP_ALLOC

int main(int argc, char *argv[]){
    

	FPSApp* app = new FPSApp();

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

	_CrtDumpMemoryLeaks();
	SDL_Quit();


    return 0;
}


