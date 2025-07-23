#ifndef BIBLIOTECAITEM_H
#define BIBLIOTECAITEM_H

#include "../gui/Visitor.h"
#include <string>
#include <vector>

using namespace std;

class BibliotecaItem {
private:
    string immagine;
    string titolo;
    int anno;
    string genere;
    string lingua;
    bool disponibile;
    int numeroCopie;
    int numeroPrestiti;
    string descrizione;

public:
    // Costruttore e distruttore
    BibliotecaItem(const string& image, const string& title, int year,
                   const string& genre, const string& language, bool available,
                   int numberCopies, int numberLoans, const string& desc = "");
    virtual ~BibliotecaItem() = default;

    string getDisponibilitaString() const {
        int disp = numeroCopie - numeroPrestiti;
        return to_string(disp) + "/" + to_string(numeroCopie) +
               (disponibile ? " (Disponibile)" : " (Esaurito)");
    }

    // Getters
    string getImmagine() const;
    string getTitolo() const;
    int getAnno() const;
    string getGenere() const;
    string getLingua() const;
    bool getDisponibile() const;
    int getNumeroCopie() const;
    int getNumeroPrestiti() const;
    string getDescrizione() const;

    // Setters
    void setImmagine(const string& image);
    void setTitolo(const string& title);
    void setAnno(int year);
    void setGenere(const string& genre);
    void setLingua(const string& language);
    void setDisponibile(bool available);
    void setNumeroCopie(int numberCopies);
    void setNumeroPrestiti(int numberLoans);
    void setDescrizione(const string& desc);

    // Metodi
    virtual void accept(Visitor* visitor) = 0;
    bool prenota();
    bool restituisci();
};

#endif // BIBLIOTECAITEM_H
