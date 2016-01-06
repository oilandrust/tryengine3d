/********************************************************************************
** Form generated from reading UI file 'MaterialInspector.ui'
**
** Created: Sun 19. Jun 17:42:22 2011
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATERIALINSPECTOR_H
#define UI_MATERIALINSPECTOR_H

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

class Ui_MaterialInspector
{
public:
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *comboBox_3;

    void setupUi(QWidget *MaterialInspector)
    {
        if (MaterialInspector->objectName().isEmpty())
            MaterialInspector->setObjectName(QString::fromUtf8("MaterialInspector"));
        MaterialInspector->resize(184, 140);
        groupBox = new QGroupBox(MaterialInspector);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 181, 151));
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 20, 160, 101));
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

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        comboBox_3 = new QComboBox(gridLayoutWidget);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        gridLayout->addWidget(comboBox_3, 2, 1, 1, 1);


        retranslateUi(MaterialInspector);

        QMetaObject::connectSlotsByName(MaterialInspector);
    } // setupUi

    void retranslateUi(QWidget *MaterialInspector)
    {
        MaterialInspector->setWindowTitle(QApplication::translate("MaterialInspector", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MaterialInspector", "Material", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MaterialInspector", "Shader", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MaterialInspector", "Texture", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MaterialInspector", "Diffuse", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MaterialInspector", "Specular", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MaterialInspector: public Ui_MaterialInspector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATERIALINSPECTOR_H
