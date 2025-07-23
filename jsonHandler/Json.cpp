#include "Json.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "../modello_logico/Libro.h"
#include "../modello_logico/Film.h"
#include "../modello_logico/Rivista.h"
#include "JsonObserver.h"

Json::Json(const QString &filePath, QObject *parent) : QObject(parent), path(filePath) {}

void Json::setFilePath(const QString& path) {
    this->path = path;
}

QList<BibliotecaItem*> Json::loadList() {
    QList<BibliotecaItem*> listaOggetti;
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Impossibile aprire il file JSON!");
        return listaOggetti;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull() || !doc.isArray()) {
        qWarning("Errore nel parsing del JSON!");
        return listaOggetti;
    }

    QJsonArray jsonArray = doc.array();
    for (int i = 0; i < jsonArray.size(); ++i) {
        QJsonValue value = jsonArray.at(i);
        QJsonObject obj = value.toObject();
        QString classe = obj["classe"].toString();
        QString immagine = obj["immagine"].toString();
        QString titolo = obj["titolo"].toString();
        QString genere = obj["genere"].toString();
        QString lingua = obj["lingua"].toString();
        int anno = obj["anno"].toInt();
        int numeroCopie = obj["numeroCopie"].toInt();
        int numeroPrestiti = obj["numeroPrestiti"].toInt();
        bool disponibile = obj["disponibile"].toBool();
        QString descrizione = obj["descrizione"].toString();

        if (classe == "libro") {
            QString autore = obj["autore"].toString();
            int pagine = obj["pagine"].toInt();
            QString isbn = obj["isbn"].toString();
            QString targetEta = obj["targetEta"].toString("Adulti");
            bool haEbook = obj["haEbook"].toBool(false);

            listaOggetti.append(new Libro(
                immagine.toStdString(),
                titolo.toStdString(),
                anno,
                genere.toStdString(),
                lingua.toStdString(),
                disponibile,
                numeroCopie,
                numeroPrestiti,
                autore.toStdString(),
                pagine,
                isbn.toStdString(),
                descrizione.toStdString(),
                targetEta.toStdString(),
                haEbook
                ));
        }
        else if (classe == "film") {
            QString regista = obj["regista"].toString();
            QString protagonista = obj["protagonista"].toString();
            int durata = obj["durata"].toInt();
            QString paeseOrigine = obj["paeseOrigine"].toString();
            bool sottotitoli = obj["sottotitoli"].toBool();
            int rating = obj["rating"].toInt();

            vector<string> premi;
            QJsonArray premiArray = obj["premi"].toArray();
            for (int i = 0; i < premiArray.size(); ++i) {
                QJsonValue premio = premiArray.at(i);
                premi.push_back(premio.toString().toStdString());
            }

            Film* film = new Film(
                immagine.toStdString(),
                titolo.toStdString(),
                anno,
                genere.toStdString(),
                lingua.toStdString(),
                disponibile,
                numeroCopie,
                numeroPrestiti,
                regista.toStdString(),
                protagonista.toStdString(),
                durata,
                descrizione.toStdString(),
                premi,
                paeseOrigine.toStdString(),
                sottotitoli,
                rating
                );
            listaOggetti.append(film);
        }
        else if (classe == "rivista") {
            QString periodicità = obj["periodicita"].toString();
            QString editore = obj["editore"].toString();
            QString direttore = obj["direttore"].toString();
            QString ISSN = obj["ISSN"].toString();
            int volume = obj["volume"].toInt();

            vector<pair<string, string>> articoli;
            QJsonArray articoliArray = obj["articoli"].toArray();
            for (int i = 0; i < articoliArray.size(); ++i) {
                QJsonValue articolo = articoliArray.at(i);
                QJsonObject artObj = articolo.toObject();
                articoli.emplace_back(
                    artObj["titolo"].toString().toStdString(),
                    artObj["autore"].toString().toStdString()
                    );
            }

            listaOggetti.append(new Rivista(
                immagine.toStdString(),
                titolo.toStdString(),
                anno,
                genere.toStdString(),
                lingua.toStdString(),
                disponibile,
                numeroCopie,
                numeroPrestiti,
                descrizione.toStdString(),
                periodicità.toStdString(),
                editore.toStdString(),
                direttore.toStdString(),
                ISSN.toStdString(),
                articoli,
                volume
                ));
        }
    }
    biblioteca = listaOggetti;
    return listaOggetti;
}

