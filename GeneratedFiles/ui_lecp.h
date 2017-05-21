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
    QAction *polar_angle_sort;
    QAction *create_VG;
    QAction *saveFile;
    QAction *openFile;
    QAction *sortedDCEL;
    QAction *DCEL_animation;
    QAction *clearDCELAnimation;
    QAction *reset;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LECPClass)
    {
        if (LECPClass->objectName().isEmpty())
            LECPClass->setObjectName(QStringLiteral("LECPClass"));
        LECPClass->resize(995, 599);
        polar_angle_sort = new QAction(LECPClass);
        polar_angle_sort->setObjectName(QStringLiteral("polar_angle_sort"));
        create_VG = new QAction(LECPClass);
        create_VG->setObjectName(QStringLiteral("create_VG"));
        saveFile = new QAction(LECPClass);
        saveFile->setObjectName(QStringLiteral("saveFile"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/save.ico"), QSize(), QIcon::Normal, QIcon::Off);
        saveFile->setIcon(icon);
        openFile = new QAction(LECPClass);
        openFile->setObjectName(QStringLiteral("openFile"));
        sortedDCEL = new QAction(LECPClass);
        sortedDCEL->setObjectName(QStringLiteral("sortedDCEL"));
        DCEL_animation = new QAction(LECPClass);
        DCEL_animation->setObjectName(QStringLiteral("DCEL_animation"));
        clearDCELAnimation = new QAction(LECPClass);
        clearDCELAnimation->setObjectName(QStringLiteral("clearDCELAnimation"));
        reset = new QAction(LECPClass);
        reset->setObjectName(QStringLiteral("reset"));
        centralWidget = new QWidget(LECPClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        LECPClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LECPClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 995, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        LECPClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LECPClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LECPClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LECPClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LECPClass->setStatusBar(statusBar);

        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu->addAction(polar_angle_sort);
        menu->addAction(sortedDCEL);
        menu->addAction(create_VG);
        menu_2->addAction(saveFile);
        menu_2->addAction(openFile);
        menu_2->addAction(reset);
        menu_3->addAction(DCEL_animation);
        menu_3->addAction(clearDCELAnimation);
        mainToolBar->addAction(saveFile);

        retranslateUi(LECPClass);

        QMetaObject::connectSlotsByName(LECPClass);
    } // setupUi

    void retranslateUi(QMainWindow *LECPClass)
    {
        LECPClass->setWindowTitle(QApplication::translate("LECPClass", "LECP", Q_NULLPTR));
        polar_angle_sort->setText(QApplication::translate("LECPClass", "\346\236\201\350\247\222\346\216\222\345\272\217\357\274\210naive\357\274\211", Q_NULLPTR));
        create_VG->setText(QApplication::translate("LECPClass", "\347\224\237\346\210\220vg\345\233\276", Q_NULLPTR));
        saveFile->setText(QApplication::translate("LECPClass", "save file", Q_NULLPTR));
        openFile->setText(QApplication::translate("LECPClass", "open file", Q_NULLPTR));
        sortedDCEL->setText(QApplication::translate("LECPClass", "\346\236\201\350\247\222\346\216\222\345\272\217\357\274\210DCEL\357\274\211", Q_NULLPTR));
        DCEL_animation->setText(QApplication::translate("LECPClass", "DCEL\346\236\201\350\247\222\346\216\222\345\272\217\345\212\250\347\224\273", Q_NULLPTR));
        clearDCELAnimation->setText(QApplication::translate("LECPClass", "\346\270\205\346\245\232DCEL\345\212\250\347\224\273\346\274\224\347\244\272", Q_NULLPTR));
        reset->setText(QApplication::translate("LECPClass", "\351\207\215\347\275\256", Q_NULLPTR));
        menu->setTitle(QApplication::translate("LECPClass", "\346\223\215\344\275\234", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("LECPClass", "\346\226\207\344\273\266", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("LECPClass", "\345\212\250\347\224\273\346\274\224\347\244\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LECPClass: public Ui_LECPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LECP_H
