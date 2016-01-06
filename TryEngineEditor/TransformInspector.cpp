#include "TransformInspector.h"


TransformInspector::TransformInspector():
gameObject(0)
{
	setupUi(this);

	connect(tx, SIGNAL(textChanged(QString)), this, SLOT(setXTranslation(QString)));
	connect(ty, SIGNAL(textChanged(QString)), this, SLOT(setYTranslation(QString)));
	connect(tz, SIGNAL(textChanged(QString)), this, SLOT(setZTranslation(QString)));

	connect(rx, SIGNAL(textChanged(QString)), this, SLOT(setXRotation(QString)));
	connect(ry, SIGNAL(textChanged(QString)), this, SLOT(setYRotation(QString)));
	connect(rz, SIGNAL(textChanged(QString)), this, SLOT(setZRotation(QString)));

	connect(sx, SIGNAL(textChanged(QString)), this, SLOT(setXScale(QString)));
	connect(sy, SIGNAL(textChanged(QString)), this, SLOT(setYScale(QString)));
	connect(sz, SIGNAL(textChanged(QString)), this, SLOT(setZScale(QString)));

	connect(tx, SIGNAL(editingFinished() ), this, SLOT(finishEditing()));
	connect(ty, SIGNAL(editingFinished() ), this, SLOT(finishEditing()));
	connect(tz, SIGNAL(editingFinished() ), this, SLOT(finishEditing()));

	connect(rx, SIGNAL(editingFinished() ), this, SLOT(finishEditing()));
	connect(ry, SIGNAL(editingFinished() ), this, SLOT(finishEditing()));
	connect(rz, SIGNAL(editingFinished() ), this, SLOT(finishEditing()));

	connect(sx, SIGNAL(editingFinished() ), this, SLOT(finishEditing()));
	connect(sy, SIGNAL(editingFinished() ), this, SLOT(finishEditing()));
	connect(sz, SIGNAL(editingFinished() ), this, SLOT(finishEditing()));
}


TransformInspector::~TransformInspector(){
}


void TransformInspector::updateView(){

	if(!gameObject)
		return;

	QString trx;
	trx.setNum(gameObject->getTransform()->getPosition()[0], 'f');
	tx->setText(trx);

	QString tryy;
	tryy.setNum(gameObject->getTransform()->getPosition()[1], 'f');
	ty->setText(tryy);

	QString trz;
	trz.setNum(gameObject->getTransform()->getPosition()[2], 'f');
	tz->setText(trz);

		QString rrx;
	rrx.setNum(gameObject->getTransform()->getRotation()[0], 'f');
	rx->setText(rrx);

	QString rryy;
	rryy.setNum(gameObject->getTransform()->getRotation()[1], 'f');
	ry->setText(rryy);

	QString rrz;
	rrz.setNum(gameObject->getTransform()->getRotation()[2], 'f');
	rz->setText(rrz);

		QString srx;
	srx.setNum(gameObject->getTransform()->getScale()[0], 'f');
	sx->setText(srx);

	QString sryy;
	sryy.setNum(gameObject->getTransform()->getScale()[1], 'f');
	sy->setText(sryy);

	QString srz;
	srz.setNum(gameObject->getTransform()->getScale()[2], 'f');
	sz->setText(srz);
}

void TransformInspector::updateData(){
	if(!gameObject)
		return;

	QString trx;
	trx.setNum(gameObject->getTransform()->getPosition()[0], 'f');
	//tx->setText(trx);

	QString tryy;
	tryy.setNum(gameObject->getTransform()->getPosition()[1], 'f');
	ty->setText(tryy);

	QString trz;
	trz.setNum(gameObject->getTransform()->getPosition()[2], 'f');
	tz->setText(trz);
}

void TransformInspector::setXRotation(QString angle){
	bool ok = true;
	float value = angle.toFloat(&ok);

	if(ok){
		setTransformValue(value,0,'r');
	}
}
void TransformInspector::setYRotation(QString angle){
	bool ok = true;
	float value = angle.toFloat(&ok);

	if(ok){
		setTransformValue(value,1,'r');
	}
}
void TransformInspector::setZRotation(QString angle){
	bool ok = true;
	float value = angle.toFloat(&ok);

	if(ok){
		setTransformValue(value,2,'r');
	}
}
void TransformInspector::setXTranslation(QString trans){
	bool ok = true;
	float value = trans.toFloat(&ok);

	if(ok){
		setTransformValue(value,0,'t');
	}
}
void TransformInspector::setYTranslation(QString trans){
	bool ok = true;
	float value = trans.toFloat(&ok);

	if(ok){
		setTransformValue(value,1,'t');
	}
}
void TransformInspector::setZTranslation(QString trans){
	bool ok = true;
	float value = trans.toFloat(&ok);

	if(ok){
		setTransformValue(value,2,'t');
	}
}
void TransformInspector::setXScale(QString scale){
	bool ok = true;
	float value = scale.toFloat(&ok);

	if(ok){
		setTransformValue(value,0,'s');
	}
}
void TransformInspector::setYScale(QString scale){
	bool ok = true;
	float value = scale.toFloat(&ok);

	if(ok){
		setTransformValue(value,1,'s');
	}
}
void TransformInspector::setZScale(QString scale){
	bool ok = true;
	float value = scale.toFloat(&ok);

	if(ok){
		setTransformValue(value,2,'s');
	}
}

void TransformInspector::setTransformValue(float value, int coord, char type){
	if(!gameObject)
		return;
	if(coord>2 || coord<0)
		return;

	Vec3f vector;
	switch(type){
		case 't':
			vector = gameObject->getTransform()->getPosition();
			vector[coord] = value;
			gameObject->getTransform()->setPosition(vector);
		break;
		case 'r':
			vector = gameObject->getTransform()->getRotation();
			vector[coord] = value;
			gameObject->getTransform()->setRotation(vector);
		break;
		case 's':
			vector = gameObject->getTransform()->getScale();
			vector[coord] = value;
			gameObject->getTransform()->setScale(vector);
		break;
	}
}

void TransformInspector::finishEditing(){
	updateView();
}

void TransformInspector::setGameObject(GameObject * object){
	gameObject = object;
	updateView();
}

void TransformInspector::changeGameObject(GameObject* object){
	gameObject = object;
	updateView();
}

