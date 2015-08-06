#include "widgetconnection.h"

widgetConnection::widgetConnection(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout;
    this->setWindowTitle("GestNotes Authentification");

    host = new QLabel("Host*");
    getHost = new QLineEdit;
    user = new QLabel("User*");
    getUser = new QLineEdit;
    password = new QLabel("Password*");
    getPassword = new QLineEdit;
    getPassword->setEchoMode(QLineEdit::Password);
    dataBase = new QLabel("DataBase*");
    getDataBase = new QLineEdit;
    bouton = new QPushButton;

    bouton->setText("Data Base Connection");
    layout->addWidget(host);
    layout->addWidget(getHost);
    layout->addWidget(user);
    layout->addWidget(getUser);
    layout->addWidget(password);
    layout->addWidget(getPassword);
    layout->addWidget(dataBase);
    layout->addWidget(getDataBase);
    layout->addWidget(bouton);
    this->setLayout(layout);

    connect(bouton,SIGNAL(clicked()),this,SLOT(checkCo()));
}

widgetConnection::~widgetConnection()
{

}

void widgetConnection::ouvrirFenetre(){

    this->show();
}

bool  widgetConnection::checkCo()
{
    Bdd* bddco = new Bdd(getHost->text(),getUser->text(),getPassword->text(),getDataBase->text(),"connectionCo");
    if (bddco->open()){
        bddco->close();
        delete bddco;
        this->close();
        emit cook(getHost->text(),getUser->text(),getPassword->text(),getDataBase->text());
        return true;
    }
    else{
        QMessageBox::information(this, "Connection Failed", "Connection to this database has failed", QMessageBox::Close);
        delete bddco;
        return false;
    }
}
