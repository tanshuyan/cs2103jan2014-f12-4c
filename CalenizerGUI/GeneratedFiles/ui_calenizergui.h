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
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CalenizerGUIClass)
    {
        if (CalenizerGUIClass->objectName().isEmpty())
            CalenizerGUIClass->setObjectName(QStringLiteral("CalenizerGUIClass"));
        CalenizerGUIClass->resize(697, 536);
        centralWidget = new QWidget(CalenizerGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 40, 101, 16));
        QFont font;
        font.setFamily(QStringLiteral("Malgun Gothic"));
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(120, 40, 551, 20));
        QFont font1;
        font1.setFamily(QStringLiteral("Malgun Gothic"));
        lineEdit->setFont(font1);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(20, 430, 650, 50));
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
        label_2->setGeometry(QRect(470, 0, 251, 31));
        QFont font2;
        font2.setFamily(QStringLiteral("Malgun Gothic"));
        font2.setPointSize(10);
        label_2->setFont(font2);
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(20, 70, 650, 350));
        QFont font3;
        font3.setFamily(QStringLiteral("Malgun Gothic"));
        font3.setBold(false);
        font3.setWeight(50);
        tableWidget->setFont(font3);
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setFrameShadow(QFrame::Sunken);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setTabKeyNavigation(false);
        tableWidget->setProperty("showDropIndicator", QVariant(false));
        tableWidget->setDragDropOverwriteMode(false);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget->setTextElideMode(Qt::ElideNone);
        tableWidget->setSortingEnabled(true);
        tableWidget->setCornerButtonEnabled(false);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(0);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(true));
        CalenizerGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CalenizerGUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 697, 21));
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
        label->setText(QApplication::translate("CalenizerGUIClass", "Enter command:", 0));
        label_2->setText(QApplication::translate("CalenizerGUIClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt; font-weight:600; color:#000000;\">Calenizer</span></p></body></html>", 0));
#ifndef QT_NO_TOOLTIP
        tableWidget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tableWidget->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
    } // retranslateUi

};

namespace Ui {
    class CalenizerGUIClass: public Ui_CalenizerGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENIZERGUI_H
