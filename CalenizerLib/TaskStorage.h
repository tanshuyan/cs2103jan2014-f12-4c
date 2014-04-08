// TaskStorage.h
// v1.1
// removed useless functions
#pragma once
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

class TaskStorage { 
private:
    std::string _fileName;		
	static const std::string _defaultFileName;
	std::ifstream _fileInput;
	std::ofstream _fileOutput;

public:
	TaskStorage();
	~TaskStorage();

	void writeFile(std::vector<Task*>);
	void loadFile(std::vector<Task*>&);
};
#endif