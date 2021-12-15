/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[24];
    char stringdata0[250];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 14), // "widget_lecture"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 14), // "widget_manette"
QT_MOC_LITERAL(4, 38, 22), // "widget_manetteLineaire"
QT_MOC_LITERAL(5, 61, 11), // "pince_moove"
QT_MOC_LITERAL(6, 73, 3), // "pos"
QT_MOC_LITERAL(7, 77, 11), // "bras1_moove"
QT_MOC_LITERAL(8, 89, 11), // "bras2_moove"
QT_MOC_LITERAL(9, 101, 11), // "bras3_moove"
QT_MOC_LITERAL(10, 113, 10), // "base_moove"
QT_MOC_LITERAL(11, 124, 10), // "test_moove"
QT_MOC_LITERAL(12, 135, 6), // "Moteur"
QT_MOC_LITERAL(13, 142, 3), // "mot"
QT_MOC_LITERAL(14, 146, 7), // "vitesse"
QT_MOC_LITERAL(15, 154, 17), // "enregistrer_chore"
QT_MOC_LITERAL(16, 172, 10), // "lire_chore"
QT_MOC_LITERAL(17, 183, 4), // "goTo"
QT_MOC_LITERAL(18, 188, 8), // "goTo_Cam"
QT_MOC_LITERAL(19, 197, 11), // "goTo_Detect"
QT_MOC_LITERAL(20, 209, 11), // "widget_leap"
QT_MOC_LITERAL(21, 221, 13), // "widget_camera"
QT_MOC_LITERAL(22, 235, 7), // "disable"
QT_MOC_LITERAL(23, 243, 6) // "enable"

    },
    "Widget\0widget_lecture\0\0widget_manette\0"
    "widget_manetteLineaire\0pince_moove\0"
    "pos\0bras1_moove\0bras2_moove\0bras3_moove\0"
    "base_moove\0test_moove\0Moteur\0mot\0"
    "vitesse\0enregistrer_chore\0lire_chore\0"
    "goTo\0goTo_Cam\0goTo_Detect\0widget_leap\0"
    "widget_camera\0disable\0enable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x08 /* Private */,
       3,    0,  110,    2, 0x08 /* Private */,
       4,    0,  111,    2, 0x08 /* Private */,
       5,    1,  112,    2, 0x08 /* Private */,
       7,    1,  115,    2, 0x08 /* Private */,
       8,    1,  118,    2, 0x08 /* Private */,
       9,    1,  121,    2, 0x08 /* Private */,
      10,    1,  124,    2, 0x08 /* Private */,
      11,    2,  127,    2, 0x08 /* Private */,
      14,    0,  132,    2, 0x08 /* Private */,
      15,    0,  133,    2, 0x08 /* Private */,
      16,    0,  134,    2, 0x08 /* Private */,
      17,    0,  135,    2, 0x08 /* Private */,
      18,    0,  136,    2, 0x08 /* Private */,
      19,    0,  137,    2, 0x08 /* Private */,
      20,    0,  138,    2, 0x08 /* Private */,
      21,    0,  139,    2, 0x08 /* Private */,
      22,    0,  140,    2, 0x08 /* Private */,
      23,    0,  141,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 12,    6,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->widget_lecture(); break;
        case 1: _t->widget_manette(); break;
        case 2: _t->widget_manetteLineaire(); break;
        case 3: _t->pince_moove((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->bras1_moove((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->bras2_moove((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->bras3_moove((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->base_moove((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->test_moove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Moteur(*)>(_a[2]))); break;
        case 9: _t->vitesse(); break;
        case 10: _t->enregistrer_chore(); break;
        case 11: _t->lire_chore(); break;
        case 12: _t->goTo(); break;
        case 13: _t->goTo_Cam(); break;
        case 14: _t->goTo_Detect(); break;
        case 15: _t->widget_leap(); break;
        case 16: _t->widget_camera(); break;
        case 17: _t->disable(); break;
        case 18: _t->enable(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Widget.data,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
