/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
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

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QPushButton *pushButtonAjouter_2;
    QPushButton *pushButtonAjouter_3;
    QPushButton *pushButtonAjouter_4;
    QPushButton *pushButtonAjouter_5;
    QPushButton *pushButtonAjouter_6;
    QGroupBox *groupBox_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEditId;
    QLineEdit *lineEdit_Nom;
    QLineEdit *lineEdit_Ta;
    QLineEdit *lineEdit_Ca;
    QTimeEdit *lineEdit_h;
    QComboBox *lineEdit_type;
    QLineEdit *lineEdit_D;
    QLineEdit *lineEdit_lieu;
    QPushButton *pushButtonAjouter;
    QPushButton *pushButtonsupprimer;
    QPushButton *pushButtonSauvegarder;
    QPushButton *pushButtonModifier;
    QPushButton *pushButtonTrier;
    QPushButton *pushButtonTrier_2;
    QTableWidget *tableFormations;
    QLabel *label_9;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(4, 4, 87);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 120, 161, 401));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(106, 166, 218);\n"
"border-radius: 10px;"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 10, 141, 381));
        groupBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 195, 0);"));
        pushButtonAjouter_2 = new QPushButton(groupBox_2);
        pushButtonAjouter_2->setObjectName("pushButtonAjouter_2");
        pushButtonAjouter_2->setGeometry(QRect(10, 40, 121, 41));
        QFont font;
        font.setPointSize(10);
        pushButtonAjouter_2->setFont(font);
        pushButtonAjouter_2->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"background-color: rgb(255, 255, 255);\n"
"border: 2px solid black;\n"
"\n"
"    /* couleur normale */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgb(112, 155, 220);\n"
"       /* quand la souris survole */\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
"\n"
""));
        pushButtonAjouter_3 = new QPushButton(groupBox_2);
        pushButtonAjouter_3->setObjectName("pushButtonAjouter_3");
        pushButtonAjouter_3->setGeometry(QRect(10, 110, 121, 41));
        pushButtonAjouter_3->setFont(font);
        pushButtonAjouter_3->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"  background-color: rgb(255, 255, 255);\n"
"border: 2px solid black;\n"
"    /* couleur normale */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgb(112, 155, 220);\n"
"       /* quand la souris survole */\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
"\n"
""));
        pushButtonAjouter_4 = new QPushButton(groupBox_2);
        pushButtonAjouter_4->setObjectName("pushButtonAjouter_4");
        pushButtonAjouter_4->setGeometry(QRect(10, 170, 121, 41));
        pushButtonAjouter_4->setFont(font);
        pushButtonAjouter_4->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"  background-color: rgb(255, 255, 255);\n"
"border: 2px solid black;\n"
"    /* couleur normale */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgb(112, 155, 220);\n"
"       /* quand la souris survole */\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
"\n"
""));
        pushButtonAjouter_5 = new QPushButton(groupBox_2);
        pushButtonAjouter_5->setObjectName("pushButtonAjouter_5");
        pushButtonAjouter_5->setGeometry(QRect(10, 230, 121, 41));
        pushButtonAjouter_5->setFont(font);
        pushButtonAjouter_5->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"  background-color: rgb(255, 255, 255);\n"
"border: 2px solid black;\n"
"    /* couleur normale */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgb(112, 155, 220);\n"
"       /* quand la souris survole */\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
"\n"
""));
        pushButtonAjouter_6 = new QPushButton(groupBox_2);
        pushButtonAjouter_6->setObjectName("pushButtonAjouter_6");
        pushButtonAjouter_6->setGeometry(QRect(10, 290, 121, 41));
        pushButtonAjouter_6->setFont(font);
        pushButtonAjouter_6->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
