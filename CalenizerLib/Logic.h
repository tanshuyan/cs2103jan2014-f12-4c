// Logic.h

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

class Logic {
private:
	std::vector<Task*> _taskList;
	std::vector<Task*> _displayList;
	std::vector<std::vector<Task*>::iterator> _displayIndexList;
	UIDisplay _display;
	TaskFilter _filter;
	History _History;
	TaskStorage _userStorage;

	static const std::string TASK_TIMED;
	static const std::string TASK_DEADLINE;
	static const std::string TASK_FLOAT;
	bool _loadStatus;
	bool _displayStatus;

public:
	Logic();

	void addFloatTask(std::string taskDesc);
	void addDeadlineTask(std::string taskDesc, DateTime);
	void addTimedTask(std::string taskDesc, DateTime, DateTime);

	void deleteTask(int index);
	void editTask(int index, std::string taskDesc);
	void editTask(int index, std::string taskDesc, DateTime);
	void editTask(int index, std::string taskDesc, DateTime, DateTime);
	void toggleComplete(int index);
	void getIncompleteTasks();
	void getCompleteTasks();
	void searchTasks(std::string searchTerm);
	void undo();
	void redo();
	std::vector<Task*>::iterator indexToIterator(int index);

	void loadFileContent();
};

#endif