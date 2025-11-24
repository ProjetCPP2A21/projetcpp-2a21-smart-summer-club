/********************************************************************************
** Form generated from reading UI file 'statistic.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTIC_H
#define UI_STATISTIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_Statistic
{
public:

    void setupUi(QDialog *Statistic)
    {
        if (Statistic->objectName().isEmpty())
            Statistic->setObjectName("Statistic");
        Statistic->resize(676, 403);
        Statistic->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        retranslateUi(Statistic);

        QMetaObject::connectSlotsByName(Statistic);
    } // setupUi

    void retranslateUi(QDialog *Statistic)
    {
        Statistic->setWindowTitle(QCoreApplication::translate("Statistic", "Statistique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Statistic: public Ui_Statistic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTIC_H
