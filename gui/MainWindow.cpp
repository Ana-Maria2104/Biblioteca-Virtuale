#include "MainWindow.h"
#include <QMessageBox>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QIcon>
#include <QDialog>
#include <QFrame>
#include <QSpacerItem>
#include <QShortcut>
#include <QMessageBox>


MainWindow::MainWindow(QStackedWidget *stackedwidget, QWidget *parent)
    : QMainWindow(parent), stack(stackedwidget)
{
    setWindowTitle("Accesso");
    setMinimumSize(1000, 800);

    // Creazione della scorciatoia
    QShortcut *shortcutClose = new QShortcut(QKeySequence("Ctrl+Q"), this);
    connect(shortcutClose, &QShortcut::activated, this, &MainWindow::close);
    QShortcut *adminShortcut = new QShortcut(QKeySequence("Ctrl+A"), this);
    connect(adminShortcut, &QShortcut::activated, this, &MainWindow::showAdminLogin);
    QShortcut *userShortcut = new QShortcut(QKeySequence("Ctrl+U"), this);
    connect(userShortcut, &QShortcut::activated, this, &MainWindow::handleUserAccess);

     // Schermata principale con sfondo rosa-bianco
    QWidget *mainWidget = new QWidget(this);
        // Rosa bianco molto chiaro
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Barra superiore rosa chiaro con pulsante chiudi
    QWidget *topBar = new QWidget(mainWidget);
    topBar->setStyleSheet("background-color: #faf0e6;"); // Rosa chiaro
    topBar->setFixedHeight(50);
    QHBoxLayout *topLayout = new QHBoxLayout(topBar);
    topLayout->setContentsMargins(0, 0, 20, 0);
    topLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QPushButton *closeButton = new QPushButton("✕", topBar);
    closeButton->setFixedSize(40, 40);
    closeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #FF6B6B;"
        "   color: white;"
        "   font-size: 24px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #FF5252;"
        "}"
        );
    connect(closeButton, &QPushButton::clicked, this, &MainWindow::confirmClose);

    topLayout->addWidget(closeButton);
    mainLayout->addWidget(topBar, 0);

    // Contenuto centrale
    QWidget *contentWidget = new QWidget(mainWidget);
    contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(80, 80, 80, 80);
    contentLayout->setSpacing(60);
    contentLayout->setAlignment(Qt::AlignCenter);

    // Titolo principale nero
    QLabel *titleLabel = new QLabel("Biblioteca Digitale", contentWidget);
    titleLabel->setStyleSheet(
        "font-size: 48px;"
        "font-weight: bold;"
        "color: #000000;" // Nero
        "background-color: transparent;"
        "padding: 10px 20px;"
        "border-radius: 25px;"
        );
    titleLabel->setAlignment(Qt::AlignCenter);
    contentLayout->addWidget(titleLabel, 0, Qt::AlignCenter);

    // Area pulsanti
    QWidget *buttonsWidget = new QWidget(contentWidget);
    buttonsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QHBoxLayout *buttonsLayout = new QHBoxLayout(buttonsWidget);
    buttonsLayout->setSpacing(80);
    buttonsLayout->setAlignment(Qt::AlignCenter);

    // Pulsante Admin (rosso con testo nero)
    QWidget *adminWidget = new QWidget(buttonsWidget);
    adminWidget->setMinimumSize(300, 400);
    QVBoxLayout *adminLayout = new QVBoxLayout(adminWidget);
    adminLayout->setAlignment(Qt::AlignCenter);
    adminLayout->setSpacing(20);

    // Area titolo e icona admin
    QWidget *adminHeader = new QWidget(adminWidget);
    QVBoxLayout *adminHeaderLayout = new QVBoxLayout(adminHeader);
    adminHeaderLayout->setContentsMargins(0, 0, 0, 20);
    adminHeaderLayout->setSpacing(15);
    adminHeaderLayout->setAlignment(Qt::AlignCenter);

    QLabel *adminIcon = new QLabel(adminHeader);
    adminIcon->setPixmap(QPixmap(":/icons/admin_icon.png").scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    adminIcon->setAlignment(Qt::AlignCenter);

    QLabel *adminText = new QLabel("Area Admin", adminHeader);
    adminText->setStyleSheet(
        "font-size: 28px;"
        "color: #ce3018;" // Nero
        "font-weight: bold;"
        );
    adminText->setAlignment(Qt::AlignCenter);

    adminHeaderLayout->addWidget(adminIcon);
    adminHeaderLayout->addWidget(adminText);
    adminLayout->addWidget(adminHeader);

    // Bottone admin
    QPushButton *adminButton = new QPushButton(adminWidget);
    adminButton->setFixedSize(280, 180);
    adminButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #D32F2F;" // Rosso
        "   border-radius: 20px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #B71C1C;"
        "}"
        );

    QLabel *adminButtonText = new QLabel("Accedi", adminButton);
    adminButtonText->setStyleSheet(
        "font-size: 32px;"
        "color: #000000;" // Nero
        "font-weight: bold;"
        );
    adminButtonText->setAlignment(Qt::AlignCenter);

    QVBoxLayout *adminButtonLayout = new QVBoxLayout(adminButton);
    adminButtonLayout->addWidget(adminButtonText);
    adminButtonLayout->setAlignment(Qt::AlignCenter);

    adminLayout->addWidget(adminButton);

    // Freccia
    QLabel *adminArrow = new QLabel(adminWidget);
    adminArrow->setPixmap(QPixmap(":/icons/freccia_icon.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    adminArrow->setAlignment(Qt::AlignCenter);
    adminLayout->addWidget(adminArrow);

    connect(adminButton, &QPushButton::clicked, this, &MainWindow::showAdminLogin);

    // Separatore verticale che va fino in fondo
    QFrame *separator = new QFrame(buttonsWidget);
    separator->setFrameShape(QFrame::VLine);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setStyleSheet("background-color: #FFC0CB;"); // Rosa chiaro come la barra superiore
    separator->setFixedHeight(400);

    // Pulsante Utente (verde con testo nero)
    QWidget *userWidget = new QWidget(buttonsWidget);
    userWidget->setMinimumSize(300, 400);
    QVBoxLayout *userLayout = new QVBoxLayout(userWidget);
    userLayout->setAlignment(Qt::AlignCenter);
    userLayout->setSpacing(20);

    // Area titolo e icona utente
    QWidget *userHeader = new QWidget(userWidget);
    QVBoxLayout *userHeaderLayout = new QVBoxLayout(userHeader);
    userHeaderLayout->setContentsMargins(0, 0, 0, 20);
    userHeaderLayout->setSpacing(15);
    userHeaderLayout->setAlignment(Qt::AlignCenter);

    QLabel *userIcon = new QLabel(userHeader);
    userIcon->setPixmap(QPixmap(":/icons/utente_icon.png").scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    userIcon->setAlignment(Qt::AlignCenter);

    QLabel *userText = new QLabel("Area Utente", userHeader);
    userText->setStyleSheet(
        "font-size: 28px;"
        "color: #33c22c;" // Nero
        "font-weight: bold;"
        );
    userText->setAlignment(Qt::AlignCenter);

    userHeaderLayout->addWidget(userIcon);
    userHeaderLayout->addWidget(userText);
    userLayout->addWidget(userHeader);

    // Bottone utente
    QPushButton *userButton = new QPushButton(userWidget);
    userButton->setFixedSize(280, 180);
    userButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #388E3C;" // Verde
        "   border-radius: 20px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2E7D32;"
        "}"
        );

    QLabel *userButtonText = new QLabel("Accedi", userButton);
    userButtonText->setStyleSheet(
        "font-size: 32px;"
        "color: #000000;" // Nero
        "font-weight: bold;"
        );
    userButtonText->setAlignment(Qt::AlignCenter);

    QVBoxLayout *userButtonLayout = new QVBoxLayout(userButton);
    userButtonLayout->addWidget(userButtonText);
    userButtonLayout->setAlignment(Qt::AlignCenter);

    userLayout->addWidget(userButton);

    // Freccia
    QLabel *userArrow = new QLabel(userWidget);
    userArrow->setPixmap(QPixmap(":/icons/freccia_icon.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    userArrow->setAlignment(Qt::AlignCenter);
    userLayout->addWidget(userArrow);

    connect(userButton, &QPushButton::clicked, this, &MainWindow::handleUserAccess);

    buttonsLayout->addWidget(adminWidget);
    buttonsLayout->addWidget(separator);
    buttonsLayout->addWidget(userWidget);
    contentLayout->addWidget(buttonsWidget);

    mainLayout->addWidget(contentWidget, 1);
    setCentralWidget(mainWidget);
}

void MainWindow::showAdminLogin() {
    QDialog *loginDialog = new QDialog(this);
    loginDialog->setWindowTitle("Accesso Admin");
    loginDialog->setFixedSize(400, 300);
    loginDialog->setStyleSheet("background-color: #F5F5F5;");

    QVBoxLayout *dialogLayout = new QVBoxLayout(loginDialog);
    dialogLayout->setContentsMargins(30, 30, 30, 30);
    dialogLayout->setSpacing(20);

    QLabel *titleLabel = new QLabel("Accesso Admin", loginDialog);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #333;");
    titleLabel->setAlignment(Qt::AlignCenter);
    dialogLayout->addWidget(titleLabel);

    adminUsername = new QLineEdit(loginDialog);
    adminUsername->setPlaceholderText("Username");
    adminUsername->setStyleSheet(
        "QLineEdit {"
        "   padding: 10px;"
        "   font-size: 16px;"
        "   border: 1px solid #CCC;"
        "   border-radius: 5px;"
        "}"
        );

    // Creazione del widget contenitore per password + pulsante occhio
    QWidget *passwordContainer = new QWidget(loginDialog);
    QHBoxLayout *passwordLayout = new QHBoxLayout(passwordContainer);
    passwordLayout->setContentsMargins(0, 0, 0, 0);
    passwordLayout->setSpacing(0);

    adminPassword = new QLineEdit(passwordContainer);
    adminPassword->setPlaceholderText("Password");
    adminPassword->setEchoMode(QLineEdit::Password);
    adminPassword->setStyleSheet(
        "QLineEdit {"
        "   padding: 10px;"
        "   font-size: 16px;"
        "   border: 1px solid #CCC;"
        "   border-top-left-radius: 5px;"
        "   border-bottom-left-radius: 5px;"
        "   border-top-right-radius: 0px;"
        "   border-bottom-right-radius: 0px;"
        "}"
        );

    // Pulsante occhio con icona personalizzata
    QPushButton *togglePasswordButton = new QPushButton(passwordContainer);
    togglePasswordButton->setObjectName("togglePasswordButton");
    togglePasswordButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #E0E0E0;"
        "   border: 1px solid #CCC;"
        "   border-left: none;"
        "   border-top-right-radius: 5px;"
        "   border-bottom-right-radius: 5px;"
        "   padding: 5px;"
        "   width: 40px;"
        "   qproperty-icon: url(:/icons/occhio_icon.png);"
        "   qproperty-iconSize: 24px 24px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #D0D0D0;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #C0C0C0;"
        "}"
        );

    passwordLayout->addWidget(adminPassword);
    passwordLayout->addWidget(togglePasswordButton);

    QPushButton *loginButton = new QPushButton("Accedi", loginDialog);
    loginButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #4682B4;"
        "   color: white;"
        "   padding: 10px;"
        "   font-size: 16px;"
        "   border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #5F9EA0;"
        "}"
        );

    dialogLayout->addWidget(adminUsername);
    dialogLayout->addWidget(passwordContainer);
    dialogLayout->addWidget(loginButton);

    // Variabile per tracciare lo stato della visibilità della password
    bool passwordVisible = false;

    // Connessione del pulsante occhio
    connect(togglePasswordButton, &QPushButton::clicked, [=, &passwordVisible]() mutable {
        passwordVisible = !passwordVisible;
        if (passwordVisible) {
            adminPassword->setEchoMode(QLineEdit::Normal);
            togglePasswordButton->setStyleSheet(
                "QPushButton {"
                "   background-color: #D0D0D0;"
                "   border: 1px solid #CCC;"
                "   border-left: none;"
                "   border-top-right-radius: 5px;"
                "   border-bottom-right-radius: 5px;"
                "   padding: 5px;"
                "   width: 40px;"
                "   qproperty-icon: url(:/icons/occhio_icon_open.png);"
                "   qproperty-iconSize: 24px 24px;"
                "}"
                );
        } else {
            adminPassword->setEchoMode(QLineEdit::Password);
            togglePasswordButton->setStyleSheet(
                "QPushButton {"
                "   background-color: #E0E0E0;"
                "   border: 1px solid #CCC;"
                "   border-left: none;"
                "   border-top-right-radius: 5px;"
                "   border-bottom-right-radius: 5px;"
                "   padding: 5px;"
                "   width: 40px;"
                "   qproperty-icon: url(:/icons/occhio_icon.png);"
                "   qproperty-iconSize: 24px 24px;"
                "}"
                );
        }
    });

    // Connessione del pulsante Accedi
    connect(loginButton, &QPushButton::clicked, [=]() {
        if (adminUsername->text() == "admin" && adminPassword->text() == "admin") {
            QMessageBox successBox(this);
            successBox.setWindowTitle("Successo");
            successBox.setText("<b>Accesso come Admin effettuato!</b>");
            successBox.setInformativeText("Ora puoi gestire il sistema.");
            successBox.setIconPixmap(QPixmap(":/icons/success_icon.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            successBox.setStyleSheet(
                "QMessageBox {"
                "   background-color: #F5F5F5;"
                "   font-size: 14px;"
                "}"
                "QMessageBox QLabel {"
                "   color: #2E7D32;"
                "   font-size: 16px;"
                "}"
                "QMessageBox QPushButton {"
                "   background-color: #4CAF50;"
                "   color: white;"
                "   padding: 8px 16px;"
                "   border-radius: 4px;"
                "   min-width: 80px;"
                "}"
                "QMessageBox QPushButton:hover {"
                "   background-color: #388E3C;"
                "}"
                );
            QPushButton *okButton = successBox.addButton("OK", QMessageBox::AcceptRole);
            okButton->setStyleSheet("font-weight: bold;");
            successBox.exec();
            loginDialog->accept();
            stack->setCurrentIndex(2);
        } else {
            QMessageBox errorBox(this);
            errorBox.setWindowTitle("Errore");
            errorBox.setText("<b>Credenziali non valide!</b>");
            errorBox.setInformativeText("Username o password errati. Riprova.");
            errorBox.setIconPixmap(QPixmap(":/icons/error_icon.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            errorBox.setStyleSheet(
                "QMessageBox {"
                "   background-color: #F5F5F5;"
                "   font-size: 14px;"
                "}"
                "QMessageBox QLabel {"
                "   color: #D32F2F;"
                "   font-size: 16px;"
                "}"
                "QMessageBox QPushButton {"
                "   background-color: #D32F2F;"
                "   color: white;"
                "   padding: 8px 16px;"
                "   border-radius: 4px;"
                "   min-width: 80px;"
                "}"
                "QMessageBox QPushButton:hover {"
                "   background-color: #B71C1C;"
                "}"
                );
            QPushButton *okButton = errorBox.addButton("OK", QMessageBox::AcceptRole);
            okButton->setStyleSheet("font-weight: bold;");
            errorBox.exec();
        }
    });

    loginDialog->exec();
}

void MainWindow::handleUserAccess() {
    // Creazione di una messagebox personalizzata per l'utente
    QMessageBox welcomeBox(this);
    welcomeBox.setWindowTitle("Benvenuto");
    welcomeBox.setText("<b>Accesso come Utente effettuato!</b>");
    welcomeBox.setInformativeText("Benvenuto nel sistema.");

    // Icona personalizzata
    welcomeBox.setIconPixmap(QPixmap(":/icons/success_icon.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Stile personalizzato
    welcomeBox.setStyleSheet(
        "QMessageBox {"
        "   background-color: #F5F5F5;"
        "   font-size: 14px;"
        "}"
        "QMessageBox QLabel {"
        "   color: #0277BD;"  // Blu scuro per differenziare dall'admin
        "   font-size: 16px;"
        "}"
        "QMessageBox QPushButton {"
        "   background-color: #0288D1;"  // Blu
        "   color: white;"
        "   padding: 8px 16px;"
        "   border-radius: 4px;"
        "   min-width: 80px;"
        "}"
        "QMessageBox QPushButton:hover {"
        "   background-color: #0277BD;"  // Blu più scuro
        "}"
        );

    // Aggiunta pulsante OK
    QPushButton *okButton = welcomeBox.addButton("OK", QMessageBox::AcceptRole);
    okButton->setStyleSheet("font-weight: bold;");

    welcomeBox.exec();
    stack->setCurrentIndex(1);
}

void MainWindow::confirmClose() {
    QMessageBox confirmBox(this);
    confirmBox.setWindowTitle("Conferma chiusura");
    confirmBox.setText("<b>Vuoi veramente chiudere il programma?</b>");

    confirmBox.setIconPixmap(QPixmap(":/icons/exit_icon.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    confirmBox.setStyleSheet(
        "QMessageBox {"
        "   background-color: #F5F5F5;"
        "   font-size: 14px;"
        "}"
        "QMessageBox QLabel {"
        "   color: #333333;"
        "   font-size: 16px;"
        "}"
        "QMessageBox QPushButton {"
        "   padding: 8px 16px;"
        "   border-radius: 4px;"
        "   min-width: 80px;"
        "}"
        );

    QPushButton *yesButton = confirmBox.addButton("Sì, chiudi", QMessageBox::YesRole);
    QPushButton *noButton = confirmBox.addButton("No, resta", QMessageBox::NoRole);

    yesButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #D32F2F;"  // Rosso
        "   color: white;"
        "}"
        "QPushButton:hover {"
        "   background-color: #B71C1C;"  // Rosso più scuro
        "}"
        );

    noButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #5F9EA0;"  // Blu-verde
        "   color: white;"
        "}"
        "QPushButton:hover {"
        "   background-color: #4682B4;"  // Blu più scuro
        "}"
        );

    confirmBox.exec();

    if (confirmBox.clickedButton() == yesButton) {
        QApplication::quit();
    }
}

void MainWindow::close() {
    confirmClose();

}
