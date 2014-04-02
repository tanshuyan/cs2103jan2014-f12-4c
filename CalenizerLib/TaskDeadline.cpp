// TaskDeadline.cpp
// v1.2
// removed setTaskType, moved tasktype-setting to the constructor
// added taskDetailsToString
#include <string>
#include <sstream>
#include <iostream>
#include "taskDeadline.h"
#include "DateTime.h"

const std::string TaskDeadline::TASK_DEADLINE = "DEADLINE";
const std::string TaskDeadline::STATUS_TRUE = "true";
const std::string TaskDeadline::STATUS_FALSE = "false";

TaskDeadline::TaskDeadline() {
	_completeStatus = false;
	_taskType = TASK_DEADLINE;
}
/*
TaskDeadline::TaskDeadline(TaskType taskType, bool status, std::string taskDesc, DateTime deadline) {
	setTaskType(taskType);
	setCompleteStatus(status);
	setTaskDesc(taskDesc);
	setDeadline(deadline);
}
*/
TaskDeadline::~TaskDeadline(){
}

void TaskDeadline::setTask(bool status, std::string taskDesc, DateTime deadline) {
	setCompleteStatus(status);
	setTaskDesc(taskDesc);
	setDeadline(deadline);
}

void TaskDeadline::setCompleteStatus(bool status) {
	if(status == true) {
		_completeStatus = true;
	} else {
		_completeStatus = false;
	}
}

void TaskDeadline::setTaskDesc(std::string taskDesc) {
	_taskDesc = taskDesc;
}

void TaskDeadline::setDeadline(DateTime deadline) {
	_deadline = deadline;
}

std::string TaskDeadline::getTaskType() const {
	return _taskType;
}

bool TaskDeadline::getCompleteStatus() const {
	return _completeStatus;
}

std::string TaskDeadline::getTaskDesc() const {
	return _taskDesc;
}

std::string TaskDeadline::statusToString() {
	if(_completeStatus) {
		return STATUS_TRUE;
	} else {
		return STATUS_FALSE;
	}
}

std::string TaskDeadline::dateTimeToString() {
	return _deadline.dataToString();
}

DateTime TaskDeadline::getDeadline() const {
	return _deadline;
}

std::string TaskDeadline::outputToString() {
	std::ostringstream output;
	output << getTaskType() << "<>"; 
	output << getTaskDesc() << "<>";
	output << _deadline.dateToString(true) << " " << _deadline.timeToString() << "<>";
	output << statusToString() << std::endl;
	return output.str();
}

std::string TaskDeadline::taskDetailsToString() {
	std::ostringstream output;
	output << getTaskDesc() << std::endl;
	output << dateTimeToString() << std::endl;
	output << statusToString() << std::endl;
	return output.str();
}


std::string TaskDeadline::taskToString() {
	std::ostringstream output;
	output << getTaskType() << std::endl; 
	output << getTaskDesc() << std::endl;
	output << dateTimeToString() << std::endl;
	output << statusToString() << std::endl;
	return output.str();
}

void TaskDeadline::stringToTask(std::string content) {
	std::istringstream input(content);
	std::string taskDesc;
	std::string dateTime;
	DateTime deadline;
	std::string statusString;
	bool status;

	std::getline(input, taskDesc);
	std::getline(input, dateTime);
	input >> statusString;
	if (statusString == STATUS_TRUE){
		status = true;
	}
	else{
		status = false;
	}
	deadline.dataFromString(dateTime);

	setTask(status, taskDesc, deadline);
}

//bool TaskDeadline::operator<(TaskDeadline taskDeadline) {
	//return (_deadline < taskDeadline.getDeadline());
//}