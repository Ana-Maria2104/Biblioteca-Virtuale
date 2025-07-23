/****************************************************************************
** Meta object code from reading C++ file 'UserPage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/UserPage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UserPage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN8UserPageE_t {};
} // unnamed namespace

template <> constexpr inline auto UserPage::qt_create_metaobjectdata<qt_meta_tag_ZN8UserPageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "UserPage",
        "itemUpdated",
        "",
        "BibliotecaItem*",
        "item",
        "close",
        "goBack",
        "search",
        "prenotaOggetto",
        "obj",
        "restituisciOggetto"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'itemUpdated'
        QtMocHelpers::SignalData<void(BibliotecaItem *)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'close'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'goBack'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'search'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'prenotaOggetto'
        QtMocHelpers::SlotData<void(BibliotecaItem *)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 9 },
        }}),
        // Slot 'restituisciOggetto'
        QtMocHelpers::SlotData<void(BibliotecaItem *)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 9 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<UserPage, qt_meta_tag_ZN8UserPageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject UserPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8UserPageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8UserPageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8UserPageE_t>.metaTypes,
    nullptr
} };

void UserPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<UserPage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->itemUpdated((*reinterpret_cast< std::add_pointer_t<BibliotecaItem*>>(_a[1]))); break;
        case 1: _t->close(); break;
        case 2: _t->goBack(); break;
        case 3: _t->search(); break;
        case 4: _t->prenotaOggetto((*reinterpret_cast< std::add_pointer_t<BibliotecaItem*>>(_a[1]))); break;
        case 5: _t->restituisciOggetto((*reinterpret_cast< std::add_pointer_t<BibliotecaItem*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (UserPage::*)(BibliotecaItem * )>(_a, &UserPage::itemUpdated, 0))
            return;
    }
}

const QMetaObject *UserPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UserPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8UserPageE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "JsonObserver"))
        return static_cast< JsonObserver*>(this);
    return QWidget::qt_metacast(_clname);
}

int UserPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void UserPage::itemUpdated(BibliotecaItem * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}
QT_WARNING_POP
