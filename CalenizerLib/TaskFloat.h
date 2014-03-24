// TaskFloat.h

#pragma once
#ifndef TaskFloat_H
#define TaskFloat_H

#include <string>
#include <sstream>
#include "task.h"
#include "DateTime.h"

/*
enum TaskType {
		DEADLINE, FLOAT, TIMED
};
*/

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
	
	DateTime getDeadline() {return DateTime::DateTime();}
	DateTime getStartDate() {return DateTime::DateTime();}  

	std::string getTaskDesc();
	std::string getTaskType();
	std::string dateTimeToString() {return "";}
	std::string statusToString();
	bool getCompleteStatus();
	std::string outputToString();
	// for storage
	std::string taskToString();
	void stringToTask(std::string);
};

#endif
