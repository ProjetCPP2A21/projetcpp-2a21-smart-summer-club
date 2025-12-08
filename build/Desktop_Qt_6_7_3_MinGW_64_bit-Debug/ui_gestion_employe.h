/********************************************************************************
** Form generated from reading UI file 'gestion_employe.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GESTION_EMPLOYE_H
#define UI_GESTION_EMPLOYE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gestion_employe
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget_principale;
    QWidget *page_login;
    QStackedWidget *stackedWidget_login;
    QWidget *page_authentification;
    QWidget *page_mdp_oublie;
    QFrame *frame_12;
    QLineEdit *lineEdit_cin2;
    QLabel *label_cin_8;
    QDateEdit *dateEdit2;
    QLabel *label_embauhe_8;
    QLabel *label_specialite_11;
    QLineEdit *lineEdit_ID2;
    QLabel *label_specialite_12;
    QLineEdit *lineEdit_mdp2;
    QWidget *page_menu;
    QFrame *frame_3;
    QPushButton *pushButton_6;
    QPushButton *pushButton_9;
    QPushButton *pushButton_22;
    QPushButton *pushButton_23;
    QPushButton *pushButton_24;
    QPushButton *pushButton_25;
    QPushButton *pushButton_26;
    QLabel *label_4;
    QLabel *label_5;
    QWidget *page_employe;
    QLabel *label;
    QWidget *Formateur;
    QFrame *frame_9;
    QLabel *label_specialite_7;
    QLineEdit *lineEdit_cin_2;
    QLabel *label_contact_4;
    QLineEdit *lineEdit_num_2;
    QLabel *label_prenom_5;
    QLineEdit *lineEdit_nom_2;
    QLineEdit *lineEdit_prenom_2;
    QPushButton *pushButton_cin_4;
    QLabel *label_cin_6;
    QLabel *label_cin_7;
    QDateEdit *dateEdit_2;
    QLabel *label_embauhe_6;
    QPushButton *btajouter_2;
    QLineEdit *lineEdit_poste_2;
    QLabel *label_specialite_8;
    QLineEdit *lineEdit_ID_2;
    QLabel *label_specialite_9;
    QLineEdit *lineEdit_email_2;
    QLabel *label_specialite_10;
    QLineEdit *lineEdit_mdp_2;
    QPushButton *pushButton_3;
    QFrame *frame_10;
    QLabel *label_embauhe_7;
    QFrame *frame_11;
    QLineEdit *lineEdit_searchEmail_2;
    QPushButton *bmodifier_2;
    QPushButton *btsupprimer_2;
    QLabel *label_3;
    QPushButton *btnStats_2;
    QTableView *tableView_2;
    QFrame *groupBox_stats_2;
    QPushButton *btSearchEmail_2;
    QPushButton *btTriDate_2;
    QPushButton *btnExportPDF_2;
    QPushButton *pushButton_stat_3;
    QPushButton *pushButton_ANNULER_4;
    QFrame *frame_5;
    QFrame *frame_2;
    QPushButton *pushButton_15;
    QPushButton *pushButton_17;
    QPushButton *pushButton_18;
    QPushButton *pushButton_19;
    QPushButton *pushButton_20;
    QPushButton *pushButton_21;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *gestion_employe)
    {
        if (gestion_employe->objectName().isEmpty())
            gestion_employe->setObjectName("gestion_employe");
        gestion_employe->resize(1920, 1080);
        gestion_employe->setStyleSheet(QString::fromUtf8("background-color: rgb(4, 4, 87);"));
        centralwidget = new QWidget(gestion_employe);
        centralwidget->setObjectName("centralwidget");
        stackedWidget_principale = new QStackedWidget(centralwidget);
        stackedWidget_principale->setObjectName("stackedWidget_principale");
        stackedWidget_principale->setGeometry(QRect(-10, -30, 1531, 691));
        page_login = new QWidget();
        page_login->setObjectName("page_login");
        stackedWidget_login = new QStackedWidget(page_login);
        stackedWidget_login->setObjectName("stackedWidget_login");
        stackedWidget_login->setGeometry(QRect(460, 60, 701, 771));
        stackedWidget_login->setStyleSheet(QString::fromUtf8("background-color: rgb(106, 166, 218);\n"
"\n"
"border-radius:30px;"));
        page_authentification = new QWidget();
        page_authentification->setObjectName("page_authentification");
        stackedWidget_login->addWidget(page_authentification);
        page_mdp_oublie = new QWidget();
        page_mdp_oublie->setObjectName("page_mdp_oublie");
        frame_12 = new QFrame(page_mdp_oublie);
        frame_12->setObjectName("frame_12");
        frame_12->setGeometry(QRect(10, 10, 681, 611));
        frame_12->setStyleSheet(QString::fromUtf8("background-color: rgb(58, 196, 255);\n"
"background-color: rgb(83, 130, 171);\n"
"border-radius:20px;\n"
"\n"
""));
        frame_12->setFrameShape(QFrame::Shape::StyledPanel);
        frame_12->setFrameShadow(QFrame::Shadow::Raised);
        lineEdit_cin2 = new QLineEdit(frame_12);
        lineEdit_cin2->setObjectName("lineEdit_cin2");
        lineEdit_cin2->setGeometry(QRect(20, 70, 113, 26));
        lineEdit_cin2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
""));
        lineEdit_cin2->setMaxLength(8);
        label_cin_8 = new QLabel(frame_12);
        label_cin_8->setObjectName("label_cin_8");
        label_cin_8->setGeometry(QRect(20, 40, 31, 20));
        dateEdit2 = new QDateEdit(frame_12);
        dateEdit2->setObjectName("dateEdit2");
        dateEdit2->setGeometry(QRect(20, 150, 121, 21));
        dateEdit2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        label_embauhe_8 = new QLabel(frame_12);
        label_embauhe_8->setObjectName("label_embauhe_8");
        label_embauhe_8->setGeometry(QRect(20, 110, 131, 20));
        label_specialite_11 = new QLabel(frame_12);
        label_specialite_11->setObjectName("label_specialite_11");
        label_specialite_11->setGeometry(QRect(30, 200, 111, 20));
        label_specialite_11->setStyleSheet(QString::fromUtf8("color: rgb(4, 4, 87);"));
        lineEdit_ID2 = new QLineEdit(frame_12);
        lineEdit_ID2->setObjectName("lineEdit_ID2");
        lineEdit_ID2->setGeometry(QRect(20, 230, 121, 26));
        lineEdit_ID2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
""));
        label_specialite_12 = new QLabel(frame_12);
        label_specialite_12->setObjectName("label_specialite_12");
        label_specialite_12->setGeometry(QRect(240, 170, 111, 61));
        label_specialite_12->setStyleSheet(QString::fromUtf8("color: rgb(4, 4, 87);\n"
"font: 24pt \"Segoe UI\";"));
        lineEdit_mdp2 = new QLineEdit(frame_12);
        lineEdit_mdp2->setObjectName("lineEdit_mdp2");
        lineEdit_mdp2->setGeometry(QRect(190, 250, 211, 71));
        lineEdit_mdp2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
""));
        stackedWidget_login->addWidget(page_mdp_oublie);
        stackedWidget_principale->addWidget(page_login);
        page_menu = new QWidget();
        page_menu->setObjectName("page_menu");
        frame_3 = new QFrame(page_menu);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(90, 40, 1061, 631));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 195, 0);\n"
"border-radius: 30px;\n"
"border: 3px solid #040457;"));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        pushButton_6 = new QPushButton(frame_3);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(660, 170, 241, 61));
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_9 = new QPushButton(frame_3);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(660, 240, 241, 61));
        pushButton_9->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_22 = new QPushButton(frame_3);
        pushButton_22->setObjectName("pushButton_22");
        pushButton_22->setGeometry(QRect(660, 380, 241, 61));
        pushButton_22->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_23 = new QPushButton(frame_3);
        pushButton_23->setObjectName("pushButton_23");
        pushButton_23->setGeometry(QRect(660, 100, 241, 61));
        pushButton_23->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_24 = new QPushButton(frame_3);
        pushButton_24->setObjectName("pushButton_24");
        pushButton_24->setGeometry(QRect(660, 450, 241, 61));
        pushButton_24->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_25 = new QPushButton(frame_3);
        pushButton_25->setObjectName("pushButton_25");
        pushButton_25->setGeometry(QRect(660, 310, 241, 61));
        pushButton_25->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_26 = new QPushButton(frame_3);
        pushButton_26->setObjectName("pushButton_26");
        pushButton_26->setGeometry(QRect(1230, 510, 141, 41));
        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(120, 100, 411, 411));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/img/image.png")));
        label_4->setScaledContents(true);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(1000, 580, 41, 31));
        label_5->setStyleSheet(QString::fromUtf8("border :none;"));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/img/reglage.png")));
        label_5->setScaledContents(true);
        stackedWidget_principale->addWidget(page_menu);
        page_employe = new QWidget();
        page_employe->setObjectName("page_employe");
        label = new QLabel(page_employe);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 40, 161, 101));
        label->setPixmap(QPixmap(QString::fromUtf8("../../Images/Captures d\342\200\231\303\251cran/image1.png")));
        label->setScaledContents(true);
        Formateur = new QWidget(page_employe);
        Formateur->setObjectName("Formateur");
        Formateur->setGeometry(QRect(250, 20, 1271, 751));
        Formateur->setMaximumSize(QSize(2000, 2000));
        Formateur->setBaseSize(QSize(1000, 1000));
        Formateur->setMouseTracking(false);
        Formateur->setTabletTracking(false);
        Formateur->setAutoFillBackground(false);
        Formateur->setStyleSheet(QString::fromUtf8("background-color: rgb(106, 166, 218);\n"
"\n"
"border-radius:30px;"));
        frame_9 = new QFrame(Formateur);
        frame_9->setObjectName("frame_9");
        frame_9->setGeometry(QRect(30, 40, 271, 701));
        frame_9->setStyleSheet(QString::fromUtf8("background-color: rgb(58, 196, 255);\n"
"background-color: rgb(83, 130, 171);\n"
"border-radius:20px;\n"
"\n"
""));
        frame_9->setFrameShape(QFrame::Shape::StyledPanel);
        frame_9->setFrameShadow(QFrame::Shadow::Raised);
        label_specialite_7 = new QLabel(frame_9);
        label_specialite_7->setObjectName("label_specialite_7");
        label_specialite_7->setGeometry(QRect(30, 380, 111, 20));
        label_specialite_7->setStyleSheet(QString::fromUtf8("color: rgb(4, 4, 87);"));
        lineEdit_cin_2 = new QLineEdit(frame_9);
        lineEdit_cin_2->setObjectName("lineEdit_cin_2");
        lineEdit_cin_2->setGeometry(QRect(30, 60, 113, 26));
        lineEdit_cin_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
""));
        lineEdit_cin_2->setMaxLength(8);
        label_contact_4 = new QLabel(frame_9);
        label_contact_4->setObjectName("label_contact_4");
        label_contact_4->setGeometry(QRect(30, 240, 63, 20));
        lineEdit_num_2 = new QLineEdit(frame_9);
        lineEdit_num_2->setObjectName("lineEdit_num_2");
        lineEdit_num_2->setGeometry(QRect(30, 270, 113, 26));
        lineEdit_num_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        label_prenom_5 = new QLabel(frame_9);
        label_prenom_5->setObjectName("label_prenom_5");
        label_prenom_5->setGeometry(QRect(30, 180, 63, 20));
        lineEdit_nom_2 = new QLineEdit(frame_9);
        lineEdit_nom_2->setObjectName("lineEdit_nom_2");
        lineEdit_nom_2->setGeometry(QRect(30, 130, 113, 26));
        lineEdit_nom_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        lineEdit_nom_2->setMaxLength(20);
        lineEdit_prenom_2 = new QLineEdit(frame_9);
        lineEdit_prenom_2->setObjectName("lineEdit_prenom_2");
        lineEdit_prenom_2->setGeometry(QRect(30, 200, 113, 26));
        lineEdit_prenom_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        pushButton_cin_4 = new QPushButton(frame_9);
        pushButton_cin_4->setObjectName("pushButton_cin_4");
        pushButton_cin_4->setGeometry(QRect(160, 60, 51, 20));
        pushButton_cin_4->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(162, 162, 162);\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(162, 162, 162);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"\n"
"\n"
""));
        label_cin_6 = new QLabel(frame_9);
        label_cin_6->setObjectName("label_cin_6");
        label_cin_6->setGeometry(QRect(30, 40, 31, 20));
        label_cin_7 = new QLabel(frame_9);
        label_cin_7->setObjectName("label_cin_7");
        label_cin_7->setGeometry(QRect(30, 110, 41, 20));
        dateEdit_2 = new QDateEdit(frame_9);
        dateEdit_2->setObjectName("dateEdit_2");
        dateEdit_2->setGeometry(QRect(30, 340, 121, 21));
        dateEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        label_embauhe_6 = new QLabel(frame_9);
        label_embauhe_6->setObjectName("label_embauhe_6");
        label_embauhe_6->setGeometry(QRect(20, 310, 131, 20));
        btajouter_2 = new QPushButton(frame_9);
        btajouter_2->setObjectName("btajouter_2");
        btajouter_2->setGeometry(QRect(180, 650, 81, 21));
        btajouter_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(162, 162, 162);\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(162, 162, 162);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
""));
        lineEdit_poste_2 = new QLineEdit(frame_9);
        lineEdit_poste_2->setObjectName("lineEdit_poste_2");
        lineEdit_poste_2->setGeometry(QRect(30, 410, 121, 26));
        lineEdit_poste_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
""));
        label_specialite_8 = new QLabel(frame_9);
        label_specialite_8->setObjectName("label_specialite_8");
        label_specialite_8->setGeometry(QRect(30, 450, 111, 20));
        label_specialite_8->setStyleSheet(QString::fromUtf8("color: rgb(4, 4, 87);"));
        lineEdit_ID_2 = new QLineEdit(frame_9);
        lineEdit_ID_2->setObjectName("lineEdit_ID_2");
        lineEdit_ID_2->setGeometry(QRect(30, 480, 121, 26));
        lineEdit_ID_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
""));
        label_specialite_9 = new QLabel(frame_9);
        label_specialite_9->setObjectName("label_specialite_9");
        label_specialite_9->setGeometry(QRect(30, 520, 111, 20));
        label_specialite_9->setStyleSheet(QString::fromUtf8("color: rgb(4, 4, 87);"));
        lineEdit_email_2 = new QLineEdit(frame_9);
        lineEdit_email_2->setObjectName("lineEdit_email_2");
        lineEdit_email_2->setGeometry(QRect(30, 550, 121, 26));
        lineEdit_email_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
""));
        label_specialite_10 = new QLabel(frame_9);
        label_specialite_10->setObjectName("label_specialite_10");
        label_specialite_10->setGeometry(QRect(30, 590, 111, 20));
        label_specialite_10->setStyleSheet(QString::fromUtf8("color: rgb(4, 4, 87);"));
        lineEdit_mdp_2 = new QLineEdit(frame_9);
        lineEdit_mdp_2->setObjectName("lineEdit_mdp_2");
        lineEdit_mdp_2->setGeometry(QRect(30, 620, 121, 26));
        lineEdit_mdp_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
""));
        pushButton_3 = new QPushButton(frame_9);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(170, 580, 93, 29));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(162, 162, 162);\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(162, 162, 162);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
""));
        frame_10 = new QFrame(Formateur);
        frame_10->setObjectName("frame_10");
        frame_10->setGeometry(QRect(30, 10, 211, 41));
        frame_10->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 157, 206);\n"
"border: 3px solid #040457;\n"
"border-radius:20px;"));
        frame_10->setFrameShape(QFrame::Shape::StyledPanel);
        frame_10->setFrameShadow(QFrame::Shadow::Raised);
        label_embauhe_7 = new QLabel(frame_10);
        label_embauhe_7->setObjectName("label_embauhe_7");
        label_embauhe_7->setGeometry(QRect(30, 10, 161, 20));
        label_embauhe_7->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 157, 206);\n"
"border: 2px solid #649dce;\n"
""));
        frame_11 = new QFrame(Formateur);
        frame_11->setObjectName("frame_11");
        frame_11->setGeometry(QRect(300, 40, 1001, 681));
        frame_11->setStyleSheet(QString::fromUtf8("border: 3px solid #040457;\n"
"border-radius:20px;\n"
""));
        frame_11->setFrameShape(QFrame::Shape::StyledPanel);
        frame_11->setFrameShadow(QFrame::Shadow::Raised);
        lineEdit_searchEmail_2 = new QLineEdit(frame_11);
        lineEdit_searchEmail_2->setObjectName("lineEdit_searchEmail_2");
        lineEdit_searchEmail_2->setGeometry(QRect(620, 130, 321, 31));
        lineEdit_searchEmail_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
"border: 3px solid #ffffff;\n"
"color: rgb(162, 162, 162);"));
        bmodifier_2 = new QPushButton(frame_11);
        bmodifier_2->setObjectName("bmodifier_2");
        bmodifier_2->setGeometry(QRect(550, 190, 81, 31));
        bmodifier_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
"border: 3px solid #ffffff;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(220, 220, 220);\n"
"	color: rgb(90, 90, 90);\n"
"\n"
"	border-radius:10px;\n"
"}\n"
""));
        btsupprimer_2 = new QPushButton(frame_11);
        btsupprimer_2->setObjectName("btsupprimer_2");
        btsupprimer_2->setGeometry(QRect(900, 190, 41, 31));
        btsupprimer_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
"border: 3px solid #ffffff;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(220, 220, 220);\n"
"	color: rgb(90, 90, 90);\n"
"\n"
"	border-radius:10px;\n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/poubelle.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btsupprimer_2->setIcon(icon);
        label_3 = new QLabel(frame_11);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(310, 50, 331, 51));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(106, 166, 218);\n"
"color: rgb(83, 130, 171);\n"
"color: rgb(157, 235, 255);\n"
"border: none;\n"
"font: 30pt \"Rockwell\";"));
        btnStats_2 = new QPushButton(frame_11);
        btnStats_2->setObjectName("btnStats_2");
        btnStats_2->setGeometry(QRect(20, 140, 111, 29));
        btnStats_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
"border: 3px solid #ffffff;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(220, 220, 220);\n"
"	color: rgb(90, 90, 90);\n"
"\n"
"	border-radius:10px;\n"
"}\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/stat.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnStats_2->setIcon(icon1);
        tableView_2 = new QTableView(frame_11);
        tableView_2->setObjectName("tableView_2");
        tableView_2->setGeometry(QRect(10, 391, 941, 281));
        groupBox_stats_2 = new QFrame(frame_11);
        groupBox_stats_2->setObjectName("groupBox_stats_2");
        groupBox_stats_2->setGeometry(QRect(10, 190, 441, 191));
        groupBox_stats_2->setFrameShape(QFrame::Shape::StyledPanel);
        groupBox_stats_2->setFrameShadow(QFrame::Shadow::Raised);
        btSearchEmail_2 = new QPushButton(frame_11);
        btSearchEmail_2->setObjectName("btSearchEmail_2");
        btSearchEmail_2->setGeometry(QRect(500, 130, 93, 29));
        btSearchEmail_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
"border: 3px solid #ffffff;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(220, 220, 220);\n"
"	color: rgb(90, 90, 90);\n"
"\n"
"	border-radius:10px;\n"
"}\n"
""));
        btTriDate_2 = new QPushButton(frame_11);
        btTriDate_2->setObjectName("btTriDate_2");
        btTriDate_2->setGeometry(QRect(670, 190, 93, 29));
        btTriDate_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
"border: 3px solid #ffffff;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(220, 220, 220);\n"
"	color: rgb(90, 90, 90);\n"
"\n"
"	border-radius:10px;\n"
"}\n"
""));
        btnExportPDF_2 = new QPushButton(frame_11);
        btnExportPDF_2->setObjectName("btnExportPDF_2");
        btnExportPDF_2->setGeometry(QRect(790, 190, 93, 29));
        btnExportPDF_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
"border: 3px solid #ffffff;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(220, 220, 220);\n"
"	color: rgb(90, 90, 90);\n"
"\n"
"	border-radius:10px;\n"
"}\n"
""));
        pushButton_stat_3 = new QPushButton(frame_11);
        pushButton_stat_3->setObjectName("pushButton_stat_3");
        pushButton_stat_3->setGeometry(QRect(20, 10, 91, 31));
        pushButton_stat_3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
"border: 3px solid #ffffff;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(220, 220, 220);\n"
"	color: rgb(90, 90, 90);\n"
"	border-radius:10px;\n"
"}\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/money.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_stat_3->setIcon(icon2);
        pushButton_ANNULER_4 = new QPushButton(frame_11);
        pushButton_ANNULER_4->setObjectName("pushButton_ANNULER_4");
        pushButton_ANNULER_4->setGeometry(QRect(120, 20, 61, 21));
        pushButton_ANNULER_4->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(162, 162, 162);\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(162, 162, 162);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"\n"
"\n"
""));
        frame_5 = new QFrame(page_employe);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(20, 170, 181, 471));
        frame_5->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(240, 195, 0);\n"
"border-radius:10px;\n"
"border: 2px solid #f0c300;\n"
"background-color: rgb(4, 4, 87);"));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        frame_2 = new QFrame(frame_5);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 10, 161, 451));
        frame_2->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(240, 195, 0);\n"
"border-radius:10px;"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        pushButton_15 = new QPushButton(frame_2);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setGeometry(QRect(30, 160, 101, 29));
        pushButton_15->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	font: 700 9pt \"Rockwell\";\n"
"background-color: rgb(255, 255, 255);\n"
"	color: rgb(4, 4, 87);\n"
"	border-radius:10px;\n"
"	font: 700 8pt \"Rockwell\";\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(236, 236, 236);\n"
"	color: #000000;\n"
"	border: 1px solid #ffffff;\n"
"	border-radius:5px;\n"
"}"));
        pushButton_17 = new QPushButton(frame_2);
        pushButton_17->setObjectName("pushButton_17");
        pushButton_17->setGeometry(QRect(30, 220, 101, 29));
        pushButton_17->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	font: 700 9pt \"Rockwell\";\n"
"background-color: rgb(255, 255, 255);\n"
"	color: rgb(4, 4, 87);\n"
"	border-radius:10px;\n"
"	font: 700 8pt \"Rockwell\";\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(236, 236, 236);\n"
"	color: #000000;\n"
"	border: 1px solid #ffffff;\n"
"	border-radius:5px;\n"
"}"));
        pushButton_18 = new QPushButton(frame_2);
        pushButton_18->setObjectName("pushButton_18");
        pushButton_18->setGeometry(QRect(30, 340, 101, 29));
        pushButton_18->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	font: 700 9pt \"Rockwell\";\n"
"background-color: rgb(255, 255, 255);\n"
"	color: rgb(4, 4, 87);\n"
"	border-radius:10px;\n"
"	font: 700 8pt \"Rockwell\";\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(236, 236, 236);\n"
"	color: #000000;\n"
"	border: 1px solid #ffffff;\n"
"	border-radius:5px;\n"
"}"));
        pushButton_19 = new QPushButton(frame_2);
        pushButton_19->setObjectName("pushButton_19");
        pushButton_19->setGeometry(QRect(30, 280, 101, 29));
        pushButton_19->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	font: 700 9pt \"Rockwell\";\n"
"background-color: rgb(255, 255, 255);\n"
"	color: rgb(4, 4, 87);\n"
"	border-radius:10px;\n"
"	font: 700 8pt \"Rockwell\";\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(236, 236, 236);\n"
"	color: #000000;\n"
"	border: 1px solid #ffffff;\n"
"	border-radius:5px;\n"
"}"));
        pushButton_20 = new QPushButton(frame_2);
        pushButton_20->setObjectName("pushButton_20");
        pushButton_20->setGeometry(QRect(30, 100, 101, 29));
        pushButton_20->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"\n"
"	font: 700 9pt \"Rockwell\";\n"
"background-color: rgb(255, 255, 255);\n"
"	color: rgb(4, 4, 87);\n"
"	border-radius:10px;\n"
"	font: 700 8pt \"Rockwell\";\n"
"}\n"
"QPushButton:hover{\n"
"	background-color: rgb(233, 233, 233);\n"
"	color: #000000;\n"
"	border: 1px solid #ffffff;\n"
"	border-radius:5px;\n"
"}"));
        pushButton_21 = new QPushButton(frame_2);
        pushButton_21->setObjectName("pushButton_21");
        pushButton_21->setGeometry(QRect(-10, 30, 181, 41));
        pushButton_21->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
"border: 2px solid #fff957;\n"
"	color: rgb(4, 4, 87);\n"
"	font: 700 8pt \"Rockwell\";\n"
"\n"
""));
        stackedWidget_principale->addWidget(page_employe);
        gestion_employe->setCentralWidget(centralwidget);
        menubar = new QMenuBar(gestion_employe);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1920, 26));
        gestion_employe->setMenuBar(menubar);
        statusbar = new QStatusBar(gestion_employe);
        statusbar->setObjectName("statusbar");
        gestion_employe->setStatusBar(statusbar);

        retranslateUi(gestion_employe);

        stackedWidget_login->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(gestion_employe);
    } // setupUi

    void retranslateUi(QMainWindow *gestion_employe)
    {
        gestion_employe->setWindowTitle(QCoreApplication::translate("gestion_employe", "MainWindow", nullptr));
        label_cin_8->setText(QCoreApplication::translate("gestion_employe", "CIN :", nullptr));
        label_embauhe_8->setText(QCoreApplication::translate("gestion_employe", "Date d'embauche :", nullptr));
        label_specialite_11->setText(QCoreApplication::translate("gestion_employe", "id :", nullptr));
        lineEdit_ID2->setText(QString());
        label_specialite_12->setText(QCoreApplication::translate("gestion_employe", "mdp :", nullptr));
        lineEdit_mdp2->setText(QString());
        pushButton_6->setText(QCoreApplication::translate("gestion_employe", "Gestion des formateurs", nullptr));
        pushButton_9->setText(QCoreApplication::translate("gestion_employe", "Gestion des formations", nullptr));
        pushButton_22->setText(QCoreApplication::translate("gestion_employe", "Gestion des equipements", nullptr));
        pushButton_23->setText(QCoreApplication::translate("gestion_employe", "Gestion des employ\303\251s ", nullptr));
        pushButton_24->setText(QCoreApplication::translate("gestion_employe", "Services", nullptr));
        pushButton_25->setText(QCoreApplication::translate("gestion_employe", "Gestion des apprenants", nullptr));
        pushButton_26->setText(QCoreApplication::translate("gestion_employe", "Reglage", nullptr));
        label_4->setText(QString());
        label_5->setText(QString());
        label->setText(QString());
        label_specialite_7->setText(QCoreApplication::translate("gestion_employe", "poste :", nullptr));
        label_contact_4->setText(QCoreApplication::translate("gestion_employe", "num :", nullptr));
        label_prenom_5->setText(QCoreApplication::translate("gestion_employe", "Pr\303\251nom :", nullptr));
        pushButton_cin_4->setText(QCoreApplication::translate("gestion_employe", "Valider", nullptr));
        label_cin_6->setText(QCoreApplication::translate("gestion_employe", "CIN :", nullptr));
        label_cin_7->setText(QCoreApplication::translate("gestion_employe", " Nom :", nullptr));
        label_embauhe_6->setText(QCoreApplication::translate("gestion_employe", "Date d'embauche :", nullptr));
        btajouter_2->setText(QCoreApplication::translate("gestion_employe", "Ajouter", nullptr));
        lineEdit_poste_2->setText(QString());
        label_specialite_8->setText(QCoreApplication::translate("gestion_employe", "id :", nullptr));
        lineEdit_ID_2->setText(QString());
        label_specialite_9->setText(QCoreApplication::translate("gestion_employe", "e-mai :l", nullptr));
        lineEdit_email_2->setText(QString());
        label_specialite_10->setText(QCoreApplication::translate("gestion_employe", "mdp :", nullptr));
        lineEdit_mdp_2->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("gestion_employe", "mdp oublie", nullptr));
        label_embauhe_7->setText(QCoreApplication::translate("gestion_employe", "Ajouter un employe", nullptr));
        lineEdit_searchEmail_2->setText(QString());
        bmodifier_2->setText(QCoreApplication::translate("gestion_employe", "Modifier", nullptr));
        btsupprimer_2->setText(QString());
        label_3->setText(QCoreApplication::translate("gestion_employe", "EMPLOYE", nullptr));
        btnStats_2->setText(QCoreApplication::translate("gestion_employe", " Statistiques", nullptr));
        btSearchEmail_2->setText(QCoreApplication::translate("gestion_employe", "rechercher", nullptr));
        btTriDate_2->setText(QCoreApplication::translate("gestion_employe", "tri", nullptr));
        btnExportPDF_2->setText(QCoreApplication::translate("gestion_employe", "pdf", nullptr));
        pushButton_stat_3->setText(QCoreApplication::translate("gestion_employe", " Rapport", nullptr));
        pushButton_ANNULER_4->setText(QCoreApplication::translate("gestion_employe", "Annuler", nullptr));
        pushButton_15->setText(QCoreApplication::translate("gestion_employe", "Formations", nullptr));
        pushButton_17->setText(QCoreApplication::translate("gestion_employe", "Equipement", nullptr));
        pushButton_18->setText(QCoreApplication::translate("gestion_employe", "Services", nullptr));
        pushButton_19->setText(QCoreApplication::translate("gestion_employe", "Apprenant", nullptr));
        pushButton_20->setText(QCoreApplication::translate("gestion_employe", "Formateurs", nullptr));
        pushButton_21->setText(QCoreApplication::translate("gestion_employe", "Employ\303\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gestion_employe: public Ui_gestion_employe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GESTION_EMPLOYE_H
