//DateTimeResolver.cpp
//Beta 1.0
//totally untested

#include "DateTimeResolver.h"

const std::string TASK_FLOAT = "FLOAT";
const std::string TASK_DEADLINE = "DEADLINE";
const std::string TASK_TIMED = "TIMED";


DateTimeResolver::DateTimeResolver(){
	_dayStart.setHMS(0,0,0);
	_dayEnd.setHMS(23,59,0);
}
bool DateTimeResolver::resolveAdd(QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime){
	completeAdd(startDate, startTime, endDate, endTime);
	return checkDateOrderIsValid(startDate, startTime, endDate, endTime);
}

bool DateTimeResolver::resolveEdit(const Task* task, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlablled){
	completeEdit(task, startDate, startTime, endDate, endTime, dateTimeIsUnlablled);
	return checkDateOrderIsValid(startDate, startTime, endDate, endTime);
}
void DateTimeResolver::completeEdit(const Task* task, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool &dateTimeIsUnlablled){
	//User input contains only desc
	if(startDate.isNull() && startTime.isNull() && endDate.isNull() && endTime.isNull()){
		return;
	}

	if(task->getTaskType() == TASK_FLOAT){
		completeAdd(startDate, startTime, endDate, endTime);
		return;
	}

	if(task->getTaskType() == TASK_DEADLINE){
		//only start date/time
		if((startDate.isValid()||startTime.isValid()) && endDate.isNull() && endTime.isNull()){
			//If only start date/time is specified, it will be used to directly edit the deadline's end date/time
			endDate = startDate;
			endTime = startTime;
			QDate nullDate;
			startDate = nullDate;
			QTime nullTime;
			startTime = nullTime;
			return;
		}
		//only end date/time
		if((endDate.isValid()||endTime.isValid()) && startDate.isNull() && startTime.isNull()){
			return;
		}
		//only start and end times specified
		if(startDate.isNull() && startTime.isValid() && endDate.isNull() && endTime.isValid()){
			//set start date to the deadline's date
			startDate = task->getDeadline().getDate();
			completeAdd(startDate, startTime, endDate, endTime);
			return;
		}
		//only start date missing
		if(startDate.isNull() && startTime.isValid() && endDate.isValid() && endTime.isValid()){
			//set start date to the deadline's date if possible, else set to today
			if (endDate > task->getDeadline().getDate()){
				startDate = task->getDeadline().getDate();
			} else{
				startDate = QDate::currentDate();
			}
			return;
		}
		//All other cases
		completeAdd(startDate, startTime, endDate, endTime);
		return;
	}

	if(task->getTaskType() == TASK_TIMED){
		if(dateTimeIsUnlablled){
			if (startDate.isNull()){
				startDate = task->getStartDate().getDate();
			}
			if (startTime.isNull()){
				startTime = task->getStartDate().getTime();
			}
			QDateTime start;
			start.setDate(task->getStartDate().getDate());
			start.setTime(task->getStartDate().getTime());
			QDateTime end;
			end.setDate(task->getDeadline().getDate());
			end.setTime(task->getDeadline().getTime());
			qint64 gap = end.toMSecsSinceEpoch() - start.toMSecsSinceEpoch();

			start.setDate(startDate);
			start.setTime(startTime);
			end = start.addMSecs(gap);
			endDate = end.date();
			endTime = end.time();
			return;
		}
		return;
	}
	assert(false);
	return;
}


void DateTimeResolver::completeAdd(QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime){
	
	//User input contains only desc
	if(startDate.isNull() && startTime.isNull() && endDate.isNull() && endTime.isNull()){
		return;
	}
	//User input is fully completed
	if(startDate.isValid() && startTime.isValid() && endDate.isValid() && endTime.isValid()){
		return;
	}
	
	//Cases where only one field is present (and are missing the associated date/time field)
	//Single start date/time
	if(endDate.isNull() && endTime.isNull()){
		//Lacks start date
		if(startDate.isNull()){
			//set the date to either today or tomorrow, depending on current time vs. startTime
			setNearestValidDay(startDate, startTime);
			return;
		}
		//Lacks start time
		if(startTime.isNull()){
			startTime = _dayEnd;
			return;
		}
		assert(false);
		return;
	}
	//Single end date/time
	if(startDate.isNull() && startTime.isNull()){
		//Lacks end date
		if(endDate.isNull()){
			setNearestValidDay(endDate, endTime);
			return;
		}
		//Lacks start time
		if(startTime.isNull()){
			startTime = _dayEnd;
			return;
		}
		assert(false);
		return;
	}

	//Cases that are missing two fields
	//Missing both dates
	if(startDate.isNull() && endDate.isNull()){
		setNearestValidDay(startDate,startTime);
		setNearestValidDay(endDate,endTime,startDate,startTime);
		return;
	}
	//Missing both times
	if(startTime.isNull() && endTime.isNull()){
		startTime = _dayStart;
		endTime = _dayEnd;
		return;
	}

	//Cases that are missing one field
	//No start date
	if(startDate.isNull()){
		setNearestValidDay(startDate, startTime);
		return;
	}
	//No start time
	if(startTime.isNull()){
		if(startDate == endDate){
			startTime = _dayStart;
		} else{
			startTime = endTime;
		}
		return;
	}
	//No end date
	if(endDate.isNull()){
		setNearestValidDay(endDate, endTime, startDate, startTime);
		return;
	}
	//No end time
	if(endTime.isNull()){
		if(startDate == endDate){
			endTime = _dayEnd;
		} else{
			endTime = startTime;
		}
		return;
	}
	assert(false);
	return;
}

void DateTimeResolver::setNearestValidDay(QDate &dateToSet, QTime eventTime, QDate &currDate, QTime &currTime){
	assert (eventTime.isValid());
	//if the event time is later than the current time
	if(eventTime > currTime){
				dateToSet = currDate;
			} else{
				dateToSet = currDate.addDays(1);
			}
	return;
}

bool DateTimeResolver::checkDateOrderIsValid(QDate startDate, QTime startTime, QDate endDate, QTime endTime){
	if(startDate.isValid() && endDate.isValid()){
		QDateTime start;
		start.setDate(startDate);
		start.setTime(startTime);
		assert(start.isValid());
		QDateTime end;
		end.setDate(startDate);
		end.setTime(startTime);
		assert(end.isValid());

		if(start >= end){
			return false;
		}
	}
	return true;
}