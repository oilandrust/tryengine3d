#include "CollisionHandler.h"
#include <map>
#include <CGLA/Mat4x4f.h>
#include <CGLA/Mat3x3f.h>

#include "SphereCollider.h"
#include "BoxCollider.h"
#include "PlaneCollider.h"
#include "StandardIncludes.h"
#include "Collider.h"
#include "GameObject.h"
#include "Behaviour.h"
#include "Transform.h"

using namespace CGLA;
using namespace std;


CollisionHandler::CollisionHandler(){
}

CollisionHandler::~CollisionHandler(){
}

void CollisionHandler::clear(){
	colliders.clear();
}

CollisionHandler::ColliderIter CollisionHandler::colliderIteratorBegin(){
	return colliders.begin();
}
CollisionHandler::ColliderIter CollisionHandler::colliderIteratorEnd(){
	return colliders.end();
}

bool CollisionHandler::rayCast(const Ray& ray, RayCastHit& hit, Collider* ignore)const{

	std::vector<Collider*> hits;
	for(size_t i = 0; i < colliders.size(); i++){
		if(colliders[i] != ignore)
			if(colliders[i]->rayCast(ray,hit))
				hits.push_back(colliders[i]);
	}
	Collider* closest = NULL;
	float minDist = 100000000;
	
	for(size_t i = 0; i < hits.size(); i++){
		
		float dist = length(ray.origine - hits[i]->getGameObject()->getTransform()->getWorldPosition());
		//cout<<hits[i]->getType().getName()<<dist<<endl;
		if( dist < minDist ){
			closest = hits[i];
			minDist = dist;
		}
	}
	if( closest ){
		//cout<<closest->getType().getName()<<endl;
		hit.collider = closest;
		return true;
	}else
		hit.collider = NULL;
	return false;

}

void CollisionHandler::addCollider(Collider *collider){
	colliders.push_back(collider);
}
void CollisionHandler::removeCollider(Collider *collider){
	//cout<<"collision handler removing"<<endl;
	std::vector<Collider*>::iterator it;
	bool has = false;
    for(it = colliders.begin(); it != colliders.end(); ++it){
		if(*it == collider){
			has = true;
            break;
		}
    }
	if(has)
		colliders.erase(it);
}

void CollisionHandler::detectCollisions(){

	vector<Collider*>::iterator it = colliders.begin();
	for(; it != colliders.end(); ++it){
		if(!(*it))
			cout<<"null collider!"<<endl;

		CollisionHit hit;
		hit.penetration = Vec3f(0);
		vector<Collider*>::iterator jt = it;
		++jt;
		string t1 = (*it)->getType().getName();

		bool inCollision = false;
		//cout<<(*it)->getGameObject()->getName()<<endl;
		for(; jt != colliders.end(); ++jt){
			if(!((*it)->isStatic() && (*jt)->isStatic())){
				string t2 = (*jt)->getType().getName();
			
				if( t1 == "SphereCollider" ){
					SphereCollider* c1 = static_cast<SphereCollider*>(*it);
					if( t2 == "SphereCollider" ){
						SphereCollider* c2 = static_cast<SphereCollider*>(*jt);
						inCollision = detectSphereSphereCollision(c1,c2,hit);
					}else if( t2 == "BoxCollider" ){
						BoxCollider* c2 = static_cast<BoxCollider*>(*jt);
						inCollision = detectSphereBoxCollision(c1,c2,hit);
					}else if( t2 == "PlaneCollider" ){
						PlaneCollider* c2 = static_cast<PlaneCollider*>(*jt);
						inCollision = detectSpherePlaneCollision(c1,c2,hit);
					}

				}else if( t1 == "BoxCollider" ){
					BoxCollider* c1 = static_cast<BoxCollider*>(*it);
					if( t2 == "SphereCollider" ){
						SphereCollider* c2 = static_cast<SphereCollider*>(*jt);
						inCollision = detectSphereBoxCollision(c2,c1,hit);
					}else if( t2 == "BoxCollider" ){
						BoxCollider* c2 = static_cast<BoxCollider*>(*jt);
						inCollision = detectBoxBoxCollision(c1,c2,hit);
					}else if( t2 == "PlaneCollider" ){
						PlaneCollider* c2 = static_cast<PlaneCollider*>(*jt);
						inCollision = detectBoxPlaneCollision(c1,c2,hit);
					}

				}else if( t1 == "PlaneCollider" ){
					PlaneCollider* c1 = static_cast<PlaneCollider*>(*it);
					if( t2 == "SphereCollider" ){
						SphereCollider* c2 = static_cast<SphereCollider*>(*jt);
						inCollision = detectSpherePlaneCollision(c2,c1,hit);
					}else if( t2 == "BoxCollider" ){
						BoxCollider* c2 = static_cast<BoxCollider*>(*jt);
						inCollision = detectBoxPlaneCollision(c2,c1,hit);
					}else if( t2 == "PlaneCollider" ){
						PlaneCollider* c2 = static_cast<PlaneCollider*>(*jt);
						inCollision = detectPlanePlaneCollision(c1,c2,hit);
					}
				}else
					cout<<"unknown collider type"<<endl;

				if(inCollision){
					//Notify the behviours if any that a collision occured
					Behaviour* be = (*it)->getGameObject()->getBehaviour();
					if(be)
						be->onCollisionEnter(hit);
					be = (*jt)->getGameObject()->getBehaviour();
					if(be)
						be->onCollisionEnter(hit);
			
					//MoveBack objects
					if(!(*it)->isStatic()){
						if(!(*jt)->isStatic()){
							(*it)->getGameObject()->getTransform()->translate(-hit.penetration/2);
							(*jt)->getGameObject()->getTransform()->translate(hit.penetration/2);
						}else
							(*it)->getGameObject()->getTransform()->translate(-hit.penetration);
					}else if(!(*jt)->isStatic())
							(*jt)->getGameObject()->getTransform()->translate(hit.penetration);

				}
			}
		}
	}
}

