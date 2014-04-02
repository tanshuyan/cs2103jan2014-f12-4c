// Task.h
// v1.3
// removed setTaskType, moved tasktype-setting to the constructor
// added taskDetailsToString
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

	virtual void setTask(bool, std::string) {return;}
	virtual void setTask(bool, std::string, DateTime) {return;}
	virtual void setTask(bool, std::string, DateTime, DateTime) {return;}
	virtual void setCompleteStatus(bool) {return;}
	virtual void setTaskDesc(std::string) {return;}
	virtual void setDeadline(DateTime) {return;}
	virtual void setStartDate(DateTime) {return;}
	
	virtual DateTime getDeadline() const {return DateTime::DateTime();}
	virtual DateTime getStartDate() const {return DateTime::DateTime();}  

	virtual std::string taskDetailsToString() {return "";}
	virtual std::string dateTimeToString() {return "";}
	virtual std::string statusToString() {return "";}
	virtual std::string getTaskDesc() const {return "";}
	virtual std::string getTaskType() const {return "";}
	virtual bool getCompleteStatus() const  {return false;}
	virtual std::string outputToString() {return "";}
	virtual std::string taskToString() {return "";}
	virtual void stringToTask(std::string) {return;}
	//virtual bool operator<(Task) {return false;}
};

#endif
