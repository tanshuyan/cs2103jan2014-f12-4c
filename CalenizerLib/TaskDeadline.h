//@author A0094659L

// TaskDeadline.h

#ifndef TASKDEADLINE_H
#define TASKDEADLINE_H

#include <iostream>
#include <string>
#include <sstream>
#include "Task.h"
#include "DateTime.h"

class TaskDeadline: public Task {
private:
	std::string _taskType;
	DateTime _deadline;
	std::string _taskDesc;
	bool _completeStatus;
	static const std::string STATUS_FALSE;
	static const std::string STATUS_TRUE;

public:
	static const std::string TASK_DEADLINE;
	TaskDeadline();
	~TaskDeadline();

	void setTask(bool status, std::string taskDesc, DateTime deadline);
	void setTask(bool status, std::string taskDesc) {return;}
	void setTask(bool status, std::string taskDesc, DateTime deadline, DateTime startDate) {return;}
	void setCompleteStatus(bool status);
	void setTaskDesc(std::string taskDesc);
	void setDeadline(DateTime deadline);
	void setStartDate(DateTime startDate) {return;}

	DateTime getDeadline() const;
	DateTime getStartDate() const {return DateTime::DateTime();}  

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
