//DateTimeResolver.h
//v 1.3
//Added setEndToDayOfWeek function for ability to parse subsequent days of the week
#include "DateTime.h"
#include <QDateTime>
#include "Task.h"
#include "TaskDeadline.h"
#include "TaskFloat.h"
#include "TaskTimed.h"
#include "AnalysedData.h"
#include <assert.h>

#ifndef DATETIMERESOLVER
#define DATETIMERESOLVER

class DateTimeResolver{
private:
	QTime _dayStart;
	QTime _dayEnd;

	//Completes the date and time fields the user left blank for the case of Edit
	void completeEdit(const Task* task, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool dateTimeIsUnlabelled);
	//Completes the date and time fields the user left blank for the case of Add
	void completeAdd(QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime);
	//Given a reference 'curr' date & time, it guesses the event date given the upcoming event time
	void setNearestValidDay(QDate &dateToSet, QTime eventTime, QDate &currDate = QDate::currentDate(), QTime &currTime = QTime::currentTime());
	void setEndToDayOfWeek(QDate startDate, QDate &endDate, int dayOfWeek);
	//If there both start and end date/times are present, it checks that they are in the valid order
	bool checkDateOrderIsValid(QDate startDate, QTime startTime, QDate endDate, QTime endTime);
	bool checkDateOrderIsValid(QDate startDate, QTime startTime, QDate endDate, QTime endTime, const Task* task);

public:
	DateTimeResolver();
	//Completes the missing date or time entries as much as possible, and checks if they are in the correct order
	//Returns false if start and end date/time are not in correct order
	bool resolveAdd(AnalysedData &);
	//Completes the missing date or time entries in certain special scenarios, and checks if they are in the correct order
	//Returns false if start and end date/time are not in correct order
	bool resolveEdit(const Task* task, AnalysedData &);
};
#endif