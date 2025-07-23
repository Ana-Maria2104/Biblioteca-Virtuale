// File Libro.cpp
#include "Libro.h"
#include <iostream>
using namespace std;

// Costruttore aggiornato con i nuovi parametri
Libro::Libro(const string& image, const string& title, int year, const string& genre,
             const string& language, bool available, int numberCopies, int numberLoans,
             const string& autor, int pages, const string& code, const string& desc,
             const string& target, bool ebook)
    : BibliotecaItem(image, title, year, genre, language, available,
                     numberCopies, numberLoans, desc),
    autore(autor), pagine(pages), isbn(code), targetEta(target), haEbook(ebook) {}

// Getters
string Libro::getAutore() const { return autore; }
int Libro::getPagine() const { return pagine; }
string Libro::getISBN() const { return isbn; }
string Libro::getTargetEta() const { return targetEta; }
bool Libro::getHaEbook() const { return haEbook; }

// Setters
void Libro::setAutore(const string& autor) { autore = autor; }
void Libro::setPagine(const int& pages) { pagine = pages; }
void Libro::setISBN(const string& code) { isbn = code; }
void Libro::setTargetEta(const string& target) { targetEta = target; }
void Libro::setHaEbook(bool ebook) { haEbook = ebook; }

// Metodi
void Libro::accept(Visitor* visitor) {
    visitor->visit(this);
}
