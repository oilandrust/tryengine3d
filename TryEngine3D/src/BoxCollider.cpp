#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "includeGL.h"

const RTTI BoxCollider::TYPE("BoxCollider", &Collider::TYPE);

BoxCollider::BoxCollider(): center(0,0,0), size(2,2,2){
}

BoxCollider::BoxCollider(const Vec3f& Center, const Vec3f& Size): center(Center), size(Size){
}

BoxCollider::~BoxCollider(){
}

//Determine if the ray intersects the box using Slabs method
bool BoxCollider::rayCast(const Ray& ray, RayCastHit& hit) const{
	Vec3f worldCenter; 
	if(center == Vec3f(0))
		worldCenter = gameObject->getTransform()->getWorldPosition();
	else{ //need to rotate
		Mat4x4f worldMat = gameObject->getTransform()->getWorldTransformMatrix();
		Mat3x3f rotateMat = Mat3x3f(Vec3f(worldMat[0]),Vec3f(worldMat[1]),Vec3f(worldMat[2]));
		worldCenter = gameObject->getTransform()->getWorldPosition() + rotateMat * center;
	}
	
	//the box's axis
	Vec3f slabs[3];
	slabs[0] = gameObject->getTransform()->getForward();
	slabs[1] = gameObject->getTransform()->getUp();
	slabs[2] = gameObject->getTransform()->getRight();

	//std::cout<<slabs[2]<<" "<<slabs[1]<<" "<<slabs[0]<<std::endl;

	//the box halfhedges
	float he[3];
	he[0] = 0.5 * size[0] * gameObject->getTransform()->getScale()[0];
	he[1] = 0.5 * size[1] * gameObject->getTransform()->getScale()[1];
	he[2] = 0.5 * size[2] * gameObject->getTransform()->getScale()[2];

	float tmin = - 1000000000;
	float tmax = 10000000000;

	Vec3f p = worldCenter - ray.origine;

	for(int i = 0; i < 3; i++){
		float e = dot(slabs[i],p);
		float f = dot(slabs[i],ray.direction);

		if( fabsf(f) > 0 ){
			float finv = 1 / f;
			float t1 = ( e + he[i] ) * finv;
			float t2 = ( e - he[i] ) * finv;

			if( t1 > t2 ){
				float tmp = t1;
				t1 = t2;
				t2 = tmp;
			}

			if( t1 > tmin )
				tmin = t1;
			if( t2 < tmax )
				tmax = t2;

			if( tmin > tmax )
				return false;
			if( tmax < 0 )
				return false;

		}else if( ( -e - he[i] > 0 ) || ( -e + he[i] < 0 ) )
			return false;
	}

	return true;
}


const Vec3f& BoxCollider::getCenter()const{
	return center;
}
const Vec3f& BoxCollider::getSize()const{
	return size;
}

void BoxCollider::renderGuizmo()const{
	glBegin(GL_QUAD_STRIP);
	glColor3f(1,1,1);
	glVertex3fv( (center + 0.5 * Vec3f( -size[0], -size[1], size[2] )).get() );
	glVertex3fv( (center + 0.5 * Vec3f( size[0], -size[1], size[2] )).get() );
	glVertex3fv( (center + 0.5 * Vec3f( -size[0], size[1], size[2] )).get() );
	glVertex3fv( (center + 0.5 * Vec3f( size[0], size[1], size[2] )).get() );

	glVertex3fv( (center + 0.5 * Vec3f( -size[0], size[1], -size[2] )).get() );
	glVertex3fv( (center + 0.5 * Vec3f( size[0], size[1], -size[2] )).get() );
	
	glVertex3fv( (center + 0.5 * Vec3f( -size[0], -size[1], -size[2] )).get() );
	glVertex3fv( (center + 0.5 * Vec3f( size[0], -size[1], -size[2] )).get() );

	glVertex3fv( (center + 0.5 * Vec3f( -size[0], -size[1], size[2] )).get() );
	glVertex3fv( (center + 0.5 * Vec3f( size[0], -size[1], size[2] )).get() );

	glEnd();
}