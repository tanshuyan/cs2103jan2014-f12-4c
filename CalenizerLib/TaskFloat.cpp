// taskDealine.cpp

#include <string>
#include <sstream>
#include <iostream>
#include "taskFloat.h"

const std::string TaskFloat::STATUS_TRUE = "true";
const std::string TaskFloat::STATUS_FALSE = "false";

/*
TaskFloat::TaskFloat(TaskType taskType, bool status, std::string taskDesc) {
	setTaskType(taskType);
	setCompleteStatus(status);
	setTaskDesc(taskDesc);
}
*/

TaskFloat::~TaskFloat(){
}

TaskFloat::TaskFloat() {
	_completeStatus = false;
}

void TaskFloat::setTask(std::string taskType, bool status, std::string taskDesc) {
	setTaskType(taskType);
	setCompleteStatus(status);
	setTaskDesc(taskDesc);
}

void TaskFloat::setTaskType(std::string taskType) {
	_taskType = taskType;
}

void TaskFloat::setCompleteStatus(bool status) {
	if(status == true) {
		_completeStatus = true;
	} else {
		_completeStatus = false;
	}
}

void TaskFloat::setTaskDesc(std::string taskDesc) {
	_taskDesc = taskDesc;
}

std::string TaskFloat::getTaskType() {
	return _taskType;
}

bool TaskFloat::getCompleteStatus() {
	return _completeStatus;
}

std::string TaskFloat::getTaskDesc() {
	return _taskDesc;
}

std::string TaskFloat::statusToString() {
	if(_completeStatus) {
		return STATUS_TRUE;
	} else {
		return STATUS_FALSE;
	}
}

std::string TaskFloat::outputToString() {
	std::ostringstream output;
	output << getTaskType() << " "; 
	output << getTaskDesc() << " ";
	output << statusToString() << std::endl;
	return output.str();
}


std::string TaskFloat::taskToString() {
	std::ostringstream output;
	output << getTaskType() << std::endl; 
	output << getTaskDesc() << std::endl;
	output << statusToString() << std::endl;
	return output.str();
}

void TaskFloat::stringToTask(std::string content) {
	std::istringstream input(content);
	std::string taskType;
	std::string dump;
	std::string taskDesc;
	bool status;
	
	std::getline(input, taskType);
	std::getline(input, taskDesc);
	input >> status;

	setTask(taskType, status, taskDesc);
}