// FilterVisitor.h
#ifndef FILTERVISITOR_H
#define FILTERVISITOR_H

#include "Visitor.h"
#include "../modello_logico/Libro.h"
#include "../modello_logico/Film.h"
#include "../modello_logico/Rivista.h"

class FilterVisitor : public Visitor {
public:
    bool isLibro = false;
    bool isFilm = false;
    bool isRivista = false;
    void visit(Libro* /*libro*/) override { isLibro = true; }
    void visit(Film* /*film*/) override { isFilm = true; }
    void visit(Rivista* /*rivista*/) override { isRivista = true; }
};

#endif // FILTERVISITOR_H
