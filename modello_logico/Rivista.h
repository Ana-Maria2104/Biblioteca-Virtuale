// File Rivista.h
#ifndef RIVISTA_H
#define RIVISTA_H

#include "BibliotecaItem.h"
#include <vector>
#include <utility>

class Rivista : public BibliotecaItem {
private:
    std::string periodicità;
    std::string editore;
    std::string direttore;
    std::string ISSN;
    std::vector<std::pair<std::string, std::string>> articoli; // <titolo, autore>
    int volume;

public:
    Rivista(const std::string& image, const std::string& title, int year,
            const std::string& genre, const std::string& language, bool available,
            int numberCopies, int numberLoans, const std::string& desc,
            const std::string& periodicità, const std::string& editore,
            const std::string& direttore, const std::string& ISSN,
            const std::vector<std::pair<std::string, std::string>>& articoli,
            int volume);

    // Getters
    std::string getPeriodicità() const;
    std::string getEditore() const;
    std::string getDirettore() const;
    std::string getISSN() const;
    std::vector<std::pair<std::string, std::string>> getArticoli() const;
    int getVolume() const;

    // Setters
    void setPeriodicità(const std::string& p);
    void setEditore(const std::string& e);
    void setDirettore(const std::string& d);
    void setISSN(const std::string& issn);
    void setArticoli(const std::vector<std::pair<std::string, std::string>>& a);
    void setVolume(int v);

    // Aggiungi un singolo articolo
    void aggiungiArticolo(const std::string& titolo, const std::string& autore);

    // Visitor pattern
    void accept(Visitor* visitor) override;
};

#endif // RIVISTA_H
