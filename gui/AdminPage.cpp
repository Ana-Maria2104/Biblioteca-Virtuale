#include "AdminPage.h"
#include "PageVisitor.h"
#include "MainWindow.h"
#include "../jsonHandler/Json.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QActionGroup>
#include <QFrame>
#include <QCheckBox>
#include <QGroupBox>

const QString AdminPage::fieldStyle = "background-color: rgb(175, 238, 238); color:rgb(0, 0, 0);";

AdminPage::AdminPage(QList<BibliotecaItem*> listaOggetti, QStackedWidget* stackedwidget, QWidget* parent)
    : QWidget(parent),
    backFromSearchButton(nullptr),
    exitSearchButton(nullptr),
    filterButton(nullptr),
    filterDialog(nullptr),
    stack(stackedwidget),
    searchBar(nullptr),
    labelPrestiti(nullptr),
    contentLayout(nullptr),
    contentWidget(nullptr),
    scrollArea(nullptr),
    lista(listaOggetti)
{
    initializeUI();
}
AdminPage::~AdminPage() {
    if(filterDialog) delete filterDialog;
}

void AdminPage::initializeUI() {
    // Layout principale
    QVBoxLayout *adminLayout = new QVBoxLayout(this);
    adminLayout->setContentsMargins(15, 15, 15, 15);
    adminLayout->setSpacing(20);

    // Contenitore per la barra superiore
    QFrame *topBarFrame = new QFrame();
    topBarFrame->setObjectName("topBarFrame");
    topBarFrame->setStyleSheet("QFrame#topBarFrame { background-color: rgba(255, 255, 255, 0.85); border-radius: 12px; }");

    QHBoxLayout *topBarLayout = new QHBoxLayout(topBarFrame);
    topBarLayout->setContentsMargins(15, 10, 15, 10);

    // Pulsante Torna Home
    QPushButton *backButton = new QPushButton(QIcon(":/icons/home_icon.png"), " Home");
    backButton->setFixedSize(150, 50);
    backButton->setToolTip("Torna alla Home");
    backButton->setStyleSheet(R"(
        QPushButton {
            background-color: #e8f5e9;
            color: #2e7d32;
            font-weight: 600;
            font-size: 15px;
            border-radius: 12px;
            border: 1px solid #c8e6c9;
            padding: 10px 18px;
        }
        QPushButton:hover {
            background-color: #c8e6c9;
        }
        QPushButton:pressed {
            background-color: #a5d6a7;
        }
    )");
    connect(backButton, &QPushButton::clicked, this, &AdminPage::goBack);

    // Pulsante Aggiungi
    QPushButton *createButton = new QPushButton(QIcon(":/icons/crea_icon.png"), " Aggiungi");
    createButton->setFixedSize(150, 50);
    createButton->setToolTip("Aggiungi nuovo elemento");
    createButton->setStyleSheet(R"(
        QPushButton {
            background-color: #f0f2f5;
            color: #2c3e50;
            font-weight: 600;
            font-size: 15px;
            border-radius: 12px;
            border: 1px solid #ccc;
            padding: 10px 18px;
        }
        QPushButton:hover {
            background-color: #e0e0e0;
        }
    )");
    connect(createButton, &QPushButton::clicked, this, &AdminPage::create);

    // Pulsante Filtri
    filterButton = new QPushButton(QIcon(":/icons/filter_icon.png"), " Filtri");
    filterButton->setFixedSize(150, 50);
    filterButton->setToolTip("Filtra elementi");
    filterButton->setStyleSheet(createButton->styleSheet());
    connect(filterButton, &QPushButton::clicked, this, &AdminPage::showFilterDialog);

    // Barra di ricerca
    searchBar = new QLineEdit();
    searchBar->setPlaceholderText(" Cerca...");
    searchBar->setFixedHeight(50);
    searchBar->setMinimumWidth(500);
    searchBar->setStyleSheet(R"(
        QLineEdit {
            background-color: #ffffff;
            border: 1px solid #d0d0d0;
            border-radius: 12px;
            padding: 0 16px 0 44px;
            font-size: 15px;
            color: #2c3e50;
        }
        QLineEdit:hover {
            border-color: #aaa;
        }
    )");
    searchBar->addAction(QIcon(":/icons/lente_icon.png"), QLineEdit::LeadingPosition);

    // Pulsante ricerca
    QPushButton *searchButton = new QPushButton("Cerca");
    searchButton->setFixedSize(120, 50);
    searchButton->setStyleSheet(R"(
        QPushButton {
            background-color: #17a2b8;
            color: white;
            font-weight: bold;
            font-size: 15px;
            border-radius: 12px;
            border: none;
            padding: 10px 20px;
        }
        QPushButton:hover {
            background-color: #138496;
        }
        QPushButton:pressed {
            background-color: #117a8b;
        }
    )");
    connect(searchButton, &QPushButton::clicked, this, &AdminPage::search);

    // Pulsante Torna indietro dalla ricerca
    backFromSearchButton = new QPushButton(QIcon(":/icons/back_icon.png"), " Torna indietro");
    backFromSearchButton->setFixedSize(180, 50);
    backFromSearchButton->setToolTip("Torna alla visualizzazione completa");
    backFromSearchButton->setStyleSheet(R"(
        QPushButton {
            background-color: #d6e0f0;
            color: #1c3d5a;
            font-weight: 600;
            font-size: 15px;
            border-radius: 12px;
            border: 1px solid #b0c4de;
            padding: 10px 18px;
        }
        QPushButton:hover {
            background-color: #c3d9ec;
        }
        QPushButton:pressed {
            background-color: #a7c0dc;
        }
    )");
    connect(backFromSearchButton, &QPushButton::clicked, this, [this]() {
        showAll();
        backFromSearchButton->hide();
        isSearchActive = false;
    });
    backFromSearchButton->hide();
    isSearchActive = false;

    // Pulsante Esci
    QPushButton *exitButton = new QPushButton(QIcon(":/icons/exit_icon.png"), " Esci");
    exitButton->setFixedSize(120, 50);
    exitButton->setToolTip("Esci dall'applicazione");
    exitButton->setStyleSheet(R"(
        QPushButton {
            background-color: #ffe6e6;
            color: #c0392b;
            font-weight: bold;
            font-size: 15px;
            border-radius: 12px;
            border: 1px solid #f5b7b1;
            padding: 10px 18px;
        }
        QPushButton:hover {
            background-color: #f5b7b1;
        }
        QPushButton:pressed {
            background-color: #ec7063;
        }
    )");
    connect(exitButton, &QPushButton::clicked, this, [this]() {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Conferma uscita");
        msgBox.setText("Sei sicuro di voler uscire dall'applicazione?");
        msgBox.setIconPixmap(QIcon(":/icons/exit_icon.png").pixmap(48, 48));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        if (msgBox.exec() == QMessageBox::Yes) {
            QApplication::quit();
        }
    });

    // Etichetta prestiti
    QLabel *iconLabel = new QLabel();
    iconLabel->setPixmap(QIcon(":/icons/book_icon.png").pixmap(24, 24));
    labelPrestiti = new QLabel("Prestiti totali: " + QString::number(showTotPrestiti()));
    labelPrestiti->setAlignment(Qt::AlignCenter);
    labelPrestiti->setStyleSheet(R"(
        QLabel {
            font-size: 15px;
            font-weight: 600;
            color: #2c3e50;
            background-color: #f8f9fa;
            padding: 12px 20px;
            border-radius: 12px;
            border: 1px solid #dcdcdc;
        }
    )");
    labelPrestiti->setFixedHeight(50);

    QHBoxLayout *prestitiLayout = new QHBoxLayout();
    prestitiLayout->addWidget(iconLabel);
    prestitiLayout->addWidget(labelPrestiti);
    prestitiLayout->setSpacing(10);
    prestitiLayout->setContentsMargins(0, 0, 0, 0);

    // Layout bottom (torna indietro)
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addStretch();
    bottomLayout->addWidget(backFromSearchButton);
    adminLayout->addLayout(bottomLayout);

    // Aggiunta elementi alla top bar
    topBarLayout->addWidget(backButton);
    topBarLayout->addWidget(createButton);
    topBarLayout->addWidget(filterButton);
    topBarLayout->addStretch();
    topBarLayout->addWidget(searchBar);
    topBarLayout->addWidget(searchButton);
    topBarLayout->addStretch();
    topBarLayout->addLayout(prestitiLayout);
    topBarLayout->addWidget(exitButton);
    adminLayout->addWidget(topBarFrame);

    // Area scroll
    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet(R"(
        QScrollArea { border: none; }
        QScrollBar:vertical {
            background: #f1f1f1;
            width: 10px;
            margin: 0px;
        }
        QScrollBar::handle:vertical {
            background: #ced4da;
            border-radius: 5px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0;
        }
    )");

    contentWidget = new QWidget();
    contentLayout = new QGridLayout(contentWidget);
    contentLayout->setSpacing(25);
    contentLayout->setContentsMargins(20, 20, 20, 20);
    scrollArea->setWidget(contentWidget);
    adminLayout->addWidget(scrollArea);

    showAll();
}
void AdminPage::showFilterDialog() {
    if (!filterDialog) {
        filterDialog = new QDialog(this);
        filterDialog->setWindowTitle("Filtri");
        filterDialog->setWindowModality(Qt::ApplicationModal);
        filterDialog->setFixedSize(400, 500);

        QVBoxLayout *dialogLayout = new QVBoxLayout(filterDialog);

        // Categorie
        QGroupBox *categoryGroup = new QGroupBox("Categorie");
        QVBoxLayout *categoryLayout = new QVBoxLayout;

        allCategoryCheck = new QCheckBox("Tutte le categorie");
        libroCheck = new QCheckBox("Libro");
        rivistaCheck = new QCheckBox("Rivista");
        filmCheck = new QCheckBox("Film");

        // Imposta stato iniziale
        allCategoryCheck->setChecked(true);
        libroCheck->setChecked(false);
        rivistaCheck->setChecked(false);
        filmCheck->setChecked(false);
        libroCheck->setEnabled(false);
        rivistaCheck->setEnabled(false);
        filmCheck->setEnabled(false);

        connect(allCategoryCheck, &QCheckBox::toggled, this, [this](bool checked) {
            if (checked) {
                libroCheck->setChecked(false);
                rivistaCheck->setChecked(false);
                filmCheck->setChecked(false);
            }
            libroCheck->setEnabled(!checked);
            rivistaCheck->setEnabled(!checked);
            filmCheck->setEnabled(!checked);
        });
        categoryLayout->addWidget(allCategoryCheck);
        categoryLayout->addWidget(libroCheck);
        categoryLayout->addWidget(rivistaCheck);
        categoryLayout->addWidget(filmCheck);
        categoryGroup->setLayout(categoryLayout);

        // Lingue
        QGroupBox *languageGroup = new QGroupBox("Lingue");
        QVBoxLayout *languageLayout = new QVBoxLayout;

        allLanguageCheck = new QCheckBox("Tutte le lingue");
        italianoCheck = new QCheckBox("Italiano");
        ingleseCheck = new QCheckBox("Inglese");
        spagnoloCheck = new QCheckBox("Spagnolo");

        // Imposta stato iniziale
        allLanguageCheck->setChecked(true);
        italianoCheck->setChecked(false);
        ingleseCheck->setChecked(false);
        spagnoloCheck->setChecked(false);
        italianoCheck->setEnabled(false);
        ingleseCheck->setEnabled(false);
        spagnoloCheck->setEnabled(false);

        connect(allLanguageCheck, &QCheckBox::toggled, this, [this](bool checked) {
            if (checked) {
                italianoCheck->setChecked(false);
                ingleseCheck->setChecked(false);
                spagnoloCheck->setChecked(false);
            }
            italianoCheck->setEnabled(!checked);
            ingleseCheck->setEnabled(!checked);
            spagnoloCheck->setEnabled(!checked);
        });
        languageLayout->addWidget(allLanguageCheck);
        languageLayout->addWidget(italianoCheck);
        languageLayout->addWidget(ingleseCheck);
        languageLayout->addWidget(spagnoloCheck);
        languageGroup->setLayout(languageLayout);

        // Pulsanti
        QHBoxLayout *buttonLayout = new QHBoxLayout;
        QPushButton *applyButton = new QPushButton("Applica filtri");
        QPushButton *clearButton = new QPushButton("Rimuovi filtri");
        QPushButton *cancelButton = new QPushButton("Annulla");

        applyButton->setStyleSheet("background-color: #4CAF50; color: white;");
        clearButton->setStyleSheet("background-color: #f39c12; color: white;");
        cancelButton->setStyleSheet("background-color: #e74c3c; color: white;");

        connect(applyButton, &QPushButton::clicked, this, [this]() {
            filterDialog->accept();
            applyFilters();
        });
        connect(clearButton, &QPushButton::clicked, this, [this]() {
            allCategoryCheck->setChecked(true);
            allLanguageCheck->setChecked(true);
            applyFilters();
        });
        connect(cancelButton, &QPushButton::clicked, filterDialog, &QDialog::reject);

        buttonLayout->addWidget(applyButton);
        buttonLayout->addWidget(clearButton);
        buttonLayout->addWidget(cancelButton);

        dialogLayout->addWidget(categoryGroup);
        dialogLayout->addWidget(languageGroup);
        dialogLayout->addStretch();
        dialogLayout->addLayout(buttonLayout);
    }

    filterDialog->exec();
}

