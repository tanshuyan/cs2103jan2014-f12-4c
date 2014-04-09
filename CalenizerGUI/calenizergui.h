//v1.1
#ifndef CALENIZERGUI_H
#define CALENIZERGUI_H

#include <QtWidgets/QMainWindow>
#include <QShortcut>
#include <QCursor>
#include <QTimer>
#include <QScrollbar>
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

private slots:
	void run();
	void checkAlphabet();
	void resetInput();
	void displayAll(); 
	void updateDateTime();
	void scrollUp();
	void scrollDown();

private:
	Ui::CalenizerGUIClass ui;
	bool checkWord(QString input);

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
	static const std::string CMD_DISPLAY_ALL;

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