" background-color: rgb(255, 255, 255);\n"
"border: 2px solid black;\n"
"    /* couleur normale */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgb(112, 155, 220);\n"
"       /* quand la souris survole */\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
"\n"
""));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(190, 10, 731, 511));
        QFont font1;
        font1.setBold(true);
        groupBox_3->setFont(font1);
        groupBox_3->setStyleSheet(QString::fromUtf8("background-color: rgb(106, 166, 218);\n"
"border-radius: 20px;"));
        label = new QLabel(groupBox_3);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 50, 63, 20));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(12);
        font2.setBold(false);
        label->setFont(font2);
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 110, 71, 20));
        label_2->setFont(font2);
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 160, 71, 31));
        QFont font3;
        font3.setPointSize(12);
        label_3->setFont(font3);
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 220, 111, 31));
        label_4->setFont(font3);
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 280, 91, 21));
        label_5->setFont(font3);
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 330, 63, 20));
        label_6->setFont(font3);
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 380, 91, 31));
        label_7->setFont(font3);
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 450, 81, 20));
        label_8->setFont(font3);
        lineEditId = new QLineEdit(groupBox_3);
        lineEditId->setObjectName("lineEditId");
        lineEditId->setGeometry(QRect(120, 50, 341, 31));
        lineEditId->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"border-color: rgb(255, 255, 255);"));
        lineEdit_Nom = new QLineEdit(groupBox_3);
        lineEdit_Nom->setObjectName("lineEdit_Nom");
        lineEdit_Nom->setGeometry(QRect(120, 115, 341, 31));
        lineEdit_Nom->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"border-color: rgb(255, 255, 255);"));
        lineEdit_Ta = new QLineEdit(groupBox_3);
        lineEdit_Ta->setObjectName("lineEdit_Ta");
        lineEdit_Ta->setGeometry(QRect(120, 450, 341, 31));
        lineEdit_Ta->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"border-color: rgb(255, 255, 255);"));
        lineEdit_Ca = new QLineEdit(groupBox_3);
        lineEdit_Ca->setObjectName("lineEdit_Ca");
        lineEdit_Ca->setGeometry(QRect(120, 390, 341, 31));
        lineEdit_Ca->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"border-color: rgb(255, 255, 255);"));
        lineEdit_h = new QTimeEdit(groupBox_3);
        lineEdit_h->setObjectName("lineEdit_h");
        lineEdit_h->setGeometry(QRect(120, 225, 341, 31));
        lineEdit_h->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        lineEdit_type = new QComboBox(groupBox_3);
        lineEdit_type->addItem(QString());
        lineEdit_type->addItem(QString());
        lineEdit_type->addItem(QString());
        lineEdit_type->addItem(QString());
        lineEdit_type->addItem(QString());
        lineEdit_type->setObjectName("lineEdit_type");
        lineEdit_type->setGeometry(QRect(120, 170, 341, 26));
        lineEdit_type->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        lineEdit_D = new QLineEdit(groupBox_3);
        lineEdit_D->setObjectName("lineEdit_D");
        lineEdit_D->setGeometry(QRect(120, 280, 341, 31));
        lineEdit_D->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"border-color: rgb(255, 255, 255);"));
        lineEdit_lieu = new QLineEdit(groupBox_3);
        lineEdit_lieu->setObjectName("lineEdit_lieu");
        lineEdit_lieu->setGeometry(QRect(120, 330, 341, 31));
        lineEdit_lieu->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"border-color: rgb(255, 255, 255);"));
        pushButtonAjouter = new QPushButton(groupBox_3);
        pushButtonAjouter->setObjectName("pushButtonAjouter");
        pushButtonAjouter->setGeometry(QRect(520, 70, 121, 41));
        pushButtonAjouter->setFont(font3);
        pushButtonAjouter->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"  background-color: rgb(240, 195, 0);   \n"
"border: 2px solid black;  /* couleur normale */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgb(112, 155, 220);\n"
"       /* quand la souris survole */\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
"\n"
""));
        pushButtonsupprimer = new QPushButton(groupBox_3);
        pushButtonsupprimer->setObjectName("pushButtonsupprimer");
        pushButtonsupprimer->setGeometry(QRect(520, 140, 121, 41));
        pushButtonsupprimer->setFont(font3);
        pushButtonsupprimer->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(240, 195, 0);\n"
"border: 2px solid black;     /* couleur normale */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgb(112, 155, 220);\n"
"       /* quand la souris survole */\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
""));
        pushButtonSauvegarder = new QPushButton(groupBox_3);
        pushButtonSauvegarder->setObjectName("pushButtonSauvegarder");
        pushButtonSauvegarder->setGeometry(QRect(520, 210, 121, 41));
        pushButtonSauvegarder->setFont(font3);
        pushButtonSauvegarder->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(240, 195, 0); \n"
