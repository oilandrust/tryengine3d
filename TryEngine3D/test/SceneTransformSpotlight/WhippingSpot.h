#ifndef WHIPPINGSPOT_H_INCLUDED
#define WHIPPINGSPOT_H_INCLUDED

#include "Behaviour.h"
#include "CGLA/Vec3f.h"
#include "CGLA/Vec2f.h"
#include "TryEngine.h"

class WhippingSpot: public Behaviour{
	protected:
		Vec2f target;
		Vec2f velocity;
		float speed;
		float dimension;

	public:
		WhippingSpot(float dim, float speed);
		~WhippingSpot();

		void update();
};

#endif
