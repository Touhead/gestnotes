#ifndef WIDGETCONNECTION_H
#define WIDGETCONNECTION_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include "bdd.h"

class widgetConnection : public QWidget
{
    Q_OBJECT
public:
    explicit widgetConnection(QWidget *parent = 0);
    ~widgetConnection();

signals:

    void cook(const QString&, const QString&, const QString&, const QString&);

public slots:

    void ouvrirFenetre();
    bool checkCo();

private:

    QPushButton* bouton;
    QVBoxLayout* layout;

    QLabel* host;
    QLineEdit* getHost;
    QLabel* user;
    QLineEdit* getUser;
    QLabel* password;
    QLineEdit* getPassword;
    QLabel* dataBase;
    QLineEdit* getDataBase;
};

#endif // WIDGETCONNECTION_H