int Json::findIndex(BibliotecaItem* oggetto) const {
    if (!oggetto) {
        qWarning() << "Oggetto nullo";
        return -1;
    }
    for (int i = 0; i < biblioteca.size(); ++i) {
        if (biblioteca[i] == oggetto) {
            return i;
        }
    }
    return -1;
}

bool Json::aggiornaStatoOggetto(BibliotecaItem* oggetto) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Impossibile aprire il file per l'aggiornamento";
        return false;
    }

    QJsonArray jsonArray = QJsonDocument::fromJson(file.readAll()).array();
    file.close();

    int index = findIndex(oggetto);
    if (index == -1) {
        qWarning() << "Oggetto non trovato nel file JSON";
        return false;
    }

    QJsonObject obj = jsonArray[index].toObject();
    obj["disponibile"] = oggetto->getDisponibile();
    obj["numeroPrestiti"] = oggetto->getNumeroPrestiti();

    jsonArray.replace(index, obj);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qCritical() << "Impossibile aprire il file per il salvataggio";
        return false;
    }

    if (file.write(QJsonDocument(jsonArray).toJson()) != -1) {
        file.close();
        notificaObservers();
        return true;
    }
    file.close();
    return false;
}

bool Json::rimuoviOggetto(BibliotecaItem* oggetto) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Impossibile aprire il file per la rimozione";
        return false;
    }

    QJsonArray jsonArray = QJsonDocument::fromJson(file.readAll()).array();
    file.close();

    int index = findIndex(oggetto);
    if (index == -1) {
        qWarning() << "Oggetto non trovato nel file JSON";
        return false;
    }

    jsonArray.removeAt(index);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qCritical() << "Impossibile aprire il file per il salvataggio";
        return false;
    }

    if (file.write(QJsonDocument(jsonArray).toJson()) != -1) {
        biblioteca.removeAt(index);
        notificaObservers();
        delete oggetto;
        file.close();
        return true;
    }
    file.close();
    return false;
}

bool Json::aggiungiOggetto(BibliotecaItem* oggetto) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Impossibile aprire il file per l'aggiunta";
        return false;
    }

    QJsonArray jsonArray = QJsonDocument::fromJson(file.readAll()).array();
    file.close();

    QJsonObject newObj;
    newObj["immagine"] = QString::fromStdString(oggetto->getImmagine());
    newObj["titolo"] = QString::fromStdString(oggetto->getTitolo());
    newObj["anno"] = oggetto->getAnno();
    newObj["genere"] = QString::fromStdString(oggetto->getGenere());
    newObj["lingua"] = QString::fromStdString(oggetto->getLingua());
    newObj["disponibile"] = oggetto->getDisponibile();
    newObj["numeroCopie"] = oggetto->getNumeroCopie();
    newObj["numeroPrestiti"] = oggetto->getNumeroPrestiti();
    newObj["descrizione"] = QString::fromStdString(oggetto->getDescrizione());

    if (Libro* libro = dynamic_cast<Libro*>(oggetto)) {
        newObj["classe"] = "libro";
        newObj["autore"] = QString::fromStdString(libro->getAutore());
        newObj["pagine"] = libro->getPagine();
        newObj["isbn"] = QString::fromStdString(libro->getISBN());
        newObj["targetEta"] = QString::fromStdString(libro->getTargetEta());
        newObj["haEbook"] = libro->getHaEbook();
    }
    else if (Film* film = dynamic_cast<Film*>(oggetto)) {
        newObj["classe"] = "film";
        newObj["regista"] = QString::fromStdString(film->getRegista());
        newObj["protagonista"] = QString::fromStdString(film->getProtagonista());
        newObj["durata"] = film->getDurata();
        newObj["paeseOrigine"] = QString::fromStdString(film->getPaeseOrigine());
        newObj["sottotitoli"] = film->getHaSottotitoli();
        newObj["rating"] = film->getRating();

        QJsonArray premiArray;
        for (const auto& premio : film->getPremi()) {
            premiArray.append(QString::fromStdString(premio));
        }
        newObj["premi"] = premiArray;
    }
    else if (Rivista* rivista = dynamic_cast<Rivista*>(oggetto)) {
        newObj["classe"] = "rivista";
        newObj["periodicita"] = QString::fromStdString(rivista->getPeriodicità());
        newObj["editore"] = QString::fromStdString(rivista->getEditore());
        newObj["direttore"] = QString::fromStdString(rivista->getDirettore());
        newObj["ISSN"] = QString::fromStdString(rivista->getISSN());
        newObj["volume"] = rivista->getVolume();

        QJsonArray articoliArray;
        for (const auto& articolo : rivista->getArticoli()) {
            QJsonObject artObj;
            artObj["titolo"] = QString::fromStdString(articolo.first);
            artObj["autore"] = QString::fromStdString(articolo.second);
            articoliArray.append(artObj);
        }
        newObj["articoli"] = articoliArray;
    }

    jsonArray.append(newObj);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qCritical() << "Impossibile aprire il file per il salvataggio";
        return false;
    }

    if (file.write(QJsonDocument(jsonArray).toJson()) != -1) {
        biblioteca.append(oggetto);
        file.close();
        notificaObservers();
        return true;
    }
    file.close();
    return false;
}

