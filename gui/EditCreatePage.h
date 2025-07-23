#ifndef EDITCREATEPAGE_H
#define EDITCREATEPAGE_H

#include "../modello_logico/Libro.h"
#include "../modello_logico/Film.h"
#include "../modello_logico/Rivista.h"
#include "../modello_logico/BibliotecaItem.h"
#include "Visitor.h"

#include <QWidget>
#include <QStackedWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QDialog>
#include <QTextEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QListWidget>
#include <QInputDialog>
#include <QScrollArea>
#include <QDir>               // Per la gestione dei percorsi
#include <QCoreApplication>   // Per applicationDirPath()
#include <QFileDialog>        // Per QFileDialog

class EditCreatePage : public QWidget, public Visitor {
    Q_OBJECT
public:
    enum Mode { Create, Edit };

    explicit EditCreatePage(QStackedWidget* stackedWidget, QWidget* adminPageWidget, QWidget* parent = nullptr);

    void setupForCreation();
    void setupForEditing(BibliotecaItem* item);

    // Visitor pattern methods
    void visit(Libro* libro) override;
    void visit(Film* film) override;
    void visit(Rivista* rivista) override;

    // Setup fields
    void setupCommonFields();
    void setupBookFields(Libro* libro = nullptr);
    void setupFilmFields(Film* film = nullptr);
    void setupRivistaFields(Rivista* rivista = nullptr);

    void cleanLayout();
    BibliotecaItem* createNewItem();

    void aggiornaDisponibilità(BibliotecaItem* item);
    bool aggiornaFields(BibliotecaItem* item);
    bool aggiornaSpecificFields(BibliotecaItem* item);

signals:
    void itemCreated(BibliotecaItem* newItem);
    void itemUpdated(BibliotecaItem* updatedItem);

private slots:
    void saveItem();
    void goBack();

private:
    void showEditingPage();
     QString buttonStyle;
     QStackedWidget* contentStack;

    // UI elements for selection buttons
    QPushButton* libroButton;
    QPushButton* filmButton;
    QPushButton* rivistaButton;

    // UI layout
    QVBoxLayout* mainLayout;
    QFormLayout* formLayout;
    QScrollArea* scrollArea;

    // Navigation buttons
    QPushButton* backButton;
    QPushButton* saveButton;

    // State
    QStackedWidget* stack;
    QWidget* adminPage;                // pagina principale
    bool sceltaTipoVisibile = true;   // serve per gestione "torna indietro"
    Mode currentMode;
    BibliotecaItem* currentItem;
    QString currentType;

    // Common fields
    QTextEdit* descriptionEdit;
    QLineEdit* titleEdit;
    QSpinBox* yearEdit;
    QLineEdit* genreEdit;
    QComboBox* languageCombo;
    QSpinBox* copiesEdit;
    QSpinBox* loansEdit;

    // Image fields
    QLineEdit* imagePathEdit;
    QPushButton* browseImageButton;
    QLabel* imagePreview;

    // Book fields
    QLineEdit* authorEdit;
    QSpinBox* pagesEdit;
    QLineEdit* isbnEdit;
    QComboBox* targetEtaCombo;
    QCheckBox* ebookCheck;

    // Film fields
    QLineEdit* directorEdit;
    QLineEdit* protagonistEdit;
    QSpinBox* durationEdit;
    QLineEdit* countryEdit;
    QCheckBox* subtitlesCheck;
    QComboBox* ratingCombo;
    QGroupBox* awardsGroup;
    QListWidget* awardsList;
    QPushButton* addAwardButton;
    QPushButton* removeAwardButton;

    // Rivista fields
    QLineEdit* editoreEdit;
    QLineEdit* direttoreEdit;
    QComboBox* periodicitàCombo;
    QLineEdit* issnEdit;
    QSpinBox* volumeEdit;
    QGroupBox* articoliGroup;
    QListWidget* articoliList;
    QPushButton* addArticoloButton;
    QPushButton* removeArticoloButton;

    static const QString fieldStyle;
};

#endif // EDITCREATEPAGE_H
