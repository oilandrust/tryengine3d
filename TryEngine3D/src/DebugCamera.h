#ifndef DEBUGCAMERA_H
#define DEBUGCAMERA_H 

#include "Behaviour.h"

/**
 *A built-in behaviour used by the engine in debug mode for free flying in the scene.
 */
class DebugCamera :public Behaviour
{
public:
	DebugCamera();
	~DebugCamera();

	//void onMouseMotion(const SDL_MouseMotionEvent & event);
	//void onMouseButton(const SDL_Event & event);
	//void onJoystickButton(const SDL_Event & event);
	void onKeyboard(const SDL_KeyboardEvent & event);
	void onMouseMotion(const SDL_MouseMotionEvent & event);
	void update();
	//void onCollisionEnter();

private:
	Vec3f velocity;
};

#endif

