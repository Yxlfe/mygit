/****************************************************************************
** Meta object code from reading C++ file 'main_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../My_music/main_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Main_Widget_t {
    QByteArrayData data[18];
    char stringdata0[306];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Main_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Main_Widget_t qt_meta_stringdata_Main_Widget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Main_Widget"
QT_MOC_LITERAL(1, 12, 16), // "on_close_clicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 19), // "on_maximize_clicked"
QT_MOC_LITERAL(4, 50, 19), // "on_minimize_clicked"
QT_MOC_LITERAL(5, 70, 15), // "on_play_clicked"
QT_MOC_LITERAL(6, 86, 16), // "on_start_clicked"
QT_MOC_LITERAL(7, 103, 16), // "on_model_clicked"
QT_MOC_LITERAL(8, 120, 14), // "on_end_clicked"
QT_MOC_LITERAL(9, 135, 15), // "on_last_clicked"
QT_MOC_LITERAL(10, 151, 15), // "on_next_clicked"
QT_MOC_LITERAL(11, 167, 20), // "on_sound_add_clicked"
QT_MOC_LITERAL(12, 188, 23), // "on_sound_reduce_clicked"
QT_MOC_LITERAL(13, 212, 15), // "on_list_clicked"
QT_MOC_LITERAL(14, 228, 18), // "on_history_clicked"
QT_MOC_LITERAL(15, 247, 36), // "on_listWidget_list_itemDouble..."
QT_MOC_LITERAL(16, 284, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(17, 301, 4) // "item"

    },
    "Main_Widget\0on_close_clicked\0\0"
    "on_maximize_clicked\0on_minimize_clicked\0"
    "on_play_clicked\0on_start_clicked\0"
    "on_model_clicked\0on_end_clicked\0"
    "on_last_clicked\0on_next_clicked\0"
    "on_sound_add_clicked\0on_sound_reduce_clicked\0"
    "on_list_clicked\0on_history_clicked\0"
    "on_listWidget_list_itemDoubleClicked\0"
    "QListWidgetItem*\0item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Main_Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    1,   97,    2, 0x08 /* Private */,

 // slots: parameters
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,

       0        // eod
};

void Main_Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Main_Widget *_t = static_cast<Main_Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_close_clicked(); break;
        case 1: _t->on_maximize_clicked(); break;
        case 2: _t->on_minimize_clicked(); break;
        case 3: _t->on_play_clicked(); break;
        case 4: _t->on_start_clicked(); break;
        case 5: _t->on_model_clicked(); break;
        case 6: _t->on_end_clicked(); break;
        case 7: _t->on_last_clicked(); break;
        case 8: _t->on_next_clicked(); break;
        case 9: _t->on_sound_add_clicked(); break;
        case 10: _t->on_sound_reduce_clicked(); break;
        case 11: _t->on_list_clicked(); break;
        case 12: _t->on_history_clicked(); break;
        case 13: _t->on_listWidget_list_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Main_Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Main_Widget.data,
      qt_meta_data_Main_Widget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Main_Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Main_Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Main_Widget.stringdata0))
        return static_cast<void*>(const_cast< Main_Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Main_Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
