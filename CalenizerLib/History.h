// History.cpp
// v1.2
// changed the function for deep copies to taskDetailsToString()
// fixed a bug in undo, deep copies
// modularise functions
#pragma once
#ifndef HISTORY_H
#define HISTORY_H

#include <vector>
#include <stack>
#include "Task.h"
#include "TaskDeadline.h"
#include "TaskFloat.h"
#include "TaskTimed.h"

class History {
private:
	std::vector<Task*> _currHistory;
	std::vector<Task*> _deleteTaskList;
	std::stack<std::vector<Task*>> _prevHistorys;
	std::stack<std::vector<Task*>> _nextHistorys;

public:
	History();

	void saveHistory(std::vector<Task*> &);
	void clearRedo();

	void createDeepCopy(std::vector<Task*> &, std::vector<Task*> &);

	//Returns success of undo operation
	bool History::undo(std::vector<Task*> &taskList);
	//Returns success of redo operation
	bool History::redo(std::vector<Task*> &taskList);
};

#endif
