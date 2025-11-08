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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
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
    QLineEdit *lineEdit_D;
    QTimeEdit *lineEdit_h;
    QLineEdit *lineEdit_lieu;
    QLineEdit *lineEdit_Ca;
    QLabel *label_embauhe_6;
    QFrame *frame_7;
    QLabel *label_embauhe_5;
    QFrame *frame_8;
    QTableWidget *tableFormations;
    QLineEdit *lineEdit_RECHERCHE_2;
    QPushButton *pushButtonModifier;
    QPushButton *pushButtonsupprimer;
    QPushButton *pushButtonTrier;
    QPushButton *pushButton_20;
    QPushButton *pushButton_rapport;
    QLabel *label_2;
    QPushButton *pushButton_stat;
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
        label_contact_4->setGeometry(QRect(30, 320, 63, 20));
        lineEdit_D = new QLineEdit(frame_6);
        lineEdit_D->setObjectName("lineEdit_D");
        lineEdit_D->setGeometry(QRect(30, 340, 113, 26));
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
        lineEdit_Ca = new QLineEdit(frame_6);
        lineEdit_Ca->setObjectName("lineEdit_Ca");
        lineEdit_Ca->setGeometry(QRect(30, 490, 113, 26));
        lineEdit_Ca->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;"));
        label_embauhe_6 = new QLabel(frame_6);
        label_embauhe_6->setObjectName("label_embauhe_6");
        label_embauhe_6->setGeometry(QRect(30, 470, 131, 20));
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
        frame_8->setGeometry(QRect(330, 40, 921, 681));
        frame_8->setStyleSheet(QString::fromUtf8("border: 3px solid #040457;\n"
"border-radius:20px;\n"
""));
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        tableFormations = new QTableWidget(frame_8);
        if (tableFormations->columnCount() < 9)
            tableFormations->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableFormations->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableFormations->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableFormations->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableFormations->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableFormations->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableFormations->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableFormations->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableFormations->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableFormations->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        tableFormations->setObjectName("tableFormations");
        tableFormations->setGeometry(QRect(60, 330, 841, 291));
        tableFormations->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 192, 239);\n"
"color: rgb(255, 255, 255);\n"
"border: 3px solid #6aa6da;\n"
"border-radius: 20px;\n"
""));
        tableFormations->setFrameShadow(QFrame::Shadow::Sunken);
        tableFormations->setLineWidth(-7);
        tableFormations->setAlternatingRowColors(false);
        tableFormations->setRowCount(0);
        tableFormations->setColumnCount(9);
        lineEdit_RECHERCHE_2 = new QLineEdit(frame_8);
        lineEdit_RECHERCHE_2->setObjectName("lineEdit_RECHERCHE_2");
        lineEdit_RECHERCHE_2->setGeometry(QRect(560, 250, 321, 31));
        lineEdit_RECHERCHE_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
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
        icon.addFile(QString::fromUtf8(":/img/poubelle.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonsupprimer->setIcon(icon);
        pushButtonTrier = new QPushButton(frame_8);
        pushButtonTrier->setObjectName("pushButtonTrier");
        pushButtonTrier->setGeometry(QRect(70, 300, 81, 31));
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
        icon1.addFile(QString::fromUtf8(":/img/trie.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonTrier->setIcon(icon1);
        pushButtonTrier->setAutoRepeatInterval(97);
        pushButton_20 = new QPushButton(frame_8);
        pushButton_20->setObjectName("pushButton_20");
        pushButton_20->setGeometry(QRect(850, 630, 41, 31));
        pushButton_20->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_20->setIcon(icon2);
        pushButton_rapport = new QPushButton(frame_8);
        pushButton_rapport->setObjectName("pushButton_rapport");
        pushButton_rapport->setGeometry(QRect(660, 290, 91, 31));
        pushButton_rapport->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/money.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_rapport->setIcon(icon3);
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
        pushButton_stat->setGeometry(QRect(540, 290, 111, 29));
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
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/stat.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_stat->setIcon(icon4);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 161, 151));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/551340347_4214510502130824_9073597560338004353_n-removebg-preview.png")));
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
        label_embauhe_6->setText(QCoreApplication::translate("formation", "Capacite", nullptr));
        label_embauhe_5->setText(QCoreApplication::translate("formation", "Ajouter une formation", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableFormations->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("formation", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableFormations->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("formation", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableFormations->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("formation", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableFormations->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("formation", "Horaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableFormations->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("formation", "Duree", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableFormations->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("formation", "Lieu", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableFormations->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("formation", "Capacite", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableFormations->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("formation", "Tarif", nullptr));
        lineEdit_RECHERCHE_2->setText(QCoreApplication::translate("formation", "    Rechercher une formation \303\240 partir de son Nom", nullptr));
        pushButtonModifier->setText(QCoreApplication::translate("formation", "Modifier", nullptr));
        pushButtonsupprimer->setText(QString());
        pushButtonTrier->setText(QCoreApplication::translate("formation", "  Trier", nullptr));
        pushButton_20->setText(QString());
        pushButton_rapport->setText(QCoreApplication::translate("formation", " Rapport", nullptr));
        label_2->setText(QCoreApplication::translate("formation", "Formations", nullptr));
        pushButton_stat->setText(QCoreApplication::translate("formation", " Statistiques", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class formation: public Ui_formation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMATION_H
