#include "Collider.h"
#include "GameObject.h"
#include "Behaviour.h"

const RTTI Collider::TYPE("Collider", &Component::TYPE);

Collider::Collider():misStatic(true){
}

Collider::~Collider(){
}

void Collider::onCollisionEnter(){
	if(!gameObject){
		std::cerr<<"Collider with null game object!"<<std::endl;
		return;
	}
	std::cout<<"Collision Enter"<<std::endl;
}

bool Collider::rayCast(const Ray& ray, RayCastHit& hit)const{
	return false;
}

void Collider::renderGuizmo()const{
}
bool getClosestPointsOnRays(const Ray& ray1, const Ray ray2, Vec3f& point1, Vec3f& point2){
	float d1d2 = dot(ray1.direction,ray2.direction);
	if( 1 - fabsf(d1d2) < 0.000001)
		return false;
/*
	std::cout<<"d1: "<<ray1.direction<<std::endl;
	std::cout<<"d2: "<<ray2.direction<<std::endl;
	std::cout<<"o1: "<<ray1.origine<<std::endl;
	std::cout<<"o2: "<<ray2.origine<<std::endl;
*/	
	Vec3f delta = ray1.origine - ray2.origine;
	float dd1 = dot(delta,ray1.direction);
	float dd2 = dot(delta,ray2.direction);

	float s = ( dd1*d1d2 - dd2 ) / ( d1d2*d1d2 - 1 );
	float t = s*d1d2 - dd1;
/*	
	std::cout<<"num: "<<dd1*d1d2 - dd2 <<std::endl;
	std::cout<<"div: "<<d1d2*d1d2 - 1 <<std::endl;
	std::cout<<"s: "<<s<<std::endl;
	std::cout<<"t: "<<t<<std::endl;
*/
	point1 = ray1.origine + t * ray1.direction;
	point2 = ray2.origine + s * ray2.direction;
/*
	std::cout<<"p1 :"<<point1<<std::endl;
	std::cout<<"p2 :"<<point2<<std::endl;
*/
	return true;
}