#ifndef MOVEDATACOMMAND_H
#define MOVEDATACOMMAND_H

#include <QUndoCommand>
#include <QModelIndex>
#include "Transform.h"

class GOHierarchyModel;

class MoveDataCommand : public QUndoCommand{
	public:
		MoveDataCommand(const QModelIndex &old,const QModelIndex &newP,Transform* child,int row, GOHierarchyModel *model)
		: QUndoCommand(), m_model(model){
			begRow = row;
			oldParent = old;
			newParent = newP;
			this->child = child;
			setText("Move");
		}
		void redo(){
			std::cout<<"redo"<<std::endl;
				
			m_model->beginInsertRows(newParent,begRow,begRow);
			((Transform*)newParent.internalPointer())->addChild(child);
			m_model->endInsertRows();
	
			((Transform*)newParent.internalPointer())->addChild(new Transform());
			emit m_model->dataChanged(newParent, newParent);
			std::cout<<"end redo"<<std::endl;
		}
		void undo(){
			std::cout<<"undo"<<std::endl;
		}
	private:
		int begRow;
		QModelIndex oldParent, newParent;
		Transform* child;
		GOHierarchyModel *m_model;
};

#endif