// TaskFloat.h
// v1.1
// added operator <
#pragma once
#ifndef TaskFloat_H
#define TaskFloat_H

#include <string>
#include <sstream>
#include "task.h"
#include "DateTime.h"

class TaskFloat: public Task {
private:

	std::string _taskType;
	std::string _taskDesc;
	bool _completeStatus;
	static const std::string STATUS_FALSE;
	static const std::string STATUS_TRUE;


public:
	TaskFloat();
	//TaskFloat(TaskType, bool, std::string);
	~TaskFloat();

	void setTask(std::string, bool, std::string);
	void setTask(std::string, bool, std::string, DateTime) {return;}
	void setTask(std::string, bool, std::string, DateTime, DateTime) {return;}
	void setCompleteStatus(bool);
	void setTaskDesc(std::string);
	void setTaskType(std::string);
	void setDeadline(DateTime) {return;}
	void setStartDate(DateTime) {return;}
	
	DateTime getDeadline() const {return DateTime::DateTime();}
	DateTime getStartDate() const {return DateTime::DateTime();}  

	std::string getTaskDesc() const ;
	std::string getTaskType() const ;
	std::string dateTimeToString() {return "";}
	std::string statusToString();
	bool getCompleteStatus() const ;
	std::string outputToString();
	// for storage
	std::string taskToString();
	void stringToTask(std::string);
	//bool operator<(TaskFloat) {return false;}
};

#endif
