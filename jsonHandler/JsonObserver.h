// File JsonObserver.h
#ifndef JSONOBSERVER_H
#define JSONOBSERVER_H

#include <QList>
class BibliotecaItem;

class JsonObserver {
public:
    virtual void onBibliotecaAggiornata(const QList<BibliotecaItem*>& nuovaLista) = 0;
    virtual ~JsonObserver() = default;
};

#endif // JSONOBSERVER_H
