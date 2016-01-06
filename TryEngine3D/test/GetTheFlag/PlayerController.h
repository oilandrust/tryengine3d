#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "TryEngine.h"
#include "TREngine.h"
#include "CGLA/Vec3f.h"

using namespace CGLA;

class PlayerController: public Behaviour{
	protected:
		SDL_Joystick* joystick;
		Vec3f velocity;
		float speed;
		Vec3f aimDir;
		float shootTimer;
		bool jumping;

		
	public:
		PlayerController();
		~PlayerController();

		//TR3D routines
		void onMouseMotion(const SDL_MouseMotionEvent & event);
		void onMouseButton(const SDL_Event & event);
		void onJoystickButton(const SDL_Event & event);
		void onKeyboard(const SDL_KeyboardEvent & event);
		void update();
		void onCollisionEnter();

		void setJoystick(SDL_Joystick* joy);

	protected:
		void handleJoystickDir();
		void stayOnGround();
};

#endif
