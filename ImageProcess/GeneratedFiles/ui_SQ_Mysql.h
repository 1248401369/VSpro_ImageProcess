/********************************************************************************
** Form generated from reading UI file 'SQ_Mysql.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SQ_MYSQL_H
#define UI_SQ_MYSQL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SQ_Mysql
{
public:
    QPushButton *QueryData;
    QTableWidget *tableWidget;

    void setupUi(QWidget *SQ_Mysql)
    {
        if (SQ_Mysql->objectName().isEmpty())
            SQ_Mysql->setObjectName(QStringLiteral("SQ_Mysql"));
        SQ_Mysql->resize(506, 356);
        QueryData = new QPushButton(SQ_Mysql);
        QueryData->setObjectName(QStringLiteral("QueryData"));
        QueryData->setGeometry(QRect(380, 40, 101, 23));
        tableWidget = new QTableWidget(SQ_Mysql);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(20, 30, 341, 301));

        retranslateUi(SQ_Mysql);

        QMetaObject::connectSlotsByName(SQ_Mysql);
    } // setupUi

    void retranslateUi(QWidget *SQ_Mysql)
    {
        SQ_Mysql->setWindowTitle(QApplication::translate("SQ_Mysql", "SQ_Mysql", Q_NULLPTR));
        QueryData->setText(QApplication::translate("SQ_Mysql", "\346\237\245\350\257\242", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SQ_Mysql: public Ui_SQ_Mysql {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SQ_MYSQL_H
