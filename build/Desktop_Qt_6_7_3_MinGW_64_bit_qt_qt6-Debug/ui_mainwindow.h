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
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_4;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_3;
    QLineEdit *lineEdit_id;
    QLineEdit *lineEdit_nom;
    QComboBox *lineEdit_type;
    QTimeEdit *lineEdit_h;
    QLineEdit *lineEdit_D;
    QLineEdit *lineEdit_lieu;
    QLineEdit *lineEdit_Ca;
    QLineEdit *lineEdit_Ta;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        QFont font;
        font.setPointSize(20);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 195, 0);\n"
"background-color: rgb(4, 4, 87);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(230, 40, 781, 551));
        QFont font1;
        font1.setBold(true);
        groupBox->setFont(font1);
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(106, 166, 218);"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(0, 90, 101, 31));
        QFont font2;
        font2.setPointSize(12);
        label_8->setFont(font2);
        label_8->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(106, 166, 218);"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 150, 101, 31));
        label_9->setFont(font2);
        label_9->setStyleSheet(QString::fromUtf8("border-color: rgb(252, 252, 252);\n"
"background-color: rgb(106, 166, 218);"));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 210, 101, 31));
        label_10->setFont(font2);
        label_10->setStyleSheet(QString::fromUtf8("border-color: rgb(252, 252, 252);\n"
"background-color: rgb(106, 166, 218);"));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 270, 101, 31));
        label_11->setFont(font2);
        label_11->setStyleSheet(QString::fromUtf8("border-color: rgb(252, 252, 252);\n"
"background-color: rgb(106, 166, 218);"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 330, 101, 31));
        label_4->setFont(font2);
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(106, 166, 218);"));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 390, 101, 31));
        label_12->setFont(font2);
        label_12->setStyleSheet(QString::fromUtf8("border-color: rgb(252, 252, 252);\n"
"background-color: rgb(106, 166, 218);"));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(20, 450, 101, 31));
        label_13->setFont(font2);
        label_13->setStyleSheet(QString::fromUtf8("border-color: rgb(252, 252, 252);\n"
"background-color: rgb(106, 166, 218);"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 500, 101, 31));
        label_3->setFont(font2);
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(106, 166, 218);"));
        lineEdit_id = new QLineEdit(groupBox);
        lineEdit_id->setObjectName("lineEdit_id");
        lineEdit_id->setGeometry(QRect(120, 90, 331, 31));
        lineEdit_id->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_nom = new QLineEdit(groupBox);
        lineEdit_nom->setObjectName("lineEdit_nom");
        lineEdit_nom->setGeometry(QRect(120, 150, 331, 31));
        lineEdit_nom->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_type = new QComboBox(groupBox);
        lineEdit_type->addItem(QString());
        lineEdit_type->addItem(QString());
        lineEdit_type->addItem(QString());
        lineEdit_type->addItem(QString());
        lineEdit_type->addItem(QString());
        lineEdit_type->addItem(QString());
        lineEdit_type->setObjectName("lineEdit_type");
        lineEdit_type->setGeometry(QRect(120, 210, 331, 31));
        lineEdit_type->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        lineEdit_h = new QTimeEdit(groupBox);
        lineEdit_h->setObjectName("lineEdit_h");
        lineEdit_h->setGeometry(QRect(120, 270, 331, 31));
        lineEdit_h->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        lineEdit_D = new QLineEdit(groupBox);
        lineEdit_D->setObjectName("lineEdit_D");
        lineEdit_D->setGeometry(QRect(120, 330, 331, 31));
        lineEdit_D->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_lieu = new QLineEdit(groupBox);
        lineEdit_lieu->setObjectName("lineEdit_lieu");
        lineEdit_lieu->setGeometry(QRect(120, 390, 331, 31));
        lineEdit_lieu->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_Ca = new QLineEdit(groupBox);
        lineEdit_Ca->setObjectName("lineEdit_Ca");
        lineEdit_Ca->setGeometry(QRect(120, 450, 331, 31));
        lineEdit_Ca->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_Ta = new QLineEdit(groupBox);
        lineEdit_Ta->setObjectName("lineEdit_Ta");
        lineEdit_Ta->setGeometry(QRect(120, 510, 331, 31));
        lineEdit_Ta->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(480, 200, 131, 51));
        pushButton->setFont(font2);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 195, 0);\n"
"color: rgb(0, 0, 0);\n"
"border-color: rgb(85, 255, 127);\n"
"border-radius: 8px;\n"
"\n"
"\n"
""));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(480, 280, 131, 51));
        pushButton_2->setFont(font2);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 195, 0);\n"
"border-radius: 8px;"));
        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(480, 360, 131, 51));
        pushButton_5->setFont(font2);
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 195, 0);\n"
"color: rgb(0, 0, 0);\n"
"border-radius: 8px;"));
        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(480, 440, 131, 51));
        pushButton_6->setFont(font2);
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 195, 0);\n"
"color: rgb(0, 0, 0);\n"
"border-radius: 8px;"));
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 620, 1021, 261));
        tableWidget->setStyleSheet(QString::fromUtf8("border-color: rgb(85, 170, 255);\n"
"background-color: rgb(106, 166, 218);"));
        tableWidget->setRowCount(3);
        tableWidget->setColumnCount(8);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(30, 160, 151, 431));
        groupBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(106, 166, 218);"));
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(10, 10, 131, 411));
        groupBox_3->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 195, 0);"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 50, 171, 91));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label->setPixmap(QPixmap(QString::fromUtf8("../../Downloads/551340347_4214510502130824_9073597560338004353_n-removebg-preview.png")));
        label->setScaledContents(true);
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
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des formations", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Gestion des formations", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "    Id ", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "  Nom", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "  Type", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "   Horaire", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "   Duree", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "   Lieu", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "  Capacite", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "    Tarif", nullptr));
        lineEdit_type->setItemText(0, QCoreApplication::translate("MainWindow", "......................", nullptr));
        lineEdit_type->setItemText(1, QCoreApplication::translate("MainWindow", "Francais", nullptr));
        lineEdit_type->setItemText(2, QCoreApplication::translate("MainWindow", "math", nullptr));
        lineEdit_type->setItemText(3, QCoreApplication::translate("MainWindow", "Science", nullptr));
        lineEdit_type->setItemText(4, QCoreApplication::translate("MainWindow", "Physique", nullptr));
        lineEdit_type->setItemText(5, QCoreApplication::translate("MainWindow", "Anglais", nullptr));

        pushButton->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Sauvgarder", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Horaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Duree", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Lieu", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Capacite", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Tarif", nullptr));
        groupBox_2->setTitle(QString());
        groupBox_3->setTitle(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
