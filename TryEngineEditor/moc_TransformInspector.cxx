/****************************************************************************
** Meta object code from reading C++ file 'TransformInspector.h'
**
** Created: Mon 20. Dec 22:22:33 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TransformInspector.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TransformInspector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TransformInspector[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   20,   19,   19, 0x05,
      50,   20,   19,   19, 0x05,
      74,   20,   19,   19, 0x05,
     104,   98,   19,   19, 0x05,
     131,   98,   19,   19, 0x05,
     158,   98,   19,   19, 0x05,
     191,  185,   19,   19, 0x05,
     212,  185,   19,   19, 0x05,
     233,  185,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     262,  254,   19,   19, 0x0a,
     284,   20,   19,   19, 0x0a,
     306,   20,   19,   19, 0x0a,
     328,   98,   19,   19, 0x0a,
     353,   98,   19,   19, 0x0a,
     378,   98,   19,   19, 0x0a,
     403,  185,   19,   19, 0x0a,
     422,  185,   19,   19, 0x0a,
     441,  185,   19,   19, 0x0a,
     467,  460,   19,   19, 0x0a,
     497,   19,   19,   19, 0x0a,
     530,  513,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TransformInspector[] = {
    "TransformInspector\0\0angle\0"
    "xRotationChanged(float)\0yRotationChanged(float)\0"
    "zRotationChanged(float)\0trans\0"
    "xTranslationChanged(float)\0"
    "yTranslationChanged(float)\0"
    "zTranslationChanged(float)\0scale\0"
    "xScaleChanged(float)\0yScaleChanged(float)\0"
    "zScaleChanged(float)\0QString\0"
    "setXRotation(QString)\0setYRotation(QString)\0"
    "setZRotation(QString)\0setXTranslation(QString)\0"
    "setYTranslation(QString)\0"
    "setZTranslation(QString)\0setXScale(QString)\0"
    "setYScale(QString)\0setZScale(QString)\0"
    "object\0changeGameObject(GameObject*)\0"
    "finishEditing()\0value,coord,type\0"
    "setTransformValue(float,int,char)\0"
};

const QMetaObject TransformInspector::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TransformInspector,
      qt_meta_data_TransformInspector, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TransformInspector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TransformInspector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TransformInspector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TransformInspector))
        return static_cast<void*>(const_cast< TransformInspector*>(this));
    if (!strcmp(_clname, "Ui::TransformInspectForm"))
        return static_cast< Ui::TransformInspectForm*>(const_cast< TransformInspector*>(this));
    return QWidget::qt_metacast(_clname);
}

int TransformInspector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: xRotationChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: yRotationChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: zRotationChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: xTranslationChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: yTranslationChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: zTranslationChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: xScaleChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: yScaleChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: zScaleChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: setXRotation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: setYRotation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: setZRotation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: setXTranslation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: setYTranslation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: setZTranslation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: setXScale((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: setYScale((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: setZScale((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: changeGameObject((*reinterpret_cast< GameObject*(*)>(_a[1]))); break;
        case 19: finishEditing(); break;
        case 20: setTransformValue((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< char(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void TransformInspector::xRotationChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TransformInspector::yRotationChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TransformInspector::zRotationChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TransformInspector::xTranslationChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TransformInspector::yTranslationChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TransformInspector::zTranslationChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void TransformInspector::xScaleChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void TransformInspector::yScaleChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void TransformInspector::zScaleChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
