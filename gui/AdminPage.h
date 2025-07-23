#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include "../modello_logico/Libro.h"
#include "../modello_logico/Film.h"
#include "../modello_logico/Rivista.h"
#include "../jsonHandler/JsonObserver.h"
#include "PageVisitor.h"
#include "filtervisitor.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include <QAction>
#include <QMenu>
#include <QGridLayout>
#include <QActionGroup>
#include <QPushButton>
#include <QFrame>
#include <QMessageBox>
#include <QDialog>
#include <QCheckBox>
#include <QGroupBox>

class AdminPage : public QWidget, public JsonObserver {
    Q_OBJECT

private:

    // UI Elements
    QPushButton* backFromSearchButton;
    QPushButton *exitSearchButton;
    QPushButton *filterButton;
    QDialog *filterDialog;
    QStackedWidget *stack ;
    QLineEdit *searchBar;
    QLabel *labelPrestiti;
    QGridLayout *contentLayout;
    QWidget *contentWidget;
    QScrollArea *scrollArea;

    // Filter Dialog Elements
    QCheckBox *allCategoryCheck;
    QCheckBox *libroCheck;
    QCheckBox *rivistaCheck;
    QCheckBox *filmCheck;
    QCheckBox *allLanguageCheck;
    QCheckBox *italianoCheck;
    QCheckBox *ingleseCheck;
    QCheckBox *spagnoloCheck;

    // Data
    QList<BibliotecaItem*> lista;

    // Constants
    static const QString fieldStyle;

    // Private methods
    void initializeUI();
    void setupFilterDialog();
    void setupFilterConnections();

public:
    explicit AdminPage(QList<BibliotecaItem *> listaOggetti, QStackedWidget *stackedwidget, QWidget *parent = nullptr);
    ~AdminPage() override;

    // Public methods

    void showAll();
    int showTotPrestiti() const;
    void cleanLayout();
    void riquadroOggetto(BibliotecaItem *obj, int &row, int &col, int maxColumns);
    void onBibliotecaAggiornata(const QList<BibliotecaItem*>& nuovaLista) override;
    void refreshUI();
    void applyFilters();

private:
    // Business Logic
    bool isSearchActive;
    void prenotaOggetto(BibliotecaItem *obj);
    void restituisciOggetto(BibliotecaItem *obj);
    void modificaOggetto(BibliotecaItem *obj);
    void eliminaOggetto(BibliotecaItem *obj);

private slots:
    void close();
    void goBack();
    void search();
    void create();
    void showFilterDialog();

signals:
    void itemUpdated(BibliotecaItem* item);
    void itemRemoved(BibliotecaItem* item);
    void createItem();
    void modifyItem(BibliotecaItem* item);
};

#endif // ADMINPAGE_H
