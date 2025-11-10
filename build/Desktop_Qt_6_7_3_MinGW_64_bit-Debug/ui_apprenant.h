/********************************************************************************
** Form generated from reading UI file 'apprenant.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPRENANT_H
#define UI_APPRENANT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_apprenant
{
public:
    QFrame *frame_5;
    QFrame *frame_2;
    QPushButton *pushButton_21;
    QPushButton *pushButton_22;
    QPushButton *pushButton_23;
    QPushButton *pushButton_24;
    QPushButton *pushButton_25;
    QPushButton *pushButton_15;
    QWidget *Formateur;
    QFrame *frame_6;
    QLineEdit *lineEdit_cin_3;
    QLabel *label_contact_3;
    QLineEdit *lineEdit_contact_3;
    QLabel *label_prenom_4;
    QLineEdit *lineEdit_nom_3;
    QLineEdit *lineEdit_prenom_3;
    QPushButton *pushButton_cin_3;
    QLabel *label_cin_4;
    QLabel *label_cin_5;
    QDateEdit *dateEdit_embauche_3;
    QLabel *label_embauhe_4;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QLabel *label_prenom_5;
    QPushButton *pushButton_ANNULER_3;
    QPushButton *pushButton_AJOUTER_3;
    QFrame *frame_7;
    QLabel *label_embauhe_5;
    QFrame *frame_8;
    QLineEdit *lineEdit_RECHERCHE_2;
    QPushButton *pushButton_17;
    QPushButton *pushButton_18;
    QPushButton *pushButton_19;
    QPushButton *pushButton_20;
    QPushButton *pushButton_stat_2;
    QLabel *label_2;
    QPushButton *pushButton_stat;
    QTableView *tableView;
    QLabel *label;

    void setupUi(QWidget *apprenant)
    {
        if (apprenant->objectName().isEmpty())
            apprenant->setObjectName("apprenant");
        apprenant->resize(1579, 980);
        apprenant->setStyleSheet(QString::fromUtf8("background-color: rgb(4, 4, 87);"));
        frame_5 = new QFrame(apprenant);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 230, 181, 471));
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
        pushButton_21 = new QPushButton(frame_2);
        pushButton_21->setObjectName("pushButton_21");
        pushButton_21->setGeometry(QRect(30, 160, 101, 29));
        pushButton_21->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_22 = new QPushButton(frame_2);
        pushButton_22->setObjectName("pushButton_22");
        pushButton_22->setGeometry(QRect(30, 280, 101, 29));
        pushButton_22->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_23 = new QPushButton(frame_2);
        pushButton_23->setObjectName("pushButton_23");
        pushButton_23->setGeometry(QRect(30, 340, 101, 29));
        pushButton_23->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_24 = new QPushButton(frame_2);
        pushButton_24->setObjectName("pushButton_24");
        pushButton_24->setGeometry(QRect(30, 100, 101, 29));
        pushButton_24->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_25 = new QPushButton(frame_2);
        pushButton_25->setObjectName("pushButton_25");
        pushButton_25->setGeometry(QRect(30, 30, 101, 29));
        pushButton_25->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_15 = new QPushButton(frame_2);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setGeometry(QRect(30, 220, 101, 29));
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
        Formateur = new QWidget(apprenant);
        Formateur->setObjectName("Formateur");
        Formateur->setGeometry(QRect(210, 60, 1301, 751));
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
        lineEdit_cin_3 = new QLineEdit(frame_6);
        lineEdit_cin_3->setObjectName("lineEdit_cin_3");
        lineEdit_cin_3->setGeometry(QRect(30, 60, 113, 26));
        lineEdit_cin_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"color: rgb(0, 0, 0);\n"
"border-radius:10px;\n"
""));
        lineEdit_cin_3->setMaxLength(8);
        label_contact_3 = new QLabel(frame_6);
        label_contact_3->setObjectName("label_contact_3");
        label_contact_3->setGeometry(QRect(30, 330, 71, 20));
        lineEdit_contact_3 = new QLineEdit(frame_6);
        lineEdit_contact_3->setObjectName("lineEdit_contact_3");
        lineEdit_contact_3->setGeometry(QRect(30, 350, 113, 26));
        lineEdit_contact_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"border-radius:10px;"));
        label_prenom_4 = new QLabel(frame_6);
        label_prenom_4->setObjectName("label_prenom_4");
        label_prenom_4->setGeometry(QRect(30, 180, 63, 20));
        lineEdit_nom_3 = new QLineEdit(frame_6);
        lineEdit_nom_3->setObjectName("lineEdit_nom_3");
        lineEdit_nom_3->setGeometry(QRect(30, 130, 113, 26));
        lineEdit_nom_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"border-radius:10px;"));
        lineEdit_nom_3->setMaxLength(20);
        lineEdit_prenom_3 = new QLineEdit(frame_6);
        lineEdit_prenom_3->setObjectName("lineEdit_prenom_3");
        lineEdit_prenom_3->setGeometry(QRect(30, 200, 113, 26));
        lineEdit_prenom_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"border-radius:10px;"));
        pushButton_cin_3 = new QPushButton(frame_6);
        pushButton_cin_3->setObjectName("pushButton_cin_3");
        pushButton_cin_3->setGeometry(QRect(160, 60, 51, 20));
        pushButton_cin_3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        label_cin_4 = new QLabel(frame_6);
        label_cin_4->setObjectName("label_cin_4");
        label_cin_4->setGeometry(QRect(30, 40, 31, 20));
        label_cin_5 = new QLabel(frame_6);
        label_cin_5->setObjectName("label_cin_5");
        label_cin_5->setGeometry(QRect(30, 110, 41, 20));
        dateEdit_embauche_3 = new QDateEdit(frame_6);
        dateEdit_embauche_3->setObjectName("dateEdit_embauche_3");
        dateEdit_embauche_3->setGeometry(QRect(30, 420, 121, 21));
        dateEdit_embauche_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"border-radius:10px;"));
        label_embauhe_4 = new QLabel(frame_6);
        label_embauhe_4->setObjectName("label_embauhe_4");
        label_embauhe_4->setGeometry(QRect(30, 400, 131, 20));
        checkBox_3 = new QCheckBox(frame_6);
        checkBox_3->setObjectName("checkBox_3");
        checkBox_3->setGeometry(QRect(30, 280, 91, 24));
        checkBox_3->setStyleSheet(QString::fromUtf8("background-color: rgb(83, 130, 171);\n"
"border-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);"));
        checkBox_4 = new QCheckBox(frame_6);
        checkBox_4->setObjectName("checkBox_4");
        checkBox_4->setGeometry(QRect(140, 280, 91, 24));
        checkBox_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_prenom_5 = new QLabel(frame_6);
        label_prenom_5->setObjectName("label_prenom_5");
        label_prenom_5->setGeometry(QRect(30, 260, 63, 20));
        pushButton_ANNULER_3 = new QPushButton(frame_6);
        pushButton_ANNULER_3->setObjectName("pushButton_ANNULER_3");
        pushButton_ANNULER_3->setGeometry(QRect(200, 670, 61, 21));
        pushButton_ANNULER_3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_AJOUTER_3 = new QPushButton(frame_6);
        pushButton_AJOUTER_3->setObjectName("pushButton_AJOUTER_3");
        pushButton_AJOUTER_3->setGeometry(QRect(200, 640, 61, 21));
        pushButton_AJOUTER_3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        frame_8->setGeometry(QRect(330, 40, 951, 681));
        frame_8->setStyleSheet(QString::fromUtf8("border: 3px solid #040457;\n"
"border-radius:20px;\n"
""));
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        lineEdit_RECHERCHE_2 = new QLineEdit(frame_8);
        lineEdit_RECHERCHE_2->setObjectName("lineEdit_RECHERCHE_2");
        lineEdit_RECHERCHE_2->setGeometry(QRect(570, 250, 321, 31));
        lineEdit_RECHERCHE_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
"border: 3px solid #ffffff;\n"
"color: rgb(162, 162, 162);"));
        pushButton_17 = new QPushButton(frame_8);
        pushButton_17->setObjectName("pushButton_17");
        pushButton_17->setGeometry(QRect(760, 290, 81, 31));
        pushButton_17->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(0, 0, 0);\n"
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
        pushButton_18 = new QPushButton(frame_8);
        pushButton_18->setObjectName("pushButton_18");
        pushButton_18->setGeometry(QRect(850, 290, 41, 31));
        pushButton_18->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_18->setIcon(icon);
        pushButton_19 = new QPushButton(frame_8);
        pushButton_19->setObjectName("pushButton_19");
        pushButton_19->setGeometry(QRect(70, 300, 81, 31));
        pushButton_19->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	color: rgb(0, 0, 0);\n"
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
        pushButton_19->setIcon(icon1);
        pushButton_19->setAutoRepeatInterval(97);
        pushButton_20 = new QPushButton(frame_8);
        pushButton_20->setObjectName("pushButton_20");
        pushButton_20->setGeometry(QRect(850, 640, 41, 31));
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
        pushButton_stat_2 = new QPushButton(frame_8);
        pushButton_stat_2->setObjectName("pushButton_stat_2");
        pushButton_stat_2->setGeometry(QRect(660, 290, 91, 31));
        pushButton_stat_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"color: rgb(0, 0, 0);\n"
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
        pushButton_stat_2->setIcon(icon3);
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
"color: rgb(0, 0, 0);\n"
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
        tableView = new QTableView(frame_8);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(60, 340, 841, 291));
        tableView->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 192, 239);\n"
"color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);\n"
"border: 3px solid #6aa6da;"));
        label = new QLabel(apprenant);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 100, 111, 101));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/image.png")));
        label->setScaledContents(true);

        retranslateUi(apprenant);

        QMetaObject::connectSlotsByName(apprenant);
    } // setupUi

    void retranslateUi(QWidget *apprenant)
    {
        apprenant->setWindowTitle(QCoreApplication::translate("apprenant", "Form", nullptr));
        pushButton_21->setText(QCoreApplication::translate("apprenant", "Formations", nullptr));
        pushButton_22->setText(QCoreApplication::translate("apprenant", "Equipements", nullptr));
        pushButton_23->setText(QCoreApplication::translate("apprenant", "Services", nullptr));
        pushButton_24->setText(QCoreApplication::translate("apprenant", "Formateurs", nullptr));
        pushButton_25->setText(QCoreApplication::translate("apprenant", "Employ\303\251", nullptr));
        pushButton_15->setText(QCoreApplication::translate("apprenant", "Apprenants", nullptr));
        label_contact_3->setText(QCoreApplication::translate("apprenant", "Email", nullptr));
        label_prenom_4->setText(QCoreApplication::translate("apprenant", "Pr\303\251nom", nullptr));
        pushButton_cin_3->setText(QCoreApplication::translate("apprenant", "Valider", nullptr));
        label_cin_4->setText(QCoreApplication::translate("apprenant", "ID", nullptr));
        label_cin_5->setText(QCoreApplication::translate("apprenant", "Nom", nullptr));
        label_embauhe_4->setText(QCoreApplication::translate("apprenant", "Date de naissance", nullptr));
        checkBox_3->setText(QCoreApplication::translate("apprenant", "Homme", nullptr));
        checkBox_4->setText(QCoreApplication::translate("apprenant", "Femme", nullptr));
        label_prenom_5->setText(QCoreApplication::translate("apprenant", "Sexe", nullptr));
        pushButton_ANNULER_3->setText(QCoreApplication::translate("apprenant", "Annuler", nullptr));
        pushButton_AJOUTER_3->setText(QCoreApplication::translate("apprenant", "Ajouter", nullptr));
        label_embauhe_5->setText(QCoreApplication::translate("apprenant", "Ajouter un apprenant", nullptr));
        lineEdit_RECHERCHE_2->setText(QString());
        pushButton_17->setText(QCoreApplication::translate("apprenant", "Modifier", nullptr));
        pushButton_18->setText(QString());
        pushButton_19->setText(QCoreApplication::translate("apprenant", "  Trier", nullptr));
        pushButton_20->setText(QString());
        pushButton_stat_2->setText(QCoreApplication::translate("apprenant", " Rapport", nullptr));
        label_2->setText(QCoreApplication::translate("apprenant", "APPRENANT", nullptr));
        pushButton_stat->setText(QCoreApplication::translate("apprenant", " Statistiques", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class apprenant: public Ui_apprenant {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPRENANT_H
