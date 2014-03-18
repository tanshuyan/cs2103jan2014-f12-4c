//History.h

#pragma once
#ifndef HISTORY_H
#define HISTORY_H

#include <vector>
#include <stack>
#include "Task.h"

class History {
private:
	std::vector<Task*> _currHistory;
	std::stack<std::vector<Task*>> _prevHistorys;
	std::stack<std::vector<Task*>> _nextHistorys;

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
