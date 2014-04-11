// TaskTimed.h

#ifndef TASKTIMED_H
#define TASKTIMED_H

#include <iostream>
#include <string>
#include <sstream>
#include "Task.h"
#include "DateTime.h"

class TaskTimed: public Task {
private:
	std::string _taskType;
	std::string _taskDesc;
	bool _completeStatus;
	DateTime _startDateTime;
	DateTime _endDateTime;
	static const std::string STATUS_FALSE;
	static const std::string STATUS_TRUE;

public:
	static const std::string TASK_TIMED;
	TaskTimed();
	~TaskTimed();

	void setTask(bool status, std::string taskDesc, DateTime deadline, DateTime startDate);
	void setTask(bool status, std::string taskDesc) {return;}
	void setTask(bool status, std::string taskDesc, DateTime deadline) {return;}
	void setCompleteStatus(bool status);
	void setTaskDesc(std::string taskDesc);
	void setDeadline(DateTime deadline);
	void setStartDate(DateTime startDate);
	
	DateTime getDeadline() const;
	DateTime getStartDate() const;

	std::string getTaskDesc() const;
	std::string getTaskType() const;
	std::string dateTimeToString();
	std::string statusToString();
	bool getCompleteStatus() const;
	std::string outputToString();
	std::string taskDetailsToString();

	std::string taskToString();
	void stringToTask(std::string content);
};
#endif

