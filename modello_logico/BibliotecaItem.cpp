#include "BibliotecaItem.h"
#include <iostream>

using namespace std;

BibliotecaItem::BibliotecaItem(const string& image, const string& title, int year,
                               const string& genre, const string& language, bool available,
                               int numberCopies, int numberLoans, const string& desc) :
    immagine(image),
    titolo(title),
    anno(year),
    genere(genre),
    lingua(language),
    disponibile(available),
    numeroCopie(numberCopies < 1 ? 1 : numberCopies),
    numeroPrestiti(numberLoans < 0 ? 0 : numberLoans),
    descrizione(desc)
{}

// Getters
string BibliotecaItem::getDescrizione() const { return descrizione; }
string BibliotecaItem::getImmagine() const { return immagine; }
string BibliotecaItem::getTitolo() const { return titolo; }
int BibliotecaItem::getAnno() const { return anno; }
string BibliotecaItem::getGenere() const { return genere; }
string BibliotecaItem::getLingua() const { return lingua; }
bool BibliotecaItem::getDisponibile() const { return disponibile; }
int BibliotecaItem::getNumeroCopie() const { return numeroCopie; }
int BibliotecaItem::getNumeroPrestiti() const { return numeroPrestiti; }

// Setters
void BibliotecaItem::setDescrizione(const string& desc) { descrizione = desc; }
void BibliotecaItem::setImmagine(const string& image) { immagine = image; }
void BibliotecaItem::setTitolo(const string& title) { titolo = title; }
void BibliotecaItem::setAnno(int year) { anno = year; }
void BibliotecaItem::setGenere(const string& genre) { genere = genre; }
void BibliotecaItem::setLingua(const string& language) { lingua = language; }
void BibliotecaItem::setDisponibile(bool available) { disponibile = available; }
void BibliotecaItem::setNumeroCopie(int numberCopies) { numeroCopie = numberCopies; }
void BibliotecaItem::setNumeroPrestiti(int numberLoans) { numeroPrestiti = numberLoans; }

// Metodi
bool BibliotecaItem::prenota() {
    if (numeroPrestiti >= numeroCopie) return false;
    numeroPrestiti++;
    disponibile = (numeroPrestiti < numeroCopie);
    return true;
}

bool BibliotecaItem::restituisci() {
    if (numeroPrestiti <= 0) return false;
    numeroPrestiti--;
    disponibile = true;
    return true;
}

