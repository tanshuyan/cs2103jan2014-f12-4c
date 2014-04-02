//TaskEditor.cpp
//Beta 1.0
//totally untested
#include "TaskEditor.h"

const std::string TASK_FLOAT = "FLOAT";
const std::string TASK_DEADLINE = "DEADLINE";
const std::string TASK_TIMED = "TIMED";

void TaskEditor::edit(Task* task, AnalysedData &analysedData){
	std::string taskDesc = analysedData.getTaskDesc();
	QDate startDate = analysedData.getStartDate();
	QTime startTime = analysedData.getStartTime();
	QDate endDate = analysedData.getEndDate();
	QTime endTime = analysedData.getEndTime();
	
	if(task->getTaskType() == TASK_FLOAT){
		editFloat(task, taskDesc, startDate, startTime, endDate, endTime);
	}
	if(task->getTaskType() == TASK_DEADLINE){
		editDeadline(task, taskDesc, startDate, startTime, endDate, endTime);
	}
	if(task->getTaskType() == TASK_TIMED){
		editTimed(task, taskDesc, startDate, startTime, endDate, endTime);
	}
	assert(false);
	return;
}

void TaskEditor::editFloat(Task* task, std::string taskDesc, QDate startDate, QTime startTime, QDate endDate, QTime endTime){
	QString desc(taskDesc.c_str());
	//updates desc only if field is not empty
	if(!desc.trimmed().isEmpty()){
		task->setTaskDesc(desc.trimmed().toStdString());
	}
	//Only desc to change
	if(startDate.isNull() && startTime.isNull() && endDate.isNull() && endTime.isNull()){
		return;
	}
	//Only start date/time
	if(startDate.isValid() && startTime.isValid() && endDate.isNull() && endTime.isNull()){
		convertToDeadline(task, startDate, startTime);
		return;
	}
	//Only end date/time
	if(startDate.isNull() && startTime.isNull() && endDate.isValid() && endTime.isValid()){
		convertToDeadline(task, endDate, endTime);
		return;
	}
	//Both start date/time and end date/time
	if(startDate.isValid() && startTime.isValid() && endDate.isValid() && endTime.isValid()){
		convertToTimed(task, startDate, startTime, endDate, endTime);
		return;
	}
	assert(false);
	return;
}

void TaskEditor::editDeadline(Task* task, std::string taskDesc, QDate startDate, QTime startTime, QDate endDate, QTime endTime){
	QString desc(taskDesc.c_str());
	//updates desc only if field is not empty
	if(!desc.trimmed().isEmpty()){
		task->setTaskDesc(desc.trimmed().toStdString());
	}

	//Only desc to change
	if(startDate.isNull() && startTime.isNull() && endDate.isNull() && endTime.isNull()){
		return;
	}
	//Only start date to change
	if(startDate.isValid() && startTime.isNull() && endDate.isNull() && endTime.isNull()){
		setStartDate(task, startDate);
		return;
	}
	//Only start time to change
	if(startDate.isNull() && startTime.isValid() && endDate.isNull() && endTime.isNull()){
		setStartTime(task, startTime);
		return;
	}
	//Only end date to change
	if(startDate.isNull() && startTime.isNull() && endDate.isValid() && endTime.isNull()){
		setEndDate(task, endDate);
		return;
	}
	//Only end time to change
	if(startDate.isNull() && startTime.isNull() && endDate.isNull() && endTime.isValid()){
		setEndTime(task, endTime);
		return;
	}
	//Only start date/time
	if(startDate.isValid() && startTime.isValid() && endDate.isNull() && endTime.isNull()){
		convertToDeadline(task, startDate, startTime);
		return;
	}
	//Only end date/time
	if(startDate.isNull() && startTime.isNull() && endDate.isValid() && endTime.isValid()){
		convertToDeadline(task, endDate, endTime);
		return;
	}
	//Both start date/time and end date/time
	if(startDate.isValid() && startTime.isValid() && endDate.isValid() && endTime.isValid()){
		convertToTimed(task, startDate, startTime, endDate, endTime);
		return;
	}
	assert(false);
	return;
}

void TaskEditor::editTimed(Task* task, std::string taskDesc, QDate startDate, QTime startTime, QDate endDate, QTime endTime){
	QString desc(taskDesc.c_str());
	//updates desc only if field is not empty
	if(!desc.trimmed().isEmpty()){
		task->setTaskDesc(desc.trimmed().toStdString());
	}
	//updates date/time fields only if they are valid
	if(startDate.isValid()){
		setStartDate(task, startDate);
	}
	if(startTime.isValid()){
		setStartTime(task, startTime);
	}
	if(endDate.isValid()){
		setEndDate(task, endDate);
	}
	if(endTime.isValid()){
		setEndTime(task, endTime);
	}
	return;
}

void TaskEditor::setStartDate(Task* task, QDate startDate){
	DateTime start(task->getStartDate());
	start.setDate(startDate);
	task->setDeadline(start);
	return;
}

void TaskEditor::setStartTime(Task* task, QTime startTime){
	DateTime start(task->getStartDate());
	start.setTime(startTime);
	task->setDeadline(start);
	return;
}

void TaskEditor::setEndDate(Task* task, QDate endDate){
	DateTime deadline(task->getDeadline());
	deadline.setDate(endDate);
	task->setDeadline(deadline);
	return;
}

void TaskEditor::setEndTime(Task* task, QTime endTime){
	DateTime deadline(task->getDeadline());
	deadline.setTime(endTime);
	task->setDeadline(deadline);
	return;
}

void TaskEditor::convertToDeadline(Task* task, QDate date, QTime time){
	task->setTaskType(TASK_DEADLINE);
	DateTime deadline;
	deadline.setDate(date);
	deadline.setTime(time);
	task->setDeadline(deadline);
	return;
}

void TaskEditor::convertToTimed(Task* task, QDate startDate, QTime startTime, QDate endDate, QTime endTime){
	task->setTaskType(TASK_TIMED);
	DateTime start;
	start.setDate(startDate);
	start.setTime(startTime);
	DateTime deadline;
	deadline.setDate(endDate);
	deadline.setTime(endTime);
	task->setStartDate(start);
	task->setDeadline(deadline);
	return;
}