#ifndef TRANSFORMITEM_H 
#define TRANSFORMITEM_H

#include <QStandardItem>

class TransformItem :public QStandardItem{
	public:
		TransformItem();
		~TransformItem();

		int type() const; 
};

#endif