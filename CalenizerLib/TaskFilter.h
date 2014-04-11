// TaskFilter.h
//updates the displayList and displayIndexList to show only the tasks that the user wants to see (i.e. only completed tasks, only tasks with search term inside)
// v1.2
// added search float == display float tasks also
// added sorting functions

#pragma once
#ifndef TASKFILTER_H
#define TASKFILTER_H

#include <algorithm>
#include <assert.h>
#include <string>
#include <sstream>
#include <vector>
#include "Task.h"
#include "TaskDeadline.h"
#include "TaskFloat.h"
#include "TaskTimed.h"
#include "DateTime.h"
#include "DisplayOutput.h"

class TaskFilter {
private:
	bool isTaskType(std::string);
	std::string toUpper(std::string);
	std::string markTask(const Task* taskToBeMarked, DateTime currentDateTime);
	void markDisplayList(const std::vector<Task*>& displayList, std::vector<std::string>& displayListStatus);
public:
	TaskFilter();
	//filters out tasks by complete/incomplete (specify at the bool)
	//post: returns false if no matching tasks are found
	bool search(std::vector<Task*> &taskList, std::vector<Task*> &displayList, std::vector<std::vector<Task*>::iterator> &displayIndexList, bool, std::vector<std::string> &displayListStatus);
	std::vector<Task*>::iterator indexToIterator(int index, std::vector<Task*> &taskList);
	//filters out tasks by search term (specify at the string)
	//post: returns false if matching tasks are found
	bool search(std::vector<Task*> &taskList, std::vector<Task*> &displayList, std::vector<std::vector<Task*>::iterator> &displayIndexList, std::string, std::vector<std::string> &displayListStatus);

	//displays all the tasks
	bool search(std::vector<Task*> &taskList, std::vector<Task*> &displayList, std::vector<std::vector<Task*>::iterator> &displayIndexList, std::vector<std::string> &displayListStatus);

	//displays today tasks
	bool search(std::vector<Task*> &taskList, std::vector<Task*> &displayList, std::vector<std::vector<Task*>::iterator> &displayIndexList, QDate, std::vector<std::string> &displayListStatus);
};

#endif