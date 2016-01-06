#include "GOHierarchyItem.h"


GOHierarchyItem::GOHierarchyItem(const QVector<QVariant> &data, GOHierarchyItem *parent)
{
    parentItem = parent;
    itemData = data;
}

GOHierarchyItem::~GOHierarchyItem()
{
    qDeleteAll(childItems);
}

GOHierarchyItem *GOHierarchyItem::child(int number)
{
    return childItems.value(number);
}

int GOHierarchyItem::childCount() const
{
    return childItems.count();
}

int GOHierarchyItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<GOHierarchyItem*>(this));

    return 0;
}

int GOHierarchyItem::columnCount() const
{
    return 1;
}

QVariant GOHierarchyItem::data(int column) const
{
    return itemData.value(column);
}

bool GOHierarchyItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        GOHierarchyItem *item = new GOHierarchyItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}

GOHierarchyItem *GOHierarchyItem::parent()
{
    return parentItem;
}

bool GOHierarchyItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}


bool GOHierarchyItem::setData(const QVariant &value)
{
    itemData[0] = value;
	//transform->getGameObject()->setName(value.toString().toStdString());
    return true;
}

Transform* GOHierarchyItem::getTransform(){
	return transform;
}
