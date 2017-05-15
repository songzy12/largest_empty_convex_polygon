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
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
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
        centralWidget = new QWidget(LECPClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        LECPClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LECPClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 995, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        LECPClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LECPClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LECPClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LECPClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LECPClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(polar_angle_sort);
        menu->addAction(create_VG);

        retranslateUi(LECPClass);

        QMetaObject::connectSlotsByName(LECPClass);
    } // setupUi

    void retranslateUi(QMainWindow *LECPClass)
    {
        LECPClass->setWindowTitle(QApplication::translate("LECPClass", "LECP", Q_NULLPTR));
        polar_angle_sort->setText(QApplication::translate("LECPClass", "\346\236\201\350\247\222\346\216\222\345\272\217", Q_NULLPTR));
        create_VG->setText(QApplication::translate("LECPClass", "\347\224\237\346\210\220vg\345\233\276", Q_NULLPTR));
        menu->setTitle(QApplication::translate("LECPClass", "\346\223\215\344\275\234", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LECPClass: public Ui_LECPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LECP_H
