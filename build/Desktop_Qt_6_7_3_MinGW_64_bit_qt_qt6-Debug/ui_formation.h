/********************************************************************************
** Form generated from reading UI file 'formation.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMATION_H
#define UI_FORMATION_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formation
{
public:
    QWidget *centralwidget;
    QFrame *frame_5;
    QFrame *frame;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_16;
    QPushButton *pushButton_17;
    QWidget *Formateur;
    QFrame *frame_6;
    QLineEdit *lineEditId;
    QLabel *label_contact_3;
    QLabel *label_prenom_4;
    QLineEdit *lineEdit_Nom;
    QLabel *label_cin_4;
    QLabel *label_cin_5;
    QLabel *label_embauhe_4;
    QLineEdit *lineEdit_Ta;
    QLabel *label_contact_7;
    QPushButton *pushButtonAjouter;
    QComboBox *lineEdit_type;
    QLabel *label_contact_4;
    QDateEdit *dateEdit_date;
    QLabel *label_date;
    QLineEdit *lineEdit_D;
    QTimeEdit *lineEdit_h;
    QLineEdit *lineEdit_lieu;
    QComboBox *comboBox_Ca;
    QLabel *label_embauhe_6;
    QLineEdit *lineEdit_id2;
    QLabel *label_contact_8;
    QFrame *frame_7;
    QLabel *label_embauhe_5;
    QFrame *frame_8;
    QLineEdit *lineEdit_rechercher;
    QPushButton *pushButtonModifier;
    QPushButton *pushButtonsupprimer;
    QPushButton *pushButtonTrier;
    QPushButton *pushButton_exporter;
    QLabel *label_2;
    QPushButton *pushButton_stat;
    QPushButton *pushButton_47;
    QTableView *tableFormation;
    QPushButton *pushButton_rechercher;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *formation)
    {
        if (formation->objectName().isEmpty())
            formation->setObjectName("formation");
        formation->resize(1920, 1080);
        formation->setStyleSheet(QString::fromUtf8("background-color: rgb(4, 4, 87);"));
        centralwidget = new QWidget(formation);
        centralwidget->setObjectName("centralwidget");
        frame_5 = new QFrame(centralwidget);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 190, 181, 471));
        frame_5->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(240, 195, 0);\n"
"border-radius:10px;\n"
"border: 2px solid #f0c300;\n"
"background-color: rgb(4, 4, 87);"));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        frame = new QFrame(frame_5);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 161, 451));
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
        pushButton_16->setGeometry(QRect(30, 40, 101, 29));
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
        pushButton_17 = new QPushButton(frame);
        pushButton_17->setObjectName("pushButton_17");
        pushButton_17->setGeometry(QRect(30, 100, 101, 29));
        pushButton_17->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        Formateur = new QWidget(centralwidget);
        Formateur->setObjectName("Formateur");
        Formateur->setGeometry(QRect(200, 10, 1271, 751));
        Formateur->setMaximumSize(QSize(2000, 2000));
        Formateur->setBaseSize(QSize(1000, 1000));
        Formateur->setMouseTracking(false);
        Formateur->setTabletTracking(false);
        Formateur->setAutoFillBackground(false);
        Formateur->setStyleSheet(QString::fromUtf8("background-color: rgb(106, 166, 218);\n"
"\n"
"border-radius:30px;"));
        frame_6 = new QFrame(Formateur);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(40, 40, 271, 701));
        frame_6->setStyleSheet(QString::fromUtf8("background-color: rgb(58, 196, 255);\n"
"background-color: rgb(83, 130, 171);\n"
"border-radius:20px;\n"
"\n"
""));
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        lineEditId = new QLineEdit(frame_6);
        lineEditId->setObjectName("lineEditId");
        lineEditId->setGeometry(QRect(30, 60, 113, 26));
        lineEditId->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
""));
        lineEditId->setMaxLength(8);
        label_contact_3 = new QLabel(frame_6);
        label_contact_3->setObjectName("label_contact_3");
        label_contact_3->setGeometry(QRect(30, 250, 63, 20));
        label_prenom_4 = new QLabel(frame_6);
        label_prenom_4->setObjectName("label_prenom_4");
        label_prenom_4->setGeometry(QRect(30, 180, 63, 20));
        lineEdit_Nom = new QLineEdit(frame_6);
        lineEdit_Nom->setObjectName("lineEdit_Nom");
        lineEdit_Nom->setGeometry(QRect(30, 130, 113, 26));
        lineEdit_Nom->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        lineEdit_Nom->setMaxLength(20);
        label_cin_4 = new QLabel(frame_6);
        label_cin_4->setObjectName("label_cin_4");
        label_cin_4->setGeometry(QRect(30, 40, 31, 20));
        label_cin_5 = new QLabel(frame_6);
        label_cin_5->setObjectName("label_cin_5");
        label_cin_5->setGeometry(QRect(30, 110, 41, 20));
        label_embauhe_4 = new QLabel(frame_6);
        label_embauhe_4->setObjectName("label_embauhe_4");
        label_embauhe_4->setGeometry(QRect(30, 400, 131, 20));
        lineEdit_Ta = new QLineEdit(frame_6);
        lineEdit_Ta->setObjectName("lineEdit_Ta");
        lineEdit_Ta->setGeometry(QRect(30, 570, 121, 26));
        lineEdit_Ta->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
""));
        label_contact_7 = new QLabel(frame_6);
        label_contact_7->setObjectName("label_contact_7");
        label_contact_7->setGeometry(QRect(30, 550, 191, 20));
        pushButtonAjouter = new QPushButton(frame_6);
        pushButtonAjouter->setObjectName("pushButtonAjouter");
        pushButtonAjouter->setGeometry(QRect(180, 640, 81, 21));
        pushButtonAjouter->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        lineEdit_type = new QComboBox(frame_6);
        lineEdit_type->addItem(QString());
        lineEdit_type->addItem(QString());
        lineEdit_type->addItem(QString());
        lineEdit_type->addItem(QString());
        lineEdit_type->addItem(QString());
        lineEdit_type->setObjectName("lineEdit_type");
        lineEdit_type->setGeometry(QRect(30, 200, 121, 26));
        lineEdit_type->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        label_contact_4 = new QLabel(frame_6);
        label_contact_4->setObjectName("label_contact_4");
        label_contact_4->setGeometry(QRect(30, 350, 63, 20));
        dateEdit_date = new QDateEdit(frame_6);
        dateEdit_date->setObjectName("dateEdit_date");
        dateEdit_date->setGeometry(QRect(30, 320, 121, 26));
        dateEdit_date->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        label_date = new QLabel(frame_6);
        label_date->setObjectName("label_date");
        label_date->setGeometry(QRect(30, 300, 111, 20));
        lineEdit_D = new QLineEdit(frame_6);
        lineEdit_D->setObjectName("lineEdit_D");
        lineEdit_D->setGeometry(QRect(30, 370, 113, 26));
        lineEdit_D->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        lineEdit_h = new QTimeEdit(frame_6);
        lineEdit_h->setObjectName("lineEdit_h");
        lineEdit_h->setGeometry(QRect(30, 270, 118, 26));
        lineEdit_h->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        lineEdit_lieu = new QLineEdit(frame_6);
        lineEdit_lieu->setObjectName("lineEdit_lieu");
        lineEdit_lieu->setGeometry(QRect(30, 420, 113, 26));
        lineEdit_lieu->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        comboBox_Ca = new QComboBox(frame_6);
        comboBox_Ca->addItem(QString());
        comboBox_Ca->addItem(QString());
        comboBox_Ca->addItem(QString());
        comboBox_Ca->addItem(QString());
        comboBox_Ca->setObjectName("comboBox_Ca");
        comboBox_Ca->setGeometry(QRect(30, 490, 121, 26));
        comboBox_Ca->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        label_embauhe_6 = new QLabel(frame_6);
        label_embauhe_6->setObjectName("label_embauhe_6");
        label_embauhe_6->setGeometry(QRect(30, 470, 131, 20));
        lineEdit_id2 = new QLineEdit(frame_6);
        lineEdit_id2->setObjectName("lineEdit_id2");
        lineEdit_id2->setGeometry(QRect(30, 640, 121, 26));
        lineEdit_id2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
""));
        label_contact_8 = new QLabel(frame_6);
        label_contact_8->setObjectName("label_contact_8");
        label_contact_8->setGeometry(QRect(30, 620, 191, 20));
        frame_7 = new QFrame(Formateur);
        frame_7->setObjectName("frame_7");
        frame_7->setGeometry(QRect(70, 20, 211, 41));
        frame_7->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 157, 206);\n"
"border: 3px solid #040457;\n"
"border-radius:20px;"));
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        label_embauhe_5 = new QLabel(frame_7);
        label_embauhe_5->setObjectName("label_embauhe_5");
        label_embauhe_5->setGeometry(QRect(30, 10, 161, 20));
        label_embauhe_5->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 157, 206);\n"
"border: 2px solid #649dce;\n"
""));
        frame_8 = new QFrame(Formateur);
        frame_8->setObjectName("frame_8");
        frame_8->setGeometry(QRect(320, 40, 921, 681));
        frame_8->setStyleSheet(QString::fromUtf8("border: 3px solid #040457;\n"
"border-radius:20px;\n"
""));
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        lineEdit_rechercher = new QLineEdit(frame_8);
        lineEdit_rechercher->setObjectName("lineEdit_rechercher");
        lineEdit_rechercher->setGeometry(QRect(560, 250, 321, 31));
        lineEdit_rechercher->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
"border: 3px solid #ffffff;\n"
"color: rgb(162, 162, 162);"));
        pushButtonModifier = new QPushButton(frame_8);
        pushButtonModifier->setObjectName("pushButtonModifier");
        pushButtonModifier->setGeometry(QRect(760, 290, 81, 31));
        pushButtonModifier->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButtonsupprimer = new QPushButton(frame_8);
        pushButtonsupprimer->setObjectName("pushButtonsupprimer");
        pushButtonsupprimer->setGeometry(QRect(850, 290, 41, 31));
        pushButtonsupprimer->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        icon.addFile(QString::fromUtf8(":/supp/supp.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonsupprimer->setIcon(icon);
        pushButtonTrier = new QPushButton(frame_8);
        pushButtonTrier->setObjectName("pushButtonTrier");
        pushButtonTrier->setGeometry(QRect(70, 290, 81, 31));
        pushButtonTrier->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        icon1.addFile(QString::fromUtf8(":/trier/Trier.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonTrier->setIcon(icon1);
        pushButtonTrier->setAutoRepeatInterval(97);
        pushButton_exporter = new QPushButton(frame_8);
        pushButton_exporter->setObjectName("pushButton_exporter");
        pushButton_exporter->setGeometry(QRect(850, 630, 41, 31));
        pushButton_exporter->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        icon2.addFile(QString::fromUtf8(":/telech/telech.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_exporter->setIcon(icon2);
        label_2 = new QLabel(frame_8);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(310, 50, 331, 51));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(106, 166, 218);\n"
"color: rgb(83, 130, 171);\n"
"color: rgb(157, 235, 255);\n"
"border: none;\n"
"font: 30pt \"Rockwell\";"));
        pushButton_stat = new QPushButton(frame_8);
        pushButton_stat->setObjectName("pushButton_stat");
        pushButton_stat->setGeometry(QRect(620, 290, 111, 29));
        pushButton_stat->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        icon3.addFile(QString::fromUtf8(":/stat/stat.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_stat->setIcon(icon3);
        pushButton_47 = new QPushButton(frame_8);
        pushButton_47->setObjectName("pushButton_47");
        pushButton_47->setGeometry(QRect(720, 630, 111, 31));
        pushButton_47->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/calendrier/d47c1ced-b41a-49dd-b864-317382d52708.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_47->setIcon(icon4);
        tableFormation = new QTableView(frame_8);
        tableFormation->setObjectName("tableFormation");
        tableFormation->setGeometry(QRect(25, 351, 871, 251));
        pushButton_rechercher = new QPushButton(frame_8);
        pushButton_rechercher->setObjectName("pushButton_rechercher");
        pushButton_rechercher->setGeometry(QRect(770, 250, 111, 31));
        pushButton_rechercher->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 161, 151));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/34e0dfa3-771e-477d-9d87-357bb95400d1-removebg-preview.png")));
        label->setScaledContents(true);
        formation->setCentralWidget(centralwidget);
        menubar = new QMenuBar(formation);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1920, 26));
        formation->setMenuBar(menubar);
        statusbar = new QStatusBar(formation);
        statusbar->setObjectName("statusbar");
        formation->setStatusBar(statusbar);

        retranslateUi(formation);

        QMetaObject::connectSlotsByName(formation);
    } // setupUi

    void retranslateUi(QMainWindow *formation)
    {
        formation->setWindowTitle(QCoreApplication::translate("formation", "formation", nullptr));
        pushButton_11->setText(QCoreApplication::translate("formation", "Employ\303\251s", nullptr));
        pushButton_12->setText(QCoreApplication::translate("formation", "Equipement", nullptr));
        pushButton_13->setText(QCoreApplication::translate("formation", "Services", nullptr));
        pushButton_14->setText(QCoreApplication::translate("formation", "Apprenant", nullptr));
        pushButton_16->setText(QCoreApplication::translate("formation", "Formations", nullptr));
        pushButton_17->setText(QCoreApplication::translate("formation", "Formateurs", nullptr));
        label_contact_3->setText(QCoreApplication::translate("formation", "Horaire", nullptr));
        label_prenom_4->setText(QCoreApplication::translate("formation", "Type", nullptr));
        label_cin_4->setText(QCoreApplication::translate("formation", "Id", nullptr));
        label_cin_5->setText(QCoreApplication::translate("formation", "Nom", nullptr));
        label_embauhe_4->setText(QCoreApplication::translate("formation", "Lieu", nullptr));
        lineEdit_Ta->setText(QString());
        label_contact_7->setText(QCoreApplication::translate("formation", "Tarif", nullptr));
        pushButtonAjouter->setText(QCoreApplication::translate("formation", "Ajouter", nullptr));
        lineEdit_type->setItemText(0, QCoreApplication::translate("formation", "Fran\303\247ais", nullptr));
        lineEdit_type->setItemText(1, QCoreApplication::translate("formation", "Anglais", nullptr));
        lineEdit_type->setItemText(2, QCoreApplication::translate("formation", "Science", nullptr));
        lineEdit_type->setItemText(3, QCoreApplication::translate("formation", "Physique", nullptr));
        lineEdit_type->setItemText(4, QCoreApplication::translate("formation", "Arabe", nullptr));

        label_contact_4->setText(QCoreApplication::translate("formation", "Duree", nullptr));
        label_date->setText(QCoreApplication::translate("formation", "Date formation", nullptr));
        comboBox_Ca->setItemText(0, QCoreApplication::translate("formation", "25", nullptr));
        comboBox_Ca->setItemText(1, QCoreApplication::translate("formation", "50", nullptr));
        comboBox_Ca->setItemText(2, QCoreApplication::translate("formation", "75", nullptr));
        comboBox_Ca->setItemText(3, QCoreApplication::translate("formation", "100", nullptr));

        label_embauhe_6->setText(QCoreApplication::translate("formation", "Capacite", nullptr));
        lineEdit_id2->setText(QString());
        label_contact_8->setText(QCoreApplication::translate("formation", "id formateur", nullptr));
        label_embauhe_5->setText(QCoreApplication::translate("formation", "Ajouter une formation", nullptr));
        lineEdit_rechercher->setText(QString());
        pushButtonModifier->setText(QCoreApplication::translate("formation", "Modifier", nullptr));
        pushButtonsupprimer->setText(QString());
        pushButtonTrier->setText(QCoreApplication::translate("formation", "  Trier", nullptr));
        pushButton_exporter->setText(QString());
        label_2->setText(QCoreApplication::translate("formation", "Formations", nullptr));
        pushButton_stat->setText(QCoreApplication::translate("formation", " Statistiques", nullptr));
        pushButton_47->setText(QCoreApplication::translate("formation", "Calendrier", nullptr));
        pushButton_rechercher->setText(QCoreApplication::translate("formation", "Rechercher", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class formation: public Ui_formation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMATION_H
