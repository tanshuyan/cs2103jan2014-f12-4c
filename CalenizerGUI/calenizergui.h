//v1.1
#ifndef CALENIZERGUI_H
#define CALENIZERGUI_H

#include <QtWidgets/QMainWindow>
#include <QShortcut>
#include <QCursor>
#include <QTimer>
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

	//void displayTasks(std::vector<Task*>* displayList);

private slots:
	//void on_lineEdit_returnPressed();
	void run();
	void checkAlphabet();
	void resetInput();
	void todayDisplay(); 
	//void updateDateTime();
	void initialiseTimeDate();

private:
	Ui::CalenizerGUIClass ui;

	void initialiseTableStyle();
	void initialiseTableSize();
	
	void initialiseShortcuts();
	void initialiseConnections();
	void initialiseTable(QTableWidget *table);
	void setColumnWidth(QTableWidget *table);
	void fixColumnWidth(QTableWidget *table);
	void getFeedback(DisplayOutput);
	void getTask(DisplayOutput, int);
	std::string setStatus(std::string);

	QPalette* palette;
	//QLineEdit* line;

	int _g_current_row;
	Logic _g_logic;

	static const QString ADD_MSG;
	static const QString DELETE_MSG;
	static const QString SEARCH_MSG;
	static const QString EDIT_MSG;
	static const QString COMPLETE_MSG;
	static const QString INCOMPLETE_MSG;
	static const QString UNDO_MSG;
	static const QString REDO_MSG;
	static const QString VIEW_MSG;
	static const QString QUIT_MSG;
	static const std::string EMPTY_STRING;
	static const std::string CMD_DISPLAY_TODAY;

	static const std::string STATUS_TRUE;
	static const std::string STATUS_FALSE;
	static const std::string STATUS_COMPLETE;
	static const std::string STATUS_INCOMPLETE;
	static const std::string STATUS_OVERDUE;
	static const std::string STATUS_ONGOING;

	static enum ColumnHeader {
		TASK_DESC, 
		TASK_DURATION, 
		TASK_STATUS,
	};
};

#endif // CALENIZERGUI_H
