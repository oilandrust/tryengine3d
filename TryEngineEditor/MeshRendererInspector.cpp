#include "MeshRendererInspector.h"


MeshRendererInspector::MeshRendererInspector(){
	setupUi(this);
}


MeshRendererInspector::~MeshRendererInspector(){
}


void MeshRendererInspector::updateView(){
	if(!gameObject)
		return;
}

void MeshRendererInspector::updateData(){
	if(!gameObject)
		return;
}

void MeshRendererInspector::finishEditing(){
	updateView();
}

void MeshRendererInspector::setGameObject(GameObject * object){
	gameObject = object;
	updateView();
}

void MeshRendererInspector::changeGameObject(GameObject* object){
	gameObject = object;
	updateView();
}

