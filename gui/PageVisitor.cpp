// File PageVisitor.cpp
#include "PageVisitor.h"
#include "stylevisitor.h"
#include "../modello_logico/BibliotecaItem.h"
#include "../modello_logico/Libro.h"
#include "../modello_logico/Film.h"
#include "../modello_logico/Rivista.h"

#include <QFormLayout>
#include <QLabel>
#include <QPixmap>
#include <QTextEdit>
#include <QListWidget>
#include <QScrollArea>

PageVisitor::PageVisitor() : pageWidget(new QWidget()), pageLayout(new QVBoxLayout()) {
    pageWidget->setLayout(pageLayout);
    pageWidget->setStyleSheet("background-color: white; border-radius: 8px;");
    pageLayout->setContentsMargins(15, 15, 15, 15);
    pageLayout->setSpacing(10);
}

void PageVisitor::buildCommonWidgets(BibliotecaItem *item){
    // pulizia
    QLayoutItem *child;
    while ((child = pageLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Layout per titolo e icona
    QHBoxLayout *titleLayout = new QHBoxLayout();

    // Creazione degli elementi UI
    QLabel *typeIcon = new QLabel();
    typeIcon->setFixedSize(30, 30);
    typeIcon->setStyleSheet("border-radius: 15px;");
    typeIcon->setAlignment(Qt::AlignCenter);

    if (!item) {
        return;
    }

    QLabel *titleLabel = new QLabel("<b>" + QString::fromStdString(item->getTitolo()) + "</b>");

    // Applicazione degli stili con Visitor
    StyleVisitor visitor(typeIcon, titleLabel);
    item->accept(&visitor);

    titleLayout->addWidget(typeIcon);
    titleLayout->addWidget(titleLabel, 1);
    titleLayout->addStretch();

    // Layout per i dettagli
    QFormLayout *detailsLayout = new QFormLayout();
    detailsLayout->setSpacing(8);
    detailsLayout->setContentsMargins(5, 5, 5, 5);

    // Immagine
    QLabel *imageLabel = new QLabel();
    QString path = QString::fromStdString(item->getImmagine());
    QPixmap image(path);

    if (!image.isNull()) {
        imageLabel->setPixmap(image.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        imageLabel->setText("\n\n\n\n\n[Nessuna immagine disponibile]\n\n\n\n\n\n\n");
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->setStyleSheet("color: gray;");
    }
    imageLabel->setFixedSize(200, 200);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet(imageLabel->styleSheet() + "border-radius: 8px;");

    // Layout per centrare l'immagine
    QHBoxLayout *imageLayout = new QHBoxLayout();
    imageLayout->addStretch();
    imageLayout->addWidget(imageLabel);
    imageLayout->addStretch();

    // Informazioni comuni
    QLabel *yearLabel = new QLabel(QString::number(item->getAnno()));
    QLabel *genreLabel = new QLabel(QString::fromStdString(item->getGenere()));
    QLabel *languageLabel = new QLabel(QString::fromStdString(item->getLingua()));

    // Disponibilità
    int disponibili = item->getNumeroCopie() - item->getNumeroPrestiti();
    QString disponibileText = QString("%1/%2 (%3)")
                                  .arg(disponibili)
                                  .arg(item->getNumeroCopie())
                                  .arg(item->getDisponibile() ? "Disponibile" : "Esaurito");

    QLabel *availableLabel = new QLabel(disponibileText);
    availableLabel->setStyleSheet(item->getDisponibile() ? "color: #4CAF50; font-weight: bold;" : "color: #F44336; font-weight: bold;");

    // Descrizione
    QTextEdit *descriptionText = new QTextEdit(QString::fromStdString(item->getDescrizione()));
    descriptionText->setReadOnly(true);
    descriptionText->setFrameStyle(QFrame::NoFrame);
    descriptionText->setStyleSheet("background: transparent; font-style: italic; border: 1px solid #E0E0E0; border-radius: 5px; padding: 5px;");
    descriptionText->setFixedHeight(80);

    // Aggiunta delle informazioni al form layout
    detailsLayout->addRow("Anno:", yearLabel);
    detailsLayout->addRow("Genere:", genreLabel);
    detailsLayout->addRow("Lingua:", languageLabel);
    detailsLayout->addRow("Disponibilità:", availableLabel);

    // Inserimento nel layout principale
    pageLayout->addLayout(titleLayout);
    pageLayout->addLayout(imageLayout);
    pageLayout->addLayout(detailsLayout);
    pageLayout->addWidget(new QLabel("<b>Descrizione:</b>"));
    pageLayout->addWidget(descriptionText);
}

void PageVisitor::visit(Libro *libro) {
    buildCommonWidgets(libro);

    QFormLayout *bookDetailsLayout = new QFormLayout();
    bookDetailsLayout->setSpacing(8);
    bookDetailsLayout->setContentsMargins(5, 5, 5, 5);

    QLabel *authorLabel = new QLabel(QString::fromStdString(libro->getAutore()));
    QLabel *pagesLabel = new QLabel(QString::number(libro->getPagine()));
    QLabel *isbnLabel = new QLabel(QString::fromStdString(libro->getISBN()));
    QLabel *targetEtaLabel = new QLabel(QString::fromStdString(libro->getTargetEta()));

    // Ebook con icona
    QHBoxLayout *ebookLayout = new QHBoxLayout();
    QLabel *ebookIcon = new QLabel();
    ebookIcon->setPixmap(QPixmap(libro->getHaEbook() ? ":/icons/ok_icon.png" : ":/icons/error_icon.png").scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QLabel *ebookText = new QLabel(libro->getHaEbook() ? "Sì" : "No");
    ebookLayout->addWidget(ebookIcon);
    ebookLayout->addWidget(ebookText);
    ebookLayout->addStretch();
    ebookLayout->setSpacing(5);

    QWidget *ebookWidget = new QWidget();
    ebookWidget->setLayout(ebookLayout);
    ebookText->setStyleSheet(libro->getHaEbook() ? "color: #4CAF50; font-weight: bold;" : "color: #F44336; font-weight: bold;");

    authorLabel->setStyleSheet("padding: 3px;");
    pagesLabel->setStyleSheet("padding: 3px;");
    isbnLabel->setStyleSheet("padding: 3px; font-family: monospace;");
    targetEtaLabel->setStyleSheet("padding: 3px; color: #2196F3; font-weight: bold;");

    bookDetailsLayout->addRow("Autore:", authorLabel);
    bookDetailsLayout->addRow("Pagine:", pagesLabel);
    bookDetailsLayout->addRow("ISBN:", isbnLabel);
    bookDetailsLayout->addRow("Fascia d'età:", targetEtaLabel);
    bookDetailsLayout->addRow("Ebook disponibile:", ebookWidget);

    pageLayout->addLayout(bookDetailsLayout);
}

void PageVisitor::visit(Film *film){
    buildCommonWidgets(film);

    QFormLayout *filmDetailsLayout = new QFormLayout();
    filmDetailsLayout->setSpacing(8);
    filmDetailsLayout->setContentsMargins(5, 5, 5, 5);

    QLabel *directorLabel = new QLabel(QString::fromStdString(film->getRegista()));
    QLabel *maincharacterLabel = new QLabel(QString::fromStdString(film->getProtagonista()));
    QLabel *durationLabel = new QLabel(QString::number(film->getDurata()) + " minuti");
    QLabel *countryLabel = new QLabel(QString::fromStdString(film->getPaeseOrigine()));

    // Sottotitoli con icona
    QHBoxLayout *subtitlesLayout = new QHBoxLayout();
    QLabel *subtitlesIcon = new QLabel();
    subtitlesIcon->setPixmap(QPixmap(film->getHaSottotitoli() ? ":/icons/ok_icon.png" : ":/icons/error_icon.png").scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QLabel *subtitlesText = new QLabel(film->getHaSottotitoli() ? "Sì" : "No");
    subtitlesLayout->addWidget(subtitlesIcon);
    subtitlesLayout->addWidget(subtitlesText);
    subtitlesLayout->addStretch();
    subtitlesLayout->setSpacing(5);

    QWidget *subtitlesWidget = new QWidget();
    subtitlesWidget->setLayout(subtitlesLayout);
    subtitlesText->setStyleSheet(film->getHaSottotitoli() ? "color: #4CAF50; font-weight: bold;" : "color: #F44336; font-weight: bold;");

    // Rating con stelle
    int rating = film->getRating();
    QString ratingStars = QString(rating, QChar(0x2605)) + QString(5-rating, QChar(0x2606));
    QLabel *ratingLabel = new QLabel(ratingStars);
    ratingLabel->setStyleSheet("color: #FFC107; font-size: 18px; letter-spacing: 2px;");

    // Premi
    QString premiText;
    const vector<string>& premi = film->getPremi();
    if(premi.empty()) {
        premiText = "Nessun premio";
    } else {
        for(const auto& premio : premi) {
            premiText += "• " + QString::fromStdString(premio) + "\n";
        }
    }

    QTextEdit *premiTextEdit = new QTextEdit(premiText);
    premiTextEdit->setReadOnly(true);
    premiTextEdit->setFrameStyle(QFrame::NoFrame);
    premiTextEdit->setStyleSheet("background: transparent; border: 1px solid #E0E0E0; border-radius: 5px; padding: 5px;");
    premiTextEdit->setFixedHeight(premi.empty() ? 30 : qMin(100, static_cast<int>(premi.size()) * 25 + 10));

    directorLabel->setStyleSheet("padding: 3px;");
    maincharacterLabel->setStyleSheet("padding: 3px;");
    durationLabel->setStyleSheet("padding: 3px;");
    countryLabel->setStyleSheet("padding: 3px; font-weight: bold;");

    filmDetailsLayout->addRow("Regista:", directorLabel);
    filmDetailsLayout->addRow("Protagonista:", maincharacterLabel);
    filmDetailsLayout->addRow("Durata:", durationLabel);
    filmDetailsLayout->addRow("Paese d'origine:", countryLabel);
    filmDetailsLayout->addRow("Sottotitoli:", subtitlesWidget);
    filmDetailsLayout->addRow("Valutazione:", ratingLabel);
    filmDetailsLayout->addRow("Premi:", premiTextEdit);

    pageLayout->addLayout(filmDetailsLayout);
}

void PageVisitor::visit(Rivista *rivista){
    buildCommonWidgets(rivista);

    QFormLayout *rivistaDetailsLayout = new QFormLayout();
    rivistaDetailsLayout->setSpacing(8);
    rivistaDetailsLayout->setContentsMargins(5, 5, 5, 5);

    QLabel *periodicitaLabel = new QLabel(QString::fromStdString(rivista->getPeriodicità()));
    QLabel *editoreLabel = new QLabel(QString::fromStdString(rivista->getEditore()));
    QLabel *direttoreLabel = new QLabel(QString::fromStdString(rivista->getDirettore()));
    QLabel *issnLabel = new QLabel(QString::fromStdString(rivista->getISSN()));
    QLabel *volumeLabel = new QLabel(QString::number(rivista->getVolume()));

    // Applicazione stili corretti
    periodicitaLabel->setStyleSheet("padding: 3px; color: #8E44AD; font-weight: bold;");
    editoreLabel->setStyleSheet("padding: 3px;");
    direttoreLabel->setStyleSheet("padding: 3px;");
    issnLabel->setStyleSheet("padding: 3px; font-family: monospace;");
    volumeLabel->setStyleSheet("padding: 3px;");

    rivistaDetailsLayout->addRow("Periodicità:", periodicitaLabel);
    rivistaDetailsLayout->addRow("Editore:", editoreLabel);
    rivistaDetailsLayout->addRow("Direttore:", direttoreLabel);
    rivistaDetailsLayout->addRow("ISSN:", issnLabel);
    rivistaDetailsLayout->addRow("Volume:", volumeLabel);

    // Articoli
    QLabel *articoliLabel = new QLabel("<b>Articoli contenuti:</b>");
    QTextEdit *articoliText = new QTextEdit();
    articoliText->setReadOnly(true);
    articoliText->setFrameStyle(QFrame::NoFrame);

    const auto& articoli = rivista->getArticoli();
    if(articoli.empty()) {
        articoliText->setPlainText("Nessun articolo disponibile");
    } else {
        QString articoliContent;
        for (const auto& articolo : articoli) {
            articoliContent += QString("<b>%1</b><br>%2<br><br>")
            .arg(QString::fromStdString(articolo.first),
                 QString::fromStdString(articolo.second));
        }
        articoliText->setHtml(articoliContent);
    }

    articoliText->setStyleSheet("background: transparent; border: 1px solid #E0E0E0; border-radius: 5px; padding: 5px;");
    articoliText->setFixedHeight(articoli.empty() ? 30 : qMin(150, static_cast<int>(articoli.size()) * 50 + 10));

    pageLayout->addLayout(rivistaDetailsLayout);
    pageLayout->addWidget(articoliLabel);
    pageLayout->addWidget(articoliText);
}

QWidget* PageVisitor::getObjectWidget() const {
    return pageWidget;
}
