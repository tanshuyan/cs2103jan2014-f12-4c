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
#include "Task.h"
#include "taskDeadline.h"
#include "TaskFloat.h"
#include "TaskTimed.h"
#include "TaskFilter.h"
#include "TaskStorage.h"
#include "History.h"
#include "UIDisplay.h"
#include "AnalysedData.h"
#include "Parser.h"
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
	Parser _parser;
	AnalysedData _currentDisplayType;
	DateTimeResolver _dateTimeResolver;
	TaskEditor _taskEditor;

	static const std::string TASK_TIMED;
	static const std::string TASK_DEADLINE;
	static const std::string TASK_FLOAT;
	bool _loadStatus;
	bool _displayStatus;

	static const std::string CMD_ADD;
	static const std::string CMD_EDIT;
	static const std::string CMD_DELETE;
	static const std::string CMD_DISPLAY;
	static const std::string CMD_EXIT;
	static const std::string CMD_SEARCH;
	static const std::string CMD_COMPLETE;
	static const std::string CMD_INCOMPLETE;
	static const std::string CMD_UNDO;
	static const std::string CMD_REDO;
	static const std::string CMD_INVALID;

	static const std::string DISPLAY_ALL;
	static const std::string DISPLAY_COMPLETE;
	static const std::string DISPLAY_INCOMPLETE;
	static const std::string DISPLAY_TODAY;


	void addTask(AnalysedData, DisplayOutput&);
	void editTask(AnalysedData, DisplayOutput&);
	void deleteTask(AnalysedData, DisplayOutput&);
	void setComplete(AnalysedData, DisplayOutput&);
	void setIncomplete(AnalysedData, DisplayOutput&);
	// displayTask can only display the complete, incomplete, all and today
	void displayTask(AnalysedData, DisplayOutput&);
	void searchTasks(AnalysedData, DisplayOutput&);
	void undo(DisplayOutput&);
	void redo(DisplayOutput&);

	std::vector<Task*>::iterator indexToIterator(int index);
	void generateDisplayListIndex();
	bool isValidIndex(int);
	void loadFileContent();
	void sortTaskList();
	void mergeSortedList(std::vector<Task*> &sortedDisplayList, std::vector<Task*> &timedList, std::vector<Task*> &deadlineList, std::vector<Task*> &floatList);
	void orderSortedList(std::vector<Task*> &sortedTaskList, std::vector<Task*> &sortedList);
public:
	Logic();
	~Logic();

	DisplayOutput executeUserInput(std::string);
	
};

#endif