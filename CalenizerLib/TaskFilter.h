// TaskFilter.h
//updates the displayList and displayIndexList to show only the tasks that the user wants to see (i.e. only completed tasks, only tasks with search term inside)
// v1.1
#pragma once
#ifndef TASKFILTER_H
#define TASKFILTER_H

#include <string>
#include <sstream>
#include <vector>
#include "Task.h"

class TaskFilter {
private:


public:
	TaskFilter();
	
	//std::vector<std::vector<Task>::iterator> search(std::vector<Task>, bool, std::string, int, int, int, int, int);
	
	//filters out tasks by complete/incomplete (specify at the bool)
	//post: returns false if no matching tasks are found
	bool search(std::vector<Task*> &taskList, std::vector<Task*> &displayList, std::vector<std::vector<Task*>::iterator> &displayIndexList, bool);
	
	//filters out tasks by search term (specify at the string)
	//post: returns false if matching tasks are found
	bool search(std::vector<Task*> &taskList, std::vector<Task*> &displayList, std::vector<std::vector<Task*>::iterator> &displayIndexList, std::string);

	//displays all the tasks
	bool search(std::vector<Task*> &taskList, std::vector<Task*> &displayList, std::vector<std::vector<Task*>::iterator> &displayIndexList);

};

#endif