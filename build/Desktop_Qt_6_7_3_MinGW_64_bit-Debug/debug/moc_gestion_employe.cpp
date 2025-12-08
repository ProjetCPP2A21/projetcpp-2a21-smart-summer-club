/****************************************************************************
** Meta object code from reading C++ file 'gestion_employe.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../gestion_employe.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gestion_employe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSgestion_employeENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSgestion_employeENDCLASS = QtMocHelpers::stringData(
    "gestion_employe",
    "on_btajouter_clicked",
    "",
    "on_btsupprimer_clicked",
    "on_bmodifier_clicked",
    "on_pushButton_cin_3_clicked",
    "clearFields",
    "on_btSearchEmail_clicked",
    "on_btTriDate_clicked",
    "afficherStatistiques",
    "on_btnStats_clicked",
    "exportWord",
    "exportPDF",
    "on_btnExportPDF_clicked",
    "validateFields",
    "forAdd",
    "forModify",
    "forDelete"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSgestion_employeENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x08,    1 /* Private */,
       3,    0,   93,    2, 0x08,    2 /* Private */,
       4,    0,   94,    2, 0x08,    3 /* Private */,
       5,    0,   95,    2, 0x08,    4 /* Private */,
       6,    0,   96,    2, 0x08,    5 /* Private */,
       7,    0,   97,    2, 0x08,    6 /* Private */,
       8,    0,   98,    2, 0x08,    7 /* Private */,
       9,    0,   99,    2, 0x08,    8 /* Private */,
      10,    0,  100,    2, 0x08,    9 /* Private */,
      11,    0,  101,    2, 0x08,   10 /* Private */,
      12,    0,  102,    2, 0x08,   11 /* Private */,
      13,    0,  103,    2, 0x08,   12 /* Private */,
      14,    3,  104,    2, 0x108,   13 /* Private | MethodIsConst  */,

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
    QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   15,   16,   17,

       0        // eod
};

Q_CONSTINIT const QMetaObject gestion_employe::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSgestion_employeENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSgestion_employeENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSgestion_employeENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<gestion_employe, std::true_type>,
        // method 'on_btajouter_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btsupprimer_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_bmodifier_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_cin_3_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearFields'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btSearchEmail_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btTriDate_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'afficherStatistiques'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnStats_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exportWord'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exportPDF'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnExportPDF_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'validateFields'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void gestion_employe::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<gestion_employe *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_btajouter_clicked(); break;
        case 1: _t->on_btsupprimer_clicked(); break;
        case 2: _t->on_bmodifier_clicked(); break;
        case 3: _t->on_pushButton_cin_3_clicked(); break;
        case 4: _t->clearFields(); break;
        case 5: _t->on_btSearchEmail_clicked(); break;
        case 6: _t->on_btTriDate_clicked(); break;
        case 7: _t->afficherStatistiques(); break;
        case 8: _t->on_btnStats_clicked(); break;
        case 9: _t->exportWord(); break;
        case 10: _t->exportPDF(); break;
        case 11: _t->on_btnExportPDF_clicked(); break;
        case 12: { QString _r = _t->validateFields((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *gestion_employe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gestion_employe::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSgestion_employeENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int gestion_employe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
