// TaskStorage.cpp
// v1.1
// remove useless functions
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "taskStorage.h"

const std::string TaskStorage:: _defaultFileName = "CalenizerStorage.txt";	
const std::string TaskStorage::DELIMITER_SPACE = " ";
const std::string TaskStorage::TASK_DEADLINE = "DEADLINE";
const std::string TaskStorage::TASK_TIMED = "TIMED";
const std::string TaskStorage::TASK_FLOAT = "FLOAT";

TaskStorage::TaskStorage() {
	_fileName = _defaultFileName;
}

TaskStorage::~TaskStorage() {
}

void TaskStorage::writeFile(std::vector<Task*> taskList){
	_fileOutput.open(_fileName.c_str(), std::ios::trunc);
	for(unsigned int i=0; i<taskList.size() ; i++) {
		_fileOutput << taskList[i]->taskToString();
	}
	_fileOutput.close();
}

void TaskStorage::loadFile(std::vector<Task*>& taskList) {
	_fileInput.open(_fileName.c_str(), std::fstream::_Noreplace);

	std::string taskType;
	while(std::getline(_fileInput,taskType)) {
		while((taskType != TASK_FLOAT) && (taskType != TASK_DEADLINE) && (taskType != TASK_TIMED)) {
			std::getline(_fileInput, taskType);
		}

		if (taskType == TASK_DEADLINE){
			std::string taskContent;
			std::string content;
			//taskContent += taskType + "\n";
			for(int i = 1; i <= 3 ; i++) { // deadline task has 3 more attributes
			std::getline(_fileInput,content);
			taskContent += content + "\n";
			}

			TaskDeadline *newTask = new TaskDeadline;
			newTask->stringToTask(taskContent);
			taskList.push_back(newTask);
		} else if (taskType == TASK_FLOAT){
			std::string taskContent;
			std::string content; 
			//taskContent += taskType + "\n";
			for(int i = 1; i <= 2 ; i++) { // floating task has 2 more attributes
			std::getline(_fileInput,content);
			taskContent  += content + "\n";
			}

			TaskFloat *newTaskFloat = new TaskFloat;
			newTaskFloat->stringToTask(taskContent);
			taskList.push_back(newTaskFloat);
		} else if (taskType == TASK_TIMED){
			std::string taskContent;
			std::string content;
			//taskContent += taskType + "\n";
			for(int i = 1; i <= 4 ; i++) { // timed task has 4 more attributes
			std::getline(_fileInput,content);
			taskContent += content + "\n";
			}

			TaskTimed *newTaskTimed = new TaskTimed;
			newTaskTimed->stringToTask(taskContent);
			taskList.push_back(newTaskTimed);
		}
	}
	_fileInput.close();
}