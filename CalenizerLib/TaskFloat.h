//@author A0094659L

// TaskFloat.h

#ifndef TaskFloat_H
#define TaskFloat_H

#include <iostream>
#include <string>
#include <sstream>
#include "Task.h"
#include "DateTime.h"

class TaskFloat: public Task {
private:
	std::string _taskType;
	std::string _taskDesc;
	bool _completeStatus;
	static const std::string STATUS_FALSE;
	static const std::string STATUS_TRUE;

public:
	static const std::string TASK_FLOAT;
	TaskFloat();
	~TaskFloat();
	
	void setTask(bool, std::string);
	void setTask(bool, std::string, DateTime) {return;}
	void setTask(bool, std::string, DateTime, DateTime) {return;}
	void setCompleteStatus(bool);
	void setTaskDesc(std::string);
	void setDeadline(DateTime) {return;}
	void setStartDate(DateTime) {return;}
	
	DateTime getDeadline() const {return DateTime::DateTime();}
	DateTime getStartDate() const {return DateTime::DateTime();}  

	std::string getTaskDesc() const;
	std::string getTaskType() const;
	std::string dateTimeToString() {return "";}
	std::string statusToString();
	bool getCompleteStatus() const;
	std::string outputToString();
	std::string taskDetailsToString();

	std::string taskToString();
	void stringToTask(std::string content);
};
#endif
