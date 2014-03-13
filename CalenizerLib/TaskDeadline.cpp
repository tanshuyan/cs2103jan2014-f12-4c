// taskDeadline.cpp

#include <string>
#include <sstream>
#include <iostream>
#include "taskDeadline.h"
#include "DateTime.h"

const std::string TaskDeadline::STATUS_TRUE = "true";
const std::string TaskDeadline::STATUS_FALSE = "false";

TaskDeadline::TaskDeadline() {
	_completeStatus = false;
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

void TaskDeadline::setTask(std::string taskType, bool status, std::string taskDesc, DateTime deadline) {
	setTaskType(taskType);
	setCompleteStatus(status);
	setTaskDesc(taskDesc);
	setDeadline(deadline);
}

void TaskDeadline::setTaskType(std::string taskType) {
	_taskType = taskType;
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

std::string TaskDeadline::getTaskType() {
	return _taskType;
}

bool TaskDeadline::getCompleteStatus() {
	return _completeStatus;
}

std::string TaskDeadline::getTaskDesc() {
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

DateTime TaskDeadline::getDeadline() {
	return _deadline;
}

/*
std::string TaskDeadline::toStandardDateTime(){
	std::ostringstream output;

	std::ostringstream temp;

	// Add Day
	temp.fill('0');
	temp.width(2);
	temp << _deadline.getDate().getDay();
	output << temp;
	output << "/";

	// Add Month
	temp.str("");
	temp.clear();
	temp.fill('0');
	temp.width(2);
	temp << _deadline.getDate().getMonth();
	output << temp;
	output << "/";

	// Add Year
	temp.str("");
	temp.clear();
	temp.fill('0');
	temp.width(2);
	temp << _deadline.getDate().getYear();
	output << temp;

	output << " ";

	// Add Hour
	temp.str("");
	temp.clear();
	temp.fill('0');
	temp.width(2);
	temp << _deadline.getTime().getHour();
	output << temp;
	output << ":";

	// Add Min
	temp.str("");
	temp.clear();
	temp.fill('0');
	temp.width(2);
	temp << _deadline.getTime().getMin();
	output << temp;

	return output.str();
}
*/

std::string TaskDeadline::outputToString() {
	std::ostringstream output;
	output << getTaskType() << " "; 
	output << getTaskDesc() << " ";
	output << _deadline.dataToString() << " ";
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
	std::string taskType;
	std::string taskDesc;
	std::string dateTime;
	DateTime deadline;
	bool status;
	
	std::getline(input, taskType);
	std::getline(input, taskDesc);
	std::getline(input, dateTime);
	input >> status;
	deadline.dataFromString(dateTime);

	setTask(taskType, status, taskDesc, deadline);
}