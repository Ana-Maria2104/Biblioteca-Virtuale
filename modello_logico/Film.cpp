#include "Film.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Costruttore completo
Film::Film(const string& image, const string& title, int year, const string& genre,
           const string& language, bool available, int numberCopies, int numberLoans,
           const string& director, const string& protagonist, int duration,
           const string& desc, const vector<string>& awards,
           const string& country, bool subtitles, int filmRating)
    : BibliotecaItem(image, title, year, genre, language, available,
                     numberCopies, numberLoans, desc),
    regista(director),
    protagonista(protagonist),
    durata(duration),
    premi(awards),
    paeseOrigine(country),
    haSottotitoli(subtitles),
    rating(max(1, min(5, filmRating))) {}  // Assicura che il rating sia tra 1 e 5

// Getters
string Film::getRegista() const { return regista; }
string Film::getProtagonista() const { return protagonista; }
int Film::getDurata() const { return durata; }
vector<string> Film::getPremi() const { return premi; }
string Film::getPaeseOrigine() const { return paeseOrigine; }
bool Film::getHaSottotitoli() const { return haSottotitoli; }
int Film::getRating() const { return rating; }

// Setters
void Film::setRegista(const string& director) { regista = director; }
void Film::setProtagonista(const string& protagonist) { protagonista = protagonist; }
void Film::setDurata(const int& duration) { durata = duration; }

void Film::setPremi(const vector<string>& awards) { premi = awards; }
void Film::aggiungiPremio(const string& award) {
    if(find(premi.begin(), premi.end(), award) == premi.end()) {
        premi.push_back(award);
    }
}
void Film::setPaeseOrigine(const string& country) { paeseOrigine = country; }
void Film::setHaSottotitoli(bool subtitles) { haSottotitoli = subtitles; }

void Film::setRating(int filmRating) {
    rating = max(1, min(5, filmRating)); // Mantiene il rating tra 1 e 5
}

// Metodo accept
void Film::accept(Visitor* visitor) {
    visitor->visit(this);
}
