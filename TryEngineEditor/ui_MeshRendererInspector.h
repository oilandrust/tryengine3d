/********************************************************************************
** Form generated from reading UI file 'MeshRendererInspector.ui'
**
** Created: Mon 13. Dec 17:50:11 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESHRENDERERINSPECTOR_H
#define UI_MESHRENDERERINSPECTOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeshRendererInspector
{
public:
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;
    QComboBox *comboBox_2;

    void setupUi(QWidget *MeshRendererInspector)
    {
        if (MeshRendererInspector->objectName().isEmpty())
            MeshRendererInspector->setObjectName(QString::fromUtf8("MeshRendererInspector"));
        MeshRendererInspector->resize(187, 76);
        groupBox = new QGroupBox(MeshRendererInspector);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 181, 71));
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 20, 160, 41));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        comboBox = new QComboBox(gridLayoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        comboBox_2 = new QComboBox(gridLayoutWidget);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 1, 1, 1, 1);


        retranslateUi(MeshRendererInspector);

        QMetaObject::connectSlotsByName(MeshRendererInspector);
    } // setupUi

    void retranslateUi(QWidget *MeshRendererInspector)
    {
        MeshRendererInspector->setWindowTitle(QApplication::translate("MeshRendererInspector", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MeshRendererInspector", "MeshRenderer", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MeshRendererInspector", "Mesh", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MeshRendererInspector", "Material", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MeshRendererInspector: public Ui_MeshRendererInspector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHRENDERERINSPECTOR_H
