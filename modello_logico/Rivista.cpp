// File Rivista.cpp
#include "Rivista.h"
#include <iostream>

using namespace std;

// Costruttore
Rivista::Rivista(const string& image, const string& title, int year,
                 const string& genre, const string& language, bool available,
                 int numberCopies, int numberLoans, const string& desc,
                 const string& periodicità, const string& editore,
                 const string& direttore, const string& ISSN,
                 const vector<pair<string, string>>& articoli,
                 int volume)
    : BibliotecaItem(image, title, year, genre, language, available,
                     numberCopies, numberLoans, desc),
    periodicità(periodicità), editore(editore), direttore(direttore),
    ISSN(ISSN), articoli(articoli), volume(volume) {}

// Getters
string Rivista::getPeriodicità() const { return periodicità; }
string Rivista::getEditore() const { return editore; }
string Rivista::getDirettore() const { return direttore; }
string Rivista::getISSN() const { return ISSN; }
vector<pair<string, string>> Rivista::getArticoli() const { return articoli; }
int Rivista::getVolume() const { return volume; }

// Setters
void Rivista::setPeriodicità(const string& p) { periodicità = p; }
void Rivista::setEditore(const string& e) { editore = e; }
void Rivista::setDirettore(const string& d) { direttore = d; }
void Rivista::setISSN(const string& issn) { ISSN = issn; }
void Rivista::setArticoli(const vector<pair<string, string>>& a) { articoli = a; }
void Rivista::setVolume(int v) { volume = v; }

// Aggiungi un singolo articolo
void Rivista::aggiungiArticolo(const string& titolo, const string& autore) {
    articoli.emplace_back(titolo, autore);
}

// Visitor pattern
void Rivista::accept(Visitor* visitor) {
    visitor->visit(this);
}
