#ifndef LIBRO_H
#define LIBRO_H

#include "BibliotecaItem.h"
#include <string>
using std::string;

class Libro : public BibliotecaItem {
private:
    string autore;
    int pagine;
    string isbn;
    string targetEta;  // Es: "12+", "18+", "Adulti", "Bambini"
    bool haEbook;      // true se disponibile in formato ebook

public:
    // Costruttore aggiornato
    Libro(const string& image, const string& title, int year, const string& genre,
          const string& language, bool available,
          int numberCopies, int numberLoans, const string& autor,
          int pages, const string& code, const string& desc = "",
          const string& target = "Adulti (18+ anni)", bool ebook = false);

    // Getters
    string getAutore() const;
    int getPagine() const;
    string getISBN() const;
    string getTargetEta() const;
    bool getHaEbook() const;

    // Setters
    void setAutore(const string& autor);
    void setPagine(const int& pages);
    void setISBN(const string& code);
    void setTargetEta(const string& target);
    void setHaEbook(bool ebook);

    // Metodi
    virtual void accept(Visitor* visitor) override;
};

#endif // LIBRO_H
