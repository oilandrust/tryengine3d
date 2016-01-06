#ifndef SPHERECOLLIDER_H_INCLUDED
#define SPHERECOLLIDER_H_INCLUDED

#include "Collider.h"
#include "CGLA/Vec3f.h"

class SphereCollider: public Collider{
	public :
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

	protected:
		Vec3f center;
		float radius;

	public:
		SphereCollider();
		~SphereCollider();

		void renderGuizmo()const;

		void setRadius(float rad);
		float getRadius()const{ return radius; }
		Vec3f getCenter()const{ return center; }

		bool rayCast(const Ray& ray, RayCastHit& hit)const;
};

#endif
