// TaskTimed.cpp
// v1.3
// removed setTaskType, moved tasktype-setting to the constructor
// added taskDetailsToString
#include <string>
#include <sstream>
#include <iostream>
#include "TaskTimed.h"
#include "DateTime.h"

const std::string TaskTimed::TASK_TIMED = "TIMED";
const std::string TaskTimed::STATUS_TRUE = "true";
const std::string TaskTimed::STATUS_FALSE = "false";

TaskTimed::TaskTimed() {
	_completeStatus = false;
	_taskType = TASK_TIMED;
}

TaskTimed::~TaskTimed() {
}

void TaskTimed::setTask(bool status, std::string taskDesc, DateTime startDateTime, DateTime endDateTime) {
	setCompleteStatus(status);
	setTaskDesc(taskDesc);
	setStartDate(startDateTime);
	setDeadline(endDateTime);
}


void TaskTimed::setCompleteStatus(bool status) {
	if(status == true) {
		_completeStatus = true;
	} else {
		_completeStatus = false;
	}
}

void TaskTimed::setTaskDesc(std::string taskDesc) {
	_taskDesc = taskDesc;
}

void TaskTimed::setDeadline(DateTime deadline) {
	_endDateTime = deadline;
}

void TaskTimed::setStartDate(DateTime startDate) {
	_startDateTime = startDate;
}

std::string TaskTimed::getTaskType() const {
	return _taskType;
}

bool TaskTimed::getCompleteStatus() const {
	return _completeStatus;
}

DateTime TaskTimed::getDeadline() const {
	return _endDateTime;
}

DateTime TaskTimed::getStartDate() const {
	return _startDateTime;
}

std::string TaskTimed::getTaskDesc() const {
	return _taskDesc;
}

std::string TaskTimed::dateTimeToString() {
	std::ostringstream output;
	output << _startDateTime.dataToString() << std::endl;
	output << _endDateTime.dataToString();
	return output.str();
}

std::string TaskTimed::statusToString() {
	if(_completeStatus) {
		return STATUS_TRUE;
	} else {
		return STATUS_FALSE;
	}
}


std::string TaskTimed::outputToString() {
	std::ostringstream output;
	output << getTaskType() << "<>"; 
	output << getTaskDesc() << "<>";
	output << _startDateTime.dateToString(true) << " " << _startDateTime.timeToString() << " to " << _endDateTime.dateToString(true) << " " << _endDateTime.timeToString() << "<>";
	output << statusToString() << std::endl;
	return output.str();
}

std::string TaskTimed::taskDetailsToString() {
	std::ostringstream output;
	output << getTaskDesc() << std::endl;
	output << dateTimeToString() << std::endl;
	output << statusToString() << std::endl;
	return output.str();
}


std::string TaskTimed::taskToString() {
	std::ostringstream output;
	output << getTaskType() << std::endl; 
	output << getTaskDesc() << std::endl;
	output << dateTimeToString() << std::endl;
	output << statusToString() << std::endl;
	return output.str();
}

void TaskTimed::stringToTask(std::string content) {
	std::istringstream input(content);
	std::string taskDesc;
	std::string dateTime;
	std::string endDate;
	DateTime startDateTime;
	DateTime endDateTime;
	std::string statusString;
	bool status = false;

	std::getline(input, taskDesc);
	std::getline(input, dateTime);
	std::getline(input, endDate);
	input >> statusString;
	if (statusString == STATUS_TRUE){
		status = true;
	}
	else{
		status = false;
	}
	startDateTime.dataFromString(dateTime);
	endDateTime.dataFromString(endDate);

	setTask(status, taskDesc, startDateTime, endDateTime);
}

//bool TaskTimed::operator<(TaskTimed taskTimed) {
	//return (_startDateTime < taskTimed.getStartDate());
//}