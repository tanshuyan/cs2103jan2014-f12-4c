// Task.h

#ifndef TASK_H
#define TASK_H

#include <string>
#include <sstream>
#include "DateTime.h"

class Task {
public:
	virtual void setTask(bool status, std::string taskDesc) {return;}
	virtual void setTask(bool status, std::string taskDesc, DateTime) {return;}
	virtual void setTask(bool status, std::string taskDesc, DateTime, DateTime) {return;}
	virtual void setCompleteStatus(bool status) {return;}
	virtual void setTaskDesc(std::string taskDesc) {return;}
	virtual void setDeadline(DateTime deadline) {return;}
	virtual void setStartDate(DateTime startDate) {return;}
	
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
	virtual void stringToTask(std::string content) {return;}
};

#endif
