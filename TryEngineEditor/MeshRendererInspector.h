#ifndef MeshRendererInspector_H
#define MeshRendererInspector_H

#include "ui_MeshRendererInspector.h"
#include "Tryengine.h"

class MeshRendererInspector: public QWidget, Ui::MeshRendererInspector{ Q_OBJECT
	public:
		MeshRendererInspector(void);
		~MeshRendererInspector(void);
		void updateView();
		void updateData();
		void setGameObject(GameObject * object);

	public slots:
		void changeGameObject(GameObject* object);
		void finishEditing();

	protected:
		GameObject* gameObject;
};

#endif

