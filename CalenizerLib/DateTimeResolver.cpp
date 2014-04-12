//DateTimeResolver.cpp

#include "DateTimeResolver.h"

const QTime DAY_START(0,0,0);
const QTime DAY_END(23,59,0);

DateTimeResolver::DateTimeResolver(){
}

bool DateTimeResolver::resolveAdd(AnalysedData &analysedData) {
	QDate startDate = analysedData.getStartDate();
	QTime startTime = analysedData.getStartTime();
	QDate endDate = analysedData.getEndDate();
	QTime endTime = analysedData.getEndTime();
	int dayOfWeek = analysedData.getDayOfWeek();
	if(startDate.isValid()){
		endDate = setEndToDayOfWeek(startDate, endDate, dayOfWeek);
	}
	completeAdd(startDate, startTime, endDate, endTime);
	analysedData.setStartDate(startDate);
	analysedData.setStartTime(startTime);
	analysedData.setEndDate(endDate);
	analysedData.setEndTime(endTime);
	return checkDateOrderIsValid(startDate, startTime, endDate, endTime);
}

bool DateTimeResolver::resolveEdit(const Task* task, AnalysedData &analysedData){
	QDate startDate = analysedData.getStartDate();
	QTime startTime = analysedData.getStartTime();
	QDate endDate = analysedData.getEndDate();
	QTime endTime = analysedData.getEndTime();
	bool dateTimeIsUnlabelled = analysedData.getDateTimeUnlabelled();
	int dayOfWeek = analysedData.getDayOfWeek();
	if(startDate.isValid()){
		endDate = setEndToDayOfWeek(startDate, endDate, dayOfWeek);
	}
	completeEdit(task, startDate, startTime, endDate, endTime, dateTimeIsUnlabelled);
	analysedData.setStartDate(startDate);
	analysedData.setStartTime(startTime);
	analysedData.setEndDate(endDate);
	analysedData.setEndTime(endTime);
	return checkDateOrderIsValid(startDate, startTime, endDate, endTime, task);
}

void DateTimeResolver::completeEdit(const Task* task, QDate &startDate, QTime &startTime, QDate &endDate, QTime &endTime, bool dateTimeIsUnlabelled){
	//User input contains only desc
	if(startDate.isNull() && startTime.isNull() && endDate.isNull() && endTime.isNull()){
		return;
	}

	if(task->getTaskType() == TaskFloat::TASK_FLOAT){
		completeAdd(startDate, startTime, endDate, endTime);
		return;
	}

	if(task->getTaskType() == TaskDeadline::TASK_DEADLINE){
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

	if(task->getTaskType() == TaskTimed::TASK_TIMED){
		if(dateTimeIsUnlabelled){
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
			startDate = setNearestValidDay(startTime);
			return;
		}
		//Lacks start time
		if(startTime.isNull()){
			startTime = DAY_END;
			return;
		}
		return;
	}
	//Single end date/time
	if(startDate.isNull() && startTime.isNull()){
		//Lacks end date
		if(endDate.isNull()){
			endDate = setNearestValidDay(endTime);
			return;
		}
		//Lacks end time
		if(endTime.isNull()){
			endTime = DAY_END;
			return;
		}
		return;
	}

	//Cases that are missing two fields
	//Missing both dates
	if(startDate.isNull() && endDate.isNull()){
		startDate = setNearestValidDay(startTime);
		endDate = setNearestValidDay(endTime,startDate,startTime);
		return;
	}
	//Missing both times
	if(startTime.isNull() && endTime.isNull()){
		startTime = DAY_START;
		endTime = DAY_END;
		return;
	}
	//Missing start time and end date
	if(startTime.isNull() && endDate.isNull()){
		startTime = DAY_START;
		endDate = startDate;
		return;
	}
	//Missing end time and start date
	if(endTime.isNull() && startDate.isNull()){
		startDate = setNearestValidDay(startTime);
		endTime = DAY_END;
		return;
	}
	//Cases that are missing one field
	//No start date
	if(startDate.isNull()){
		startDate = setNearestValidDay(startTime);
		return;
	}
	//No start time
	if(startTime.isNull()){
		if(startDate == endDate){
			startTime = DAY_START;
		} else{
			startTime = endTime;
		}
		return;
	}
	//No end date
	if(endDate.isNull()){
		endDate = setNearestValidDay(endTime, startDate, startTime);
		return;
	}
	//No end time
	if(endTime.isNull()){
		if(startDate == endDate){
			endTime = DAY_END;
		} else{
			endTime = startTime;
		}
		return;
	}
	assert(false);
	return;
}

QDate DateTimeResolver::setNearestValidDay(QTime eventTime, QDate currDate, QTime currTime){
	assert (eventTime.isValid());
	//if the event time is later than the current time
	QDate dateToSet;
	if(eventTime > currTime){
				dateToSet = currDate;
			} else{
				dateToSet = currDate.addDays(1);
			}
	return dateToSet;
}

QDate DateTimeResolver::setEndToDayOfWeek(QDate startDate, QDate endDate, int dayOfWeek){
	assert(dayOfWeek >= -1 && dayOfWeek <= 7);
	if(dayOfWeek == 0){
		return startDate.addDays(7);
	}
	if(dayOfWeek != -1){
		endDate = startDate;
		do{
			endDate = endDate.addDays(1);
		} while(endDate.toString("dddd") != QDate::longDayName(dayOfWeek));
	}
	return endDate;
}

bool DateTimeResolver::checkDateOrderIsValid(QDate startDate, QTime startTime, QDate endDate, QTime endTime){
	if(startDate.isValid() && endDate.isValid()){
		QDateTime start;
		start.setDate(startDate);
		start.setTime(startTime);
		assert(start.isValid());
		QDateTime end;
		end.setDate(endDate);
		end.setTime(endTime);
		assert(end.isValid());

		if(start > end){
			return false;
		}
	}
	return true;
}

bool DateTimeResolver::checkDateOrderIsValid(QDate startDate, QTime startTime, QDate endDate, QTime endTime, const Task* task){
	if(task->getTaskType() == TaskTimed::TASK_TIMED){
		if(startDate.isNull()){
			startDate = task->getStartDate().getDate();
		}
		if(startTime.isNull()){
			startTime = task->getStartDate().getTime();
		}
		if(endDate.isNull()){
			endDate = task->getDeadline().getDate();
		}
		if(endTime.isNull()){
			endTime = task->getDeadline().getTime();
		}
	}
	if(startDate.isValid() && endDate.isValid()){
		QDateTime start;
		start.setDate(startDate);
		start.setTime(startTime);
		assert(start.isValid());
		QDateTime end;
		end.setDate(endDate);
		end.setTime(endTime);
		assert(end.isValid());

		if(start > end){
			return false;
		}
	}
	return true;
}