void AdminPage::close() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Conferma uscita");
    msgBox.setText("Sei sicuro di voler uscire dall'applicazione?");
    msgBox.setIconPixmap(QIcon(":/icons/exit_icon.png").pixmap(48, 48));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if (msgBox.exec() == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void AdminPage::goBack() {
    stack->setCurrentIndex(0);
}

void AdminPage::search() {
    QString searchText = searchBar->text().trimmed().toLower();
    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "ATTENZIONE", "Inserisci un testo di ricerca!");
        return;
    }

    cleanLayout();
    int row = 0, col = 0;
    bool found = false;

    for (int i = 0; i < lista.size(); ++i) {
        BibliotecaItem* obj = lista.at(i);
        QString titolo = QString::fromStdString(obj->getTitolo()).toLower();
        if (titolo.contains(searchText)) {
            found = true;
            riquadroOggetto(obj, row, col, 3);
        }
    }
    if (found) {
        backFromSearchButton->show();
        isSearchActive = true;
    } else {
        backFromSearchButton->hide();
        isSearchActive = false;
        QMessageBox::information(this, "Nessun risultato", "Nessun oggetto trovato con il titolo inserito.");
        showAll();
    }
}
void AdminPage::create() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Caricamento");
    msgBox.setText("Caricamento della pagina in corso.\nAttendere il completamento per aggiungere contenuti...");
    msgBox.setIconPixmap(QIcon(":/icons/load_icon.png").pixmap(48, 48));
    QPushButton *okButton = msgBox.addButton("OK", QMessageBox::AcceptRole);
    okButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #4CAF50;"
        "   color: white;"
        "   padding: 8px 16px;"
        "   border-radius: 4px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #45a049;"
        "}"
        );
    msgBox.exec();

    stack->setCurrentIndex(3);
    emit createItem();
}

