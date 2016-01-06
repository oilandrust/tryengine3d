#ifndef BULLET_H
#define BULLET_H

#include "TryEngine.h"
#include "CGLA/Vec3f.h"

using namespace CGLA;

class Bullet: public Behaviour{
	protected:
		Vec3f velocity;
		float speed;
		
	public:
		Bullet();
		~Bullet();

		void setVelocity(const Vec3f& dir){
			velocity = dir;
		}

		//TR3D routines
		void onMouseMotion(const SDL_MouseMotionEvent & event);
		void onMouseButton(const SDL_Event & event);
		void onKeyboard(const SDL_KeyboardEvent & event);
		void update();
		void onCollisionEnter();
};

#endif
