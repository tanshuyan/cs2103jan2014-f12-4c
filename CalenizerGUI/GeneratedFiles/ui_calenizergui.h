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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
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
    QTextEdit *textEdit_2;
    QLabel *label_2;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QFrame *line_6;
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
        label->setGeometry(QRect(30, 40, 101, 16));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(120, 40, 471, 20));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 290, 581, 51));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(10, 70, 581, 211));
        textEdit_2->setFrameShadow(QFrame::Sunken);
        textEdit_2->setLineWidth(7);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(210, 10, 181, 16));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(20, 90, 561, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(20, 120, 561, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(20, 150, 561, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(20, 180, 561, 20));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(20, 210, 561, 20));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(20, 240, 561, 20));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        CalenizerGUIClass->setCentralWidget(centralWidget);
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

        QMetaObject::connectSlotsByName(CalenizerGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *CalenizerGUIClass)
    {
        CalenizerGUIClass->setWindowTitle(QApplication::translate("CalenizerGUIClass", "CalenizerGUI", 0));
        label->setText(QApplication::translate("CalenizerGUIClass", "Enter command:", 0));
        label_2->setText(QApplication::translate("CalenizerGUIClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:600; color:#ffffff;\">Welcome to Calenizer!</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class CalenizerGUIClass: public Ui_CalenizerGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENIZERGUI_H
