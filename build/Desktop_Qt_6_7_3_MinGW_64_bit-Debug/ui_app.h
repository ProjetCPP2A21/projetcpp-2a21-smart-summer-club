/********************************************************************************
** Form generated from reading UI file 'app.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APP_H
#define UI_APP_H

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

class Ui_app
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
    QLabel *label_2;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *app)
    {
        if (app->objectName().isEmpty())
            app->setObjectName("app");
        app->resize(1365, 982);
        centralwidget = new QWidget(app);
        centralwidget->setObjectName("centralwidget");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(100, 100, 1061, 631));
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
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(1000, 580, 41, 31));
        label_2->setStyleSheet(QString::fromUtf8("border :none;"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/img/reglage.png")));
        label_2->setScaledContents(true);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(140, 130, 381, 361));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/image.png")));
        label->setScaledContents(true);
        app->setCentralWidget(centralwidget);
        menubar = new QMenuBar(app);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1365, 25));
        app->setMenuBar(menubar);
        statusbar = new QStatusBar(app);
        statusbar->setObjectName("statusbar");
        app->setStatusBar(statusbar);

        retranslateUi(app);

        QMetaObject::connectSlotsByName(app);
    } // setupUi

    void retranslateUi(QMainWindow *app)
    {
        app->setWindowTitle(QCoreApplication::translate("app", "app", nullptr));
        pushButton->setText(QCoreApplication::translate("app", "Gestion des formateurs", nullptr));
        pushButton_2->setText(QCoreApplication::translate("app", "Gestion des formations", nullptr));
        pushButton_3->setText(QCoreApplication::translate("app", "Gestion des equipements", nullptr));
        pushButton_4->setText(QCoreApplication::translate("app", "Gestion des employ\303\251s ", nullptr));
        pushButton_5->setText(QCoreApplication::translate("app", "Services", nullptr));
        pushButton_7->setText(QCoreApplication::translate("app", "Gestion des apprenants", nullptr));
        pushButton_8->setText(QCoreApplication::translate("app", "Reglage", nullptr));
        label_2->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class app: public Ui_app {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP_H
