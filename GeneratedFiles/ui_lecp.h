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
    QWidget *centralWidget;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QAction *polar_angle_sort;
    QAction *create_VG;
    QAction *saveFile;
    QAction *openFile;
    QAction *sortedDCEL;
    QAction *sortMenu;
    QAction *vgMenu;
    QAction *chainMenu;
    QAction *DCEL_animation;
    QAction *clearDCELAnimation;
    QAction *reset;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_show;
    QToolBar *showContent;
    QToolBar *showControl;

    void setupUi(QMainWindow *LECPClass)
    {
        if (LECPClass->objectName().isEmpty())
            LECPClass->setObjectName(QStringLiteral("LECPClass"));
        LECPClass->resize(995, 605);
        randomPoints = new QAction(LECPClass);
        randomPoints->setObjectName(QStringLiteral("randomPoints"));
        actionConvex_Chain = new QAction(LECPClass);
        actionConvex_Chain->setObjectName(QStringLiteral("actionConvex_Chain"));
        centralWidget = new QWidget(LECPClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        statusBar = new QStatusBar(centralWidget);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setGeometry(QRect(0, 547, 991, 21));
        LECPClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LECPClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 995, 21));
        polar_angle_sort = new QAction(menuBar);
        polar_angle_sort->setObjectName(QStringLiteral("polar_angle_sort"));
        create_VG = new QAction(menuBar);
        create_VG->setObjectName(QStringLiteral("create_VG"));
        saveFile = new QAction(menuBar);
        saveFile->setObjectName(QStringLiteral("saveFile"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/save.ico"), QSize(), QIcon::Normal, QIcon::Off);
        saveFile->setIcon(icon);
        openFile = new QAction(menuBar);
        openFile->setObjectName(QStringLiteral("openFile"));
        sortedDCEL = new QAction(menuBar);
        sortedDCEL->setObjectName(QStringLiteral("sortedDCEL"));
        sortMenu = new QAction(menuBar);
        sortMenu->setObjectName(QStringLiteral("sortMenu"));
        vgMenu = new QAction(menuBar);
        vgMenu->setObjectName(QStringLiteral("vgMenu"));
        chainMenu = new QAction(menuBar);
        chainMenu->setObjectName(QStringLiteral("chainMenu"));
        DCEL_animation = new QAction(menuBar);
        DCEL_animation->setObjectName(QStringLiteral("DCEL_animation"));
        clearDCELAnimation = new QAction(menuBar);
        clearDCELAnimation->setObjectName(QStringLiteral("clearDCELAnimation"));
        reset = new QAction(menuBar);
        reset->setObjectName(QStringLiteral("reset"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_show = new QMenu(menuBar);
        menu_show->setObjectName(QStringLiteral("menu_show"));
        LECPClass->setMenuBar(menuBar);
        showContent = new QToolBar(LECPClass);
        showContent->setObjectName(QStringLiteral("showContent"));
        LECPClass->addToolBar(Qt::TopToolBarArea, showContent);
        showControl = new QToolBar(LECPClass);
        showControl->setObjectName(QStringLiteral("showControl"));
        LECPClass->addToolBar(Qt::TopToolBarArea, showControl);

        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_show->menuAction());
        menu->addAction(polar_angle_sort);
        menu->addAction(sortedDCEL);
        menu->addAction(create_VG);
        menu->addAction(actionConvex_Chain);
        menu->addAction(randomPoints);
        menu_2->addAction(saveFile);
        menu_2->addAction(openFile);
        menu_2->addAction(reset);
        menu_3->addAction(DCEL_animation);
        menu_3->addAction(clearDCELAnimation);
        menu_show->addAction(sortMenu);
        menu_show->addAction(vgMenu);
        menu_show->addAction(chainMenu);

        retranslateUi(LECPClass);

        QMetaObject::connectSlotsByName(LECPClass);
    } // setupUi

    void retranslateUi(QMainWindow *LECPClass)
    {
        LECPClass->setWindowTitle(QApplication::translate("LECPClass", "LECP", Q_NULLPTR));
        randomPoints->setText(QApplication::translate("LECPClass", "\351\232\217\346\234\272\347\202\271\347\224\237\346\210\220", Q_NULLPTR));
        actionConvex_Chain->setText(QApplication::translate("LECPClass", "Convex Chain", Q_NULLPTR));
        polar_angle_sort->setText(QApplication::translate("LECPClass", "\346\236\201\350\247\222\346\216\222\345\272\217\357\274\210naive\357\274\211", Q_NULLPTR));
        create_VG->setText(QApplication::translate("LECPClass", "\347\224\237\346\210\220vg\345\233\276", Q_NULLPTR));
        saveFile->setText(QApplication::translate("LECPClass", "save file", Q_NULLPTR));
        openFile->setText(QApplication::translate("LECPClass", "open file", Q_NULLPTR));
        sortedDCEL->setText(QApplication::translate("LECPClass", "\346\236\201\350\247\222\346\216\222\345\272\217\357\274\210DCEL\357\274\211", Q_NULLPTR));
        sortMenu->setText(QApplication::translate("LECPClass", "final result", Q_NULLPTR));
        vgMenu->setText(QApplication::translate("LECPClass", "all points animation", Q_NULLPTR));
        chainMenu->setText(QApplication::translate("LECPClass", "simple point animation", Q_NULLPTR));
        DCEL_animation->setText(QApplication::translate("LECPClass", "DCEL\346\236\201\350\247\222\346\216\222\345\272\217\345\212\250\347\224\273", Q_NULLPTR));
        clearDCELAnimation->setText(QApplication::translate("LECPClass", "\346\270\205\351\231\244DCEL\345\212\250\347\224\273\346\274\224\347\244\272", Q_NULLPTR));
        reset->setText(QApplication::translate("LECPClass", "\351\207\215\347\275\256", Q_NULLPTR));
        menu->setTitle(QApplication::translate("LECPClass", "\346\223\215\344\275\234", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("LECPClass", "\346\226\207\344\273\266", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("LECPClass", "\345\212\250\347\224\273\346\274\224\347\244\272", Q_NULLPTR));
        menu_show->setTitle(QApplication::translate("LECPClass", "\345\212\250\347\224\273\346\274\224\347\244\272", Q_NULLPTR));
        showContent->setWindowTitle(QApplication::translate("LECPClass", "toolBar", Q_NULLPTR));
        showControl->setWindowTitle(QApplication::translate("LECPClass", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LECPClass: public Ui_LECPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LECP_H
