#include "includeGL.h"
#include <QtGui>
#include <QtOpenGL>

#include <math.h>

#include "glwidget.h"
#include "sdlglutils.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

GLWidget::GLWidget(int timerInterval,Scene* scen, QWidget *parent): 
	QGLWidget(QGLFormat(QGL::SampleBuffers), parent), 
	selectedObject(NULL),	
	xAxis(Vec3f(0.5f,0,0),Vec3f(1,0.2f,0.2f)),
	yAxis(Vec3f(0,0.5f,0),Vec3f(0.2f,1,0.2f)),
	zAxis(Vec3f(0,0,0.5f),Vec3f(0.2f,0.2f,1)), 
	movingDirection(NONE){

	scene = scen;

	if( timerInterval == 0 )
		m_timer = 0;
	else
	{
		m_timer = new QTimer( this );
		connect( m_timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()) );
		m_timer->start( timerInterval );
	}

	GameObject* camObj = GameObjectFactory::getInstance()->createGameObject("EditorCamera");
	Transform* camTrans = new Transform(Vec3f(6,6,6));
	camera = new TrackBallCameraQT(camTrans,scene);
	Camera* cam = new Camera();

	Transform* root = scene->getRoot();

	cam->setGameObject(camObj);
	camObj->setTransform(camTrans);
	camTrans->setGameObject(camObj);
	scene->setMainCamera(cam);
	
	camera->setMotionSensivity(0.01f);	
}

GLWidget::~GLWidget(){
}

QSize GLWidget::minimumSizeHint() const{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const{
    return QSize(640, 480);
}

static void qNormalizeAngle(int &angle){
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::initializeGL(){

	GLenum err = glewInit();
	if (GLEW_OK != err)	{
	  /* Problem: glewInit failed, something is seriously wrong. */
	  fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	camera->look(0);
	scene->render();

	if(selectedObject && camera->getCameraMode() == SELECT){
		glDisable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);

		glBegin(GL_LINES);
		glColor3f(1,1,1);
		glVertex3fv(rayPoint.get());
		glVertex3fv(movePoint.get());
		glEnd();

		selectedObject->getTransform()->applyWorldTransform();

		xAxis.renderGuizmo();
		yAxis.renderGuizmo();
		zAxis.renderGuizmo();

		//selectedObject->getRenderer()->render();
		glPolygonMode(GL_FRONT, GL_FILL);
		drawAxis(1.0);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}
}

void GLWidget::resizeGL(int width, int height){
    int side = qMin(width, height);
    glViewport(0, 0, width, height);

	Screen::height = height;
	Screen::width = width;
	
	glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective(70,(double)width/height,0.001,1000);

    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent *event){
	camera->OnMousePressQT(*event);
	if(camera->getCameraMode() == SELECT){
		if(selectedObject){
			Ray ray = Camera::getMainCamera()->getWorldRayFromScreenPos(event->x(),event->y());
			//std::cout<<"xaxis attached to: "<<xAxis.getGameObject()->getName()<<std::endl;
			RayCastHit hit;
			if( xAxis.rayCast(ray,hit) ){
				
				std::cout<<"hit xAxis"<<std::endl;
				Transform* trans = selectedObject->getTransform();
				Ray xRay = { trans->getWorldPosition(), trans->getRight() };
				
				if( getClosestPointsOnRays(xRay,ray,movePoint,rayPoint) )
					movingDirection = X;
									
			}
			if( yAxis.rayCast(ray,hit) ){
				std::cout<<"hit yAxis"<<std::endl;

				Transform* trans = selectedObject->getTransform();
				Ray xRay = { trans->getWorldPosition(), trans->getUp() };
				
				if( getClosestPointsOnRays(xRay,ray,movePoint,rayPoint) )
					movingDirection = Y;
			}
			if( zAxis.rayCast(ray,hit) ){
				std::cout<<"hit zAxis"<<std::endl;
				Transform* trans = selectedObject->getTransform();
				Ray xRay = { trans->getWorldPosition(), trans->getForward() };
				
				if( getClosestPointsOnRays(xRay,ray,movePoint,rayPoint) )
					movingDirection = Z;
			}
		}
	}
}
void GLWidget::mouseReleaseEvent(QMouseEvent *event){
	camera->OnMouseReleaseQT(*event);
	if(camera->getCameraMode() == SELECT){
		movingDirection = NONE;
		//RAYCAST
		Ray ray = Camera::getMainCamera()->getWorldRayFromScreenPos(event->x(),event->y());
		RayCastHit hit;

		EditorCollidersIterator it = getEditorCollidersIteratorBegin();
		for(; it != getEditorCollidersIteratorEnd(); ++it){
			if( (*it)->rayCast(ray,hit) ){
				emit(gameObjectChanged((*it)->getGameObject()));
			}
		}
	}
}

void GLWidget::mouseMoveEvent(QMouseEvent *event){
	camera->OnMouseMotionQT(*event);
	
	if(camera->getCameraMode() == SELECT && selectedObject){
		if(selectedObject && movingDirection !=NONE ){
			Transform* trans = selectedObject->getTransform();
			Ray ray = Camera::getMainCamera()->getWorldRayFromScreenPos(event->x(),event->y());
			Ray axisRay;

			if( movingDirection == X ){
				axisRay.origine = trans->getWorldPosition();
				axisRay.direction = trans->getRight();
			}else if( movingDirection == Y ){
				axisRay.origine = trans->getWorldPosition();
				axisRay.direction = trans->getUp();
			}else if( movingDirection == Z ){				
				axisRay.origine = trans->getWorldPosition();
				axisRay.direction = trans->getForward();
			}else
				std::cout<<"shouldn't be here"<<std::endl;
					
			Vec3f newMovingPoint;
			if( getClosestPointsOnRays(axisRay,ray,newMovingPoint,rayPoint) ){
				Vec3f delta = newMovingPoint - movePoint;
				movePoint = newMovingPoint;

				if(fabsf(dot(delta,delta))>0){
					trans->translate(0.1*normalize(delta));	
					emit gameObjectMoved();
				}
			}
		}
	}
}

void GLWidget::timeOut(){
	updateGL();
}

void GLWidget::timeOutSlot(){
	timeOut();
}

void GLWidget::setCameraMode(EditorCameraModeEnum mod){
	camera->setCameraMode(mod);
}
EditorCameraModeEnum GLWidget::getCameraMode()const{
	return camera->getCameraMode();
}

void GLWidget::addEditorCollider(Collider * collider){
	editorColliders.push_back(collider);
}

GLWidget::EditorCollidersIterator GLWidget::getEditorCollidersIteratorBegin()const{
	return editorColliders.begin();
}
GLWidget::EditorCollidersIterator GLWidget::getEditorCollidersIteratorEnd()const{
	return editorColliders.end();
}

void GLWidget::changeGameObject(GameObject* obj){
	selectedObject = obj;
	xAxis.setGameObject(selectedObject);
	yAxis.setGameObject(selectedObject);
	zAxis.setGameObject(selectedObject);
}