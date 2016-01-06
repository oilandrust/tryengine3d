 #include <QtGui>

 #include "GOHierarchyItem.h"
 #include "treemodel.h"

 TreeModel::TreeModel(const QStringList &headers, const QString &data,
                      QObject *parent)
     : QAbstractItemModel(parent)
 {
     QVector<QVariant> rootData;
     foreach (QString header, headers)
         rootData << header;

     rootItem = new GOHierarchyItem(rootData);
 }

  TreeModel::TreeModel(QObject *parent)
     : QAbstractItemModel(parent)
 {
	 QVector<QVariant> data;
	 data.append(QString("rootData"));
     rootItem = new GOHierarchyItem(data);
 }

 TreeModel::~TreeModel()
 {
     delete rootItem;
 }

 int TreeModel::columnCount(const QModelIndex & /* parent */) const
 {
     return 1;
 }

 QVariant TreeModel::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
         return QVariant();

     if (role != Qt::DisplayRole && role != Qt::EditRole)
         return QVariant();

     GOHierarchyItem *item = getItem(index);

     return item->data(index.column());
 }



 GOHierarchyItem *TreeModel::getItem(const QModelIndex &index) const
 {
     if (index.isValid()) {
         GOHierarchyItem *item = static_cast<GOHierarchyItem*>(index.internalPointer());
         if (item) return item;
     }
     return rootItem;
 }

 QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
 {
     if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
         return rootItem->data(section);

     return QVariant();
 }

 QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
 {
     if (parent.isValid() && parent.column() != 0)
         return QModelIndex();
	 
     GOHierarchyItem *parentItem = getItem(parent);

     GOHierarchyItem *childItem = parentItem->child(row);
     if (childItem)
         return createIndex(row, column, childItem);
     else
         return QModelIndex();
 }


 bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
 {
     GOHierarchyItem *parentItem = getItem(parent);
     bool success;

     beginInsertRows(parent, position, position + rows - 1);
     success = parentItem->insertChildren(position, rows, rootItem->columnCount());
     endInsertRows();

	 if(!success)
		 std::cout<<"failed"<<std::endl;

     return success;
 }

 QModelIndex TreeModel::parent(const QModelIndex &index) const
 {
     if (!index.isValid())
         return QModelIndex();

     GOHierarchyItem *childItem = getItem(index);
     GOHierarchyItem *parentItem = childItem->parent();

     if (parentItem == rootItem)
         return QModelIndex();

     return createIndex(parentItem->childNumber(), 0, parentItem);
 }

 bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
 {
     GOHierarchyItem *parentItem = getItem(parent);
     bool success = true;

     beginRemoveRows(parent, position, position + rows - 1);
     success = parentItem->removeChildren(position, rows);
     endRemoveRows();

     return success;
 }

 int TreeModel::rowCount(const QModelIndex &parent) const
 {
     GOHierarchyItem *parentItem = getItem(parent);

     return parentItem->childCount();
 }

 bool TreeModel::setData(const QModelIndex &index, const QVariant &value,
                         int role)
 {
     if (role != Qt::EditRole)
         return false;

     GOHierarchyItem *item = getItem(index);
     bool result = item->setData(value);

     if (result)
         emit dataChanged(index, index);
	 else
		 std::cout<<"failed to set data"<<std::endl;

     return result;
 }

 bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                               const QVariant &value, int role)
 {
     if (role != Qt::EditRole || orientation != Qt::Horizontal)
         return false;

     bool result = rootItem->setData(value);

     if (result)
         emit headerDataChanged(orientation, section, section);

     return result;
 }

 Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const{
     Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

     if (index.isValid())
         return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags | Qt::ItemIsEditable;
     else
         return Qt::ItemIsDropEnabled | defaultFlags;
}

void TreeModel::setRootItem(Transform* root){ rootItem->setTransform(root); }

QModelIndex TreeModel::getGameObjectIndex(GameObject* obj){
	if(obj->getTransform()->getParent() == rootItem->getTransform()){
		return index(rootItem->getTransform()->getChildIndex(obj->getTransform()),0,QModelIndex());
	}
	QModelIndex parentIndex = getGameObjectIndex(obj->getTransform()->getParent()->getGameObject());

	return index(getItem(parentIndex)->getTransform()->getChildIndex(obj->getTransform()), 0, parentIndex);
}

void TreeModel::addGameObject(GameObject* gameObject, GameObject* parentObject){
	QModelIndex parentIndex;
	if(!parentObject)
		parentIndex = QModelIndex();
	else{
		parentIndex = getGameObjectIndex(parentObject);
	}


	if (!insertRow(rowCount(parentIndex),parentIndex))
        return;
	 
	QModelIndex child = index(rowCount(parentIndex)-1, 0,parentIndex);
	QString name(gameObject->getName().c_str());
	getItem(child)->setTransform(gameObject->getTransform());
	setData(child, QVariant(name), Qt::EditRole);

	Transform* trans = gameObject->getTransform();
	for( int i = 0; i < trans->getChildCount(); i++){
		addGameObject(trans->getChild(i)->getGameObject(),gameObject);
	}
}
Qt::DropActions TreeModel::supportedDropActions() const{
	return Qt::CopyAction | Qt::MoveAction;
}
QStringList TreeModel::mimeTypes() const{
	QStringList types;
	types << "application/vnd.text.list";
	return types;
}
QMimeData *TreeModel::mimeData(const QModelIndexList &indexes) const{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (QModelIndex index, indexes) {
        if (index.isValid()) {
            //QString text = data(index, Qt::DisplayRole).toString();
			//stream << text;

			GOHierarchyItem* item = getItem(index);
			encodedData.append((char*)&item, sizeof(GOHierarchyItem*));
            
        }
    }

    mimeData->setData("application/vnd.text.list", encodedData);
    return mimeData;
}
 bool TreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent){
	if (action == Qt::IgnoreAction)
		return true;

	if (!data->hasFormat("application/vnd.text.list"))
		return false;

	if (column > 0)
		return false;

	int beginRow;

	if (parent.isValid())
		beginRow = rowCount(parent);
	else
		beginRow = rowCount(QModelIndex());

	QByteArray encodedData = data->data("application/vnd.text.list");
	QDataStream stream(&encodedData, QIODevice::ReadOnly);
	QStringList newItems;
	int rows = 0;

	QList<GOHierarchyItem*> items;
	GOHierarchyItem    *object;
	object  = *((GOHierarchyItem**)encodedData.data());
	//while (!stream.atEnd()) {
		/*
		QString text;
		stream >> text;
		newItems << text;
		++rows;
		*/
	//}
	getItem(parent)->getTransform()->addChild(object->getTransform());
	cout<<"dropping to "<<getItem(parent)->getTransform()->getGameObject()->getName()<<endl;
	insertChild(object,beginRow,parent);
	
	
	/*
	foreach (QString text, newItems) {
		QModelIndex idx = index(beginRow, 0, parent);
		setData(idx, text);
		beginRow++;
	}*/

	return true;
}

 void TreeModel::insertChild(GOHierarchyItem* item, int row, QModelIndex parent){
	insertRows(row, 1, parent);
	
	QModelIndex idx = index(row, 0, parent);
	setData(idx, item->data(0) );
	getItem(idx)->setTransform(item->getTransform());
	for( int i = 0; i < item->childCount(); i++){
		insertChild(item->child(i),i,idx);
	}
 }