void AdminPage::cleanLayout() {
    QLayoutItem *item;
    while ((item = contentLayout->takeAt(0)) != nullptr) {
        if (QWidget *w = item->widget()) {
            w->deleteLater();
        }
        delete item;
    }
}

void AdminPage::showAll() {
    cleanLayout();
    int row = 0, col = 0;
    for (int i = 0; i < lista.size(); ++i) {
        BibliotecaItem* obj = lista.at(i);
        riquadroOggetto(obj, row, col, 3);
    }
    if (isSearchActive) {
        backFromSearchButton->hide();
        isSearchActive = false;
    }
}

void AdminPage::prenotaOggetto(BibliotecaItem *obj) {
    if (!obj) return;

    QString styleCritical = "QLabel{font-weight: bold; font-size: 14px; color: #d9534f;}";
    QString styleWarning = "QLabel{font-weight: bold; font-size: 14px; color: #f0ad4e;}";
    QString styleSuccess = "QLabel{font-weight: bold; font-size: 14px; color: #5cb85c;}";

    int copieDisponibiliPrima = obj->getNumeroCopie() - obj->getNumeroPrestiti();

    if (obj->prenota()) {
        labelPrestiti->setText("Prestiti totali: " + QString::number(showTotPrestiti()));
        emit itemUpdated(obj);

        QMessageBox successMsg;
        successMsg.setWindowTitle("✅ Prenotazione effettuata");
        successMsg.setText("<b>PRENOTAZIONE REGISTRATA!</b>");
        successMsg.setInformativeText("La copia è stata prenotata con successo.");
        successMsg.setIconPixmap(QIcon(":/icons/ok_icon.png").pixmap(64, 64));
        successMsg.setStyleSheet(styleSuccess);
        successMsg.exec();

        int copieDisponibiliDopo = obj->getNumeroCopie() - obj->getNumeroPrestiti();

        // Mostra avviso se siamo passati da 2 a 1 copia disponibile
        if (copieDisponibiliPrima == 2 && copieDisponibiliDopo == 1) {
            QMessageBox warningMsg;
            warningMsg.setWindowTitle("⚠️ Attenzione - Ultima copia");
            warningMsg.setText("<b>ULTIMA COPIA DISPONIBILE!</b>");
            warningMsg.setInformativeText("Rimane solo 1 copia disponibile per il prestito.");
            warningMsg.setIconPixmap(QIcon(":/icons/attenzione_icon.png").pixmap(64, 64));
            warningMsg.setStyleSheet(styleWarning);
            warningMsg.exec();
        }
        // Mostra avviso se siamo passati a 0 copie disponibili
        else if (copieDisponibiliDopo == 0) {
            QMessageBox criticalMsg;
            criticalMsg.setWindowTitle("❌ Esaurito");
            criticalMsg.setText("<b>OGGETTO ESAURITO!</b>");
            criticalMsg.setInformativeText("Tutte le copie sono ora in prestito.");
            criticalMsg.setIconPixmap(QIcon(":/icons/out_icon.png").pixmap(64, 64));
            criticalMsg.setStyleSheet(styleCritical);
            criticalMsg.exec();
        }
    } else {
        QMessageBox errorMsg;
        errorMsg.setWindowTitle("❌ Prenotazione impossibile");
        errorMsg.setText("<b>NON DISPONIBILE!</b>");
        errorMsg.setInformativeText("Tutte le copie sono attualmente in prestito.");
        errorMsg.setIconPixmap(QIcon(":/icons/out_icon.png").pixmap(64, 64));
        errorMsg.setStyleSheet(styleCritical);
        errorMsg.exec();
    }
}

