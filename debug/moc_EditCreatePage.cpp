/****************************************************************************
** Meta object code from reading C++ file 'EditCreatePage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/EditCreatePage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EditCreatePage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
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
struct qt_meta_tag_ZN14EditCreatePageE_t {};
} // unnamed namespace

template <> constexpr inline auto EditCreatePage::qt_create_metaobjectdata<qt_meta_tag_ZN14EditCreatePageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "EditCreatePage",
        "itemCreated",
        "",
        "BibliotecaItem*",
        "newItem",
        "itemUpdated",
        "updatedItem",
        "saveItem",
        "goBack"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'itemCreated'
        QtMocHelpers::SignalData<void(BibliotecaItem *)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'itemUpdated'
        QtMocHelpers::SignalData<void(BibliotecaItem *)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 6 },
        }}),
        // Slot 'saveItem'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'goBack'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<EditCreatePage, qt_meta_tag_ZN14EditCreatePageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject EditCreatePage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14EditCreatePageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14EditCreatePageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14EditCreatePageE_t>.metaTypes,
    nullptr
} };

void EditCreatePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<EditCreatePage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->itemCreated((*reinterpret_cast< std::add_pointer_t<BibliotecaItem*>>(_a[1]))); break;
        case 1: _t->itemUpdated((*reinterpret_cast< std::add_pointer_t<BibliotecaItem*>>(_a[1]))); break;
        case 2: _t->saveItem(); break;
        case 3: _t->goBack(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (EditCreatePage::*)(BibliotecaItem * )>(_a, &EditCreatePage::itemCreated, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (EditCreatePage::*)(BibliotecaItem * )>(_a, &EditCreatePage::itemUpdated, 1))
            return;
    }
}

const QMetaObject *EditCreatePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditCreatePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14EditCreatePageE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Visitor"))
        return static_cast< Visitor*>(this);
    return QWidget::qt_metacast(_clname);
}

int EditCreatePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void EditCreatePage::itemCreated(BibliotecaItem * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void EditCreatePage::itemUpdated(BibliotecaItem * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}
QT_WARNING_POP
