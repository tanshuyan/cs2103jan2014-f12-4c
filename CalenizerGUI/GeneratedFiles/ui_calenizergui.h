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
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
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
    QCalendarWidget *calendarWidget;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CalenizerGUIClass)
    {
        if (CalenizerGUIClass->objectName().isEmpty())
            CalenizerGUIClass->setObjectName(QStringLiteral("CalenizerGUIClass"));
        CalenizerGUIClass->resize(992, 533);
        centralWidget = new QWidget(CalenizerGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(790, 0, 151, 61));
        QFont font;
        font.setFamily(QStringLiteral("Malgun Gothic"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setLayoutDirection(Qt::RightToLeft);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 40, 711, 35));
        QFont font1;
        font1.setFamily(QStringLiteral("Malgun Gothic"));
        lineEdit->setFont(font1);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(750, 220, 221, 251));
        textEdit->setFont(font1);
        textEdit->setFocusPolicy(Qt::NoFocus);
        textEdit->setContextMenuPolicy(Qt::NoContextMenu);
        textEdit->setInputMethodHints(Qt::ImhNone);
        textEdit->setFrameShape(QFrame::NoFrame);
        textEdit->setFrameShadow(QFrame::Plain);
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit->setReadOnly(true);
        textEdit->setTextInteractionFlags(Qt::NoTextInteraction);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(600, -10, 131, 31));
        QFont font2;
        font2.setFamily(QStringLiteral("Malgun Gothic"));
        font2.setPointSize(10);
        label_2->setFont(font2);
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(20, 79, 711, 341));
        QFont font3;
        font3.setFamily(QStringLiteral("Malgun Gothic"));
        font3.setPointSize(10);
        font3.setBold(false);
        font3.setWeight(50);
        tableWidget->setFont(font3);
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->setFrameShape(QFrame::StyledPanel);
        tableWidget->setFrameShadow(QFrame::Raised);
        tableWidget->setLineWidth(5);
        tableWidget->setMidLineWidth(3);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setTabKeyNavigation(false);
        tableWidget->setProperty("showDropIndicator", QVariant(false));
        tableWidget->setDragDropOverwriteMode(false);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget->setTextElideMode(Qt::ElideNone);
        tableWidget->setSortingEnabled(false);
        tableWidget->setCornerButtonEnabled(false);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(0);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(true));
        calendarWidget = new QCalendarWidget(centralWidget);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setGeometry(QRect(750, 70, 221, 141));
        calendarWidget->setAutoFillBackground(true);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 420, 141, 61));
        QFont font4;
        font4.setFamily(QStringLiteral("Malgun Gothic"));
        font4.setBold(false);
        font4.setWeight(50);
        label_3->setFont(font4);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(640, 420, 71, 61));
        label_4->setFont(font1);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(490, 420, 111, 61));
        label_5->setFont(font1);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(330, 420, 151, 61));
        label_6->setFont(font1);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(180, 420, 131, 61));
        QFont font5;
        font5.setFamily(QStringLiteral("Malgun Gothic"));
        font5.setPointSize(8);
        label_7->setFont(font5);
        CalenizerGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CalenizerGUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 992, 21));
        CalenizerGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CalenizerGUIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CalenizerGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CalenizerGUIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CalenizerGUIClass->setStatusBar(statusBar);
        QWidget::setTabOrder(tableWidget, lineEdit);

        retranslateUi(CalenizerGUIClass);
        QObject::connect(lineEdit, SIGNAL(returnPressed()), textEdit, SLOT(copy()));
        QObject::connect(lineEdit, SIGNAL(returnPressed()), tableWidget, SLOT(doItemsLayout()));

        QMetaObject::connectSlotsByName(CalenizerGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *CalenizerGUIClass)
    {
        CalenizerGUIClass->setWindowTitle(QApplication::translate("CalenizerGUIClass", "CalenizerGUI", 0));
        label->setText(QApplication::translate("CalenizerGUIClass", "a", 0));
        label_2->setText(QApplication::translate("CalenizerGUIClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt; font-weight:600; color:#000000;\">Calenizer</span></p></body></html>", 0));
#ifndef QT_NO_TOOLTIP
        tableWidget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tableWidget->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        label_3->setText(QApplication::translate("CalenizerGUIClass", "<html><head/><body><p><span style=\" font-size:10pt;\">[</span><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\">a</span><span style=\" font-size:10pt;\">]dd </span></p><p><span style=\" font-size:10pt;\">[</span><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\">c</span><span style=\" font-size:10pt;\">]omplete </span></p></body></html>", 0));
        label_4->setText(QApplication::translate("CalenizerGUIClass", "<html><head/><body><p><span style=\" font-size:10pt;\">[</span><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\">v</span><span style=\" font-size:10pt;\">]iew </span></p><p><span style=\" font-size:10pt;\">[</span><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\">q</span><span style=\" font-size:10pt;\">]uit</span></p></body></html>", 0));
        label_5->setText(QApplication::translate("CalenizerGUIClass", "<html><head/><body><p><span style=\" font-size:10pt;\">[</span><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\">s</span><span style=\" font-size:10pt;\">]earch </span></p><p><span style=\" font-size:10pt;\">[</span><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\">u</span><span style=\" font-size:10pt;\">]ndo</span></p></body></html>", 0));
        label_6->setText(QApplication::translate("CalenizerGUIClass", "<html><head/><body><p><span style=\" font-size:10pt;\">[</span><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\">i</span><span style=\" font-size:10pt;\">]ncomplete </span></p><p><span style=\" font-size:10pt;\">[</span><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\">r</span><span style=\" font-size:10pt;\">]edo </span></p></body></html>", 0));
        label_7->setText(QApplication::translate("CalenizerGUIClass", "<html><head/><body><p><span style=\" font-size:10pt;\">[</span><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\">d</span><span style=\" font-size:10pt;\">]elete </span></p><p><span style=\" font-size:10pt;\">[</span><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\">e</span><span style=\" font-size:10pt;\">]dit </span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class CalenizerGUIClass: public Ui_CalenizerGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENIZERGUI_H
