/********************************************************************************
** Form generated from reading UI file 'TransformInspector.ui'
**
** Created: Sun 19. Jun 17:42:22 2011
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSFORMINSPECTOR_H
#define UI_TRANSFORMINSPECTOR_H

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

class Ui_TransformInspectForm
{
public:
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *tx;
    QLineEdit *ty;
    QLineEdit *tz;
    QLineEdit *rx;
    QLineEdit *ry;
    QLineEdit *rz;
    QLineEdit *sx;
    QLineEdit *sy;
    QLineEdit *sz;

    void setupUi(QWidget *TransformInspectForm)
    {
        if (TransformInspectForm->objectName().isEmpty())
            TransformInspectForm->setObjectName(QString::fromUtf8("TransformInspectForm"));
        TransformInspectForm->resize(235, 106);
        groupBox = new QGroupBox(TransformInspectForm);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 231, 101));
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(9, 10, 216, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        tx = new QLineEdit(gridLayoutWidget);
        tx->setObjectName(QString::fromUtf8("tx"));

        gridLayout->addWidget(tx, 0, 1, 1, 1);

        ty = new QLineEdit(gridLayoutWidget);
        ty->setObjectName(QString::fromUtf8("ty"));

        gridLayout->addWidget(ty, 0, 2, 1, 1);

        tz = new QLineEdit(gridLayoutWidget);
        tz->setObjectName(QString::fromUtf8("tz"));

        gridLayout->addWidget(tz, 0, 3, 1, 1);

        rx = new QLineEdit(gridLayoutWidget);
        rx->setObjectName(QString::fromUtf8("rx"));

        gridLayout->addWidget(rx, 1, 1, 1, 1);

        ry = new QLineEdit(gridLayoutWidget);
        ry->setObjectName(QString::fromUtf8("ry"));

        gridLayout->addWidget(ry, 1, 2, 1, 1);

        rz = new QLineEdit(gridLayoutWidget);
        rz->setObjectName(QString::fromUtf8("rz"));

        gridLayout->addWidget(rz, 1, 3, 1, 1);

        sx = new QLineEdit(gridLayoutWidget);
        sx->setObjectName(QString::fromUtf8("sx"));

        gridLayout->addWidget(sx, 2, 1, 1, 1);

        sy = new QLineEdit(gridLayoutWidget);
        sy->setObjectName(QString::fromUtf8("sy"));

        gridLayout->addWidget(sy, 2, 2, 1, 1);

        sz = new QLineEdit(gridLayoutWidget);
        sz->setObjectName(QString::fromUtf8("sz"));

        gridLayout->addWidget(sz, 2, 3, 1, 1);


        retranslateUi(TransformInspectForm);

        QMetaObject::connectSlotsByName(TransformInspectForm);
    } // setupUi

    void retranslateUi(QWidget *TransformInspectForm)
    {
        TransformInspectForm->setWindowTitle(QApplication::translate("TransformInspectForm", "TransformInspectForm", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("TransformInspectForm", "Transform", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TransformInspectForm", "Position", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TransformInspectForm", "Rotation", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("TransformInspectForm", "Scaling", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TransformInspectForm: public Ui_TransformInspectForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSFORMINSPECTOR_H
