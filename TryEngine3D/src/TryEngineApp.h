#ifndef TRYENGINEAPP_H
#define TRYENGINEAPP_H

#include <SDL.h>
#include <vector>
#include "Behaviour.h"

class Scene;
class CollisionHandler;
class Timer;
class TREngine;
class RessourceManager;
class Animation;

class TryEngineApp{
	public:
		TryEngineApp(void);
		virtual ~TryEngineApp(void);

		void initializeOpenGLWindow(int w, int h, bool fullscreen);
		void initializeEngine();
		virtual void setupApp() = 0;

		void run();

		virtual void close() = 0;

	protected:
		//SDL HANDLE FOR WINDOW AND OPENGL
		SDL_Window* windowHandle;
		SDL_GLContext glContext;

		//TR3D Managers
		Scene* scene;
		vector<Behaviour*>* updateQueue;
		vector< boost::shared_ptr<Animation> >* animations;
		CollisionHandler* collHandler;
		Timer* timer;
		TREngine* trEngine;
		RessourceManager* ressManager;
};

void sdldie(char *msg);

#endif
