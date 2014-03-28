#ifndef CALENIZERGUI_H
#define CALENIZERGUI_H

#include <QtWidgets/QMainWindow>
#include <iostream>
#include "ui_calenizergui.h"
#include "DisplayOutput.h"
#include "Logic.h"

class CalenizerGUI : public QMainWindow
{
	Q_OBJECT

public:
	CalenizerGUI(QWidget *parent = 0);
	~CalenizerGUI();

	void displayTasks(std::vector<Task*>* displayList);

public slots: void on_lineEdit_returnPressed();

private:
	int _g_current_row;

	Ui::CalenizerGUIClass ui;
	
	Parser _g_parser;
	Logic _g_logic;
};

#endif // CALENIZERGUI_H
