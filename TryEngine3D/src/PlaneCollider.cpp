#include "PlaneCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "includeGL.h"

const RTTI PlaneCollider::TYPE("PlaneCollider", &Collider::TYPE);

PlaneCollider::PlaneCollider(): center(0,0,0), normal(0,0,1), size(1,1){
}

PlaneCollider::PlaneCollider(const Vec3f& Center, const Vec3f& normal, const Vec2f& Size): center(Center), normal(normal), size(Size){
}

PlaneCollider::~PlaneCollider(){
}

Vec3f PlaneCollider::getWorldNormal()const{
	Mat3x3f invrot;
	transpose(gameObject->getTransform()->getWorldRotationMatrix(),invrot);
	return invrot*normal;
}

void PlaneCollider::renderGuizmo()const{
	Vec3f right = gameObject->getTransform()->getRight();
	Vec3f fwd = cross(right,normal);

	glBegin(GL_LINES);
	glVertex3fv(center.get());
	glVertex3fv((center+normal).get());
	glEnd();
    glBegin(GL_TRIANGLE_STRIP);
	glNormal3fv(normal.get());
        glVertex3fv((center - size[0]*right - size[1]*fwd).get());
        glVertex3fv((center - size[0]*right + size[1]*fwd).get());
        glVertex3fv((center + size[0]*right - size[1]*fwd).get());
        glVertex3fv((center + size[0]*right + size[1]*fwd).get());
    glEnd();
}

bool PlaneCollider::rayCast(const Ray& ray, RayCastHit& hit) const{
	
	Vec3f norm = getWorldNormal();

	Vec3f p = center + gameObject->getTransform()->getWorldPosition();
	Vec3f o = ray.origine;

	if( abs(dot(norm,ray.direction)) < 0.0001){
		/*
		if(dot(norm,p-o) == 0){
			hit.intersection = o;
			return true;
		}else*/
			return false;
	}
	

	float s = -dot(norm,o-p)/dot(norm,ray.direction);
	Vec3f intersect = o + s*ray.direction;
	Vec3f planeScale = gameObject->getTransform()->getScale();
	Vec2f planeSize(size[0] * planeScale[0],size[1] * planeScale[1]);

	Vec3f interProj = intersect-p;
	if(abs(interProj[0]) <= planeSize[0] && abs(interProj[1]) <= planeSize[1]){
			hit.intersection = intersect; 
			return true;
	}
	
	return false;
}