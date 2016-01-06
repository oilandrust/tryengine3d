#ifndef GRAVITYOBJECT_H
#define GRAVITYOBJECT_H

#include "TryEngine.h"
#include "TREngine.h"
#include "CGLA/Vec3f.h"

using namespace CGLA;

class GravityObject: public Behaviour{
	protected:
		Vec3f velocity;
		float speed;
		bool jumping;

		
	public:
		GravityObject();
		~GravityObject();

		//TR3D routines
		void update();
		void stayOnGround(const RayCastHit& hit, bool overSomething);

};

#endif
