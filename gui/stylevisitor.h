#ifndef STYLEVISITOR_H
#define STYLEVISITOR_H

#include "Visitor.h"
#include <QLabel>

class StyleVisitor : public Visitor {
public:
    StyleVisitor(QLabel* typeIcon, QLabel* titleLabel);

    void visit(Libro* libro) override;
    void visit(Film* film) override;
    void visit(Rivista* rivista) override;

private:
    QLabel* m_typeIcon;
    QLabel* m_titleLabel;
};

#endif // STYLEVISITOR_H
