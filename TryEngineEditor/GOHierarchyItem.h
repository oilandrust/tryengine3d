#ifndef GOHIERARCHYITEM_H
#define GOHIERARCHYITEM_H

#include <QList>
#include <QVariant>
#include <QVector>
#include "Transform.h"

class GOHierarchyItem{

	public:
		GOHierarchyItem(const QVector<QVariant> &data, GOHierarchyItem *parent = 0);
		~GOHierarchyItem();

		GOHierarchyItem *child(int number);
		int childCount() const;
		int columnCount() const;
		QVariant data(int column) const;
		bool insertChildren(int position, int count, int columns);
		
		GOHierarchyItem *parent();
		bool removeChildren(int position, int count);
		
		int childNumber() const;
		bool setData(const QVariant &value);

		Transform* getTransform();
		void setTransform(Transform* trans){
			transform = trans;
		}

	private:
		QList<GOHierarchyItem*> childItems;
		QVector<QVariant> itemData;
		GOHierarchyItem *parentItem;
		Transform *transform;
};

#endif

