#include "SceneTreeViewer.h"


SceneTreeViewer::SceneTreeViewer(Scene* scen){
	scene = scen;
	readSceneGraph();
}

SceneTreeViewer::~SceneTreeViewer(){
}

void SceneTreeViewer::readSceneGraph()const{
	Transform * root = scene->getRoot();

	Transform::ChildrenIterator it = root->getChildrenIteratorBegin();
	for(; it != root->getChildrenIteratorEnd(); ++it){
		inspectNode(*it);
	}
}

void SceneTreeViewer::inspectNode(Transform * transform)const{
	QString name = QString(transform->getGameObject()->getName().c_str());
	QTreeWidgetItem *i = new QTreeWidgetItem((QTreeWidget*)this);
	i->setText(0,name);

	Transform::ChildrenIterator it = transform->getChildrenIteratorBegin();
	for(; it != transform->getChildrenIteratorEnd(); ++it){
		inspectNode(*it);
	}
	
}