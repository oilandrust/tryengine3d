#ifndef WINDOW_H
#define WINDOW_H

#include "includeGL.h"
#include "TryEngine.h"
#include <QWidget>
#include <QMenuBar>
#include <QMainWindow>
#include <QListView>
#include <QTreeView>
#include "GOInspector.h"
#include "treemodel.h"

QT_BEGIN_NAMESPACE
class QSlider;
QT_END_NAMESPACE

class GLWidget;

class Window : public QMainWindow{	Q_OBJECT
	public:
		Window();

	protected:
		void keyPressEvent(QKeyEvent *event);

	private:
		GLWidget *glWidget;
		QTreeView *view;
		TreeModel* model;
		GOInspector* inspector;
		QToolBar* cameraModeToolBar;
		QAction* setMoveCam;
		QAction* setSelectCam;
		Scene* scene;
		GameObject* selectedObject;

	private:
		void setupScene();
		void setupMenuBar();
		GameObject * loadAndAttachChilds(GameObject *parent,boost::archive::text_iarchive& ia,std::ifstream & ifs);

	public slots :
		void createObject();
		void removeObject();

		void saveObject();
		void openObject();

		void createCube();
		void createSphere();
		void createPlane();

		void updateActions();
		void setMoveCamera();
		void setSelectCamera();

		void changeGameObject(GameObject * obj);
		void changeGameObject(QModelIndex idx);
	
		void printSceneInfo();

	signals :
		void gameObjectChanged(GameObject* obj);

};
//! [0]

#endif
