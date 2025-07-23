// File Json.h
#ifndef JSON_H
#define JSON_H

#include <QObject>
#include <QString>
#include <QList>
#include "../modello_logico/BibliotecaItem.h"
#include <QDir>               // Per la gestione dei percorsi
#include <QCoreApplication>   // Per applicationDirPath()

class JsonObserver;

class Json : public QObject {
    Q_OBJECT
public:
    explicit Json(const QString& filePath = "", QObject *parent = nullptr);

    // Carica i dati dal file JSON
    QList<BibliotecaItem*> loadList();
    // Salva i dati nel file JSON
    void setFilePath(const QString& path);

    bool aggiornaStatoOggetto(BibliotecaItem* oggetto); // Per prenotazioni/restituzioni
    bool rimuoviOggetto(BibliotecaItem* oggetto); // Per eliminazioni
    bool aggiungiOggetto(BibliotecaItem* oggetto); // Per aggiunta
    bool modificaOggetto(BibliotecaItem* oggetto); // Per modifiche

    void aggiungiObserver(JsonObserver* observer);
    void rimuoviObserver(JsonObserver* observer);

private:
    QString path;
    int findIndex(BibliotecaItem* oggetto) const;
    QList<BibliotecaItem *> biblioteca;
    QList<JsonObserver*> observers;
    void notificaObservers();
};

#endif // JSON_H
