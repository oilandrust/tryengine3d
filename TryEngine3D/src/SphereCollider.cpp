#include "SphereCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "includeGL.h"

const RTTI SphereCollider::TYPE("SphereCollider", &Collider::TYPE);

SphereCollider::SphereCollider():center(0,0,0), radius(1){
}

SphereCollider::~SphereCollider(){
}

void drawCircle(const Vec3f& center, float radius){
	glBegin(GL_LINE_LOOP);
	float angle;
	for(int i = 0; i < 60; i++){
		angle = 12*i*M_PI/360;
		glVertex3fv( (center + radius*Vec3f(cosf(angle),sin(angle),0)).get() );
	}
	glEnd();
}
void SphereCollider::renderGuizmo()const{
	drawCircle(center,radius);
	glPushMatrix();
	glRotatef(90,1,0,0);
	drawCircle(center,radius);
	glPopMatrix();
	glRotatef(90,0,1,0);
	drawCircle(center,radius);
}

void SphereCollider::setRadius(float rad){
	radius = rad;
}

bool SphereCollider::rayCast(const Ray& ray, RayCastHit& hit)const{
	Vec3f worldCenter = gameObject->getTransform()->getWorldPosition() + center;
	float lambda = (dot(worldCenter,ray.direction)-dot(ray.origine,ray.direction))/dot(ray.direction,ray.direction);

	Vec3f projectedCenter = ray.origine + lambda*ray.direction;

	return sqr_length( projectedCenter - worldCenter ) <= radius*radius; 
}
