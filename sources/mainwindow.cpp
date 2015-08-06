#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName("MainWindow");
    this->resize(732, 552);
    centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");
    this->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(this);
    menuBar->setObjectName("menuBar");
    menuBar->setGeometry(QRect(0, 0, 732, 21));
    this->setMenuBar(menuBar);
    mainToolBar = new QToolBar(this);
    mainToolBar->setObjectName("mainToolBar");
    this->addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(this);
    statusBar->setObjectName("statusBar");
    this->setStatusBar(statusBar);

    widgetCo = new widgetConnection();
    widgetIdentification = new widgetID();
    modele = 0;
    dockWidgetDonnee = 0;
    actionsDonnee = new QActionGroup(this);
    dockWidgetOutil = 0;
    actionsOutil = new QActionGroup(this);


    QMenu* menuFichier = menuBar->addMenu(tr("Fichier"));
    QMenu* menuEdition = menuBar->addMenu(tr("Edition"));

    QAction* actionConnection = menuFichier->addAction(tr("Connection"));
    actionConnection->setShortcut(QKeySequence(tr("Ctrl+C")));

    actionLogin = menuFichier->addAction(tr("Login"));
    actionLogin->setShortcut(QKeySequence(tr("Ctrl+L")));
    actionLogin->setEnabled(false);

    QAction* actionQuitter = menuFichier->addAction(tr("Quitter"));
    actionQuitter->setShortcut(QKeySequence(tr("Ctrl+Q")));

    actionMAJ = menuEdition->addAction(tr("Mettre à jour"));
    actionMAJ->setShortcut(QKeySequence(tr("Ctrl+M")));

    QToolBar* toolBarFichier = addToolBar(tr("Fichier"));
    toolBarFichier->addAction(actionConnection);
    toolBarFichier->addAction(actionLogin);

    QToolBar* toolBarEdition = addToolBar(tr("Edition"));
    toolBarEdition->addAction(actionMAJ);

    connect(widgetIdentification,SIGNAL(idok(int)),this,SLOT(initialiserModele(int)));
    connect(widgetCo,SIGNAL(cook(const QString&, const QString&, const QString&, const QString&)),this,SLOT(initialiserCoInfo(const QString&, const QString&, const QString&, const QString&)));
    connect(actionConnection,SIGNAL(triggered()),this,SLOT(resetConnection()));
    connect(actionLogin,SIGNAL(triggered()),this,SLOT(resetID()));
    connect(actionQuitter,SIGNAL(triggered()),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
}

QWidget* MainWindow::createFenetreDonnee(QAction* action){

    QWidget* fenetre = new QWidget;
        QGridLayout* layout = new QGridLayout;
            QTableView* view = new QTableView;
            view->setModel(modele->getModele(action));
            view->sortByColumn(0,Qt::AscendingOrder);
            view->setSortingEnabled(true);
            view->hideColumn(0);
        layout->addWidget(view,0,0,1,1);
    fenetre->setLayout(layout);

    return fenetre;
}

QWidget* MainWindow::createFenetreOutil(QAction* action){

    return modele->getFenetre(action);
}

void MainWindow::openFenetreDonnee(QAction* action){

    this->setCentralWidget(createFenetreDonnee(action));
}

void MainWindow::openFenetreOutil(QAction* action){


    /*QWidget* fenetre = createFenetreOutil(action);
    fenetre->show();*/

    QWidget* fenetre;

    if (action->parent()->objectName() == "edition") {

        if (action->objectName() == "ajouterUtilisateurs")
            fenetre = new WidgetAjouterUtilisateur(modele);

        if (action->objectName() == "modifierUtilisateurs")
            fenetre = new WidgetModifierUtilisateur(modele);

        if (action->objectName() == "supprimerUtilisateurs")
            fenetre = new WidgetSupprimerUtilisateur(modele);

        if (action->objectName() == "modifierProfesseurTuteur")
            fenetre = new WidgetModifierProfesseurTuteur(modele);

        if (action->objectName() == "modifierProfesseurResp")
            fenetre = new WidgetModifierProfesseurResp(modele);

        if (action->objectName() == "admissionAnneeSup")
            fenetre = new WidgetAdmissionAnneeSup(modele);

        if (action->objectName() == "choisirModuleOpt")
            fenetre = new WidgetChoisirModuleEleve(modele);
    }

    fenetre->show();
}

void MainWindow::initialiserCoInfo(const QString& host, const QString& user, const QString& password, const QString& dataBase){

    this->host = host;
    this->user = user;
    this->password = password;
    this->dataBase = dataBase;
    widgetIdentification->setCoInfo(host,user,password,dataBase);
    actionLogin->setEnabled(true);
}

void MainWindow::initialiserModele(int id)
{
    modele = new Modele(host,user,password,dataBase,id);

    dockWidgetDonnee = new QDockWidget;

    actionsDonnee = new QActionGroup(dockWidgetDonnee);
    actionsDonnee->setExclusive(false);
    modele->createDockDonnee(dockWidgetDonnee,actionsDonnee);
    addDockWidget(Qt::LeftDockWidgetArea,dockWidgetDonnee);

    dockWidgetOutil = new QDockWidget;

    actionsOutil = new QActionGroup(dockWidgetOutil);
    actionsOutil->setExclusive(false);
    modele->createDockOutil(dockWidgetOutil,actionsOutil);
    addDockWidget(Qt::RightDockWidgetArea,dockWidgetOutil);

    connect(actionsDonnee,SIGNAL(triggered(QAction*)),this,SLOT(openFenetreDonnee(QAction*)));
    connect(actionsOutil,SIGNAL(triggered(QAction*)),this,SLOT(openFenetreOutil(QAction*)));
    connect(actionMAJ,SIGNAL(triggered()),modele,SLOT(mettreAJour()));
}

void MainWindow::resetConnection(){

    actionLogin->setEnabled(false);

    reset();

    widgetCo->ouvrirFenetre();
}

void MainWindow::resetID(){

    reset();

    widgetIdentification->ouvrirFenetre();
}

void MainWindow::reset(){

    if (modele != 0){
        disconnect(actionMAJ,SIGNAL(triggered()),modele,SLOT(mettreAJour()));
        delete modele;
        modele = 0;
    }

    if (dockWidgetDonnee != 0){
        removeDockWidget(dockWidgetDonnee);
        delete dockWidgetDonnee;
        dockWidgetDonnee = 0;
    }

    if (dockWidgetOutil != 0){
        removeDockWidget(dockWidgetOutil);
        delete dockWidgetOutil;
        dockWidgetOutil = 0;
    }
}
