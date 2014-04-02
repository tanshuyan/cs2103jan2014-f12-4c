// TaskTimed.h
// v1.2
// removed setTaskType, moved tasktype-setting to the constructor
// v1.3
// Shifted tasktype string to public so it may be scoped by other classes
#pragma once
#ifndef TASKTIMED_H
#define TASKTIMED_H

#include <string>
#include <sstream>
#include "task.h"
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
	//TaskTimed(bool, std::string, DateTime, DateTime);
	~TaskTimed();

	void setTask(bool, std::string, DateTime, DateTime);
	void setTask(bool, std::string) {return;}
	void setTask(bool, std::string, DateTime) {return;}
	void setCompleteStatus(bool);
	void setTaskDesc(std::string);
	void setDeadline(DateTime);
	void setStartDate(DateTime);
	
	DateTime getDeadline() const ;
	DateTime getStartDate() const ;

	std::string getTaskDesc() const ;
	std::string getTaskType() const ;
	std::string dateTimeToString();
	std::string statusToString();
	bool getCompleteStatus() const ;
	std::string outputToString();

	// for storage
	std::string taskToString();
	void stringToTask(std::string);
	//bool operator<(TaskTimed);
};
#endif

