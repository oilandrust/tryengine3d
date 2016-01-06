#ifndef BOXCOLLIDER_H_INCLUDED
#define BOXCOLLIDER_H_INCLUDED

#include "Collider.h"
#include "CGLA/Vec3f.h"

using namespace CGLA;

/**
 *Class for a oriented box collider Component.
 */
class BoxCollider: public Collider{
	public :
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

	protected:
		/**
		 *Center of the box in the GameObject owner's space.
		 */
		Vec3f center;
		/**
		 *Size (halfhedges) of the box in the GameObject owner's space.
		 */
		Vec3f size;

	public:
		BoxCollider();
		BoxCollider(const Vec3f& Center, const Vec3f& size);
		~BoxCollider();

		const Vec3f& getCenter()const;
		const Vec3f& getSize()const;

		/**
		 *Casts a ray against the box using the slabs method.
		 */
		bool rayCast(const Ray& ray, RayCastHit& hit)const;

		/**
		 *render the box guizmo, used by the engine in debug mode.
		 */
		void renderGuizmo()const;


};

#endif