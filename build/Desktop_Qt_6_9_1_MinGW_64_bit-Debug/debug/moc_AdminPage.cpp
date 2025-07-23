/****************************************************************************
** Meta object code from reading C++ file 'AdminPage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../Biblioteca_D/Biblioteca_D_main/gui/AdminPage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AdminPage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN9AdminPageE_t {};
} // unnamed namespace

template <> constexpr inline auto AdminPage::qt_create_metaobjectdata<qt_meta_tag_ZN9AdminPageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AdminPage",
        "itemUpdated",
        "",
        "Biblioteca*",
        "item",
        "itemRemoved",
        "createItem",
        "modifyItem",
        "close",
        "goBack",
        "search",
        "filter",
        "prenotaOggetto",
        "obj",
        "restituisciOggetto",
        "create",
        "modificaOggetto",
        "eliminaOggetto"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'itemUpdated'
        QtMocHelpers::SignalData<void(Biblioteca *)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'itemRemoved'
        QtMocHelpers::SignalData<void(Biblioteca *)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'createItem'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'modifyItem'
        QtMocHelpers::SignalData<void(Biblioteca *)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'close'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'goBack'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'search'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'filter'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'prenotaOggetto'
        QtMocHelpers::SlotData<void(Biblioteca *)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 13 },
        }}),
        // Slot 'restituisciOggetto'
        QtMocHelpers::SlotData<void(Biblioteca *)>(14, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 13 },
        }}),
        // Slot 'create'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'modificaOggetto'
        QtMocHelpers::SlotData<void(Biblioteca *)>(16, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 13 },
        }}),
        // Slot 'eliminaOggetto'
        QtMocHelpers::SlotData<void(Biblioteca *)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 13 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<AdminPage, qt_meta_tag_ZN9AdminPageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject AdminPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9AdminPageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9AdminPageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9AdminPageE_t>.metaTypes,
    nullptr
} };

void AdminPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AdminPage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->itemUpdated((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        case 1: _t->itemRemoved((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        case 2: _t->createItem(); break;
        case 3: _t->modifyItem((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        case 4: _t->close(); break;
        case 5: _t->goBack(); break;
        case 6: _t->search(); break;
        case 7: _t->filter(); break;
        case 8: _t->prenotaOggetto((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        case 9: _t->restituisciOggetto((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        case 10: _t->create(); break;
        case 11: _t->modificaOggetto((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        case 12: _t->eliminaOggetto((*reinterpret_cast< std::add_pointer_t<Biblioteca*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)(Biblioteca * )>(_a, &AdminPage::itemUpdated, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)(Biblioteca * )>(_a, &AdminPage::itemRemoved, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)()>(_a, &AdminPage::createItem, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)(Biblioteca * )>(_a, &AdminPage::modifyItem, 3))
            return;
    }
}

const QMetaObject *AdminPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AdminPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9AdminPageE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "JsonObserver"))
        return static_cast< JsonObserver*>(this);
    return QWidget::qt_metacast(_clname);
}

int AdminPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void AdminPage::itemUpdated(Biblioteca * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void AdminPage::itemRemoved(Biblioteca * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void AdminPage::createItem()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AdminPage::modifyItem(Biblioteca * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}
QT_WARNING_POP