bool CollisionHandler::detectSphereSphereCollision(const SphereCollider* const col1,const SphereCollider* const col2, CollisionHit& hit){

	Vec3f c1 = col1->getGameObject()->getTransform()->getWorldPosition();
	Vec3f c2 = col2->getGameObject()->getTransform()->getWorldPosition();
	float r1 = col1->getRadius();
	float r2 = col2->getRadius();

	if(c1 == c2){
		hit.penetration = Vec3f(0,0,r1+r2);
		return true;
	}
	float d2 = sqr_length(c1 - c2);
	float sigmaR = (r1 + r2);
	
	if(d2 < sigmaR*sigmaR+0.00001){
		float d12 = length( c2 - c1 );
		hit.penetration = ( r1 + r2 - d12)*(c2 - c1)/d12;
		return true;
	}
	return false;
}

bool CollisionHandler::detectSphereBoxCollision(const SphereCollider* const col1,const BoxCollider* const col2, CollisionHit& hit){ 
	Vec3f c = col1->getGameObject()->getTransform()->getWorldPosition() + col1->getCenter();

	//the box's axis
	Vec3f A[3];
	A[2] = col2->getGameObject()->getTransform()->getForward();
	A[1] = col2->getGameObject()->getTransform()->getUp();
	A[0] = col2->getGameObject()->getTransform()->getRight();

	//center of sphere in box axis
	c = c - (col2->getGameObject()->getTransform()->getWorldPosition() + col2->getCenter());
	Vec3f C(dot(c,A[0]),dot(c,A[1]),dot(c,A[2]));
	float r = col1->getRadius();

	//Box halfedges
	float a[3];
	a[0] = 0.5 * col2->getSize()[0] * col2->getGameObject()->getTransform()->getScale()[0];
	a[1] = 0.5 * col2->getSize()[1] * col2->getGameObject()->getTransform()->getScale()[1];
	a[2] = 0.5 * col2->getSize()[2] * col2->getGameObject()->getTransform()->getScale()[2];

	//compute the closest point on the box to the sphere
	Vec3f closest = Vec3f(clamp(C[0],-a[0],a[0]),clamp(C[1],-a[1],a[1]),clamp(C[2],-a[2],a[2]));
	Vec3f v = closest-C;
	float dist2 = dot(v,v);

	//The sphere intersects the box iff closest is inside the sphere
	if( dist2 < r*r ){
		//If the center of the sphere is not in the box, the penetration is easy
		bool centerInside = true;
		for(int i = 0; i < 3; i++){
			centerInside = centerInside && (abs(C[i]) < a[i]);
		}
		if( !centerInside ){
			hit.penetration = (r-sqrt(dist2)+0.1)*normalize(v);
			return true;
		}

	}else
		return false;	
}
bool CollisionHandler::detectSpherePlaneCollision(const SphereCollider* const sphere, const PlaneCollider* const plane, CollisionHit& hit){ 
	//if( sphere->getGameObject()->getName() == "Player" )
	//	return false;
	Vec3f c = sphere->getGameObject()->getTransform()->getWorldPosition() + sphere->getCenter();
	Vec3f p = plane->getGameObject()->getTransform()->getWorldPosition() + plane->getCenter();

	Vec3f n = normalize(plane->getWorldNormal());

	float d = dot(n,p);
	float cDotn = dot(c,n);
	float num = abs(d) - abs(cDotn);
	float dcp2 = num*num;

	if( dcp2 < sphere->getRadius()*sphere->getRadius()){
		Vec3f planeScale = plane->getGameObject()->getTransform()->getScale();
		Vec2f planeSize(plane->getSize()[0] * planeScale[0],plane->getSize()[1] * planeScale[1]);

		Vec3f pc = p - c;
		Vec3f right = plane->getGameObject()->getTransform()->getRight();
		Vec3f up = cross(right,n);
		Vec3f cproj = Vec3f(dot(pc,right),dot(pc,up),0);
		//Vec3f cproj = p - (c - cDotn*n);
				
		if( ( abs(cproj[0]) <= planeSize[0] && abs(cproj[1]) <= planeSize[1] )   ){
			hit.penetration = (abs(num) - sphere->getRadius())*normalize(dot(pc,n)*n);
			return true;
		}
	}
	return false; 
}
bool CollisionHandler::detectBoxBoxCollision(const BoxCollider* const col1, const BoxCollider*const col2, CollisionHit& hit){ 
	Vec3f Pa = col1->getGameObject()->getTransform()->getWorldPosition() + col1->getCenter();
	Vec3f Pb = col2->getGameObject()->getTransform()->getWorldPosition() + col2->getCenter();

	//the box halfhedges
	float a[3];
	a[0] = 0.5 * col1->getSize()[0] * col1->getGameObject()->getTransform()->getScale()[0];
	a[1] = 0.5 * col1->getSize()[1] * col1->getGameObject()->getTransform()->getScale()[1];
	a[2] = 0.5 * col1->getSize()[2] * col1->getGameObject()->getTransform()->getScale()[2];
	float b[3];
	b[0] = 0.5 * col1->getSize()[0] * col2->getGameObject()->getTransform()->getScale()[0];
	b[1] = 0.5 * col1->getSize()[1] * col2->getGameObject()->getTransform()->getScale()[1];
	b[2] = 0.5 * col1->getSize()[2] * col2->getGameObject()->getTransform()->getScale()[2];

	//the box's axis
	Vec3f A[3];
	A[0] = col1->getGameObject()->getTransform()->getForward();
	A[1] = col1->getGameObject()->getTransform()->getUp();
	A[2] = col1->getGameObject()->getTransform()->getRight();
	Vec3f B[3];
	B[0] = col2->getGameObject()->getTransform()->getForward();
	B[1] = col2->getGameObject()->getTransform()->getUp();
	B[2] = col2->getGameObject()->getTransform()->getRight();

	//Translation in world space
	Vec3f v = Pb - Pa;
	//Translation in col1's space
	Vec3f T(dot(v,A[0]),dot(v,A[1]),dot(v,A[2]));

	//B's basis in A's basis
	float R[3][3];
	 //calculate rotation matrix
	for( int i=0 ; i<3 ; i++ )
		for( int k=0 ; k<3 ; k++ ) 
			R[i][k] = dot(A[i],B[k]); 
	
	float ra, rb, t;

	//A's basis vectors
	for( int i=0 ; i<3 ; i++ ){
		ra = a[i];
		rb = b[0]*fabs(R[i][0]) + b[1]*fabs(R[i][1]) + b[2]*fabs(R[i][2]);

		t = fabs( T[i] );

		if( t > ra + rb )
			return false;
	}

	//B's basis vectors
	for( int k=0 ; k<3 ; k++ ){
		ra = a[0]*fabs(R[0][k]) + a[1]*fabs(R[1][k]) + a[2]*fabs(R[2][k]); 
		rb = b[k];

		t =	fabs( T[0]*R[0][k] + T[1]*R[1][k] +	T[2]*R[2][k] );

		if( t > ra + rb )
			return false;
	}

	//9 cross products

	//L = A0 x B0
	ra = a[1]*fabs(R[2][0]) + a[2]*fabs(R[1][0]);
	rb = b[1]*fabs(R[0][2]) + b[2]*fabs(R[0][1]);

	t =	fabs( T[2]*R[1][0] - T[1]*R[2][0] );

	if( t > ra + rb )
		return false;

	//L = A0 x B1
	ra = a[1]*fabs(R[2][1]) + a[2]*fabs(R[1][1]);
	rb = b[0]*fabs(R[0][2]) + b[2]*fabs(R[0][0]);

	t =	fabs( T[2]*R[1][1] - T[1]*R[2][1] );

	if( t > ra + rb )
		return false;

	//L = A0 x B2
	ra = a[1]*fabs(R[2][2]) + a[2]*fabs(R[1][2]);
	rb = b[0]*fabs(R[0][1]) + b[1]*fabs(R[0][0]);

	t =	fabs( T[2]*R[1][2] - T[1]*R[2][2] );
	if( t > ra + rb )
		return false;

	//L = A1 x B0
	ra = a[0]*fabs(R[2][0]) + a[2]*fabs(R[0][0]);
	rb = b[1]*fabs(R[1][2]) + b[2]*fabs(R[1][1]);

	t =	fabs( T[0]*R[2][0] - T[2]*R[0][0] );

	if( t > ra + rb )
		return false;

	//L = A1 x B1
	ra = a[0]*fabs(R[2][1]) + a[2]*fabs(R[0][1]);
	rb = b[0]*fabs(R[1][2]) + b[2]*fabs(R[1][0]);

	t =	fabs( T[0]*R[2][1] - T[2]*R[0][1] );

	if( t > ra + rb )
		return false;

	//L = A1 x B2
	ra = a[0]*fabs(R[2][2]) + a[2]*fabs(R[0][2]);
	rb = b[0]*fabs(R[1][1]) + b[1]*fabs(R[1][0]);

	t =	fabs( T[0]*R[2][2] - T[2]*R[0][2] );

	if( t > ra + rb )
		return false;

	//L = A2 x B0
	ra = a[0]*fabs(R[1][0]) + a[1]*fabs(R[0][0]);
	rb = b[1]*fabs(R[2][2]) + b[2]*fabs(R[2][1]);

	t =	fabs( T[1]*R[0][0] - T[0]*R[1][0] );

	if( t > ra + rb )
		return false;

	//L = A2 x B1
	ra = a[0]*fabs(R[1][1]) + a[1]*fabs(R[0][1]);
	rb = b[0] *fabs(R[2][2]) + b[2]*fabs(R[2][0]);

	t =	fabs( T[1]*R[0][1] - T[0]*R[1][1] );

	if( t > ra + rb )
		return false;

	//L = A2 x B2
	ra = a[0]*fabs(R[1][2]) + a[1]*fabs(R[0][2]);
	rb = b[0]*fabs(R[2][1]) + b[1]*fabs(R[2][0]);

	t =	fabs( T[1]*R[0][2] - T[0]*R[1][2] );

	if( t > ra + rb )
		return false;

	/*no separating axis found,
	the two boxes overlap */
	hit.penetration = -normalize(Pa-Pb)/2;

	return true;  
}
bool CollisionHandler::detectBoxPlaneCollision(const BoxCollider* const col1, const PlaneCollider* const col2, CollisionHit& hit){ return false; }
bool CollisionHandler::detectPlanePlaneCollision(const PlaneCollider* const col1, const PlaneCollider* const col2, CollisionHit& hit){ return false; }