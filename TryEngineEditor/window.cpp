#include "includeGL.h"
#include <QtGui>
#include <QSizePolicy>
#include <QToolBar>

#include "glwidget.h"
#include "window.h"
#include <QStandardItem>
#include "GOHierarchyItem.h"
#include <boost/archive/archive_exception.hpp>
#include "Transform.h"

using namespace std;
using namespace boost;
using namespace archive;


Window::Window():selectedObject(NULL){
	//Setup the TryEngine Scene
	setupScene();
	//Setup the OpenGLWindow
    glWidget = new GLWidget(50,scene);

	//MODEL/VIEW
	//enable drag and drop
	view = new QTreeView();
	view->setDragEnabled(true);
	view->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	view->viewport()->setAcceptDrops(true);
	view->setDropIndicatorShown(true);
	view->setDragDropMode(QAbstractItemView::InternalMove);

	view->setContextMenuPolicy ( Qt::ActionsContextMenu );
	QAction* removeAction = new QAction("remove", view);
	view->addAction(removeAction);
	connect(removeAction, SIGNAL(triggered()), this, SLOT(removeObject()));

	QSizePolicy sp = view->sizePolicy();
	sp.setHorizontalPolicy(QSizePolicy::Minimum);
	view->setSizePolicy(sp);

	model = new TreeModel(this);//GOHierarchyModel(this);
	model->setRootItem(scene->getRoot());
	view->setModel(model);

	//Setup the menu bar
	setupMenuBar();
	
	//Layout
	QWidget* central = new QWidget();
	setCentralWidget(central);
	QHBoxLayout* globalLayout = new QHBoxLayout(central);
	centralWidget()->setLayout(globalLayout);
	
	inspector = new GOInspector();
	
	globalLayout->addWidget(glWidget);
    globalLayout->addWidget(inspector);
	globalLayout->addWidget(view);

	//connect gameObject Selection
	connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(changeGameObject(QModelIndex)));
	connect(this, SIGNAL(gameObjectChanged(QModelIndex)), view, SLOT(setCurrentIndex(QModelIndex)) );
	
	connect(glWidget, SIGNAL(gameObjectChanged(GameObject*)), this, SLOT(changeGameObject(GameObject*)));
	connect(this, SIGNAL(gameObjectChanged(GameObject*)), inspector, SLOT(changeGameObject(GameObject*)) );
	connect(this, SIGNAL(gameObjectChanged(GameObject*)), glWidget, SLOT(changeGameObject(GameObject*)) );

	connect(glWidget, SIGNAL(gameObjectMoved()), inspector, SLOT(updateView()) );

	//Toolbar
	cameraModeToolBar = addToolBar(tr("CameraMode"));
	setMoveCam = new QAction("move",this);
	setSelectCam = new QAction("select",this);
	cameraModeToolBar->addAction(setMoveCam);
	cameraModeToolBar->addAction(setSelectCam);
	setMoveCam->setCheckable(true);
	setMoveCam->setChecked(true);
	setSelectCam->setCheckable(true);

	connect(setMoveCam, SIGNAL(triggered()), this, SLOT(setMoveCamera()));
	connect(setSelectCam, SIGNAL(triggered()), this, SLOT(setSelectCamera()));

	setWindowTitle(tr("TryEngine Editor"));
}

void Window::removeObject(){
	QModelIndex current = view->currentIndex();
	QModelIndex parent = view->model()->parent(current);

	view->model()->removeRows(current.row(), 1, parent); 
}

void Window::setupMenuBar(){
		//FILE MENU
	QMenu* fileMenu = new QMenu("File");
	menuBar()->addMenu(fileMenu);
	QAction* newSceneAction = new QAction("New Scene",this);
	QAction* saveSceneAction = new QAction("Save",this);
	QAction* openSceneAction = new QAction("Open",this);
	fileMenu->addAction(newSceneAction);
	fileMenu->addAction(saveSceneAction);
	fileMenu->addAction(openSceneAction);
	connect(saveSceneAction, SIGNAL(triggered()), this, SLOT(saveObject()));
	connect(openSceneAction, SIGNAL(triggered()), this, SLOT(openObject()));

	/*
	QMenu* edit = new QMenu("Edit");
	menuBar()->addMenu(edit);

	QAction *redoAction = model->getUndoStack()->createRedoAction(this, "Redo");
	redoAction->setShortcut(QKeySequence("Ctrl+Y"));
	
	QAction* undoAction = model->getUndoStack()->createUndoAction(this,"Undo");
	undoAction->setShortcut(QKeySequence("Ctrl+Z"));
	
	edit->addAction(undoAction);
	edit->addAction(redoAction);
*/
	//GameObject Menu

	QMenu* GObjectMenu = new QMenu("GameObject");
	menuBar()->addMenu(GObjectMenu);
	QAction* CreateCube = new QAction("create cube",this);
	QAction* CreateObject = new QAction("create object",this);
	QAction* CreateSphere = new QAction("create sphere",this);
	QAction* CreatePlane = new QAction("create plane", this);
	QAction* PrintInfo = new QAction("print scene info", this);
	
	GObjectMenu->addAction(CreateObject);
	GObjectMenu->addAction(CreateCube);
	GObjectMenu->addAction(CreateSphere);
	GObjectMenu->addAction(CreatePlane);
	GObjectMenu->addAction(PrintInfo);

	connect(CreateObject, SIGNAL(triggered()), this, SLOT(createObject()));
	connect(CreateCube, SIGNAL(triggered()), this, SLOT(createCube()));
	connect(CreateSphere, SIGNAL(triggered()), this, SLOT(createSphere()));	
	connect(CreatePlane, SIGNAL(triggered()), this, SLOT(createPlane()));
	connect(PrintInfo, SIGNAL(triggered()), this, SLOT(printSceneInfo()));

}

