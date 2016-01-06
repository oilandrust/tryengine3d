#ifndef TREEMODEL_H
 #define TREEMODEL_H

 #include <QAbstractItemModel>
 #include <QModelIndex>
 #include <QVariant>
 #include "GameObject.h"

 class GOHierarchyItem;

 class TreeModel : public QAbstractItemModel
 {
     Q_OBJECT

 public:
     TreeModel(const QStringList &headers, const QString &data,
               QObject *parent = 0);
	 TreeModel(QObject *parent = 0);
     ~TreeModel();

     QVariant data(const QModelIndex &index, int role) const;
     QVariant headerData(int section, Qt::Orientation orientation,
                         int role = Qt::DisplayRole) const;

     QModelIndex index(int row, int column,
                       const QModelIndex &parent = QModelIndex()) const;
     QModelIndex parent(const QModelIndex &index) const;

     int rowCount(const QModelIndex &parent = QModelIndex()) const;
     int columnCount(const QModelIndex &parent = QModelIndex()) const;

     Qt::ItemFlags flags(const QModelIndex &index) const;
     bool setData(const QModelIndex &index, const QVariant &value,
                  int role = Qt::EditRole);
     bool setHeaderData(int section, Qt::Orientation orientation,
                        const QVariant &value, int role = Qt::EditRole);

     bool insertRows(int position, int rows,
                     const QModelIndex &parent = QModelIndex());
     bool removeRows(int position, int rows,
                     const QModelIndex &parent = QModelIndex());
	 


	void setRootItem(Transform* root);
	void addGameObject(GameObject* gameObject, GameObject* parentObject = NULL);
	QModelIndex getGameObjectIndex(GameObject* obj);
	Qt::DropActions supportedDropActions() const;
	QMimeData * mimeData(const QModelIndexList &indexes) const;
	QStringList mimeTypes() const;
	bool dropMimeData(const QMimeData *data,
		Qt::DropAction action, int row, int column, const QModelIndex &parent);	
	 void insertChild(GOHierarchyItem* item, int row, QModelIndex parent);

 private:
     GOHierarchyItem *getItem(const QModelIndex &index) const;

     GOHierarchyItem *rootItem;
 };

 #endif