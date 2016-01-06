#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"
#include <iostream>
#include "StandardIncludes.h"


class GameObject;
class Behaviour;

struct Ray{
	Vec3f origine;
	Vec3f direction;
};

struct CollisionHit{
	Vec3f penetration;
};
struct RayCastHit;


/// finds the closests points of 2 rays, returns false if the ray are parallels
bool getClosestPointsOnRays(const Ray& ray1, const Ray ray2, Vec3f& point1, Vec3f& point2);

class Collider: public Component{
	public :
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

	public:
		Collider();
		virtual ~Collider();
		virtual void onCollisionEnter();
		virtual bool rayCast(const Ray& ray, RayCastHit& hit)const;
		virtual void renderGuizmo()const;

		bool isStatic()const { return misStatic; }
		void isStatic(bool stat) { misStatic = stat; }

	protected:
		bool misStatic;
};

struct RayCastHit{
	Collider* collider;
	Vec3f intersection;
};

#endif