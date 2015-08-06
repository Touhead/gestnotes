#include "mainwindow.h"
#include <QTextCodec>
#include <QApplication>
#include "bdd.h"
#include "bdd.t.h"
#include <QDebug>
#include <QHash>
#include <QTableView>
#include <QGridLayout>
#include <eleve.h>
#include <professeur.h>
#include <personne.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
