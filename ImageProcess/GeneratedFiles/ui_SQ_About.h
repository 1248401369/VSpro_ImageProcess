/********************************************************************************
** Form generated from reading UI file 'SQ_About.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SQ_ABOUT_H
#define UI_SQ_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SQ_About
{
public:
    QLabel *About;
    QPushButton *AboutClose;

    void setupUi(QWidget *SQ_About)
    {
        if (SQ_About->objectName().isEmpty())
            SQ_About->setObjectName(QStringLiteral("SQ_About"));
        SQ_About->resize(283, 214);
        About = new QLabel(SQ_About);
        About->setObjectName(QStringLiteral("About"));
        About->setGeometry(QRect(90, 60, 131, 78));
        About->setStyleSheet(QStringLiteral("font: 57 14pt \"Adobe Myungjo Std M\";"));
        AboutClose = new QPushButton(SQ_About);
        AboutClose->setObjectName(QStringLiteral("AboutClose"));
        AboutClose->setGeometry(QRect(90, 160, 75, 23));

        retranslateUi(SQ_About);

        QMetaObject::connectSlotsByName(SQ_About);
    } // setupUi

    void retranslateUi(QWidget *SQ_About)
    {
        SQ_About->setWindowTitle(QApplication::translate("SQ_About", "SQ_About", Q_NULLPTR));
        About->setText(QApplication::translate("SQ_About", "2018.7.9", Q_NULLPTR));
        AboutClose->setText(QApplication::translate("SQ_About", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SQ_About: public Ui_SQ_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SQ_ABOUT_H
