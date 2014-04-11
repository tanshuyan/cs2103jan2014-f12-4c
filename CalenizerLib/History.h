// History.h

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

	void saveHistory(std::vector<Task*> &taskList);
	void clearRedo();

	void createDeepCopy(std::vector<Task*> &taskList, std::vector<Task*> &copyList);

	//Returns success of undo operation
	bool History::undo(std::vector<Task*> &taskList);
	//Returns success of redo operation
	bool History::redo(std::vector<Task*> &taskList);
};

#endif
