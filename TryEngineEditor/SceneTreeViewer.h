#ifndef SCENETREEVIEWER_H
#define SCENETREEVIEWER_H

#include "TryEngine.h"
#include <QTreeWidget>
#include <QTreeView>

class SceneTreeViewer: public QTreeView{ Q_OBJECT
	protected:
		Scene* scene;
		void readSceneGraph()const;
		void inspectNode(Transform * transform)const;

	public:
		SceneTreeViewer(Scene* scen = NULL);
		~SceneTreeViewer();
};

#endif
