#ifndef BOUNCINGBALL_H_INCLUDED
#define BOUNCINGBALL_H_INCLUDED

#include "CGLA/Vec3f.h"
#include "Behaviour.h"
using namespace CGLA;

class BouncingBall: public Behaviour{
	protected:
		Vec3f velocity;
		float speed;
		float dimension;

	public:
		BouncingBall(float dim, float Speed);
		~BouncingBall();

		void update();
		void onCollisionEnter();
};

#endif