"border: 2px solid black;    /* couleur normale */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgb(112, 155, 220);\n"
"       /* quand la souris survole */\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
""));
        pushButtonModifier = new QPushButton(groupBox_3);
        pushButtonModifier->setObjectName("pushButtonModifier");
        pushButtonModifier->setGeometry(QRect(520, 280, 121, 41));
        pushButtonModifier->setFont(font3);
        pushButtonModifier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(240, 195, 0);\n"
"border: 2px solid black;     /* couleur normale */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgb(112, 155, 220);\n"
"       /* quand la souris survole */\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
""));
        pushButtonTrier = new QPushButton(groupBox_3);
        pushButtonTrier->setObjectName("pushButtonTrier");
        pushButtonTrier->setGeometry(QRect(520, 350, 121, 41));
        pushButtonTrier->setFont(font3);
        pushButtonTrier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(240, 195, 0); \n"
"border: 2px solid black;    /* couleur normale */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgb(112, 155, 220);\n"
"       /* quand la souris survole */\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
""));
        pushButtonTrier_2 = new QPushButton(groupBox_3);
        pushButtonTrier_2->setObjectName("pushButtonTrier_2");
        pushButtonTrier_2->setGeometry(QRect(520, 420, 121, 41));
        pushButtonTrier_2->setFont(font3);
        pushButtonTrier_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(240, 195, 0); \n"
"border: 2px solid black;    /* couleur normale */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgb(112, 155, 220);\n"
"       /* quand la souris survole */\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
""));
        tableFormations = new QTableWidget(centralwidget);
        if (tableFormations->columnCount() < 8)
            tableFormations->setColumnCount(8);
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
        tableFormations->setObjectName("tableFormations");
        tableFormations->setGeometry(QRect(30, 530, 1011, 311));
        tableFormations->setStyleSheet(QString::fromUtf8("background-color: rgb(106, 166, 218);\n"
"color: rgb(0, 0, 0);\n"
"border-radius: 10px;"));
        tableFormations->setRowCount(0);
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(30, 10, 151, 101));
        label_9->setStyleSheet(QString::fromUtf8("border :none;"));
        label_9->setPixmap(QPixmap(QString::fromUtf8(":/img/551340347_4214510502130824_9073597560338004353_n-removebg-preview.png")));
        label_9->setScaledContents(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1920, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestions des formations", nullptr));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QString());
        pushButtonAjouter_2->setText(QCoreApplication::translate("MainWindow", "Formations", nullptr));
        pushButtonAjouter_3->setText(QCoreApplication::translate("MainWindow", "Formateurs", nullptr));
        pushButtonAjouter_4->setText(QCoreApplication::translate("MainWindow", "Employ\303\251es", nullptr));
        pushButtonAjouter_5->setText(QCoreApplication::translate("MainWindow", "les apprenants", nullptr));
        pushButtonAjouter_6->setText(QCoreApplication::translate("MainWindow", "les services", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Gestions des formations", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "    Id", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "   Nom", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "   Type", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "    Horaire", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "    Duree", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "    Lieu", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Capacite", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "    Tarif", nullptr));
        lineEdit_type->setItemText(0, QCoreApplication::translate("MainWindow", "Fran\303\247ais", nullptr));
        lineEdit_type->setItemText(1, QCoreApplication::translate("MainWindow", "Math", nullptr));
        lineEdit_type->setItemText(2, QCoreApplication::translate("MainWindow", "Science", nullptr));
        lineEdit_type->setItemText(3, QCoreApplication::translate("MainWindow", "Physique", nullptr));
        lineEdit_type->setItemText(4, QCoreApplication::translate("MainWindow", "Anglais", nullptr));

        pushButtonAjouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        pushButtonsupprimer->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        pushButtonSauvegarder->setText(QCoreApplication::translate("MainWindow", "Sauvegarder", nullptr));
        pushButtonModifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        pushButtonTrier->setText(QCoreApplication::translate("MainWindow", "Trier", nullptr));
        pushButtonTrier_2->setText(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableFormations->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableFormations->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableFormations->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableFormations->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Horaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableFormations->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Duree", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableFormations->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Lieu", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableFormations->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Capacite", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableFormations->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Tarif", nullptr));
        label_9->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