void AdminPage::restituisciOggetto(BibliotecaItem *obj) {
    if (!obj) return;

    QString styleCritical = "QLabel{font-weight: bold; font-size: 14px; color: #d9534f;}";
    QString styleWarning = "QLabel{font-weight: bold; font-size: 14px; color: #f0ad4e;}";
    QString styleSuccess = "QLabel{font-weight: bold; font-size: 14px; color: #5cb85c;}";

    int copieDisponibiliPrima = obj->getNumeroCopie() - obj->getNumeroPrestiti();

    if (obj->getNumeroPrestiti() > 0) {
        obj->restituisci();
        labelPrestiti->setText("Prestiti totali: " + QString::number(showTotPrestiti()));
        emit itemUpdated(obj);

        QMessageBox successMsg;
        successMsg.setWindowTitle("✅ Restituzione completata");
        successMsg.setText("<b>RESTITUZIONE EFFETTUATA!</b>");
        successMsg.setInformativeText("La copia è stata correttamente restituita.");
        successMsg.setIconPixmap(QIcon(":/icons/ok_icon.png").pixmap(64, 64));
        successMsg.setStyleSheet(styleSuccess);
        successMsg.exec();

        int copieDisponibiliDopo = obj->getNumeroCopie() - obj->getNumeroPrestiti();

        // Mostra avviso se siamo passati da 0 a 1 copia disponibile
        if (copieDisponibiliPrima == 0 && copieDisponibiliDopo == 1) {
            QMessageBox warningMsg;
            warningMsg.setWindowTitle("⚠️ Attenzione - Ultima copia");
            warningMsg.setText("<b>ULTIMA COPIA DISPONIBILE!</b>");
            warningMsg.setInformativeText("Rimane solo 1 copia disponibile per il prestito.");
            warningMsg.setIconPixmap(QIcon(":/icons/attenzione_icon.png").pixmap(64, 64));
            warningMsg.setStyleSheet(styleWarning);
            warningMsg.exec();
        }
    } else {
        QMessageBox errorMsg;
        errorMsg.setWindowTitle("⚠️ Attenzione");
        errorMsg.setText("<b>NESSUN PRESTITO ATTIVO!</b>");
        errorMsg.setInformativeText("Non ci sono copie da restituire per questo oggetto.");
        errorMsg.setIconPixmap(QIcon(":/icons/attenzione_icon.png").pixmap(64, 64));
        errorMsg.setStyleSheet(styleCritical);
        errorMsg.exec();
    }
}

