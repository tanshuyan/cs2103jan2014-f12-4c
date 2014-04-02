// TaskDeadline.h
// v1.2
// removed setTaskType, moved tasktype-setting to the constructor
#pragma once
#ifndef TASKDEADLINE_H
#define TASKDEADLINE_H

#include <string>
#include <sstream>
#include "task.h"
#include "DateTime.h"

class TaskDeadline: public Task {
private:

	std::string _taskType;
	DateTime _deadline;
	std::string _taskDesc;
	bool _completeStatus;
	static const std::string TASK_DEADLINE;
	static const std::string STATUS_FALSE;
	static const std::string STATUS_TRUE;

public:
	TaskDeadline();
	TaskDeadline(bool, std::string, DateTime);
	~TaskDeadline();

	void setTask(bool, std::string, DateTime);
	void setTask(bool, std::string) {return;}
	void setTask(bool, std::string, DateTime, DateTime) {return;}
	void setCompleteStatus(bool);
	void setTaskDesc(std::string);
	void setDeadline(DateTime);
	void setStartDate(DateTime) {return;}

	DateTime getDeadline() const ;
	DateTime getStartDate() const {return DateTime::DateTime();}  

	std::string getTaskDesc() const ;
	std::string getTaskType() const ;
	std::string dateTimeToString();
	std::string statusToString();
	bool getCompleteStatus() const ;
	std::string outputToString();

	// for storage
	std::string taskToString();
	void stringToTask(std::string);
	//bool operator<(TaskDeadline);
};

#endif
