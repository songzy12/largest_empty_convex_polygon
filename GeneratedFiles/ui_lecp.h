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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LECPClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LECPClass)
    {
        if (LECPClass->objectName().isEmpty())
            LECPClass->setObjectName(QStringLiteral("LECPClass"));
        LECPClass->resize(600, 400);
        menuBar = new QMenuBar(LECPClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        LECPClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LECPClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LECPClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(LECPClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        LECPClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(LECPClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LECPClass->setStatusBar(statusBar);

        retranslateUi(LECPClass);

        QMetaObject::connectSlotsByName(LECPClass);
    } // setupUi

    void retranslateUi(QMainWindow *LECPClass)
    {
        LECPClass->setWindowTitle(QApplication::translate("LECPClass", "LECP", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LECPClass: public Ui_LECPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LECP_H
