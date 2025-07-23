#include "EditCreatePage.h"
#include <QMessageBox>
#include <QDate>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QScrollArea>
#include <QDir>
#include <QCoreApplication>
#include <QFileDialog>
#include "EditCreatePage.h"

QString checkBoxStyle = R"(
    QCheckBox {
        font-size: 15px;
        font-weight: bold;
        color: #495057;
        spacing: 8px;
    }
    QCheckBox::indicator {
        width: 20px;
        height: 20px;
    }
QCheckBox::indicator:checked {
        background-color: #4CAF50;
        border: 1px solid #388E3C;
        image: url(:/icons/exit_icon.png);  /* usa la tua icona qui */
    }
    QCheckBox::indicator:unchecked {
        background-color: #FFFFFF;
        border: 1px solid #CED4DA;
        image: none;
    }
)";

const QString EditCreatePage::fieldStyle = R"(
    QLineEdit, QSpinBox, QComboBox, QTextEdit {
        background-color: #FFFFFF;
        color: #212529;
        font-size: 15px;
        border: 1px solid #CED4DA;
        border-radius: 6px;
        padding: 8px;
    }
    QLabel {
        font-size: 15px;
        font-weight: bold;
        color: #495057;
    }
    QCheckBox {
        font-size: 15px;
        color: #495057;
        spacing: 8px;
    }
    QCheckBox::indicator {
        width: 18px;
        height: 18px;
    }
    QGroupBox {
        font-size: 15px;
        font-weight: bold;
        color: #495057;
        border: 1px solid #CED4DA;
        border-radius: 6px;
        margin-top: 10px;
    }
    QGroupBox::title {
        subcontrol-origin: margin;
        left: 10px;
        padding: 0 3px;
    }
    QListWidget {
        background-color: #FFFFFF;
        border: 1px solid #CED4DA;
        border-radius: 6px;
        font-size: 14px;
    }
)";
QString dialogStyle = R"(
    * {
        font-size: 16px;
        font-weight: bold;
        color: #555555;
    }
    QLabel {
        padding: 6px;
    }
    QLineEdit {
        font-size: 15px;
        padding: 6px;
        border: 1px solid #CED4DA;
        border-radius: 6px;
    }
    QPushButton {
        padding: 6px 12px;
        border-radius: 8px;
        background-color: #E3F2FD;
        color: #333;
        font-weight: bold;
        border: 1px solid #90CAF9;
    }
    QPushButton:hover {
        background-color: #BBDEFB;
    }
)";
QLabel* createStyledLabel(const QString& text) {
    QLabel* label = new QLabel(text);
    label->setStyleSheet("font-size: 18px; font-weight: bold; color: #495057;");
    return label;
}


