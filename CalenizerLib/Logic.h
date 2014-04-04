// Logic.h
// v 2.1
// updated logic to accomodate new architecture
// added sort function
#pragma once
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

	void addTask(AnalysedData, DisplayOutput&);
	void editTask(AnalysedData, DisplayOutput&);
	void deleteTask(AnalysedData, DisplayOutput&);
	void setComplete(AnalysedData, DisplayOutput&);
	void setIncomplete(AnalysedData, DisplayOutput&);
	// displayTask can only display the complete, incomplete, all and today
	void displayTask(AnalysedData, DisplayOutput&);
	void undo(DisplayOutput&);
	void redo(DisplayOutput&);

	std::vector<Task*>::iterator indexToIterator(int index);
	bool isValidIndex(int);
	void generateDisplayListIndex();
	void loadFileContent();
	void sortTaskList();
public:
	Logic();
	~Logic();

	DisplayOutput executeUserInput(std::string);
	
};

#endif