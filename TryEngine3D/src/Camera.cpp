#include "Camera.h"
#include "Screen.h"
#include "Collider.h"
#include "includeGL.h"
#include "GameObject.h"
#include "Transform.h"

Camera* Camera::mainCamera = NULL;
const RTTI Camera::TYPE("Camera", &Component::TYPE);

Camera::Camera(): projectionType(PERSPECTIVE), aspectRatio(4.0f/3.0f), _near(0.01f), _far(1000), fovy(70) {
	if(!mainCamera)
		mainCamera = this;
}

Camera::Camera(float AspectRatio, float Near, float Far, float Fovy): projectionType(PERSPECTIVE), aspectRatio(AspectRatio), _near(Near), _far(Far), fovy(Fovy) {
	if(!mainCamera)
		mainCamera = this;
}

Camera::~Camera(){
}

void Camera::drawFrustum()const{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	gameObject->getTransform()->applyWorldTransform();
	//drawAxis();

	float hw = 1.5 * 2 * _near * tanf(fovy / 2);
	float ww = aspectRatio * hw;
	float hwf = hw * (_near + _far)/_near;
	float wwf = ww * (_near + _far)/_near;

	glColor3f(0,1,0);

	glPolygonMode(GL_FRONT,GL_LINE);
    glPolygonMode(GL_BACK,GL_LINE);
	glDisable(GL_CULL_FACE);

	glBegin(GL_QUADS);
	glVertex3f( -ww/2, -hw/2, _near);
	glVertex3f( ww/2, -hw/2, _near);
	glVertex3f( ww/2, hw/2, _near);
	glVertex3f( -ww/2, hw/2, _near);

	glVertex3f( -wwf/2, -hwf/2, _far);
	glVertex3f( wwf/2, -hwf/2, _far);
	glVertex3f( wwf/2, hwf/2, _far);
	glVertex3f( -wwf/2, hwf/2, _far);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glVertex3f( -wwf/2, -hwf/2, _far);
	glVertex3f( -ww/2, -hw/2, _near);
	glVertex3f( wwf/2, -hwf/2, _far);
	glVertex3f( ww/2, -hw/2, _near);
	glVertex3f( wwf/2, hwf/2, _far);
	glVertex3f( ww/2, hw/2, _near);
	glVertex3f( -wwf/2, hwf/2, _far);
	glVertex3f( -ww/2, hw/2, _near);
	
	glEnd();

	glPopMatrix();	
	glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_LINE);
    glEnable(GL_CULL_FACE);
}


Ray Camera::getWorldRayFromScreenPos(int xScreen, int yScreen)const{
	if(!gameObject){
		std::cerr<<"gameObject not set to Camera :"<<name<<std::endl;
		Ray ray = {Vec3f(0),Vec3f(0)};
		return ray;
	}
	Transform* transform = getGameObject()->getTransform();
	float Hw = 2 * _near * tanf(fovy/2);
	float Ww = aspectRatio * Hw;
	
	float xWorld = (float)xScreen / Screen::width - 0.5;
	float yWorld = (1 - (float)yScreen / Screen::height ) - 0.5;
	
	//coordinate of the mouse in the view plane in the object coordinate of the camera
	xWorld *= -Ww * 1.5;
	yWorld *= Hw * 1.5;
	
	//direction in object space
	Vec3f dir = _near * Vec3f(0,0,1) + Vec3f(xWorld,yWorld,0);

	//rotate to have it in world space
	Mat4x4f wrans = transform->getWorldInverseTransformMatrix();
	Mat3x3f rotMat = Mat3x3f(Vec3f(wrans[0]),Vec3f(wrans[1]),Vec3f(wrans[2]));
	dir =  rotMat * dir;

	Ray ray = {transform->getWorldPosition(), dir};
	return ray;
}


void Camera::setProjectionMatrix()const{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	switch(projectionType){
		case PERSPECTIVE:
		    gluPerspective(fovy,aspectRatio,_near,_far);
		break;
		case ORTHOGRAPHIC:
		    gluPerspective(fovy,aspectRatio,_near,_far);
		break;
	}
}