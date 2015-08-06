#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include "modele.h"
#include <QDebug>
#include "widgetajouterutilisateur.h"
#include "widgetmodifierutilisateur.h"
#include "widgetsupprimerutilisateur.h"
#include "widgetmodifierprofesseurtuteur.h"
#include "widgetmodifierprofesseurresp.h"
#include "widgetadmissionanneesup.h"
#include "widgetchoisirmoduleeleve.h"
#include "widgetconnection.h"
#include "widgetid.h"
#include <QTableView>
#include <QMenuBar>
#include <QStatusBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QWidget* createFenetreDonnee(QAction*);
    QWidget* createFenetreOutil(QAction*);

    void reset();

public slots:

    void openFenetreDonnee(QAction*);
    void openFenetreOutil(QAction*);

    void initialiserCoInfo(const QString& host, const QString& user, const QString& password, const QString& dataBase);
    void initialiserModele(int);
    void resetConnection();
    void resetID();

private:

    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    Modele* modele;
    QAction* actionLogin;
    QActionGroup* actionsDonnee;
    QActionGroup* actionsOutil;

    QDockWidget* dockWidgetDonnee;
    QDockWidget* dockWidgetOutil;

    widgetConnection* widgetCo;
    widgetID* widgetIdentification;

    QAction* actionMAJ;

    QString host;
    QString user;
    QString password;
    QString dataBase;
};

#endif // MAINWINDOW_H
