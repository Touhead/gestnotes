#-------------------------------------------------
#
# Project created by QtCreator 2014-04-24T17:42:31
#
#-------------------------------------------------

QT       += core gui\
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gestnotes
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bdd.cpp \
    modele.cpp \
    eleve.cpp \
    personne.cpp \
    professeur.cpp \
    administration.cpp \
    modelnotemodule.cpp \
    sqlquerymodeloptimized.cpp \
    widgetajouterutilisateur.cpp \
    widgetmodifierutilisateur.cpp \
    widgetsupprimerutilisateur.cpp \
    widgetmodifierprofesseurtuteur.cpp \
    widgetmodifierprofesseurresp.cpp \
    widgetadmissionanneesup.cpp \
    widgetchoisirmoduleeleve.cpp \
    widgetid.cpp \
    modelemodule.cpp \
    widgetconnection.cpp

HEADERS  += mainwindow.h \
    bdd.h \
    bdd.t.h \
    modele.h \
    eleve.h \
    personne.h \
    professeur.h \
    administration.h \
    modelnotemodule.h \
    sqlquerymodeloptimized.h \
    widgetajouterutilisateur.h \
    widgetmodifierutilisateur.h \
    widgetsupprimerutilisateur.h \
    widgetmodifierprofesseurtuteur.h \
    widgetmodifierprofesseurresp.h \
    widgetadmissionanneesup.h \
    widgetchoisirmoduleeleve.h \
    widgetid.h \
    modelemodule.h \
    widgetconnection.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -llibmysql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -llibmysqld
unix:!macx: LIBS += -L$$PWD/lib/ -lqsqlmysql

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
