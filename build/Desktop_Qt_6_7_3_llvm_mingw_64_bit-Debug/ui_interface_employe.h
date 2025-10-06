/********************************************************************************
** Form generated from reading UI file 'interface_employe.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_EMPLOYE_H
#define UI_INTERFACE_EMPLOYE_H

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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Interface_employe
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QWidget *Formateur;
    QFrame *frame_15;
    QLineEdit *lineEdit_cin_6;
    QLabel *label_contact_6;
    QLineEdit *lineEdit_contact_6;
    QLabel *label_prenom_10;
    QLineEdit *lineEdit_nom_6;
    QLineEdit *lineEdit_prenom_6;
    QPushButton *pushButton_cin_6;
    QLabel *label_cin_10;
    QLabel *label_cin_11;
    QDateEdit *dateEdit_embauche_6;
    QLabel *label_embauhe_10;
    QPushButton *pushButton_ANNULER_6;
    QPushButton *pushButton_AJOUTER_6;
    QStackedWidget *stackedWidget_4;
    QWidget *page_7;
    QWidget *page_8;
    QLineEdit *lineEdit_prenom_11;
    QLabel *label_prenom_11;
    QLabel *label_prenom_16;
    QLineEdit *lineEdit_prenom_14;
    QLineEdit *lineEdit_prenom_15;
    QLabel *label_prenom_17;
    QLabel *label_contact_7;
    QLineEdit *lineEdit_contact_9;
    QFrame *frame_16;
    QLabel *label_embauhe_11;
    QFrame *frame_17;
    QTableWidget *tableau_liste_5;
    QLineEdit *lineEdit_RECHERCHE_5;
    QPushButton *pushButton_37;
    QPushButton *pushButton_38;
    QPushButton *pushButton_39;
    QPushButton *pushButton_40;
    QLabel *label_5;
    QPushButton *pushButton_stat_2;
    QPushButton *pushButton_41;
    QFrame *frame;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_16;
    QPushButton *pushButton_10;
    QFrame *frame_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Interface_employe)
    {
        if (Interface_employe->objectName().isEmpty())
            Interface_employe->setObjectName("Interface_employe");
        Interface_employe->resize(1920, 1080);
        Interface_employe->setStyleSheet(QString::fromUtf8("background-color: rgb(4, 4, 87);"));
        centralwidget = new QWidget(Interface_employe);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 10, 111, 101));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/image.png")));
        label->setScaledContents(true);
        Formateur = new QWidget(centralwidget);
        Formateur->setObjectName("Formateur");
        Formateur->setGeometry(QRect(230, 30, 1271, 751));
        Formateur->setMaximumSize(QSize(2000, 2000));
        Formateur->setBaseSize(QSize(1000, 1000));
        Formateur->setMouseTracking(false);
        Formateur->setTabletTracking(false);
        Formateur->setAutoFillBackground(false);
        Formateur->setStyleSheet(QString::fromUtf8("background-color: rgb(106, 166, 218);\n"
"\n"
"border-radius:30px;"));
        frame_15 = new QFrame(Formateur);
        frame_15->setObjectName("frame_15");
        frame_15->setGeometry(QRect(40, 40, 271, 701));
        frame_15->setStyleSheet(QString::fromUtf8("background-color: rgb(58, 196, 255);\n"
"background-color: rgb(83, 130, 171);\n"
"border-radius:20px;\n"
"\n"
""));
        frame_15->setFrameShape(QFrame::Shape::StyledPanel);
        frame_15->setFrameShadow(QFrame::Shadow::Raised);
        lineEdit_cin_6 = new QLineEdit(frame_15);
        lineEdit_cin_6->setObjectName("lineEdit_cin_6");
        lineEdit_cin_6->setGeometry(QRect(30, 60, 113, 26));
        lineEdit_cin_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
""));
        lineEdit_cin_6->setMaxLength(8);
        label_contact_6 = new QLabel(frame_15);
        label_contact_6->setObjectName("label_contact_6");
        label_contact_6->setGeometry(QRect(30, 510, 63, 20));
        lineEdit_contact_6 = new QLineEdit(frame_15);
        lineEdit_contact_6->setObjectName("lineEdit_contact_6");
        lineEdit_contact_6->setGeometry(QRect(30, 530, 113, 26));
        lineEdit_contact_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        label_prenom_10 = new QLabel(frame_15);
        label_prenom_10->setObjectName("label_prenom_10");
        label_prenom_10->setGeometry(QRect(30, 180, 63, 20));
        lineEdit_nom_6 = new QLineEdit(frame_15);
        lineEdit_nom_6->setObjectName("lineEdit_nom_6");
        lineEdit_nom_6->setGeometry(QRect(30, 130, 113, 26));
        lineEdit_nom_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        lineEdit_nom_6->setMaxLength(20);
        lineEdit_prenom_6 = new QLineEdit(frame_15);
        lineEdit_prenom_6->setObjectName("lineEdit_prenom_6");
        lineEdit_prenom_6->setGeometry(QRect(30, 200, 113, 26));
        lineEdit_prenom_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        pushButton_cin_6 = new QPushButton(frame_15);
        pushButton_cin_6->setObjectName("pushButton_cin_6");
        pushButton_cin_6->setGeometry(QRect(160, 60, 51, 20));
        pushButton_cin_6->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        label_cin_10 = new QLabel(frame_15);
        label_cin_10->setObjectName("label_cin_10");
        label_cin_10->setGeometry(QRect(30, 40, 101, 20));
        label_cin_11 = new QLabel(frame_15);
        label_cin_11->setObjectName("label_cin_11");
        label_cin_11->setGeometry(QRect(30, 110, 41, 20));
        dateEdit_embauche_6 = new QDateEdit(frame_15);
        dateEdit_embauche_6->setObjectName("dateEdit_embauche_6");
        dateEdit_embauche_6->setGeometry(QRect(30, 600, 121, 21));
        dateEdit_embauche_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        label_embauhe_10 = new QLabel(frame_15);
        label_embauhe_10->setObjectName("label_embauhe_10");
        label_embauhe_10->setGeometry(QRect(30, 580, 131, 20));
        pushButton_ANNULER_6 = new QPushButton(frame_15);
        pushButton_ANNULER_6->setObjectName("pushButton_ANNULER_6");
        pushButton_ANNULER_6->setGeometry(QRect(200, 670, 61, 21));
        pushButton_ANNULER_6->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_AJOUTER_6 = new QPushButton(frame_15);
        pushButton_AJOUTER_6->setObjectName("pushButton_AJOUTER_6");
        pushButton_AJOUTER_6->setGeometry(QRect(200, 640, 61, 21));
        pushButton_AJOUTER_6->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        stackedWidget_4 = new QStackedWidget(frame_15);
        stackedWidget_4->setObjectName("stackedWidget_4");
        stackedWidget_4->setGeometry(QRect(230, 120, 120, 80));
        page_7 = new QWidget();
        page_7->setObjectName("page_7");
        stackedWidget_4->addWidget(page_7);
        page_8 = new QWidget();
        page_8->setObjectName("page_8");
        stackedWidget_4->addWidget(page_8);
        lineEdit_prenom_11 = new QLineEdit(frame_15);
        lineEdit_prenom_11->setObjectName("lineEdit_prenom_11");
        lineEdit_prenom_11->setGeometry(QRect(30, 270, 113, 26));
        lineEdit_prenom_11->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        label_prenom_11 = new QLabel(frame_15);
        label_prenom_11->setObjectName("label_prenom_11");
        label_prenom_11->setGeometry(QRect(30, 250, 111, 20));
        label_prenom_16 = new QLabel(frame_15);
        label_prenom_16->setObjectName("label_prenom_16");
        label_prenom_16->setGeometry(QRect(30, 390, 111, 20));
        lineEdit_prenom_14 = new QLineEdit(frame_15);
        lineEdit_prenom_14->setObjectName("lineEdit_prenom_14");
        lineEdit_prenom_14->setGeometry(QRect(30, 410, 113, 26));
        lineEdit_prenom_14->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        lineEdit_prenom_15 = new QLineEdit(frame_15);
        lineEdit_prenom_15->setObjectName("lineEdit_prenom_15");
        lineEdit_prenom_15->setGeometry(QRect(30, 340, 113, 26));
        lineEdit_prenom_15->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        label_prenom_17 = new QLabel(frame_15);
        label_prenom_17->setObjectName("label_prenom_17");
        label_prenom_17->setGeometry(QRect(30, 320, 121, 20));
        label_contact_7 = new QLabel(frame_15);
        label_contact_7->setObjectName("label_contact_7");
        label_contact_7->setGeometry(QRect(30, 450, 111, 20));
        lineEdit_contact_9 = new QLineEdit(frame_15);
        lineEdit_contact_9->setObjectName("lineEdit_contact_9");
        lineEdit_contact_9->setGeometry(QRect(30, 470, 113, 26));
        lineEdit_contact_9->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        frame_16 = new QFrame(Formateur);
        frame_16->setObjectName("frame_16");
        frame_16->setGeometry(QRect(70, 20, 211, 41));
        frame_16->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 157, 206);\n"
"border: 3px solid #040457;\n"
"border-radius:20px;"));
        frame_16->setFrameShape(QFrame::Shape::StyledPanel);
        frame_16->setFrameShadow(QFrame::Shadow::Raised);
        label_embauhe_11 = new QLabel(frame_16);
        label_embauhe_11->setObjectName("label_embauhe_11");
        label_embauhe_11->setGeometry(QRect(30, 10, 161, 20));
        label_embauhe_11->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 157, 206);\n"
"border: 2px solid #649dce;\n"
""));
        frame_17 = new QFrame(Formateur);
        frame_17->setObjectName("frame_17");
        frame_17->setGeometry(QRect(330, 40, 1001, 681));
        frame_17->setStyleSheet(QString::fromUtf8("border: 3px solid #040457;\n"
"border-radius:20px;\n"
""));
        frame_17->setFrameShape(QFrame::Shape::StyledPanel);
        frame_17->setFrameShadow(QFrame::Shadow::Raised);
        tableau_liste_5 = new QTableWidget(frame_17);
        if (tableau_liste_5->columnCount() < 7)
            tableau_liste_5->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableau_liste_5->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableau_liste_5->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableau_liste_5->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableau_liste_5->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableau_liste_5->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableau_liste_5->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableau_liste_5->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableau_liste_5->setObjectName("tableau_liste_5");
        tableau_liste_5->setGeometry(QRect(60, 330, 841, 291));
        tableau_liste_5->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 192, 239);\n"
"color: rgb(255, 255, 255);\n"
"border: 3px solid #6aa6da;\n"
"border-radius: 20px;\n"
""));
        tableau_liste_5->setFrameShadow(QFrame::Shadow::Sunken);
        tableau_liste_5->setLineWidth(-7);
        tableau_liste_5->setAlternatingRowColors(false);
        tableau_liste_5->setRowCount(0);
        tableau_liste_5->setColumnCount(7);
        lineEdit_RECHERCHE_5 = new QLineEdit(frame_17);
        lineEdit_RECHERCHE_5->setObjectName("lineEdit_RECHERCHE_5");
        lineEdit_RECHERCHE_5->setGeometry(QRect(570, 260, 321, 31));
        lineEdit_RECHERCHE_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
"border: 3px solid #ffffff;\n"
"color: rgb(162, 162, 162);"));
        pushButton_37 = new QPushButton(frame_17);
        pushButton_37->setObjectName("pushButton_37");
        pushButton_37->setGeometry(QRect(730, 300, 111, 31));
        pushButton_37->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_38 = new QPushButton(frame_17);
        pushButton_38->setObjectName("pushButton_38");
        pushButton_38->setGeometry(QRect(850, 300, 41, 31));
        pushButton_38->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_38->setIcon(icon);
        pushButton_39 = new QPushButton(frame_17);
        pushButton_39->setObjectName("pushButton_39");
        pushButton_39->setGeometry(QRect(70, 300, 81, 31));
        pushButton_39->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        icon1.addFile(QString::fromUtf8(":/img/trie.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_39->setIcon(icon1);
        pushButton_39->setAutoRepeatInterval(97);
        pushButton_40 = new QPushButton(frame_17);
        pushButton_40->setObjectName("pushButton_40");
        pushButton_40->setGeometry(QRect(850, 630, 41, 31));
        pushButton_40->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/download.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_40->setIcon(icon2);
        label_5 = new QLabel(frame_17);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(310, 50, 331, 51));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(106, 166, 218);\n"
"color: rgb(83, 130, 171);\n"
"color: rgb(157, 235, 255);\n"
"border: none;\n"
"font: 30pt \"Rockwell\";"));
        pushButton_stat_2 = new QPushButton(frame_17);
        pushButton_stat_2->setObjectName("pushButton_stat_2");
        pushButton_stat_2->setGeometry(QRect(610, 300, 111, 29));
        pushButton_stat_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/stat.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_stat_2->setIcon(icon3);
        pushButton_41 = new QPushButton(frame_17);
        pushButton_41->setObjectName("pushButton_41");
        pushButton_41->setGeometry(QRect(540, 260, 51, 31));
        pushButton_41->setStyleSheet(QString::fromUtf8("border:none;\n"
"background-color: rgb(255, 255, 255);\n"
"border-radius : 10px;\n"
""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/loupe.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_41->setIcon(icon4);
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(30, 160, 161, 451));
        frame->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(240, 195, 0);\n"
"border-radius:10px;"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        pushButton_11 = new QPushButton(frame);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(30, 160, 101, 29));
        pushButton_11->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_12 = new QPushButton(frame);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(30, 220, 101, 29));
        pushButton_12->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_13 = new QPushButton(frame);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(30, 340, 101, 29));
        pushButton_13->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_14 = new QPushButton(frame);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(30, 280, 101, 29));
        pushButton_14->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_16 = new QPushButton(frame);
        pushButton_16->setObjectName("pushButton_16");
        pushButton_16->setGeometry(QRect(30, 100, 101, 29));
        pushButton_16->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_10 = new QPushButton(frame);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(-10, 30, 181, 41));
        pushButton_10->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
"border: 2px solid #fff957;\n"
"	color: rgb(4, 4, 87);\n"
"	font: 700 8pt \"Rockwell\";\n"
"\n"
""));
        frame_5 = new QFrame(centralwidget);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(20, 150, 181, 471));
        frame_5->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(240, 195, 0);\n"
"border-radius:10px;\n"
"border: 2px solid #f0c300;\n"
"background-color: rgb(4, 4, 87);"));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        Interface_employe->setCentralWidget(centralwidget);
        frame_5->raise();
        label->raise();
        Formateur->raise();
        frame->raise();
        menubar = new QMenuBar(Interface_employe);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1920, 26));
        Interface_employe->setMenuBar(menubar);
        statusbar = new QStatusBar(Interface_employe);
        statusbar->setObjectName("statusbar");
        Interface_employe->setStatusBar(statusbar);

        retranslateUi(Interface_employe);

        QMetaObject::connectSlotsByName(Interface_employe);
    } // setupUi

    void retranslateUi(QMainWindow *Interface_employe)
    {
        Interface_employe->setWindowTitle(QCoreApplication::translate("Interface_employe", "Interface_employe", nullptr));
        label->setText(QString());
        label_contact_6->setText(QCoreApplication::translate("Interface_employe", "Contact", nullptr));
        label_prenom_10->setText(QCoreApplication::translate("Interface_employe", "Pr\303\251nom", nullptr));
        pushButton_cin_6->setText(QCoreApplication::translate("Interface_employe", "Valider", nullptr));
        label_cin_10->setText(QCoreApplication::translate("Interface_employe", "ID employe", nullptr));
        label_cin_11->setText(QCoreApplication::translate("Interface_employe", "Nom", nullptr));
        label_embauhe_10->setText(QCoreApplication::translate("Interface_employe", "Date d'embauche", nullptr));
        pushButton_ANNULER_6->setText(QCoreApplication::translate("Interface_employe", "Annuler", nullptr));
        pushButton_AJOUTER_6->setText(QCoreApplication::translate("Interface_employe", "Ajouter", nullptr));
        label_prenom_11->setText(QCoreApplication::translate("Interface_employe", "CIN", nullptr));
        label_prenom_16->setText(QCoreApplication::translate("Interface_employe", "Poste", nullptr));
        label_prenom_17->setText(QCoreApplication::translate("Interface_employe", "Adresse email", nullptr));
        label_contact_7->setText(QCoreApplication::translate("Interface_employe", "Mot de passe", nullptr));
        label_embauhe_11->setText(QCoreApplication::translate("Interface_employe", "Ajouter un formateur", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableau_liste_5->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Interface_employe", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableau_liste_5->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Interface_employe", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableau_liste_5->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Interface_employe", "Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableau_liste_5->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Interface_employe", "CIN", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableau_liste_5->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Interface_employe", "Adresse email", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableau_liste_5->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Interface_employe", "Mot de passe", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableau_liste_5->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("Interface_employe", "Date d'embauche", nullptr));
        lineEdit_RECHERCHE_5->setText(QCoreApplication::translate("Interface_employe", "      Rechercher un formateur \303\240 partir de son ID", nullptr));
        pushButton_37->setText(QCoreApplication::translate("Interface_employe", "    Modifier", nullptr));
        pushButton_38->setText(QString());
        pushButton_39->setText(QCoreApplication::translate("Interface_employe", "  Trier", nullptr));
        pushButton_40->setText(QString());
        label_5->setText(QCoreApplication::translate("Interface_employe", "EMPLOYE", nullptr));
        pushButton_stat_2->setText(QCoreApplication::translate("Interface_employe", " Statistiques", nullptr));
        pushButton_41->setText(QString());
        pushButton_11->setText(QCoreApplication::translate("Interface_employe", "Formations", nullptr));
        pushButton_12->setText(QCoreApplication::translate("Interface_employe", "Equipement", nullptr));
        pushButton_13->setText(QCoreApplication::translate("Interface_employe", "Services", nullptr));
        pushButton_14->setText(QCoreApplication::translate("Interface_employe", "Apprenant", nullptr));
        pushButton_16->setText(QCoreApplication::translate("Interface_employe", "Formateurs", nullptr));
        pushButton_10->setText(QCoreApplication::translate("Interface_employe", "Employ\303\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Interface_employe: public Ui_Interface_employe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_EMPLOYE_H
