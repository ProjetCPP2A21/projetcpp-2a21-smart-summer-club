/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_menu
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *menu)
    {
        if (menu->objectName().isEmpty())
            menu->setObjectName("menu");
        menu->resize(1920, 1080);
        menu->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 195, 0);"));
        centralwidget = new QWidget(menu);
        centralwidget->setObjectName("centralwidget");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(90, 70, 1061, 631));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 195, 0);\n"
"border-radius: 30px;\n"
"border: 3px solid #040457;"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(660, 170, 241, 61));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border: 3px solid #040457;\n"
"background-color: rgb(255, 255, 153);\n"
"	color: rgb(4, 4, 87);\n"
"border-radius: 20px;\n"
"	font: 700 9pt \"Rockwell\";\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	border: 3px solid #ffffff;\n"
"	border-radius:10px;\n"
"}"));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(660, 240, 241, 61));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border: 3px solid #040457;\n"
"background-color: rgb(255, 255, 153);\n"
"	color: rgb(4, 4, 87);\n"
"border-radius: 20px;\n"
"	font: 700 9pt \"Rockwell\";\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	border: 3px solid #ffffff;\n"
"	border-radius:10px;\n"
"}"));
        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(660, 380, 241, 61));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border: 3px solid #040457;\n"
"background-color: rgb(255, 255, 153);\n"
"	color: rgb(4, 4, 87);\n"
"border-radius: 20px;\n"
"	font: 700 9pt \"Rockwell\";\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	border: 3px solid #ffffff;\n"
"	border-radius:10px;\n"
"}"));
        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(660, 100, 241, 61));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border: 3px solid #040457;\n"
"background-color: rgb(255, 255, 153);\n"
"	color: rgb(4, 4, 87);\n"
"border-radius: 20px;\n"
"	font: 700 9pt \"Rockwell\";\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	border: 3px solid #ffffff;\n"
"	border-radius:10px;\n"
"}"));
        pushButton_5 = new QPushButton(frame);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(660, 450, 241, 61));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border: 3px solid #040457;\n"
"background-color: rgb(255, 255, 153);\n"
"	color: rgb(4, 4, 87);\n"
"border-radius: 20px;\n"
"	font: 700 9pt \"Rockwell\";\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	border: 3px solid #ffffff;\n"
"	border-radius:10px;\n"
"}"));
        pushButton_7 = new QPushButton(frame);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(660, 310, 241, 61));
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border: 3px solid #040457;\n"
"background-color: rgb(255, 255, 153);\n"
"	color: rgb(4, 4, 87);\n"
"border-radius: 20px;\n"
"	font: 700 9pt \"Rockwell\";\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	border: 3px solid #ffffff;\n"
"	border-radius:10px;\n"
"}"));
        pushButton_8 = new QPushButton(frame);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(1230, 510, 141, 41));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(120, 100, 411, 411));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/image.png")));
        label->setScaledContents(true);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(1000, 580, 41, 31));
        label_2->setStyleSheet(QString::fromUtf8("border :none;"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/img/reglage.png")));
        label_2->setScaledContents(true);
        menu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(menu);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1920, 26));
        menu->setMenuBar(menubar);
        statusbar = new QStatusBar(menu);
        statusbar->setObjectName("statusbar");
        menu->setStatusBar(statusbar);

        retranslateUi(menu);

        QMetaObject::connectSlotsByName(menu);
    } // setupUi

    void retranslateUi(QMainWindow *menu)
    {
        menu->setWindowTitle(QCoreApplication::translate("menu", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("menu", "Gestion des formateurs", nullptr));
        pushButton_2->setText(QCoreApplication::translate("menu", "Gestion des formations", nullptr));
        pushButton_3->setText(QCoreApplication::translate("menu", "Gestion des equipements", nullptr));
        pushButton_4->setText(QCoreApplication::translate("menu", "Gestion des employ\303\251s ", nullptr));
        pushButton_5->setText(QCoreApplication::translate("menu", "Services", nullptr));
        pushButton_7->setText(QCoreApplication::translate("menu", "Gestion des apprenants", nullptr));
        pushButton_8->setText(QCoreApplication::translate("menu", "Reglage", nullptr));
        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class menu: public Ui_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