int AdminPage::showTotPrestiti() const {
    int tot = 0;
    for (BibliotecaItem *obj : lista) {
        tot += obj->getNumeroPrestiti();
    }
    return tot;
}

void AdminPage::applyFilters() {
    cleanLayout();

    // Determina quali filtri sono attivi
    bool filterAllCategories = allCategoryCheck->isChecked();
    bool filterAllLanguages = allLanguageCheck->isChecked();

    int row = 0, col = 0;
    bool found = false;

    for (int i = 0; i < lista.size(); ++i) {
        BibliotecaItem* obj = lista.at(i);
        bool matchesCategory = filterAllCategories;
        bool matchesLanguage = filterAllLanguages;

        // Filtro categoria con Visitor
        if (!filterAllCategories) {
            FilterVisitor visitor;
            obj->accept(&visitor);  // Rileva il tipo tramite il Visitor

            matchesCategory = false;
            if (libroCheck->isChecked() && visitor.isLibro) matchesCategory = true;
            if (rivistaCheck->isChecked() && visitor.isRivista) matchesCategory = true;
            if (filmCheck->isChecked() && visitor.isFilm) matchesCategory = true;
        }


        // Filtro lingua
        if (!filterAllLanguages) {
            matchesLanguage = false;
            QString objLanguage = QString::fromStdString(obj->getLingua()).toLower();
            if (italianoCheck->isChecked() && objLanguage == "italiano") matchesLanguage = true;
            if (ingleseCheck->isChecked() && objLanguage == "inglese") matchesLanguage = true;
            if (spagnoloCheck->isChecked() && objLanguage == "spagnolo") matchesLanguage = true;
        }

        if (matchesCategory && matchesLanguage) {
            found = true;
            riquadroOggetto(obj, row, col, 3);
        }
    }

    if (!found) {
        QMessageBox::information(this, "Filtri", "Nessun elemento corrisponde ai filtri selezionati");
    }
}
void AdminPage::riquadroOggetto(BibliotecaItem *obj, int &row, int &col, int maxColumns) {
    PageVisitor visitor;
    obj->accept(&visitor);

    QFrame *frame = new QFrame();
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Raised);
    frame->setMinimumSize(350, 450);
    frame->setMaximumSize(380, 480);
    frame->setStyleSheet("background-color: rgb(240, 230, 245); border-radius: 10px;");

    QVBoxLayout *frameLayout = new QVBoxLayout(frame);
    frameLayout->setContentsMargins(10, 10, 10, 10);

    // Widget scrollabile
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(visitor.getObjectWidget());
    scrollArea->setStyleSheet(
        "QScrollArea {"
        "    border: none;"
        "}"
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: #f0f0f0;"
        "    width: 8px;"
        "    margin: 0px 0px 0px 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #a0a0a0;"
        "    min-height: 25px;"
        "    border-radius: 4px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    height: 0px;"
        "    background: none;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: none;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "    background: #808080;"
        "}"
        "QScrollBar::handle:vertical:pressed {"
        "    background: #606060;"
        "}"
        );
    frameLayout->addWidget(scrollArea);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(5);

    QPushButton *buttons[] = {
        new QPushButton("Prenota"),
        new QPushButton("Restituisci"),
        new QPushButton("Modifica"),
        new QPushButton("Elimina")
    };

    // Stili bottoni: bordo colorato, sfondo bianco
    buttons[0]->setStyleSheet(
        "QPushButton {"
        "    background-color: white;"
        "    color: #333;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    border: 2px solid #A8E6CF;"
        "}"
        "QPushButton:hover { background-color: #F0F0F0; }"
        "QPushButton:pressed { background-color: #E0E0E0; }"
        );
    buttons[1]->setStyleSheet(
        "QPushButton {"
        "    background-color: white;"
        "    color: #333;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    border: 2px solid #FFD3B6;"
        "}"
        "QPushButton:hover { background-color: #F0F0F0; }"
        "QPushButton:pressed { background-color: #E0E0E0; }"
        );
    buttons[2]->setStyleSheet(
        "QPushButton {"
        "    background-color: white;"
        "    color: #333;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    border: 2px solid #DCE2F0;"
        "}"
        "QPushButton:hover { background-color: #F0F0F0; }"
        "QPushButton:pressed { background-color: #E0E0E0; }"
        );
    buttons[3]->setStyleSheet(
        "QPushButton {"
        "    background-color: white;"
        "    color: #333;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    font-weight: bold;"
        "    border: 2px solid #FFAAA5;"
        "}"
        "QPushButton:hover { background-color: #F0F0F0; }"
        "QPushButton:pressed { background-color: #E0E0E0; }"
        );

    connect(buttons[0], &QPushButton::clicked, this, [this, obj]() { prenotaOggetto(obj); });
    connect(buttons[1], &QPushButton::clicked, this, [this, obj]() { restituisciOggetto(obj); });
    connect(buttons[2], &QPushButton::clicked, this, [this, obj]() { modificaOggetto(obj); });
    connect(buttons[3], &QPushButton::clicked, this, [this, obj]() { eliminaOggetto(obj); });

    for (auto btn : buttons) {
        btn->setCursor(Qt::PointingHandCursor);
        buttonLayout->addWidget(btn);
    }
    frameLayout->addLayout(buttonLayout);

    contentLayout->addWidget(frame, row, col);
    if (++col >= maxColumns) { col = 0; row++; }
}

