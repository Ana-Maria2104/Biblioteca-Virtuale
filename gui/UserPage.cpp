#include "UserPage.h"
#include "PageVisitor.h"
#include "../modello_logico/Libro.h"
#include "../modello_logico/Film.h"
#include "../modello_logico/Rivista.h"
#include "MainWindow.h"
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
#include <QListWidget>
#include <QTimer>
#include "filtervisitor.h"

const QString UserPage::fieldStyle = "background-color: rgb(175, 238, 238); color:rgb(0, 0, 0);";

UserPage::UserPage(QList<BibliotecaItem*> listaOggetti, QStackedWidget *stackedwidget, QWidget *parent)
    : QWidget(parent), lista(listaOggetti), stack(stackedwidget),
    filterButton(nullptr), filterDialog(nullptr) {

    initializeUI();
}

UserPage::~UserPage() {
    if(filterDialog) delete filterDialog;
}

void UserPage::initializeUI() {
    // Layout principale
    QVBoxLayout *userLayout = new QVBoxLayout(this);
    userLayout->setContentsMargins(15, 15, 15, 15);
    userLayout->setSpacing(20);

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
    connect(backButton, &QPushButton::clicked, this, &UserPage::goBack);

    // Pulsante Filtri
    filterButton = new QPushButton(QIcon(":/icons/filter_icon.png"), " Filtri");
    filterButton->setFixedSize(150, 50);
    filterButton->setToolTip("Filtra elementi");
    filterButton->setStyleSheet(R"(
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
    connect(filterButton, &QPushButton::clicked, this, &UserPage::showFilterDialog);

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
    connect(searchButton, &QPushButton::clicked, this, &UserPage::search);

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

    // Pulsante Ordini
    ordiniButton = new QPushButton(QIcon(":/icons/spesa_icon.png"), " Ordini");
    ordiniButton->setFixedSize(150, 50);
    ordiniButton->setToolTip("Visualizza i tuoi ordini");
    ordiniButton->setStyleSheet(R"(
        QPushButton {
            background-color: #e3f2fd;
            color: #0d47a1;
            font-weight: 600;
            font-size: 15px;
            border-radius: 12px;
            border: 1px solid #bbdefb;
            padding: 10px 18px;
        }
        QPushButton:hover {
            background-color: #bbdefb;
        }
        QPushButton:pressed {
            background-color: #90caf9;
        }
    )");
    connect(ordiniButton, &QPushButton::clicked, this, &UserPage::showOrdiniDialog);

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
    userLayout->addLayout(bottomLayout);

    // Aggiunta elementi alla top bar
    topBarLayout->addWidget(backButton);
    topBarLayout->addWidget(filterButton);
    topBarLayout->addWidget(ordiniButton);
    topBarLayout->addStretch();
    topBarLayout->addWidget(searchBar);
    topBarLayout->addWidget(searchButton);
    topBarLayout->addStretch();
    topBarLayout->addLayout(prestitiLayout);
    topBarLayout->addWidget(exitButton);
    userLayout->addWidget(topBarFrame);

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
    userLayout->addWidget(scrollArea);

    showAll();
}

void UserPage::showFilterDialog() {
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

void UserPage::close() {
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

void UserPage::goBack() {
    stack->setCurrentIndex(0);
}

void UserPage::search() {
    QString searchText = searchBar->text().trimmed().toLower();
    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "ATTENZIONE", "Inserisci un testo di ricerca!");
        return;
    }

    cleanLayout();
    int row = 0, col = 0;
    bool found = false;

    for (BibliotecaItem *obj : lista) {
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

void UserPage::cleanLayout() {
    QLayoutItem *item;
    while ((item = contentLayout->takeAt(0)) != nullptr) {
        if (QWidget *w = item->widget()) {
            w->deleteLater();
        }
        delete item;
    }
}

void UserPage::showAll() {
    cleanLayout();
    int row = 0, col = 0;
    for (BibliotecaItem *obj : lista) {
        riquadroOggetto(obj, row, col, 3);
    }
    if (isSearchActive) {
        backFromSearchButton->hide();
        isSearchActive = false;
    }
}

void UserPage::showOrdiniDialog() {
    if (prenotati.isEmpty()) {
        QMessageBox::information(this, "Ordini", "Non hai alcun oggetto prenotato.");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("I tuoi ordini");
    dialog.setMinimumSize(400, 300);
    dialog.setStyleSheet("QDialog { background-color: #f5f5f5; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(10);

    QLabel *titleLabel = new QLabel("Oggetti prenotati:");
    titleLabel->setStyleSheet("QLabel { font-weight: bold; font-size: 16px; color: #333; }");
    mainLayout->addWidget(titleLabel);

    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setStyleSheet("color: #ccc;");
    mainLayout->addWidget(separator);

    QVBoxLayout *itemsLayout = new QVBoxLayout();
    itemsLayout->setSpacing(10);

    for (BibliotecaItem* item : prenotati) {
        QFrame *itemFrame = new QFrame();
        itemFrame->setStyleSheet("QFrame { background-color: white; border-radius: 5px; padding: 10px; }");

        QHBoxLayout *itemLayout = new QHBoxLayout(itemFrame);
        itemLayout->setContentsMargins(10, 5, 10, 5);

        // Punto elenco
        QLabel *bullet = new QLabel("•");
        bullet->setStyleSheet("QLabel { font-size: 18px; color: #555; }");
        bullet->setFixedWidth(20);

        // Titolo oggetto
        QLabel *titleLabel = new QLabel(QString::fromStdString(item->getTitolo()));
        titleLabel->setStyleSheet("QLabel { font-size: 14px; color: #333; }");
        titleLabel->setWordWrap(true);

        // Pulsante restituisci
        QPushButton *restituisciBtn = new QPushButton("Restituisci");
        restituisciBtn->setFixedSize(100, 30);
        restituisciBtn->setStyleSheet(R"(
            QPushButton {
                background-color: #f8d7da;
                color: #721c24;
                border: 1px solid #f5c6cb;
                border-radius: 4px;
                padding: 5px;
            }
            QPushButton:hover {
                background-color: #f5c6cb;
            }
            QPushButton:pressed {
                background-color: #e0a5aa;
            }
        )");

        connect(restituisciBtn, &QPushButton::clicked, [this, item, &dialog]() {
            restituisciOggetto(item);
            prenotati.removeAll(item);
            dialog.close();
            showOrdiniDialog(); // Ricarica la lista aggiornata
        });

        itemLayout->addWidget(bullet);
        itemLayout->addWidget(titleLabel, 1);
        itemLayout->addWidget(restituisciBtn);
        itemsLayout->addWidget(itemFrame);
    }

    QWidget *scrollWidget = new QWidget();
    scrollWidget->setLayout(itemsLayout);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setStyleSheet("QScrollArea { border: none; }");

    mainLayout->addWidget(scrollArea, 1);

    // Pulsante chiudi
    QPushButton *closeButton = new QPushButton("Chiudi");
    closeButton->setFixedSize(100, 30);
    closeButton->setStyleSheet(R"(
        QPushButton {
            background-color: #d4edda;
            color: #155724;
            border: 1px solid #c3e6cb;
            border-radius: 4px;
            padding: 5px;
        }
        QPushButton:hover {
            background-color: #c3e6cb;
        }
        QPushButton:pressed {
            background-color: #b1dfbb;
        }
    )");
    connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    mainLayout->addWidget(closeButton, 0, Qt::AlignRight);

    dialog.exec();
}

void UserPage::prenotaOggetto(BibliotecaItem *obj) {
    if (!obj) return;

    QString styleCritical = "QLabel{font-weight: bold; font-size: 14px; color: #d9534f;}";
    QString styleWarning = "QLabel{font-weight: bold; font-size: 14px; color: #f0ad4e;}";
    QString styleSuccess = "QLabel{font-weight: bold; font-size: 14px; color: #5cb85c;}";

    // Controlla se l'oggetto è già stato prenotato
    if (prenotati.contains(obj)) {
        QMessageBox errorMsg(this);
        errorMsg.setWindowTitle("❌ Errore prenotazione");
        errorMsg.setText("<b>HAI GIÀ PRENOTATO QUESTO LIBRO!</b>");
        errorMsg.setInformativeText("Hai già prenotato una copia di questo oggetto.");
        errorMsg.setIconPixmap(QIcon(":/icons/attenzione_icon.png").pixmap(64, 64));
        errorMsg.setStyleSheet(styleCritical);
        errorMsg.exec();
        return;
    }

    int copieDisponibiliPrima = obj->getNumeroCopie() - obj->getNumeroPrestiti();

    if (obj->prenota()) {
        prenotati.append(obj);
        labelPrestiti->setText("Prestiti totali: " + QString::number(showTotPrestiti()));
        emit itemUpdated(obj);

        // Mostra prima il messaggio di successo
        QMessageBox successMsg(this);
        successMsg.setWindowTitle("✅ Prenotazione effettuata");
        successMsg.setText("<b>PRENOTAZIONE REGISTRATA!</b>");
        successMsg.setInformativeText("La copia è stata prenotata con successo.");
        successMsg.setIconPixmap(QIcon(":/icons/ok_icon.png").pixmap(64, 64));
        successMsg.setStyleSheet(styleSuccess);
        successMsg.exec();

        int copieDisponibiliDopo = obj->getNumeroCopie() - obj->getNumeroPrestiti();

        // Se necessario, mostra il messaggio di avviso dopo un breve ritardo
        if (copieDisponibiliPrima == 2 && copieDisponibiliDopo == 1) {
            QTimer::singleShot(300, this, [this, styleWarning]() {  // Add styleWarning to capture list
                QMessageBox warningMsg(this);
                warningMsg.setWindowTitle("⚠️ Attenzione - Ultima copia");
                warningMsg.setText("<b>ULTIMA COPIA DISPONIBILE!</b>");
                warningMsg.setInformativeText("Rimane solo 1 copia disponibile per il prestito.");
                warningMsg.setIconPixmap(QIcon(":/icons/attenzione_icon.png").pixmap(64, 64));
                warningMsg.setStyleSheet(styleWarning);
                warningMsg.exec();
            });
        }
        else if (copieDisponibiliDopo == 0) {
            QTimer::singleShot(300, this, [this, styleCritical]() {  // Add styleCritical to capture list
                QMessageBox criticalMsg(this);
                criticalMsg.setWindowTitle("❌ Esaurito");
                criticalMsg.setText("<b>OGGETTO ESAURITO!</b>");
                criticalMsg.setInformativeText("Tutte le copie sono ora in prestito.");
                criticalMsg.setIconPixmap(QIcon(":/icons/out_icon.png").pixmap(64, 64));
                criticalMsg.setStyleSheet(styleCritical);
                criticalMsg.exec();
            });
        }
    } else {
        QMessageBox errorMsg(this);
        errorMsg.setWindowTitle("❌ Prenotazione impossibile");
        errorMsg.setText("<b>NON DISPONIBILE!</b>");
        errorMsg.setInformativeText("Tutte le copie sono attualmente in prestito.");
        errorMsg.setIconPixmap(QIcon(":/icons/out_icon.png").pixmap(64, 64));
        errorMsg.setStyleSheet(styleCritical);
        errorMsg.exec();
    }
}

void UserPage::restituisciOggetto(BibliotecaItem *obj) {
    if (!obj) return;

    QString styleCritical = "QLabel{font-weight: bold; font-size: 14px; color: #d9534f;}";
    QString styleWarning = "QLabel{font-weight: bold; font-size: 14px; color: #f0ad4e;}";
    QString styleSuccess = "QLabel{font-weight: bold; font-size: 14px; color: #5cb85c;}";

    int copieDisponibiliPrima = obj->getNumeroCopie() - obj->getNumeroPrestiti();

    if (obj->getNumeroPrestiti() > 0) {
        obj->restituisci();
        prenotati.removeAll(obj);
        labelPrestiti->setText("Prestiti totali: " + QString::number(showTotPrestiti()));
        emit itemUpdated(obj);

        // Mostra prima il messaggio di successo
        QMessageBox successMsg(this);
        successMsg.setWindowTitle("✅ Restituzione completata");
        successMsg.setText("<b>RESTITUZIONE EFFETTUATA!</b>");
        successMsg.setInformativeText("La copia è stata correttamente restituita.");
        successMsg.setIconPixmap(QIcon(":/icons/ok_icon.png").pixmap(64, 64));
        successMsg.setStyleSheet(styleSuccess);
        successMsg.exec();

        int copieDisponibiliDopo = obj->getNumeroCopie() - obj->getNumeroPrestiti();

        // Se necessario, mostra il messaggio di avviso dopo un breve ritardo
        if (copieDisponibiliPrima == 0 && copieDisponibiliDopo == 1) {
            QTimer::singleShot(300, this, [this, styleWarning]() {  // Add styleWarning to capture list
                QMessageBox warningMsg(this);
                warningMsg.setWindowTitle("⚠️ Attenzione - Ultima copia");
                warningMsg.setText("<b>ULTIMA COPIA DISPONIBILE!</b>");
                warningMsg.setInformativeText("Rimane solo 1 copia disponibile per il prestito.");
                warningMsg.setIconPixmap(QIcon(":/icons/attenzione_icon.png").pixmap(64, 64));
                warningMsg.setStyleSheet(styleWarning);
                warningMsg.exec();
            });
        }
    } else {
        QMessageBox errorMsg(this);
        errorMsg.setWindowTitle("⚠️ Attenzione");
        errorMsg.setText("<b>NESSUN PRESTITO ATTIVO!</b>");
        errorMsg.setInformativeText("Non ci sono copie da restituire per questo oggetto.");
        errorMsg.setIconPixmap(QIcon(":/icons/attenzione_icon.png").pixmap(64, 64));
        errorMsg.setStyleSheet(styleCritical);
        errorMsg.exec();
    }
}
int UserPage::showTotPrestiti() const {
    int tot = 0;
    for (BibliotecaItem *obj : lista) {
        tot += obj->getNumeroPrestiti();
    }
    return tot;
}

void UserPage::applyFilters() {
    cleanLayout();

    // Determina quali filtri sono attivi
    bool filterAllCategories = allCategoryCheck->isChecked();
    bool filterAllLanguages = allLanguageCheck->isChecked();

    int row = 0, col = 0;
    bool found = false;

    for (BibliotecaItem *obj : lista) {
        bool matchesCategory = filterAllCategories;
        bool matchesLanguage = filterAllLanguages;

        // Filtro categoria
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

void UserPage::riquadroOggetto(BibliotecaItem *obj, int &row, int &col, int maxColumns) {
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

    QPushButton *prenotaButton = new QPushButton("Prenota");
    QPushButton *restituisciButton = new QPushButton("Restituisci");

    // Stili bottoni: bordo colorato, sfondo bianco
    prenotaButton->setStyleSheet(
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
    restituisciButton->setStyleSheet(
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

    connect(prenotaButton, &QPushButton::clicked, this, [this, obj]() { prenotaOggetto(obj); });
    connect(restituisciButton, &QPushButton::clicked, this, [this, obj]() { restituisciOggetto(obj); });

    buttonLayout->addWidget(prenotaButton);
    buttonLayout->addWidget(restituisciButton);
    frameLayout->addLayout(buttonLayout);

    contentLayout->addWidget(frame, row, col);
    if (++col >= maxColumns) { col = 0; row++; }
}
void UserPage::onBibliotecaAggiornata(const QList<BibliotecaItem*>& nuovaLista) {
    lista = nuovaLista;
    refreshUI();
}

void UserPage::refreshUI() {
    showAll();
    labelPrestiti->setText("Prestiti totali: " + QString::number(showTotPrestiti()));
}
