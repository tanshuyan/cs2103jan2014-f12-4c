// TaskTimed.h
// v1.1
// added operator <
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
	TaskTimed();
	//TaskTimed(std::string, bool, std::string, DateTime, DateTime);
	~TaskTimed();

	void setTask(std::string, bool, std::string, DateTime, DateTime);
	void setTask(std::string, bool, std::string) {return;}
	void setTask(std::string, bool, std::string, DateTime) {return;}
	void setCompleteStatus(bool);
	void setTaskDesc(std::string);
	void setDeadline(DateTime);
	void setStartDate(DateTime);
	void setTaskType(std::string);
	
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

