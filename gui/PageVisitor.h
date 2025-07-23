// File PageVisitor.h
#ifndef PAGEVISITOR_H
#define PAGEVISITOR_H
#include "Visitor.h"
#include <QWidget>
#include <QVBoxLayout>

class BibliotecaItem;

class PageVisitor : public Visitor {
    private:
        QWidget *pageWidget;
        QVBoxLayout *pageLayout;
        void buildCommonWidgets(BibliotecaItem *item);
    public:
        PageVisitor();
        //void visit(BibliotecaItem *item);
        void visit(Libro *libro) override; 
        void visit(Film *film) override;
        void visit(Rivista *rivista) override;
        QWidget* getObjectWidget() const;
};


#endif // PAGEVISITOR_H
