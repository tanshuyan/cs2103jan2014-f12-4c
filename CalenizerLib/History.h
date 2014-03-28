//History.h
// v1.0
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

	static const std::string TASK_TIMED;
	static const std::string TASK_DEADLINE;
	static const std::string TASK_FLOAT;

public:
	History();

	void saveHistory(std::vector<Task*>);
	void clearRedo();

	//Returns success of undo operation
	bool History::undo(std::vector<Task*> &taskList);
	//Returns success of redo operation
	bool History::redo(std::vector<Task*> &taskList);
};

#endif
