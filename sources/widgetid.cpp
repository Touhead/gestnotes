#include "widgetid.h"


widgetID::widgetID(QWidget *parent) :
    QWidget(parent)
{
    bouton = new QPushButton;
    zonetexte = new QSpinBox;
    zonetexte->setMinimum(20000000);
    zonetexte->setMaximum(29999999);
    layout = new QVBoxLayout;
    this->setWindowTitle("GestNotes Authentification");
    bouton->setText("Connection");
    layout->addWidget(zonetexte);
    layout->addWidget(bouton);
    this->setLayout(layout);

    connect(bouton,SIGNAL(clicked()),this,SLOT(checkId()));
}

void widgetID::setCoInfo(const QString& host, const QString& user, const QString& password, const QString& dataBase){

    this->host = host;
    this->user = user;
    this->password = password;
    this->dataBase = dataBase;
}

void widgetID::ouvrirFenetre(){

    this->show();
}

bool widgetID::checkId()
{
    Bdd* bddauthentification = new Bdd(host,user,password,dataBase,"connectionId");
    bddauthentification->open();
    if (bddauthentification->existe(zonetexte->value())){
        bddauthentification->close();
        delete bddauthentification;
        this->close();
        emit idok(zonetexte->value());
        return true;
    }
    else{
        delete bddauthentification;
        return false;
    }
}