EditCreatePage::EditCreatePage(QStackedWidget* stackedWidget, QWidget* adminPageWidget, QWidget* parent)
    : QWidget(parent), stack(stackedWidget), adminPage(adminPageWidget), currentItem(nullptr) {

    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 10, 20, 20);
    mainLayout->setSpacing(5);

    // --- BOTTONE TORNA INDIETRO E SALVA --- (sempre visibili in alto)
    QHBoxLayout* topButtonLayout = new QHBoxLayout();
    topButtonLayout->setContentsMargins(0, 0, 0, 5);
    topButtonLayout->setSpacing(10);

    backButton = new QPushButton("Torna indietro");
    backButton->setIcon(QIcon(":/icons/back_icon.png"));
    backButton->setIconSize(QSize(24, 24));

    saveButton = new QPushButton("Salva");
    saveButton->setIcon(QIcon(":/icons/save_icon.png"));
    saveButton->setIconSize(QSize(24, 24));
    saveButton->setEnabled(false);

    buttonStyle = R"(
        QPushButton {
            background-color: #F8F9FA;
            color: #495057;
            font-size: 16px;
            font-weight: bold;
            border: 2px solid #DEE2E6;
            border-radius: 8px;
            padding: 8px 16px;
        }
        QPushButton:hover {
            background-color: #E9ECEF;
            border-color: #CED4DA;
        }
        QPushButton:pressed {
            background-color: #DEE2E6;
        }
    )";

    backButton->setStyleSheet(buttonStyle);
    saveButton->setStyleSheet(buttonStyle);

    topButtonLayout->addWidget(backButton);
    topButtonLayout->addWidget(saveButton);
    topButtonLayout->addStretch();

    mainLayout->addLayout(topButtonLayout);

    // --- CONTENUTO DINAMICO ---
    contentStack = new QStackedWidget();

    // Pagina di scelta tipo
    QWidget* choicePage = new QWidget();
    QVBoxLayout* choiceLayout = new QVBoxLayout(choicePage);
    choiceLayout->setContentsMargins(0, 0, 0, 0);
    choiceLayout->setSpacing(30);

    libroButton = new QPushButton("  Libro");
    filmButton = new QPushButton("  Film");
    rivistaButton = new QPushButton("  Rivista");

    libroButton->setIcon(QIcon(":/icons/libro_icon.png"));
    filmButton->setIcon(QIcon(":/icons/film_icon.png"));
    rivistaButton->setIcon(QIcon(":/icons/rivista_icon.png"));

    QSize iconSize(60, 60);
    libroButton->setIconSize(iconSize);
    filmButton->setIconSize(iconSize);
    rivistaButton->setIconSize(iconSize);

    QString commonStyle = R"(
        QPushButton {
            color: black;
            font-size: 28px;
            font-weight: bold;
            border-radius: 20px;
            padding: 20px 40px;
            text-align: left;
        }
    )";

    libroButton->setStyleSheet(commonStyle + R"(
        QPushButton { background-color: #ADD8E6; }
        QPushButton:hover { background-color: #9AC7DD; }
    )");
    filmButton->setStyleSheet(commonStyle + R"(
        QPushButton { background-color: #FADADD; }
        QPushButton:hover { background-color: #F4C5CC; }
    )");
    rivistaButton->setStyleSheet(commonStyle + R"(
        QPushButton { background-color: #B2F2BB; }
        QPushButton:hover { background-color: #A0E2A8; }
    )");

    libroButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    filmButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    rivistaButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    libroButton->setFixedHeight(160);
    filmButton->setFixedHeight(160);
    rivistaButton->setFixedHeight(160);

    QHBoxLayout* centerButtonsLayout = new QHBoxLayout();
    centerButtonsLayout->setSpacing(30);
    centerButtonsLayout->setAlignment(Qt::AlignCenter);
    centerButtonsLayout->addWidget(libroButton);
    centerButtonsLayout->addWidget(filmButton);
    centerButtonsLayout->addWidget(rivistaButton);

    QVBoxLayout* centerVerticalLayout = new QVBoxLayout();
    centerVerticalLayout->addStretch();
    centerVerticalLayout->addLayout(centerButtonsLayout);
    centerVerticalLayout->addStretch();

    choiceLayout->addLayout(centerVerticalLayout);

    // Pagina del form
    QWidget* formPage = new QWidget();
    QVBoxLayout* formPageLayout = new QVBoxLayout(formPage);
    formPageLayout->setContentsMargins(0, 0, 0, 0);
    formPageLayout->setSpacing(0);

    formLayout = new QFormLayout();
    formLayout->setSpacing(8);
    formLayout->setContentsMargins(0, 0, 0, 0);

    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget* scrollContent = new QWidget();
    scrollContent->setLayout(formLayout);
    scrollArea->setWidget(scrollContent);

    formPageLayout->addWidget(scrollArea);

    // Aggiungi le pagine allo stack
    contentStack->addWidget(choicePage);
    contentStack->addWidget(formPage);

    mainLayout->addWidget(contentStack, 1); // Il fattore di stretch 1 fa occupare tutto lo spazio rimanente

    // Connessioni
    connect(backButton, &QPushButton::clicked, this, &EditCreatePage::goBack);
    connect(saveButton, &QPushButton::clicked, this, &EditCreatePage::saveItem);

    connect(libroButton, &QPushButton::clicked, this, [this]() {
        currentType = "Libro";
        saveButton->setEnabled(true);
        cleanLayout();
        setupCommonFields();
        setupBookFields();
        contentStack->setCurrentIndex(1); // Mostra il form
    });

    connect(filmButton, &QPushButton::clicked, this, [this]() {
        currentType = "Film";
        saveButton->setEnabled(true);
        cleanLayout();
        setupCommonFields();
        setupFilmFields();
        contentStack->setCurrentIndex(1); // Mostra il form
    });

    connect(rivistaButton, &QPushButton::clicked, this, [this]() {
        currentType = "Rivista";
        saveButton->setEnabled(true);
        cleanLayout();
        setupCommonFields();
        setupRivistaFields();
        contentStack->setCurrentIndex(1); // Mostra il form
    });
}

void EditCreatePage::setupForCreation() {
    currentMode = Create;
    currentItem = nullptr;
    saveButton->setEnabled(false);
    contentStack->setCurrentIndex(0); // Mostra la scelta del tipo
    cleanLayout();
}

void EditCreatePage::setupForEditing(BibliotecaItem* item) {
    currentMode = Edit;
    currentItem = item;
    saveButton->setEnabled(true);
    cleanLayout();
    setupCommonFields();
    item->accept(this);
    contentStack->setCurrentIndex(1); // Mostra il form
}

void EditCreatePage::goBack() {
    if (currentMode == Edit) {
        // Siamo in modifica: torna alla pagina admin
        if (adminPage) {
            int index = stack->indexOf(adminPage);
            if (index != -1)
                stack->setCurrentIndex(index);
        }
    } else if (currentMode == Create) {
        // Siamo in creazione: se siamo nel form, torna al menu di scelta
        if (contentStack->currentIndex() == 1) { // 1 è l'indice del form
            cleanLayout();
            contentStack->setCurrentIndex(0); // 0 è l'indice del menu scelta
            saveButton->setEnabled(false);
        } else {
            // Siamo già nel menu di scelta: torna ad AdminPage
            if (adminPage) {
                int index = stack->indexOf(adminPage);
                if (index != -1)
                    stack->setCurrentIndex(index);
            }
        }
    }
}

void EditCreatePage::saveItem() {
    BibliotecaItem* item = nullptr;

    QString styleSuccess = "QLabel{font-weight: bold; font-size: 14px; color: #5cb85c;}";

    if (currentMode == Create) {
        item = createNewItem();
        if (item) {
            emit itemCreated(item);

            // Mostra messaggio successo
            QMessageBox successMsg(this);
            successMsg.setWindowTitle("✅ Oggetto creato");
            successMsg.setText("<b>OGGETTO CREATO CON SUCCESSO!</b>");
            successMsg.setIconPixmap(QPixmap(":/icons/ok_icon.png").scaled(48, 48));
            successMsg.setStyleSheet(styleSuccess);
            successMsg.exec();

            stack->setCurrentWidget(adminPage);  // torna alla pagina principale
        }
    } else if (currentMode == Edit) {
        if (aggiornaFields(currentItem)) {
            emit itemUpdated(currentItem);

            QMessageBox successMsg(this);
            successMsg.setWindowTitle("✅ Oggetto modificato");
            successMsg.setText("<b>OGGETTO MODIFICATO CON SUCCESSO!</b>");
            successMsg.setIconPixmap(QPixmap(":/icons/ok_icon.png").scaled(48, 48));
            successMsg.setStyleSheet(styleSuccess);
            successMsg.exec();

            stack->setCurrentWidget(adminPage);
        }
    }
}

// Visitor pattern per mostrare i campi specifici
void EditCreatePage::visit(Libro* libro) {
    setupBookFields(libro);
}

void EditCreatePage::visit(Film* film) {
    setupFilmFields(film);
}

void EditCreatePage::visit(Rivista* rivista) {
    setupRivistaFields(rivista);
}

void EditCreatePage::setupCommonFields() {
    // Campo per il percorso immagine
    QString relativeImagePath;
    if (currentItem) {
        QString fullPath = QString::fromStdString(currentItem->getImmagine());
        // Converti percorso assoluto in relativo se necessario
        QDir projectDir(QCoreApplication::applicationDirPath());
        relativeImagePath = projectDir.relativeFilePath(fullPath);
    }

    imagePathEdit = new QLineEdit(relativeImagePath);
    imagePathEdit->setPlaceholderText("Inserisci percorso relativo immagine...");
    browseImageButton = new QPushButton("Sfoglia immagine da locale...");

    connect(browseImageButton, &QPushButton::clicked, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this,
                                                        "Seleziona immagine",
                                                        QCoreApplication::applicationDirPath(),
                                                        "Immagini (*.png *.jpg *.jpeg)");

        if (!filePath.isEmpty()) {
            // Converti il percorso assoluto in relativo
            QDir projectDir(QCoreApplication::applicationDirPath());
            QString relativePath = projectDir.relativeFilePath(filePath);
            imagePathEdit->setText(relativePath);
        }
    });

    // Aggiungi i widget al layout
    formLayout->addRow("Immagine:", imagePathEdit);
    formLayout->addRow("", browseImageButton);


    titleEdit = new QLineEdit(currentItem ? QString::fromStdString(currentItem->getTitolo()) : "");
    yearEdit = new QSpinBox();
    yearEdit->setRange(1900, QDate::currentDate().year());
    yearEdit->setValue(currentItem ? currentItem->getAnno() : 2000);

    genreEdit = new QLineEdit(currentItem ? QString::fromStdString(currentItem->getGenere()) : "");

    languageCombo = new QComboBox();
    languageCombo->addItems({"Italiano", "Inglese", "Spagnolo"});
    if(currentItem) {
        int index = languageCombo->findText(QString::fromStdString(currentItem->getLingua()));
        if(index >= 0) languageCombo->setCurrentIndex(index);
    }

    copiesEdit = new QSpinBox();
    copiesEdit->setRange(1, 100);
    copiesEdit->setValue(currentItem ? currentItem->getNumeroCopie() : 1);

    loansEdit = new QSpinBox();
    loansEdit->setRange(0, 100);
    loansEdit->setValue(currentItem ? currentItem->getNumeroPrestiti() : 0);

    // Connessione per aggiornare automaticamente la disponibilità quando cambiano copie o prestiti
    connect(copiesEdit, QOverload<int>::of(&QSpinBox::valueChanged), this, [this]() {
        if (loansEdit->value() > copiesEdit->value()) {
            loansEdit->setValue(copiesEdit->value());
        }
    });

    connect(loansEdit, QOverload<int>::of(&QSpinBox::valueChanged), this, [this]() {
        if (loansEdit->value() > copiesEdit->value()) {
            loansEdit->setValue(copiesEdit->value());
        }
    });

    // Aggiungi campo descrizione
    descriptionEdit = new QTextEdit(currentItem ? QString::fromStdString(currentItem->getDescrizione()) : "");
    descriptionEdit->setStyleSheet(fieldStyle);
    descriptionEdit->setMaximumHeight(100);



    imagePathEdit->setStyleSheet(fieldStyle);
    browseImageButton->setStyleSheet(fieldStyle);
    titleEdit->setStyleSheet(fieldStyle);
    yearEdit->setStyleSheet(fieldStyle);
    genreEdit->setStyleSheet(fieldStyle);
    languageCombo->setStyleSheet(fieldStyle);
    copiesEdit->setStyleSheet(fieldStyle);
    loansEdit->setStyleSheet(fieldStyle);





    formLayout->addRow(createStyledLabel("Immagine:"), imagePathEdit);
    formLayout->addWidget(browseImageButton);
    formLayout->addRow(createStyledLabel("Titolo:"), titleEdit);
    formLayout->addRow(createStyledLabel("Anno:"), yearEdit);
    formLayout->addRow(createStyledLabel("Genere:"), genreEdit);
    formLayout->addRow(createStyledLabel("Lingua:"), languageCombo);
    formLayout->addRow(createStyledLabel("Numero Copie:"), copiesEdit);
    formLayout->addRow(createStyledLabel("Numero Prestiti:"), loansEdit);
    formLayout->addRow(createStyledLabel("Descrizione:"), descriptionEdit);
}

void EditCreatePage::setupBookFields(Libro* libro) {
    authorEdit = new QLineEdit(libro ? QString::fromStdString(libro->getAutore()) : "");
    pagesEdit = new QSpinBox();
    pagesEdit->setRange(1, 5000);
    pagesEdit->setValue(libro ? libro->getPagine() : 200);

    isbnEdit = new QLineEdit(libro ? QString::fromStdString(libro->getISBN()) : "");

    // Nuovi campi per il libro
    targetEtaCombo = new QComboBox();
    targetEtaCombo->addItems({
        "Neonati (0-3 anni)",
        "Prescolare (4-6 anni)",
        "Bambini (7-12 anni)",
        "Adolescenti (13-17 anni)",
        "Adulti (18+ anni)",
        "Tutte le età"
    });
    if (libro) {
        int index = targetEtaCombo->findText(QString::fromStdString(libro->getTargetEta()));
        if (index >= 0) targetEtaCombo->setCurrentIndex(index);
    }

    ebookCheck = new QCheckBox("Disponibile come ebook");
    ebookCheck->setChecked(libro ? libro->getHaEbook() : false);

    // Stile
    authorEdit->setPlaceholderText("Inserisci l'autore...");
    pagesEdit->setStyleSheet(fieldStyle + "font-weight: bold;");
    isbnEdit->setPlaceholderText("Formato: XXX-XX-XXXXX-XX-X");
    targetEtaCombo->setStyleSheet(fieldStyle);
    ebookCheck->setStyleSheet(checkBoxStyle);

    formLayout->addRow(createStyledLabel("Autore:"), authorEdit);
    formLayout->addRow(createStyledLabel("Pagine:"), pagesEdit);
    formLayout->addRow(createStyledLabel("ISBN:"), isbnEdit);
    formLayout->addRow(createStyledLabel("Fascia d'età':"), targetEtaCombo);
    formLayout->addRow(createStyledLabel("Formato Digitale:"), ebookCheck);

}

void EditCreatePage::setupFilmFields(Film* film) {
    directorEdit = new QLineEdit(film ? QString::fromStdString(film->getRegista()) : "");
    protagonistEdit = new QLineEdit(film ? QString::fromStdString(film->getProtagonista()) : "");
    durationEdit = new QSpinBox();
    durationEdit->setRange(1, 300);
    durationEdit->setValue(film ? film->getDurata() : 120);

    // New fields for Film
    countryEdit = new QLineEdit(film ? QString::fromStdString(film->getPaeseOrigine()) : "");

    subtitlesCheck = new QCheckBox("Ha sottotitoli");
    subtitlesCheck->setChecked(film ? film->getHaSottotitoli() : false);

    // Rating stars selector
    ratingCombo = new QComboBox();
    ratingCombo->addItems({"1 stella", "2 stelle", "3 stelle", "4 stelle", "5 stelle"});
    if (film) {
        ratingCombo->setCurrentIndex(film->getRating() - 1);
    } else {
        ratingCombo->setCurrentIndex(2); // Default to 3 stars
    }

    // Awards list
    awardsGroup = new QGroupBox("Premi vinti");
    awardsList = new QListWidget();
    addAwardButton = new QPushButton("Aggiungi premio");
    removeAwardButton = new QPushButton("Rimuovi premio");

    QVBoxLayout* awardsLayout = new QVBoxLayout();
    awardsLayout->addWidget(awardsList);
    QHBoxLayout* awardsButtonsLayout = new QHBoxLayout();
    awardsButtonsLayout->addWidget(addAwardButton);
    awardsButtonsLayout->addWidget(removeAwardButton);
    awardsLayout->addLayout(awardsButtonsLayout);
    awardsGroup->setLayout(awardsLayout);

    // Populate awards list if editing
    if (film) {
        const vector<string>& premi = film->getPremi();
        for (const auto& premio : premi) {
            awardsList->addItem(QString::fromStdString(premio));
        }
    }

    // Connect buttons
    connect(addAwardButton, &QPushButton::clicked, this, [this]() {
        bool ok;
        QString award = QInputDialog::getText(this, "Aggiungi premio", "Inserisci il nome del premio:",
                                              QLineEdit::Normal, "", &ok);
        if (ok && !award.isEmpty()) {
            awardsList->addItem(award);
        }
    });

    connect(removeAwardButton, &QPushButton::clicked, this, [this]() {
        int currentRow = awardsList->currentRow();
        if (currentRow < 0) {
            QMessageBox errorMsg;
            errorMsg.setWindowTitle("⚠️ Attenzione");
            errorMsg.setText("<b>NESSUN PREMIO SELEZIONATO!</b>");
            errorMsg.setInformativeText("Seleziona un premio dalla lista per poterlo rimuovere.");
            errorMsg.setIconPixmap(QIcon(":/icons/attenzione_icon.png").pixmap(64, 64));
            errorMsg.setStyleSheet(dialogStyle);
            errorMsg.exec();
            return;
        }

        delete awardsList->takeItem(currentRow);
    });


    // Aggiungi questo alla fine del metodo
    // Stile specifico per i campi del film
    directorEdit->setPlaceholderText("Inserisci il regista...");
    protagonistEdit->setPlaceholderText("Inserisci il protagonista...");
    durationEdit->setStyleSheet(fieldStyle + "font-weight: bold;");
    countryEdit->setPlaceholderText("Es: Italia, Francia...");
    subtitlesCheck->setStyleSheet(checkBoxStyle);
    ratingCombo->setStyleSheet(fieldStyle);

    // Stile per i premi
    awardsGroup->setStyleSheet(fieldStyle);
    awardsList->setStyleSheet(fieldStyle + "font-size: 14px;");
    addAwardButton->setStyleSheet(buttonStyle + "font-size: 14px;");
    removeAwardButton->setStyleSheet(buttonStyle + "font-size: 14px;");

    // Add to form layout
    formLayout->addRow(createStyledLabel("Regista:"), directorEdit);
    formLayout->addRow(createStyledLabel("Protagonista:"), protagonistEdit);
    formLayout->addRow(createStyledLabel("Durata(min):"), durationEdit);
    formLayout->addRow(createStyledLabel("Paese d'origine:"), countryEdit);
    formLayout->addRow(createStyledLabel("Sottotitoli:"), subtitlesCheck);
    formLayout->addRow(createStyledLabel("Valutazione:"), ratingCombo);
    formLayout->addRow(awardsGroup);
}

void EditCreatePage::setupRivistaFields(Rivista* rivista) {
    // Campi specifici per Rivista
    periodicitàCombo = new QComboBox();
    periodicitàCombo->addItems({"Mensile", "Bimestrale", "Trimestrale", "Semestrale", "Annuale"});
    if (rivista) {
        int index = periodicitàCombo->findText(QString::fromStdString(rivista->getPeriodicità()));
        if (index >= 0) periodicitàCombo->setCurrentIndex(index);
    }

    editoreEdit = new QLineEdit(rivista ? QString::fromStdString(rivista->getEditore()) : "");
    direttoreEdit = new QLineEdit(rivista ? QString::fromStdString(rivista->getDirettore()) : "");
    issnEdit = new QLineEdit(rivista ? QString::fromStdString(rivista->getISSN()) : "");
    volumeEdit = new QSpinBox();
    volumeEdit->setRange(1, 1000);
    volumeEdit->setValue(rivista ? rivista->getVolume() : 1);

    // Lista articoli
    articoliGroup = new QGroupBox("Articoli contenuti");
    articoliList = new QListWidget();
    addArticoloButton = new QPushButton("Aggiungi articolo");
    removeArticoloButton = new QPushButton("Rimuovi articolo");

    QVBoxLayout* articoliLayout = new QVBoxLayout();
    articoliLayout->addWidget(articoliList);
    QHBoxLayout* articoliButtonsLayout = new QHBoxLayout();
    articoliButtonsLayout->addWidget(addArticoloButton);
    articoliButtonsLayout->addWidget(removeArticoloButton);
    articoliLayout->addLayout(articoliButtonsLayout);
    articoliGroup->setLayout(articoliLayout);

    // Popola la lista articoli se in modalità modifica
    if (rivista) {
        const auto& articoli = rivista->getArticoli();
        for (const auto& articolo : articoli) {
            QString itemText = QStringLiteral("%1 - %2")
                                    .arg(QString::fromStdString(articolo.first),
                                         QString::fromStdString(articolo.second));
            articoliList->addItem(itemText);
        }
    }

    // Connessioni pulsanti
    connect(addArticoloButton, &QPushButton::clicked, this, [this]() {
        bool ok;
        QString titolo = QInputDialog::getText(this, "Aggiungi articolo", "Titolo articolo:", QLineEdit::Normal, "", &ok);
        if (!ok || titolo.isEmpty()) return;

        QString autore = QInputDialog::getText(this, "Aggiungi articolo", "Autore articolo:", QLineEdit::Normal, "", &ok);
        if (!ok || autore.isEmpty()) return;

        QString itemText = QStringLiteral("%1 - %2").arg(titolo, autore);
        articoliList->addItem(itemText);
    });

    QString dialogStyle = "...";
    connect(removeArticoloButton, &QPushButton::clicked, this, [this, dialogStyle]() {
        int currentRow = articoliList->currentRow();
        if (currentRow < 0) {
            QMessageBox errorMsg;
            errorMsg.setWindowTitle("⚠️ Attenzione");
            errorMsg.setText("<b>NESSUN ARTICOLO SELEZIONATO!</b>");
            errorMsg.setInformativeText("Seleziona un articolo dalla lista per poterlo rimuovere.");
            errorMsg.setIconPixmap(QIcon(":/icons/attenzione_icon.png").pixmap(64, 64));
            errorMsg.setStyleSheet(dialogStyle);
            errorMsg.exec();
            return;
        }

        delete articoliList->takeItem(currentRow);
    });
    // Aggiungi questo alla fine del metodo
    // Stile specifico per i campi della rivista
    periodicitàCombo->setStyleSheet(fieldStyle);
    editoreEdit->setPlaceholderText("Inserisci l'editore...");
    direttoreEdit->setPlaceholderText("Inserisci il direttore...");
    issnEdit->setPlaceholderText("Formato: XXXX-XXXX");
    volumeEdit->setStyleSheet(fieldStyle + "font-weight: bold;");

    // Stile per gli articoli
    articoliGroup->setStyleSheet(fieldStyle);
    articoliList->setStyleSheet(fieldStyle + "font-size: 14px;");
    addArticoloButton->setStyleSheet(buttonStyle + "font-size: 14px;");
    removeArticoloButton->setStyleSheet(buttonStyle + "font-size: 14px;");

    // Aggiunta al form layout
    formLayout->addRow(createStyledLabel("Periodicità:"), periodicitàCombo);
    formLayout->addRow(createStyledLabel("Editore:"), editoreEdit);
    formLayout->addRow(createStyledLabel("Direttore:"), direttoreEdit);
    formLayout->addRow(createStyledLabel("ISSN:"), issnEdit);
    formLayout->addRow(createStyledLabel("Volume:"), volumeEdit);
    formLayout->addRow(articoliGroup);
}

void EditCreatePage::aggiornaDisponibilità(BibliotecaItem* item) {
    item->setDisponibile(item->getNumeroPrestiti() < item->getNumeroCopie());
}


bool EditCreatePage::aggiornaFields(BibliotecaItem* item) {
    // Gestione percorso immagine
    QString imagePath = imagePathEdit->text();
    if (!imagePath.isEmpty() && !QDir::isAbsolutePath(imagePath)) {
        imagePath = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(imagePath);
    }
    item->setImmagine(imagePath.toStdString());
    class UpdateVisitor : public Visitor {
    public:
        EditCreatePage* parent;
        bool success = true;

        UpdateVisitor(EditCreatePage* p) : parent(p) {}

        void visit(Libro* libro) override {
            if (parent->authorEdit->text().isEmpty() || parent->isbnEdit->text().isEmpty()) {
                QMessageBox::warning(parent, "Errore", "Compila tutti i campi necessari per il libro!");
                success = false;
                return;
            }
            libro->setAutore(parent->authorEdit->text().toStdString());
            libro->setPagine(parent->pagesEdit->value());
            libro->setISBN(parent->isbnEdit->text().toStdString());
            libro->setTargetEta(parent->targetEtaCombo->currentText().toStdString());
            libro->setHaEbook(parent->ebookCheck->isChecked());
        }

        void visit(Film* film) override {
            if (parent->directorEdit->text().isEmpty() ||
                parent->protagonistEdit->text().isEmpty() ||
                parent->countryEdit->text().isEmpty()) {
                QMessageBox::warning(parent, "Errore", "Compila tutti i campi necessari per il film!");
                success = false;
                return;
            }
            film->setRegista(parent->directorEdit->text().toStdString());
            film->setProtagonista(parent->protagonistEdit->text().toStdString());
            film->setDurata(parent->durationEdit->value());
            film->setPaeseOrigine(parent->countryEdit->text().toStdString());
            film->setHaSottotitoli(parent->subtitlesCheck->isChecked());
            film->setRating(parent->ratingCombo->currentIndex() + 1);

            // Aggiorna i premi
            vector<string> premi;
            for (int i = 0; i < parent->awardsList->count(); ++i) {
                premi.push_back(parent->awardsList->item(i)->text().toStdString());
            }
            film->setPremi(premi);
        }

        void visit(Rivista* rivista) override {
            if (parent->editoreEdit->text().isEmpty() ||
                parent->direttoreEdit->text().isEmpty() ||
                parent->issnEdit->text().isEmpty()) {
                QMessageBox::warning(parent, "Errore", "Compila tutti i campi necessari per la rivista!");
                success = false;
                return;
            }
            rivista->setEditore(parent->editoreEdit->text().toStdString());
            rivista->setDirettore(parent->direttoreEdit->text().toStdString());
            rivista->setPeriodicità(parent->periodicitàCombo->currentText().toStdString());
            rivista->setISSN(parent->issnEdit->text().toStdString());
            rivista->setVolume(parent->volumeEdit->value());

            // Aggiorna gli articoli
            vector<pair<string, string>> articoli;
            for (int i = 0; i < parent->articoliList->count(); ++i) {
                QString itemText = parent->articoliList->item(i)->text();
                QStringList parts = itemText.split(" - ");
                if (parts.size() == 2) {
                    articoli.emplace_back(parts[0].toStdString(), parts[1].toStdString());
                }
            }
            rivista->setArticoli(articoli);
        }
    };

    UpdateVisitor visitor(this);
    item->accept(&visitor);
    return visitor.success;
    return true;
}

BibliotecaItem* EditCreatePage::createNewItem() {
    // Gestione percorso immagine
    QString imagePath = imagePathEdit->text();
    if (!imagePath.isEmpty() && !QDir::isAbsolutePath(imagePath)) {
        // Converti percorso relativo in assoluto
        imagePath = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(imagePath);
    }

    if(currentType == "Libro") {
        return new Libro(
            imagePath.toStdString(),
            titleEdit->text().toStdString(),
            yearEdit->value(),
            genreEdit->text().toStdString(),
            languageCombo->currentText().toStdString(),
            true,
            copiesEdit->value(),
            loansEdit->value(),
            authorEdit->text().toStdString(),
            pagesEdit->value(),
            isbnEdit->text().toStdString(),
            descriptionEdit->toPlainText().toStdString(),
            targetEtaCombo->currentText().toStdString(),
            ebookCheck->isChecked()
            );
    }
    else if(currentType == "Film") {
        return new Film(
            imagePath.toStdString(),
            titleEdit->text().toStdString(),
            yearEdit->value(),
            genreEdit->text().toStdString(),
            languageCombo->currentText().toStdString(),
            true,
            copiesEdit->value(),
            loansEdit->value(),
            directorEdit->text().toStdString(),
            protagonistEdit->text().toStdString(),
            durationEdit->value(),
            descriptionEdit->toPlainText().toStdString()
            );
    }
    else {
        // Creazione di una nuova Rivista
        vector<pair<string, string>> articoli;
        for (int i = 0; i < articoliList->count(); ++i) {
            QString itemText = articoliList->item(i)->text();
            QStringList parts = itemText.split(" - ");
            if (parts.size() == 2) {
                articoli.emplace_back(parts[0].toStdString(), parts[1].toStdString());
            }
        }

        return new Rivista(
            imagePath.toStdString(),
            titleEdit->text().toStdString(),
            yearEdit->value(),
            genreEdit->text().toStdString(),
            languageCombo->currentText().toStdString(),
            true,
            copiesEdit->value(),
            loansEdit->value(),
            descriptionEdit->toPlainText().toStdString(),
            periodicitàCombo->currentText().toStdString(),
            editoreEdit->text().toStdString(),
            direttoreEdit->text().toStdString(),
            issnEdit->text().toStdString(),
            articoli,
            volumeEdit->value()
            );
    }
}



void EditCreatePage::cleanLayout() {
    while (formLayout->count() > 0) {
        QLayoutItem* item = formLayout->takeAt(0);
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }

    // Reset di tutti i puntatori ai widget
    imagePathEdit = nullptr;
    browseImageButton = nullptr;
    titleEdit = nullptr;
    yearEdit = nullptr;
    genreEdit = nullptr;
    languageCombo = nullptr;
    copiesEdit = nullptr;
    loansEdit = nullptr;
    descriptionEdit = nullptr;
    authorEdit = nullptr;
    pagesEdit = nullptr;
    isbnEdit = nullptr;
    directorEdit = nullptr;
    protagonistEdit = nullptr;
    durationEdit = nullptr;
    periodicitàCombo = nullptr;
    editoreEdit = nullptr;
    direttoreEdit = nullptr;
    issnEdit = nullptr;
    volumeEdit = nullptr;
    articoliList = nullptr;
    addArticoloButton = nullptr;
    removeArticoloButton = nullptr;
    articoliGroup = nullptr;
    targetEtaCombo = nullptr;
    ebookCheck = nullptr;
}












