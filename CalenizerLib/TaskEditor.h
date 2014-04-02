//TaskEditor.h
//Beta 1.1
//Lots of code fixes because I suck
//Still untested
#include "DateTime.h"
#include <QDateTime>
#include "Task.h"
#include "TaskDeadline.h"
#include "TaskTimed.h"
#include "AnalysedData.h"
#include "TaskDeadline.h"
#include "TaskFloat.h"
#include "TaskTimed.h"
#include <assert.h>

#ifndef TASKEDITOR
#define TASKEDITOR

class TaskEditor{
private:
	void editFloat(Task* task, std::string taskDesc, QDate startDate, QTime startTime, QDate endDate, QTime endTime);
	void editDeadline(Task* task, std::string taskDesc, QDate startDate, QTime startTime, QDate endDate, QTime endTime);
	void editTimed(Task* task, std::string taskDesc, QDate startDate, QTime startTime, QDate endDate, QTime endTime);
	
	void setDesc(Task* task, std::string taskDesc);
	void setStartDate(Task* task, QDate startDate);
	void setStartTime(Task* task, QTime startTime);
	void setEndDate(Task* task, QDate endDate);
	void setEndTime(Task* task, QTime endTime);
	void upgradeToDeadline(Task* task, QDate date, QTime time);
	void upgradeToTimed(Task* task, QDate startDate, QTime startTime, QDate endDate, QTime endTime);

public:
	//Edits the given task using the given parameters. Does not make changes if the parameters are null or empty
	void edit(Task* task, AnalysedData&);
};
#endif