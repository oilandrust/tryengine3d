#ifndef FLYINGCAMERA_H
#define FLYINGCAMERA_H 

#include "Behaviour.h"

class FlyingCamera :public Behaviour
{
public:
	FlyingCamera();
	~FlyingCamera();

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

