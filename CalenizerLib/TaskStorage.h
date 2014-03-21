// TaskStorage.h

#pragma once
#ifndef TASKSTORAGE_H
#define TASKSTORAGE_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "task.h"
#include "taskDeadline.h"
#include "taskFloat.h"
#include "taskTimed.h"

class TaskStorage { 
private:
    std::string _fileName;		
	static const std::string _defaultFileName;
	std::vector<Task *> _taskList;

	std::ifstream _fileInput;
	std::ofstream _fileOutput;

	static const std::string DELIMITER_SPACE;
	static const std::string TASK_TIMED;
	static const std::string TASK_DEADLINE;
	static const std::string TASK_FLOAT;
public:
	TaskStorage();
	TaskStorage(std::string);
	~TaskStorage();

	void writeFile(std::vector<Task*>);
	void loadFile(std::vector<Task*>&);

	std::vector<Task*> loadStorage();
	void writeStorage(std::vector<Task*>);

};

#endif