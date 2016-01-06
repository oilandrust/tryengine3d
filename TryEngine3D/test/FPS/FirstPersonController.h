#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "TryEngine.h"
#include "TREngine.h"
#include "CGLA/Vec3f.h"

using namespace CGLA;

class FirstPersonController: public Behaviour{
	protected:
		SDL_Joystick* joystick;
		Vec3f velocity;
		float speed;
		Vec3f aimDir;
		float shootTimer;
		bool jumping;
		Transform* head;
		float mouseSensitivity;
		GameObject* weapon;

	public:
		FirstPersonController();
		~FirstPersonController();

		//TR3D routines
		void onMouseMotion(const SDL_MouseMotionEvent & event);
		void onMouseButton(const SDL_Event & event);
		void onJoystickButton(const SDL_Event & event);
		void onKeyboard(const SDL_KeyboardEvent & event);
		void update();
		void onCollisionEnter(const CollisionHit& hit);

		void setHead(Transform *h){head = h;}
		void setWeapon(GameObject* w){weapon = w;}

	protected:
		void stayOnGround(const RayCastHit& ray, bool overSomething);
};

#endif
