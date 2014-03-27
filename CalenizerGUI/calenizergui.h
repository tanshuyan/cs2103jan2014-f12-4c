#ifndef CALENIZERGUI_H
#define CALENIZERGUI_H

#include <QtWidgets/QMainWindow>
#include "ui_calenizergui.h"
#include "Parser.h"

class CalenizerGUI : public QMainWindow
{
	Q_OBJECT

public:
	CalenizerGUI(QWidget *parent = 0);
	~CalenizerGUI();

public slots: void on_lineEdit_returnPressed();

private:
	Ui::CalenizerGUIClass ui;
	Parser _g_parser;
};

#endif // CALENIZERGUI_H
