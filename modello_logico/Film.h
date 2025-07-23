#ifndef FILM_H
#define FILM_H

#include "BibliotecaItem.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

class Film : public BibliotecaItem {
private:
    string regista;
    string protagonista;
    int durata;
    vector<string> premi;
    string paeseOrigine;
    bool haSottotitoli;
    int rating; // da 1 a 5

public:
    // Costruttore
    Film(const string& image, const string& title, int year, const string& genre,
         const string& language, bool available, int numberCopies, int numberLoans,
         const string& director, const string& protagonist, int duration,
         const string& desc = "", const vector<string>& awards = {},
         const string& country = "", bool subtitles = false, int filmRating = 3);

    // Getters
    string getRegista() const;
    string getProtagonista() const;
    int getDurata() const;
    vector<string> getPremi() const;
    string getPaeseOrigine() const;
    bool getHaSottotitoli() const;
    int getRating() const;

    // Setters
    void setRegista(const string& director);
    void setProtagonista(const string& protagonist);
    void setDurata(const int& duration);
    void setPremi(const vector<string>& awards);
    void aggiungiPremio(const string& award);
    void setPaeseOrigine(const string& country);
    void setHaSottotitoli(bool subtitles);
    void setRating(int rating);

    // Metodi
    virtual void accept(Visitor* visitor) override;
};

#endif // FILM_H
