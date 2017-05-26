/********************************************************************************
** Form generated from reading UI file 'lecp.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LECP_H
#define UI_LECP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LECPClass
{
public:
    QAction *randomPoints;
    QAction *actionConvex_Chain;
    QAction *startShow;
    QAction *lastPoint;
    QAction *nextPoint;
    QWidget *centralWidget;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QAction *polar_angle_sort;
    QAction *create_VG;
    QAction *saveFile;
    QAction *openFile;
    QAction *sortedDCEL;
    QAction *finalResultShow;
    QAction *allPointsShow;
    QAction *singlePointShow;
    QAction *DCEL_animation;
    QAction *clearDCELAnimation;
    QAction *reset;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QToolBar *operationsTB;
    QToolBar *pointSelectTB;
    QToolBar *strartShowTB;
    QToolBar *showContentTB;
    QToolBar *sortTB;
    QToolBar *qTB;
    QToolBar *lTB;
    QToolBar *showControlTB;

    void setupUi(QMainWindow *LECPClass)
    {
        if (LECPClass->objectName().isEmpty())
            LECPClass->setObjectName(QStringLiteral("LECPClass"));
        LECPClass->resize(961, 605);
        randomPoints = new QAction(LECPClass);
        randomPoints->setObjectName(QStringLiteral("randomPoints"));
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/rpoints.ico"), QSize(), QIcon::Normal, QIcon::Off);
        randomPoints->setIcon(icon);
        actionConvex_Chain = new QAction(LECPClass);
        actionConvex_Chain->setObjectName(QStringLiteral("actionConvex_Chain"));
        startShow = new QAction(LECPClass);
        startShow->setObjectName(QStringLiteral("startShow"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("Resources/start.ico"), QSize(), QIcon::Normal, QIcon::Off);
        startShow->setIcon(icon1);
        lastPoint = new QAction(LECPClass);
        lastPoint->setObjectName(QStringLiteral("lastPoint"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("Resources/left.ico"), QSize(), QIcon::Normal, QIcon::Off);
        lastPoint->setIcon(icon2);
        nextPoint = new QAction(LECPClass);
        nextPoint->setObjectName(QStringLiteral("nextPoint"));
        QIcon icon3;
        icon3.addFile(QStringLiteral("Resources/right.ico"), QSize(), QIcon::Normal, QIcon::Off);
        nextPoint->setIcon(icon3);
        centralWidget = new QWidget(LECPClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        statusBar = new QStatusBar(centralWidget);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setGeometry(QRect(0, 547, 991, 21));
        LECPClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LECPClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 961, 23));
        polar_angle_sort = new QAction(menuBar);
        polar_angle_sort->setObjectName(QStringLiteral("polar_angle_sort"));
        create_VG = new QAction(menuBar);
        create_VG->setObjectName(QStringLiteral("create_VG"));
        saveFile = new QAction(menuBar);
        saveFile->setObjectName(QStringLiteral("saveFile"));
        QIcon icon4;
        icon4.addFile(QStringLiteral("Resources/save.ico"), QSize(), QIcon::Normal, QIcon::Off);
        saveFile->setIcon(icon4);
        openFile = new QAction(menuBar);
        openFile->setObjectName(QStringLiteral("openFile"));
        QIcon icon5;
        icon5.addFile(QStringLiteral("Resources/open.ico"), QSize(), QIcon::Normal, QIcon::Off);
        openFile->setIcon(icon5);
        sortedDCEL = new QAction(menuBar);
        sortedDCEL->setObjectName(QStringLiteral("sortedDCEL"));
        finalResultShow = new QAction(menuBar);
        finalResultShow->setObjectName(QStringLiteral("finalResultShow"));
        QIcon icon6;
        icon6.addFile(QStringLiteral("Resources/final.ico"), QSize(), QIcon::Normal, QIcon::Off);
        finalResultShow->setIcon(icon6);
        allPointsShow = new QAction(menuBar);
        allPointsShow->setObjectName(QStringLiteral("allPointsShow"));
        QIcon icon7;
        icon7.addFile(QStringLiteral("Resources/points.ico"), QSize(), QIcon::Normal, QIcon::Off);
        allPointsShow->setIcon(icon7);
        singlePointShow = new QAction(menuBar);
        singlePointShow->setObjectName(QStringLiteral("singlePointShow"));
        QIcon icon8;
        icon8.addFile(QStringLiteral("Resources/point.ico"), QSize(), QIcon::Normal, QIcon::Off);
        singlePointShow->setIcon(icon8);
        DCEL_animation = new QAction(menuBar);
        DCEL_animation->setObjectName(QStringLiteral("DCEL_animation"));
        clearDCELAnimation = new QAction(menuBar);
        clearDCELAnimation->setObjectName(QStringLiteral("clearDCELAnimation"));
        reset = new QAction(menuBar);
        reset->setObjectName(QStringLiteral("reset"));
        QIcon icon9;
        icon9.addFile(QStringLiteral("Resources/clear.ico"), QSize(), QIcon::Normal, QIcon::Off);
        reset->setIcon(icon9);
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        LECPClass->setMenuBar(menuBar);
        operationsTB = new QToolBar(LECPClass);
        operationsTB->setObjectName(QStringLiteral("operationsTB"));
        LECPClass->addToolBar(Qt::TopToolBarArea, operationsTB);
        pointSelectTB = new QToolBar(LECPClass);
        pointSelectTB->setObjectName(QStringLiteral("pointSelectTB"));
        LECPClass->addToolBar(Qt::TopToolBarArea, pointSelectTB);
        strartShowTB = new QToolBar(LECPClass);
        strartShowTB->setObjectName(QStringLiteral("strartShowTB"));
        LECPClass->addToolBar(Qt::TopToolBarArea, strartShowTB);
        showContentTB = new QToolBar(LECPClass);
        showContentTB->setObjectName(QStringLiteral("showContentTB"));
        LECPClass->addToolBar(Qt::TopToolBarArea, showContentTB);
        LECPClass->insertToolBarBreak(showContentTB);
        sortTB = new QToolBar(LECPClass);
        sortTB->setObjectName(QStringLiteral("sortTB"));
        LECPClass->addToolBar(Qt::TopToolBarArea, sortTB);
        qTB = new QToolBar(LECPClass);
        qTB->setObjectName(QStringLiteral("qTB"));
        LECPClass->addToolBar(Qt::TopToolBarArea, qTB);
        lTB = new QToolBar(LECPClass);
        lTB->setObjectName(QStringLiteral("lTB"));
        LECPClass->addToolBar(Qt::TopToolBarArea, lTB);
        showControlTB = new QToolBar(LECPClass);
        showControlTB->setObjectName(QStringLiteral("showControlTB"));
        LECPClass->addToolBar(Qt::TopToolBarArea, showControlTB);

        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu->addAction(polar_angle_sort);
        menu->addAction(sortedDCEL);
        menu_3->addAction(clearDCELAnimation);
        menu_3->addAction(DCEL_animation);
        operationsTB->addAction(openFile);
        operationsTB->addAction(saveFile);
        operationsTB->addAction(reset);
        operationsTB->addAction(randomPoints);
        operationsTB->addAction(finalResultShow);
        operationsTB->addAction(allPointsShow);
        operationsTB->addAction(singlePointShow);
        pointSelectTB->addAction(lastPoint);
        pointSelectTB->addAction(nextPoint);
        strartShowTB->addAction(startShow);

        retranslateUi(LECPClass);

        QMetaObject::connectSlotsByName(LECPClass);
    } // setupUi

    void retranslateUi(QMainWindow *LECPClass)
    {
        LECPClass->setWindowTitle(QApplication::translate("LECPClass", "LECP", Q_NULLPTR));
        randomPoints->setText(QApplication::translate("LECPClass", "\351\232\217\346\234\272\347\202\271\347\224\237\346\210\220", Q_NULLPTR));
        actionConvex_Chain->setText(QApplication::translate("LECPClass", "Convex Chain", Q_NULLPTR));
        startShow->setText(QApplication::translate("LECPClass", "\345\274\200\345\247\213\345\212\250\347\224\273\346\274\224\347\244\272", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        startShow->setToolTip(QApplication::translate("LECPClass", "\345\274\200\345\247\213\345\212\250\347\224\273\346\274\224\347\244\272", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lastPoint->setText(QApplication::translate("LECPClass", "\344\270\212\344\270\200\347\202\271", Q_NULLPTR));
        nextPoint->setText(QApplication::translate("LECPClass", "\344\270\213\344\270\200\347\202\271", Q_NULLPTR));
        polar_angle_sort->setText(QApplication::translate("LECPClass", "\346\236\201\350\247\222\346\216\222\345\272\217\357\274\210naive\357\274\211", Q_NULLPTR));
        create_VG->setText(QApplication::translate("LECPClass", "\347\224\237\346\210\220vg\345\233\276", Q_NULLPTR));
        saveFile->setText(QApplication::translate("LECPClass", "\344\277\235\345\255\230\346\226\207\344\273\266", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        saveFile->setToolTip(QApplication::translate("LECPClass", "\344\277\235\345\255\230\346\226\207\344\273\266", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        openFile->setText(QApplication::translate("LECPClass", "\346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        openFile->setToolTip(QApplication::translate("LECPClass", "\344\277\235\345\255\230\346\226\207\344\273\266", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        sortedDCEL->setText(QApplication::translate("LECPClass", "\346\236\201\350\247\222\346\216\222\345\272\217\357\274\210DCEL\357\274\211", Q_NULLPTR));
        finalResultShow->setText(QApplication::translate("LECPClass", "\346\230\276\347\244\272\346\234\200\347\273\210\347\273\223\346\236\234", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        finalResultShow->setToolTip(QApplication::translate("LECPClass", "\346\230\276\347\244\272\346\234\200\347\273\210\347\273\223\346\236\234", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        allPointsShow->setText(QApplication::translate("LECPClass", "\346\211\200\346\234\211\347\202\271\346\274\224\347\244\272", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        allPointsShow->setToolTip(QApplication::translate("LECPClass", "\346\211\200\346\234\211\347\202\271\346\274\224\347\244\272", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        singlePointShow->setText(QApplication::translate("LECPClass", "\345\215\225\347\202\271\346\274\224\347\244\272", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        singlePointShow->setToolTip(QApplication::translate("LECPClass", "\345\215\225\347\202\271\346\274\224\347\244\272", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        DCEL_animation->setText(QApplication::translate("LECPClass", "DCEL\346\236\201\350\247\222\346\216\222\345\272\217\345\212\250\347\224\273", Q_NULLPTR));
        clearDCELAnimation->setText(QApplication::translate("LECPClass", "\346\270\205\351\231\244DCEL\345\212\250\347\224\273\346\274\224\347\244\272", Q_NULLPTR));
        reset->setText(QApplication::translate("LECPClass", "\351\207\215\347\275\256", Q_NULLPTR));
        menu->setTitle(QApplication::translate("LECPClass", "\346\223\215\344\275\234", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("LECPClass", "\346\226\207\344\273\266", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("LECPClass", "\345\212\250\347\224\273\346\274\224\347\244\272", Q_NULLPTR));
        operationsTB->setWindowTitle(QApplication::translate("LECPClass", "toolBar", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        operationsTB->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pointSelectTB->setWindowTitle(QApplication::translate("LECPClass", "toolBar", Q_NULLPTR));
        strartShowTB->setWindowTitle(QApplication::translate("LECPClass", "toolBar", Q_NULLPTR));
        showContentTB->setWindowTitle(QApplication::translate("LECPClass", "toolBar", Q_NULLPTR));
        sortTB->setWindowTitle(QApplication::translate("LECPClass", "toolBar", Q_NULLPTR));
        qTB->setWindowTitle(QApplication::translate("LECPClass", "toolBar", Q_NULLPTR));
        lTB->setWindowTitle(QApplication::translate("LECPClass", "toolBar_2", Q_NULLPTR));
        showControlTB->setWindowTitle(QApplication::translate("LECPClass", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LECPClass: public Ui_LECPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LECP_H
