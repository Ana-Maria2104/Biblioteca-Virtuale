#include "stylevisitor.h"
#include <QPixmap>

StyleVisitor::StyleVisitor(QLabel* typeIcon, QLabel* titleLabel)
    : m_typeIcon(typeIcon), m_titleLabel(titleLabel) {}

void StyleVisitor::visit(Libro*) {
    m_typeIcon->setStyleSheet(m_typeIcon->styleSheet() + "background-color: #DCE2F0;");
    m_typeIcon->setPixmap(QPixmap(":/icons/libro_icon.png").scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_titleLabel->setStyleSheet("font-size: 18px; color: #2196F3;");
}

void StyleVisitor::visit(Film*) {
    m_typeIcon->setStyleSheet(m_typeIcon->styleSheet() + "background-color: #FFAAA5;");
    m_typeIcon->setPixmap(QPixmap(":/icons/film_icon.png").scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_titleLabel->setStyleSheet("font-size: 18px; color: #F44336;");
}

void StyleVisitor::visit(Rivista*) {
    m_typeIcon->setStyleSheet(m_typeIcon->styleSheet() + "background-color: #A8E6CF;");
    m_typeIcon->setPixmap(QPixmap(":/icons/rivista_icon.png").scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_titleLabel->setStyleSheet("font-size: 18px; color: #4CAF50;");
}
