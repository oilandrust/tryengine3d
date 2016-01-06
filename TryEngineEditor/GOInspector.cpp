#include "GOInspector.h"

GOInspector::GOInspector(QWidget* parent):QWidget(parent), gameObject(NULL){
	transformInspect = new TransformInspector();
	meshRendererInspect = new MeshRendererInspector();

	layout = new QVBoxLayout();

	layout->addWidget(transformInspect);
	layout->addWidget(meshRendererInspect);

	this->setLayout(layout);
}

GOInspector::~GOInspector(){
}


void GOInspector::setGameObject(GameObject * object){
	gameObject = object;
	transformInspect->setGameObject(object);
	meshRendererInspect->setGameObject(object);
}

void GOInspector::changeGameObject(GameObject* object){
	gameObject = object;
	transformInspect->changeGameObject(object);
	meshRendererInspect->changeGameObject(object);
}