void Window::setupScene(){
	//SCENE
	scene = new Scene();
	Transform* root = new Transform();
	GameObject* worldCoord = GameObjectFactory::getInstance()->createGameObject("Root Object");

	scene->setRoot(root);
	root->setGameObject(worldCoord);
	worldCoord->setTransform(root);
}

void Window::saveObject(){
	if(selectedObject){
		
		cout<<"saving object"<<endl;
		std::string filename("test.go");
		std::ofstream ofs(filename.c_str());
		boost::archive::text_oarchive oa(ofs);
		
		std::vector<GameObject*> nodes;
		nodes.push_back(selectedObject);
		GameObject* currentNode;
		while (! nodes.empty() ){
			currentNode = nodes.back();
			nodes.pop_back();
			oa << currentNode;

			int childCount = currentNode->getTransform()->getChildCount();
			ofs << endl << childCount << endl;
			
			for( int i = 0; i < childCount; i++){
				nodes.push_back(currentNode->getTransform()->getChild(currentNode->getTransform()->getChildCount()-i-1)->getGameObject());
			}
		}
	}
}
GameObject * Window::loadAndAttachChilds(GameObject * parent,boost::archive::text_iarchive& ia,std::ifstream & ifs){
	int nbOfChilds = 0;
	try{
		ia >> parent;
	}catch(archive_exception exp){
			cout<<"window "<<exp.what()<<endl;
		   cout<<"SERIALIZATION EXCEPTION : "<<exp.what()<<endl;
	}
	if(parent->getTransform()->getParent())
		cout<<"parent of trans should be null"<<endl;
	ifs >> nbOfChilds;

	parent->getTransform()->setGameObject(parent);

	for( int i = 0; i < nbOfChilds; i++){
		GameObject* child = NULL;
		child = loadAndAttachChilds(child,ia,ifs);
		parent->getTransform()->addChild(child->getTransform());
	}

	return parent;
}
void Window::openObject(){
	cout<<"loading object"<<endl;
	std::string filename("test.go");
	
	// open the archive
    std::ifstream ifs(filename.c_str());
    boost::archive::text_iarchive ia(ifs);
	GameObject* loadedObject = NULL;
	loadedObject = loadAndAttachChilds(loadedObject,ia,ifs);
	
	scene->addGameObject(loadedObject);
	model->addGameObject(loadedObject);

	ifs.close();
}

void Window::createObject(){	
	GameObject* newGO = GameObjectFactory::getInstance()->createGameObject("Empty Game Object");
	scene->addGameObject(newGO);
	model->addGameObject(newGO);
}

void Window::createCube(){
	GameObject* newGO = GameObjectFactory::getInstance()->createGameObject("Cube");
		
	MeshRenderer* cube = new MeshRenderer(CUBE);
	cube->setGameObject(newGO) ;
    newGO->setRenderer(cube);
    Material* redMat = new Material(RED);
    cube->setMaterial(redMat);

	scene->addGameObject(newGO);
	model->addGameObject(newGO);
}

void Window::createSphere(){
	GameObject* newGO = GameObjectFactory::getInstance()->createGameObject("Sphere");

	MeshRenderer* cube = new MeshRenderer(SPHERE);
	cube->setGameObject(newGO);
    newGO->setRenderer(cube);
    Material* redMat = new Material(RED);
    cube->setMaterial(redMat);

	scene->addGameObject(newGO);
	model->addGameObject(newGO);
}

void Window::createPlane(){
	GameObject* newGO = GameObjectFactory::getInstance()->createGameObject("Plane");
	
	MeshRenderer* cube = new MeshRenderer(PLANE);
	cube->setGameObject(newGO);
    newGO->setRenderer(cube);
    Material* redMat = new Material(RED);
    cube->setMaterial(redMat);

	scene->addGameObject(newGO);
	model->addGameObject(newGO);
}


void Window::keyPressEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_Escape)
        close();
	else if (e->key() == Qt::Key_Backspace){
		std::cout<<"hest"<<std::endl;
		printSceneInfo();
	}
	else
        QWidget::keyPressEvent(e);
}

void Window::printSceneInfo(){
//	Scene::printSceneInfo(scene);
}

void Window::updateActions(){
	view->closePersistentEditor(view->selectionModel()->currentIndex());
}

void Window::setMoveCamera(){ 
	glWidget->setCameraMode(MOVE);
	if(!setMoveCam->isChecked())
		setMoveCam->setChecked(true);
	setSelectCam->setChecked(false);
}
void Window::setSelectCamera(){
	glWidget->setCameraMode(SELECT);
		if(!setSelectCam->isChecked())
			setSelectCam->setChecked(true);
	setMoveCam->setChecked(false);
}

void Window::changeGameObject(GameObject * obj){
	emit gameObjectChanged(obj);
}

void Window::changeGameObject(QModelIndex index){
	GameObject* obj = static_cast<GOHierarchyItem*>(index.internalPointer())->getTransform()->getGameObject();
	selectedObject = obj;
	emit gameObjectChanged(obj);
}
