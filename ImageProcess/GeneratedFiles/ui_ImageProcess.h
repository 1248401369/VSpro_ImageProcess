/********************************************************************************
** Form generated from reading UI file 'ImageProcess.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEPROCESS_H
#define UI_IMAGEPROCESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <sq_qopenglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_ImageProcessClass
{
public:
    QAction *action22;
    QAction *About;
    QAction *Database;
    QWidget *centralWidget;
    QLabel *ImageShow;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *OpenImage;
    QPushButton *SaveImage;
    QPushButton *ImageRecover;
    QPushButton *OpenStl;
    QPushButton *OpenCloudSTL;
    QPushButton *ThreeDRecover;
    QGroupBox *groupBox;
    QLabel *Message;
    SQ_QOpenGLWidget *OpenGLWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *ImageInfo;
    QPushButton *SaveCloudData;
    QPushButton *ReadCloudData;
    QCheckBox *KeyPoint;
    QPushButton *OpenCloudPCD;
    QLineEdit *KeyPointNumber;
    QPushButton *GetDepthImage2D;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImageProcessClass)
    {
        if (ImageProcessClass->objectName().isEmpty())
            ImageProcessClass->setObjectName(QStringLiteral("ImageProcessClass"));
        ImageProcessClass->resize(1267, 967);
        action22 = new QAction(ImageProcessClass);
        action22->setObjectName(QStringLiteral("action22"));
        About = new QAction(ImageProcessClass);
        About->setObjectName(QStringLiteral("About"));
        Database = new QAction(ImageProcessClass);
        Database->setObjectName(QStringLiteral("Database"));
        centralWidget = new QWidget(ImageProcessClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ImageShow = new QLabel(centralWidget);
        ImageShow->setObjectName(QStringLiteral("ImageShow"));
        ImageShow->setGeometry(QRect(20, 60, 600, 600));
        ImageShow->setFrameShape(QFrame::NoFrame);
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 10, 1221, 36));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        OpenImage = new QPushButton(horizontalLayoutWidget);
        OpenImage->setObjectName(QStringLiteral("OpenImage"));
        OpenImage->setIconSize(QSize(21, 16));

        horizontalLayout->addWidget(OpenImage);

        SaveImage = new QPushButton(horizontalLayoutWidget);
        SaveImage->setObjectName(QStringLiteral("SaveImage"));

        horizontalLayout->addWidget(SaveImage);

        ImageRecover = new QPushButton(horizontalLayoutWidget);
        ImageRecover->setObjectName(QStringLiteral("ImageRecover"));

        horizontalLayout->addWidget(ImageRecover);

        OpenStl = new QPushButton(horizontalLayoutWidget);
        OpenStl->setObjectName(QStringLiteral("OpenStl"));

        horizontalLayout->addWidget(OpenStl);

        OpenCloudSTL = new QPushButton(horizontalLayoutWidget);
        OpenCloudSTL->setObjectName(QStringLiteral("OpenCloudSTL"));

        horizontalLayout->addWidget(OpenCloudSTL);

        ThreeDRecover = new QPushButton(horizontalLayoutWidget);
        ThreeDRecover->setObjectName(QStringLiteral("ThreeDRecover"));

        horizontalLayout->addWidget(ThreeDRecover);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 670, 601, 51));
        Message = new QLabel(groupBox);
        Message->setObjectName(QStringLiteral("Message"));
        Message->setGeometry(QRect(10, 0, 581, 51));
        OpenGLWidget = new SQ_QOpenGLWidget(centralWidget);
        OpenGLWidget->setObjectName(QStringLiteral("OpenGLWidget"));
        OpenGLWidget->setGeometry(QRect(640, 60, 600, 560));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 730, 601, 156));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        ImageInfo = new QLineEdit(gridLayoutWidget);
        ImageInfo->setObjectName(QStringLiteral("ImageInfo"));

        gridLayout->addWidget(ImageInfo, 2, 0, 1, 1);

        SaveCloudData = new QPushButton(gridLayoutWidget);
        SaveCloudData->setObjectName(QStringLiteral("SaveCloudData"));

        gridLayout->addWidget(SaveCloudData, 3, 0, 1, 1);

        ReadCloudData = new QPushButton(gridLayoutWidget);
        ReadCloudData->setObjectName(QStringLiteral("ReadCloudData"));

        gridLayout->addWidget(ReadCloudData, 3, 1, 1, 1);

        KeyPoint = new QCheckBox(gridLayoutWidget);
        KeyPoint->setObjectName(QStringLiteral("KeyPoint"));

        gridLayout->addWidget(KeyPoint, 1, 1, 1, 1);

        OpenCloudPCD = new QPushButton(gridLayoutWidget);
        OpenCloudPCD->setObjectName(QStringLiteral("OpenCloudPCD"));

        gridLayout->addWidget(OpenCloudPCD, 1, 0, 1, 1);

        KeyPointNumber = new QLineEdit(gridLayoutWidget);
        KeyPointNumber->setObjectName(QStringLiteral("KeyPointNumber"));

        gridLayout->addWidget(KeyPointNumber, 2, 1, 1, 1);

        GetDepthImage2D = new QPushButton(gridLayoutWidget);
        GetDepthImage2D->setObjectName(QStringLiteral("GetDepthImage2D"));

        gridLayout->addWidget(GetDepthImage2D, 0, 1, 1, 1);

        ImageProcessClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ImageProcessClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1267, 30));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        ImageProcessClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageProcessClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ImageProcessClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImageProcessClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ImageProcessClass->setStatusBar(statusBar);

        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu->menuAction());
        menu->addAction(About);
        menu_2->addAction(Database);

        retranslateUi(ImageProcessClass);

        QMetaObject::connectSlotsByName(ImageProcessClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageProcessClass)
    {
        ImageProcessClass->setWindowTitle(QApplication::translate("ImageProcessClass", "ImageProcess", Q_NULLPTR));
        action22->setText(QApplication::translate("ImageProcessClass", "22", Q_NULLPTR));
        About->setText(QApplication::translate("ImageProcessClass", "About", Q_NULLPTR));
        Database->setText(QApplication::translate("ImageProcessClass", "Database", Q_NULLPTR));
        ImageShow->setText(QString());
        OpenImage->setText(QApplication::translate("ImageProcessClass", "\346\211\223\345\274\200\345\233\276\345\203\217", Q_NULLPTR));
        SaveImage->setText(QApplication::translate("ImageProcessClass", "\344\277\235\345\255\230\345\233\276\345\203\217", Q_NULLPTR));
        ImageRecover->setText(QApplication::translate("ImageProcessClass", "\345\244\204\347\220\206\345\233\276\347\211\207", Q_NULLPTR));
        OpenStl->setText(QApplication::translate("ImageProcessClass", "\346\211\223\345\274\200\344\270\211\347\273\264\345\233\276", Q_NULLPTR));
        OpenCloudSTL->setText(QApplication::translate("ImageProcessClass", "\346\211\223\345\274\200\347\202\271\344\272\221\345\233\276-STL", Q_NULLPTR));
        ThreeDRecover->setText(QApplication::translate("ImageProcessClass", "\346\212\245\350\255\246", Q_NULLPTR));
        groupBox->setTitle(QString());
        Message->setText(QString());
        SaveCloudData->setText(QString());
        ReadCloudData->setText(QString());
        KeyPoint->setText(QApplication::translate("ImageProcessClass", "KeyPoint", Q_NULLPTR));
        OpenCloudPCD->setText(QString());
        GetDepthImage2D->setText(QString());
        menu->setTitle(QApplication::translate("ImageProcessClass", "\345\205\263\344\272\216", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("ImageProcessClass", "\346\225\260\346\215\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageProcessClass: public Ui_ImageProcessClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEPROCESS_H
