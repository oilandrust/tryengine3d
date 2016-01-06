#include "TryEngineApp.h"

#include "Scene.h"
#include "CollisionHandler.h"
#include "Timer.h"
#include "TREngine.h"
#include "Screen.h"
#include "RessourceManager.h"
#include "LightManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Collider.h"
#include "Animation.h"

#include <CGLA/Mat4x4f.h>

TryEngineApp::TryEngineApp():
windowHandle(0),
scene(0),
updateQueue(0),
animations(0),
collHandler(0),
timer(0),
trEngine(0),
ressManager(0)
{
}

TryEngineApp::~TryEngineApp(void)
{
	//DELTE ALL THE GAME OBJECT
	delete scene->getRoot()->getGameObject();

	//DELETE SPECIFIC OBJECTS
	delete scene;
	delete updateQueue;
	delete collHandler;
	delete timer;
	delete animations;

	//kill singletons
	RessourceManager::getInstance()->shutDown();
	TREngine::getInstance()->shutDown();
	LightManager::getInstance()->shutDown();
}

void TryEngineApp::initializeOpenGLWindow(int w, int h, bool fullscreen){
	assert( this->windowHandle == 0 );

	Uint32 flags = SDL_INIT_VIDEO;
	if(fullscreen)
		flags |= SDL_FULLSCREEN;
	 
    if (SDL_Init(flags) < 0) /* Initialize SDL's Video subsystem */
        sdldie("Unable to initialize SDL"); /* Or die on error */	

	/* Request an opengl 2.0 context.*/
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
 
    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	/* Create our window centered at 512x512 resolution */
	flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	if(fullscreen)
		flags |= SDL_WINDOW_FULLSCREEN;

    this->windowHandle = SDL_CreateWindow("FPS Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		w, h, flags);

	if (!this->windowHandle) /* Die if creation failed */
        sdldie("Unable to create window");

	Screen::windowHandle = this->windowHandle;
	Screen::width = w;
	Screen::height = h;

    /* Create our opengl context and attach it to our window */
    this->glContext = SDL_GL_CreateContext(windowHandle);

	    /* If using GLEW */
    GLenum err = glewInit();
    if (err != GLEW_OK)
        sdldie("Unable to initialize GLEW");
 
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);

	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_ShowCursor(0);
	SDL_EnableUNICODE(SDL_TRUE);

}

void TryEngineApp::initializeEngine(){
	assert( this->windowHandle != 0 );

	assert( this->scene == 0 );
	assert( this->updateQueue == 0 );
	assert( this->collHandler == 0 );
	assert( this->timer == 0 );
	assert( this->trEngine == 0 );

	//TR3D Managers
	this->scene = new Scene();
	this->scene->useShadow(false);
	
	this->updateQueue = new vector<Behaviour*>();
	this->animations = new vector<boost::shared_ptr<Animation> >();
	this->collHandler = new CollisionHandler();
	this->timer = new Timer();
	
	this->trEngine = TREngine::getInstance();
	this->trEngine->initialize(scene,updateQueue,collHandler);
}

void TryEngineApp::run(){
	SDL_Event event;

	TREngine::getInstance()->endFrame();
	while(true)
    {
		timer->begginFrame();
		while(SDL_PollEvent(&event)){
			switch(event.type)
			{
				case SDL_QUIT:
				exit(0);
				break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					for(size_t i = 0; i < updateQueue->size(); i++)
						(*updateQueue)[i]->onKeyboard((SDL_KeyboardEvent&)event);
				switch (event.key.keysym.sym)
				{
					break;
					case SDLK_ESCAPE:
					exit(0);
					break;
					case SDLK_f:
						if(SDL_GetModState())
						if(event.type == SDL_KEYDOWN)
							if(!TREngine::getInstance()->inDebugMode()){
								TREngine::getInstance()->setDebugMode(true);
							}else{
								TREngine::getInstance()->setDebugMode(false);
							}
						break;
					default :;
				}
				break;
				case SDL_MOUSEMOTION:
				for(size_t i = 0; i < updateQueue->size(); i++)
					(*updateQueue)[i]->onMouseMotion(event.motion);
				break;
				case SDL_MOUSEBUTTONUP:
				break;
				case SDL_JOYBUTTONDOWN:
					for(size_t i = 0; i < updateQueue->size(); i++)
						(*updateQueue)[i]->onJoystickButton(event);
				break;
				case SDL_MOUSEBUTTONDOWN:
					if( event.button.button == SDL_BUTTON_LEFT ){
						for(size_t i = 0; i < updateQueue->size(); i++)
							(*updateQueue)[i]->onMouseButton(event);
					}

				break;
			}
		}

		for(size_t i = 0; i < updateQueue->size(); i++){
			(*updateQueue)[i]->update();
		}
		for(size_t i = 0; i < this->animations->size(); i++){
			(*animations)[i]->animate(Timer::time());
		}
		

		collHandler->detectCollisions();

		/********** RENDER ****************/
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity( );
		gluPerspective(70,(double)Screen::width/Screen::height,.1f,200);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glPolygonMode(GL_FRONT,GL_FILL);
		glPolygonMode(GL_BACK,GL_LINE);
		glEnable(GL_CULL_FACE);

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity( );

        scene->render();

		if( TREngine::getInstance()->inDebugMode() ){
			glDisable(GL_DEPTH_TEST);
			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity( );
			glDisable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			glUseProgram(0);

			Camera::getMainCamera()->getGameObject()->getTransform()->applyViewTransform();
			
			drawAxis(3);

			vector<GameObject*>* objects = TREngine::getInstance()->getObjectList();
			for(size_t i = 0; i < objects->size(); i++){
				glPushMatrix();
				glMultMatrixf((*objects)[i]->getTransform()->getWorldTransformMatrix().get());
				drawAxis(1);
				glPopMatrix();
			}

			CollisionHandler::ColliderIter it = collHandler->colliderIteratorBegin();
			
			for(; it != collHandler->colliderIteratorEnd(); ++it){
				glPushMatrix();
				glMultMatrixf((*it)->getGameObject()->getTransform()->getWorldTransformMatrix().get());
				(*it)->renderGuizmo();
				glPopMatrix();
			}
			glEnable(GL_DEPTH_TEST);
			glPolygonMode(GL_FRONT,GL_FILL);
			glPolygonMode(GL_BACK,GL_LINE);
			glEnable(GL_CULL_FACE);
		}
		glFlush();
		SDL_GL_SwapWindow(this->windowHandle);
		
		TREngine::getInstance()->endFrame();
		timer->delay();
		timer->endFrame();
    }
}

void sdldie(char *msg)
{
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}