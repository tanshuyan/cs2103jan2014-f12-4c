//@author A0004695A

// Logic.h

#ifndef LOGIC_H
#define LOGIC_H

#include <string>
#include <sstream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include "Task.h"
#include "TaskDeadline.h"
#include "TaskFloat.h"
#include "TaskTimed.h"
#include "TaskFilter.h"
#include "TaskStorage.h"
#include "History.h"
#include "UIDisplay.h"
#include "AnalysedData.h"
#include "LogicParser.h"
#include "DisplayOutput.h"
#include "Logger.h"
#include "DateTime.h"
#include "Comparator.h"
#include "DateTimeResolver.h"
#include "TaskEditor.h"
#include "Exception.h"
#include "Message.h"

class Logic {
private:
	std::vector<Task*> _taskList;
	std::vector<Task*> _displayList;
	std::vector<std::vector<Task*>::iterator> _displayIndexList;
	DisplayOutput _actionMsg;
	TaskFilter _filter;
	History _History;
	TaskStorage _userStorage;
	LogicParser _parser;
	AnalysedData _currentDisplayType;
	DateTimeResolver _dateTimeResolver;
	TaskEditor _taskEditor;

	bool _loadStatus;
	bool _displayStatus;

	void executeCommand(AnalysedData &analysedData, DisplayOutput &displayOutput);

	void addTask(AnalysedData analysedData, DisplayOutput &displayOutput);
	void editTask(AnalysedData analysedData, DisplayOutput &displayOutput);
	void deleteTask(AnalysedData analysedData, DisplayOutput &displayOutput);
	void setComplete(AnalysedData analysedData, DisplayOutput &displayOutput);
	void setIncomplete(AnalysedData analysedData, DisplayOutput &displayOutput);
	void displayTask(AnalysedData analysedData, DisplayOutput &displayOutput);
	void undo(DisplayOutput &displayOutput);
	void redo(DisplayOutput &displayOutput);

	std::vector<Task*>::iterator indexToIterator(int index);
	bool isValidIndex(int index);
	void generateDisplayListIndex();
	void loadFileContent();
	void sortTaskList();

public:
	Logic();
	~Logic();
	DisplayOutput executeUserInput(std::string userInput);
};
#endif