#ifndef USERPAGE_H
#define USERPAGE_H

#include <QWidget>
#include <QStackedWidget>
#include <QList>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>
#include <QGridLayout>
#include <QCheckBox>
#include <QGroupBox>
#include <QDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include "../modello_logico/BibliotecaItem.h"
#include "../jsonHandler/JsonObserver.h"

class UserPage : public QWidget, public JsonObserver {
    Q_OBJECT

private:
    QList<BibliotecaItem*> lista;
    QList<BibliotecaItem*> prenotati; // Lista degli oggetti prenotati
    QStackedWidget* stack;

    // UI Components
    QFrame* topBarFrame;
    QLabel* labelPrestiti;
    QLineEdit* searchBar;
    QPushButton* backFromSearchButton;
    QPushButton* filterButton;
    QPushButton* ordiniButton;

    // Content area
    QScrollArea* scrollArea;
    QWidget* contentWidget;
    QGridLayout* contentLayout;

    // Filter dialog components
    QDialog* filterDialog;
    QCheckBox* allCategoryCheck;
    QCheckBox* libroCheck;
    QCheckBox* rivistaCheck;
    QCheckBox* filmCheck;
    QCheckBox* allLanguageCheck;
    QCheckBox* italianoCheck;
    QCheckBox* ingleseCheck;
    QCheckBox* spagnoloCheck;

    // State
    bool isSearchActive;
    static const QString fieldStyle;

    void initializeUI();
    void showFilterDialog();
    void applyFilters();
    void showOrdiniDialog();

public:
    UserPage(QList<BibliotecaItem*> listaOggetti, QStackedWidget* stackedwidget, QWidget* parent = nullptr);
    ~UserPage();

    // JsonObserver interface
    void onBibliotecaAggiornata(const QList<BibliotecaItem*>& nuovaLista) override;

    // UI update methods
    void refreshUI();
    void showAll();
    void cleanLayout();
    int showTotPrestiti() const;
    void riquadroOggetto(BibliotecaItem* obj, int& row, int& col, int maxColumns);

private slots:
    void close();
    void goBack();
    void search();
    void prenotaOggetto(BibliotecaItem* obj);
    void restituisciOggetto(BibliotecaItem* obj);

signals:
    void itemUpdated(BibliotecaItem* item);
};

#endif // USERPAGE_H
