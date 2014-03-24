// task.h
// v1.0
#pragma once
#ifndef TASK_H
#define TASK_H

#include <string>
#include <sstream>
#include "DateTime.h"
/*
enum TaskType {
		DEADLINE, FLOAT, TIMED
};
*/
class Task {
private:
	
public:
	//Task();
	//~Task();

	virtual void setTaskType(std::string) {return;}
	virtual void setTask(std::string, bool, std::string) {return;}
	virtual void setTask(std::string, bool, std::string, DateTime) {return;}
	virtual void setTask(std::string, bool, std::string, DateTime, DateTime) {return;}
	virtual void setCompleteStatus(bool) {return;}
	virtual void setTaskDesc(std::string) {return;}
	virtual void setDeadline(DateTime) {return;}
	virtual void setStartDate(DateTime) {return;}
	
	virtual DateTime getDeadline() {return DateTime::DateTime();}
	virtual DateTime getStartDate() {return DateTime::DateTime();}  
	virtual std::string dateTimeToString() {return "";}
	virtual std::string statusToString() {return "";}
	virtual std::string getTaskDesc() {return "";}
	virtual std::string getTaskType() {return "";}
	virtual bool getCompleteStatus() {return false;}
	virtual std::string outputToString() {return "";}
	virtual std::string taskToString() {return "";}
	virtual void stringToTask(std::string) {return;}
	
};

#endif
