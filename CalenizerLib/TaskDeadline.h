// taskDeadline.h
// v1.1
// added operator <
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
	static const std::string STATUS_FALSE;
	static const std::string STATUS_TRUE;

public:
	TaskDeadline();
	TaskDeadline(std::string, bool, std::string, DateTime);
	~TaskDeadline();

	void setTask(std::string, bool, std::string, DateTime);
	void setTask(std::string, bool, std::string) {return;}
	void setTask(std::string, bool, std::string, DateTime, DateTime) {return;}
	void setTaskType(std::string);
	void setCompleteStatus(bool);
	void setTaskDesc(std::string);
	void setDeadline(DateTime);
	void setStartDate(DateTime) {return;}

	DateTime getDeadline() const ;
	DateTime getStartDate() const {return DateTime::DateTime();}  


	std::string getTaskDesc() const ;
	std::string getTaskType() const ;
	std::string statusToString();
	std::string dateTimeToString();
	bool getCompleteStatus() const ;
	std::string outputToString();
	// for storage
	std::string taskToString();
	void stringToTask(std::string);
	//bool operator<(TaskDeadline);
};

#endif
