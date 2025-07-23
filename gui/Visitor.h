//File Visitor.h
#ifndef VISITOR_H
#define VISITOR_H

class Libro;
class Film;
class Rivista;
class Visitor{
public:
    virtual ~Visitor() = default;
    virtual void visit(Libro* libro) = 0;
    virtual void visit(Film* film) = 0;
    virtual void visit(Rivista* rivista) = 0;
};

#endif


