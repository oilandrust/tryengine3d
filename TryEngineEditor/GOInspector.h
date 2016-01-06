#ifndef GOINSPECTOR_H
#define GOINSPECTOR_H

#include <QWidget>
#include <QDataWidgetMapper>
#include "ui_TextureInspector.h"
#include "Tryengine.h"
#include "TransformInspector.h"
#include "MeshRendererInspector.h"


class GOInspector: public QWidget{ Q_OBJECT
	public:
		GOInspector(QWidget* parent = 0);
		~GOInspector();
		void setGameObject(GameObject * object);

	private:
		TransformInspector *transformInspect;
		MeshRendererInspector *meshRendererInspect;

		GameObject* gameObject;
		QVBoxLayout * layout;

	public slots:
		void changeGameObject(GameObject* object);

	signals:
		void gameObjectChanged(QModelIndex index);
		

};

#endif
