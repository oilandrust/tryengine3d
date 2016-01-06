#ifndef PLANECOLLIDER_H_INCLUDED
#define PLANECOLLIDER_H_INCLUDED

#include "Collider.h"
#include "CGLA/Vec2f.h"

using namespace CGLA;

class PlaneCollider: public Collider{
	public :
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

	protected:
		Vec3f center;
		Vec3f normal;
		Vec2f size;

	public:
		PlaneCollider();
		PlaneCollider(const Vec3f& center, const Vec3f& normal, const Vec2f& size);
		~PlaneCollider();

		void renderGuizmo()const;

		Vec3f getNormal()const{ return normal; }
		Vec3f getWorldNormal()const;
		Vec3f getCenter()const{ return center; }
		Vec2f getSize()const{ return size; }

		bool rayCast(const Ray& ray, RayCastHit& hit)const;
};

#endif