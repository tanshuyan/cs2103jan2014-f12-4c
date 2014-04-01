//TaskEditor.h
//Beta 1.0
//totally untested

#include "DateTime.h"
#include <QDateTime>
#include "Task.h"
#include <assert.h>

#ifndef TASKEDITOR
#define TASKEDITOR

class TaskEditor{
private:
	void editFloat(Task* task, std::string taskDesc, QDate startDate, QTime startTime, QDate endDate, QTime endTime);
	void editDeadline(Task* task, std::string taskDesc, QDate startDate, QTime startTime, QDate endDate, QTime endTime);
	void editTimed(Task* task, std::string taskDesc, QDate startDate, QTime startTime, QDate endDate, QTime endTime);
	
	void setStartDate(Task* task, QDate startDate);
	void setStartTime(Task* task, QTime startTime);
	void setEndDate(Task* task, QDate endDate);
	void setEndTime(Task* task, QTime endTime);
	void convertToDeadline(Task* task, QDate date, QTime time);
	void convertToTimed(Task* task, QDate startDate, QTime startTime, QDate endDate, QTime endTime);

public:
	//Edits the given task using the given parameters. Does not make changes if the parameters are null or empty
	void edit(Task* task, std::string taskDesc, QDate startDate, QTime startTime, QDate endDate, QTime endTime);
};
#endif