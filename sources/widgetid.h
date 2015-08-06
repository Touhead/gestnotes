#ifndef WIDGETID_H
#define WIDGETID_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QSpinBox>
#include "bdd.h"

class widgetID : public QWidget
{
    Q_OBJECT
public:
    widgetID(QWidget *parent = 0);

    void setCoInfo(const QString& host, const QString& user, const QString& password, const QString& dataBase);

signals:

    void idok(int);

public slots:

    bool checkId();
    void ouvrirFenetre();

private:

    QPushButton* bouton;
    QSpinBox* zonetexte;
    QVBoxLayout* layout;

    QString host;
    QString user;
    QString password;
    QString dataBase;
};

#endif // WIDGETID_H
