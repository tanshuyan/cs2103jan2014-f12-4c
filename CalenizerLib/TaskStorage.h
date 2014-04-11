// TaskStorage.h

#ifndef TASKSTORAGE_H
#define TASKSTORAGE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Task.h"
#include "TaskDeadline.h"
#include "TaskFloat.h"
#include "TaskTimed.h"
#include "Logger.h"
#include "DisplayOutput.h"

class TaskStorage { 
private:
    std::string _fileName;		
	static const std::string _defaultFileName;
	std::ifstream _fileInput;
	std::ofstream _fileOutput;

public:
	TaskStorage();
	~TaskStorage();

	void writeFile(const std::vector<Task*> &taskList);
	void loadFile(std::vector<Task*> &taskList);
};
#endif