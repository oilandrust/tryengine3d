#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "TryEngine.h"
#include "trackballcameraQT.h"
#include <QModelIndex>
#include <QGLWidget>
#include <vector>
#include "includegl.h"



class GLWidget : public QGLWidget{ Q_OBJECT
	public: 
		typedef std::vector<Collider*>::const_iterator EditorCollidersIterator;
	private:
		enum MoveDirEnum{NONE, X, Y, Z};

	public:
		GLWidget(int timerInterval = 0, Scene* scen = NULL,QWidget *parent = 0);
		~GLWidget();

		QSize minimumSizeHint() const;
		QSize sizeHint() const;

		EditorCollidersIterator getEditorCollidersIteratorBegin()const;
		EditorCollidersIterator getEditorCollidersIteratorEnd()const;

		void setCameraMode(EditorCameraModeEnum mode);
		EditorCameraModeEnum getCameraMode()const;
		void addEditorCollider(Collider * collider);

	public slots:
		void changeGameObject(GameObject* obj);
		
	protected slots:
	  virtual void timeOutSlot();
		  
	signals:
		void gameObjectMoved();
		void gameObjectChanged(GameObject* obj);


	protected:
		void initializeGL();
		void paintGL();
		void resizeGL(int width, int height);
		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		virtual void timeOut();
		
	private:
		TrackBallCameraQT* camera;
		Scene* scene;
		GameObject* selectedObject;
		QTimer *m_timer;
		std::vector<Collider*> editorColliders;

		BoxCollider xAxis;
		BoxCollider yAxis;
		BoxCollider zAxis;
		
		MoveDirEnum movingDirection;
		Vec3f movePoint;
		Vec3f rayPoint;
};

 #endif