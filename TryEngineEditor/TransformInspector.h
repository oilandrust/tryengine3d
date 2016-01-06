#ifndef TransformInspector_H
#define TransformInspector_H

#include "ui_TransformInspector.h"
#include "Tryengine.h"

class TransformInspector: public QWidget, Ui::TransformInspectForm{ Q_OBJECT
	public:
		TransformInspector(void);
		~TransformInspector(void);
		void updateView();
		void updateData();
		void setGameObject(GameObject * object);

	public slots:
		void setXRotation(QString QString);
		void setYRotation(QString angle);
		void setZRotation(QString angle);
		void setXTranslation(QString trans);
		void setYTranslation(QString trans);
		void setZTranslation(QString trans);
		void setXScale(QString scale);
		void setYScale(QString scale);
		void setZScale(QString scale);

		void changeGameObject(GameObject* object);
		
		void finishEditing();
		void setTransformValue(float value, int coord, char type);

	signals:
		void xRotationChanged(float angle);
		void yRotationChanged(float angle);
		void zRotationChanged(float angle);
		void xTranslationChanged(float trans);
		void yTranslationChanged(float trans);
		void zTranslationChanged(float trans);
		void xScaleChanged(float scale);
		void yScaleChanged(float scale);
		void zScaleChanged(float scale);

	protected:
		GameObject* gameObject;
};

#endif

