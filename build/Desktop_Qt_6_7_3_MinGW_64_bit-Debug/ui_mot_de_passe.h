/********************************************************************************
** Form generated from reading UI file 'mot_de_passe.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOT_DE_PASSE_H
#define UI_MOT_DE_PASSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mot_de_passe
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mot_de_passe)
    {
        if (mot_de_passe->objectName().isEmpty())
            mot_de_passe->setObjectName("mot_de_passe");
        mot_de_passe->resize(800, 600);
        centralwidget = new QWidget(mot_de_passe);
        centralwidget->setObjectName("centralwidget");
        mot_de_passe->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mot_de_passe);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        mot_de_passe->setMenuBar(menubar);
        statusbar = new QStatusBar(mot_de_passe);
        statusbar->setObjectName("statusbar");
        mot_de_passe->setStatusBar(statusbar);

        retranslateUi(mot_de_passe);

        QMetaObject::connectSlotsByName(mot_de_passe);
    } // setupUi

    void retranslateUi(QMainWindow *mot_de_passe)
    {
        mot_de_passe->setWindowTitle(QCoreApplication::translate("mot_de_passe", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mot_de_passe: public Ui_mot_de_passe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOT_DE_PASSE_H
