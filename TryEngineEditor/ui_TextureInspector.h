/********************************************************************************
** Form generated from reading UI file 'TextureInspector.ui'
**
** Created: Mon 13. Dec 17:16:42 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTUREINSPECTOR_H
#define UI_TEXTUREINSPECTOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextureInspectorForm
{
public:
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *nameEdit;
    QLabel *widthLabel;
    QLabel *heightLabel;
    QLabel *TextureView;

    void setupUi(QWidget *TextureInspectorForm)
    {
        if (TextureInspectorForm->objectName().isEmpty())
            TextureInspectorForm->setObjectName(QString::fromUtf8("TextureInspectorForm"));
        TextureInspectorForm->resize(222, 121);
        groupBox = new QGroupBox(TextureInspectorForm);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 221, 121));
        verticalLayoutWidget = new QWidget(groupBox);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 20, 89, 60));
        gridLayout = new QGridLayout(verticalLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        nameEdit = new QLineEdit(verticalLayoutWidget);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        gridLayout->addWidget(nameEdit, 0, 1, 1, 1);

        widthLabel = new QLabel(verticalLayoutWidget);
        widthLabel->setObjectName(QString::fromUtf8("widthLabel"));

        gridLayout->addWidget(widthLabel, 1, 1, 1, 1);

        heightLabel = new QLabel(verticalLayoutWidget);
        heightLabel->setObjectName(QString::fromUtf8("heightLabel"));

        gridLayout->addWidget(heightLabel, 2, 1, 1, 1);

        TextureView = new QLabel(groupBox);
        TextureView->setObjectName(QString::fromUtf8("TextureView"));
        TextureView->setGeometry(QRect(100, 20, 111, 91));

        retranslateUi(TextureInspectorForm);

        QMetaObject::connectSlotsByName(TextureInspectorForm);
    } // setupUi

    void retranslateUi(QWidget *TextureInspectorForm)
    {
        TextureInspectorForm->setWindowTitle(QApplication::translate("TextureInspectorForm", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("TextureInspectorForm", "Texture", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TextureInspectorForm", "Name", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TextureInspectorForm", "Width", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("TextureInspectorForm", "Height", 0, QApplication::UnicodeUTF8));
        widthLabel->setText(QString());
        heightLabel->setText(QString());
        TextureView->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TextureInspectorForm: public Ui_TextureInspectorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTUREINSPECTOR_H