void AdminPage::modificaOggetto(BibliotecaItem *obj) {
    if (!obj) return;
    stack->setCurrentIndex(3);
    emit modifyItem(obj);
}




void AdminPage::eliminaOggetto(BibliotecaItem *obj) {
    if (!obj) return;

    QMessageBox msgBox;
    msgBox.setWindowTitle("Conferma eliminazione");
    msgBox.setText("Sei sicuro di voler eliminare '" +
                   QString::fromStdString(obj->getTitolo()) + "'?");
    msgBox.setIconPixmap(QIcon(":/icons/attenzione_icon.png").pixmap(48, 48));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if (msgBox.exec() == QMessageBox::Yes) {
        emit itemRemoved(obj);
        labelPrestiti->setText("Prestiti totali: " + QString::number(showTotPrestiti()));
        cleanLayout();
        showAll();

        QMessageBox successMsg;
        successMsg.setWindowTitle("Eliminazione");
        successMsg.setText("Oggetto eliminato con successo!");
        successMsg.setIconPixmap(QIcon(":/icons/ok_icon.png").pixmap(48, 48));
        successMsg.setStandardButtons(QMessageBox::Ok);
        successMsg.exec();
    }
}

void AdminPage::onBibliotecaAggiornata(const QList<BibliotecaItem*>& nuovaLista) {
    lista = nuovaLista;
    refreshUI();
}

void AdminPage::refreshUI() {
    showAll();
    labelPrestiti->setText("Prestiti totali: " + QString::number(showTotPrestiti()));
}