bool Json::modificaOggetto(BibliotecaItem* oggetto) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Impossibile aprire il file per la modifica";
        return false;
    }

    QJsonArray jsonArray = QJsonDocument::fromJson(file.readAll()).array();
    file.close();

    int index = findIndex(oggetto);
    if (index == -1) {
        qWarning() << "Oggetto non trovato nel file JSON";
        return false;
    }

    QJsonObject obj = jsonArray[index].toObject();
    obj["immagine"] = QString::fromStdString(oggetto->getImmagine());
    obj["titolo"] = QString::fromStdString(oggetto->getTitolo());
    obj["anno"] = oggetto->getAnno();
    obj["genere"] = QString::fromStdString(oggetto->getGenere());
    obj["lingua"] = QString::fromStdString(oggetto->getLingua());
    obj["disponibile"] = oggetto->getDisponibile();
    obj["numeroCopie"] = oggetto->getNumeroCopie();
    obj["numeroPrestiti"] = oggetto->getNumeroPrestiti();
    obj["descrizione"] = QString::fromStdString(oggetto->getDescrizione());

    if (Libro* libro = dynamic_cast<Libro*>(oggetto)) {
        obj["classe"] = "libro";
        obj["autore"] = QString::fromStdString(libro->getAutore());
        obj["pagine"] = libro->getPagine();
        obj["isbn"] = QString::fromStdString(libro->getISBN());
        obj["targetEta"] = QString::fromStdString(libro->getTargetEta());
        obj["haEbook"] = libro->getHaEbook();
    }
    else if (Film* film = dynamic_cast<Film*>(oggetto)) {
        obj["classe"] = "film";
        obj["regista"] = QString::fromStdString(film->getRegista());
        obj["protagonista"] = QString::fromStdString(film->getProtagonista());
        obj["durata"] = film->getDurata();
        obj["paeseOrigine"] = QString::fromStdString(film->getPaeseOrigine());
        obj["sottotitoli"] = film->getHaSottotitoli();
        obj["rating"] = film->getRating();

        QJsonArray premiArray;
        for (const auto& premio : film->getPremi()) {
            premiArray.append(QString::fromStdString(premio));
        }
        obj["premi"] = premiArray;
    }
    else if (Rivista* rivista = dynamic_cast<Rivista*>(oggetto)) {
        obj["classe"] = "rivista";
        obj["periodicita"] = QString::fromStdString(rivista->getPeriodicità());
        obj["editore"] = QString::fromStdString(rivista->getEditore());
        obj["direttore"] = QString::fromStdString(rivista->getDirettore());
        obj["ISSN"] = QString::fromStdString(rivista->getISSN());
        obj["volume"] = rivista->getVolume();

        QJsonArray articoliArray;
        for (const auto& articolo : rivista->getArticoli()) {
            QJsonObject artObj;
            artObj["titolo"] = QString::fromStdString(articolo.first);
            artObj["autore"] = QString::fromStdString(articolo.second);
            articoliArray.append(artObj);
        }
        obj["articoli"] = articoliArray;
    }

    jsonArray.replace(index, obj);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qCritical() << "Impossibile aprire il file per il salvataggio";
        return false;
    }

    if (file.write(QJsonDocument(jsonArray).toJson()) != -1) {
        if (index >= 0 && index < biblioteca.size()) {
            BibliotecaItem* existingObj = biblioteca[index];
            *existingObj = *oggetto;
        }
        file.close();
        notificaObservers();
        return true;
    }
    file.close();
    return false;
}

void Json::aggiungiObserver(JsonObserver* observer) {
    if(observer && !observers.contains(observer)) {
        observers.append(observer);
    }
}

void Json::rimuoviObserver(JsonObserver* observer) {
    observers.removeAll(observer);
}

void Json::notificaObservers() {

    for (int i = 0; i < observers.size(); ++i) {
        JsonObserver* observer = observers.at(i);
        observer->onBibliotecaAggiornata(biblioteca);
    }
}

