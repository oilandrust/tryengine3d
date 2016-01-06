#ifndef COLLISIONHANDLER_H_INCLUDED
#define COLLISIONHANDLER_H_INCLUDED


#include <CGLA/Vec3f.h>
#include <vector>


class Collider;
class SphereCollider;
class BoxCollider;
class PlaneCollider;
struct Ray;
struct RayCastHit;
struct CollisionHit;

using namespace CGLA;
using namespace std;

/**
 *Clamp the value of a between b and c.
 */
inline float clamp(float a, float b, float c){
	if( a < b )
		return b;
	else if( a > c )
		return c;
	else
		return a;
}

/**
 *Core class of the engine, keeps track of the colliders present in the scene and resolves the collisions.
 */
class CollisionHandler{
	public: 
		typedef vector<Collider*>::iterator ColliderIter;

	protected:
		/**
		 *All the colliders in the scene
		 */
		vector<Collider*> colliders;

	public:
		CollisionHandler();
		~CollisionHandler();
		/**
		 *Remove all the collider from the handler, colliders still exist.
		 */
		void clear();
		void addCollider(Collider* collider);
		void removeCollider(Collider* collider);

		/**
		 *Resolve the collisions, n2 pass to detect the collision and to move the objects  so that they don't collide anymore.
		 *The object are moved according to the penetration odf the colliders.
		 */
		void detectCollisions();
		ColliderIter colliderIteratorBegin();
		ColliderIter colliderIteratorEnd();

		/**
		 *Cast a ray against all the colliders in the scene except ignore.
		 *Returns true if a collider is intersection with the ray, false otherwise.
		 *The reference to a RayCastHit is filled with info about the closest collider from the origine on the ray.
		 */
		bool rayCast(const Ray& ray, RayCastHit& hit,Collider* ignore = NULL)const;

	protected:
		/**
		 *Detect a collision between two spheres, the penetration is filled int the reference to the CollisionHit
		 */
		bool detectSphereSphereCollision(const SphereCollider* const col1, const SphereCollider* const col2, CollisionHit& hit);
		/**
		 *Detect a collision between a sphere and an oriented box, the penetration is filled int the reference to the CollisionHit
		 */
		bool detectSphereBoxCollision(const SphereCollider* const col1, const BoxCollider* const col2, CollisionHit& hit);
		/**
		 *Detect a collision between a sphere and a plane, the penetration is filled int the reference to the CollisionHit
		 */
		bool detectSpherePlaneCollision(const SphereCollider* const col1, const PlaneCollider* const col2, CollisionHit& hit);
		/**
		 *Detect a collision between two oriented boxes, the penetration is filled int the reference to the CollisionHit
		 */
		bool detectBoxBoxCollision(const BoxCollider* const col1, const BoxCollider* const col2, CollisionHit& hit);
		/**
		 *Detect a collision between an oriented box and a plane, the penetration is filled int the reference to the CollisionHit
		 */
		bool detectBoxPlaneCollision(const BoxCollider* const col1, const PlaneCollider* const col2, CollisionHit& hit);

		/**
		 *Detect a collision between two planes, not implemented/used
		 */
		bool detectPlanePlaneCollision(const PlaneCollider* const col1, const PlaneCollider* const col2, CollisionHit& hit);		
};

#endif
