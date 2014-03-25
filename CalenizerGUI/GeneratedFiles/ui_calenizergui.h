/********************************************************************************
** Form generated from reading UI file 'calenizergui.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALENIZERGUI_H
#define UI_CALENIZERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalenizerGUIClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLineEdit *lineEdit;
    QTextEdit *textEdit;
    QLabel *label_2;
    QTableWidget *tableWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QLabel *label_3;
    QLCDNumber *lcdNumber;
    QLabel *label_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CalenizerGUIClass)
    {
        if (CalenizerGUIClass->objectName().isEmpty())
            CalenizerGUIClass->setObjectName(QStringLiteral("CalenizerGUIClass"));
        CalenizerGUIClass->resize(600, 400);
        centralWidget = new QWidget(CalenizerGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 101, 16));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(90, 40, 471, 20));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 320, 571, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(210, 10, 181, 16));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 5)
            tableWidget->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem7);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(90, 110, 371, 181));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(90, 90, 161, 80));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 300, 101, 16));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(500, 250, 64, 23));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(480, 230, 111, 16));
        CalenizerGUIClass->setCentralWidget(centralWidget);
        tabWidget->raise();
        label->raise();
        lineEdit->raise();
        textEdit->raise();
        label_2->raise();
        tableWidget->raise();
        label_3->raise();
        lcdNumber->raise();
        label_4->raise();
        menuBar = new QMenuBar(CalenizerGUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        CalenizerGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CalenizerGUIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CalenizerGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CalenizerGUIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CalenizerGUIClass->setStatusBar(statusBar);

        retranslateUi(CalenizerGUIClass);
        QObject::connect(lineEdit, SIGNAL(returnPressed()), textEdit, SLOT(copy()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(CalenizerGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *CalenizerGUIClass)
    {
        CalenizerGUIClass->setWindowTitle(QApplication::translate("CalenizerGUIClass", "CalenizerGUI", 0));
        label->setText(QApplication::translate("CalenizerGUIClass", "Enter command:", 0));
        label_2->setText(QApplication::translate("CalenizerGUIClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#000000;\">Welcome to Calenizer!</span></p></body></html>", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CalenizerGUIClass", "Index", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CalenizerGUIClass", "Description", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("CalenizerGUIClass", "Time and Date", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("CalenizerGUIClass", "New Row", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("CalenizerGUIClass", "New Row", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("CalenizerGUIClass", "New Row", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem6->setText(QApplication::translate("CalenizerGUIClass", "New Row", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem7->setText(QApplication::translate("CalenizerGUIClass", "New Row", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("CalenizerGUIClass", "Today Tasks", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("CalenizerGUIClass", "All Tasks", 0));
        label_3->setText(QApplication::translate("CalenizerGUIClass", "System Feedback", 0));
        label_4->setText(QApplication::translate("CalenizerGUIClass", "No. of tasks for today", 0));
    } // retranslateUi

};

namespace Ui {
    class CalenizerGUIClass: public Ui_CalenizerGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENIZERGUI_H
