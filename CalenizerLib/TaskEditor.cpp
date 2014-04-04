//TaskEditor.cpp
//v 1.2
//Bug fixes
#include "TaskEditor.h"

void TaskEditor::edit(Task* &task, AnalysedData &analysedData){
	std::string taskDesc = analysedData.getTaskDesc();
	QDate startDate = analysedData.getStartDate();
	QTime startTime = analysedData.getStartTime();
	QDate endDate = analysedData.getEndDate();
	QTime endTime = analysedData.getEndTime();
	
	if(task->getTaskType() == TaskFloat::TASK_FLOAT){
		editFloat(task, taskDesc, startDate, startTime, endDate, endTime);
	}
	if(task->getTaskType() == TaskDeadline::TASK_DEADLINE){
		editDeadline(task, taskDesc, startDate, startTime, endDate, endTime);
	}
	if(task->getTaskType() == TaskTimed::TASK_TIMED){
		editTimed(task, taskDesc, startDate, startTime, endDate, endTime);
	}
	return;
}

void TaskEditor::editFloat(Task* &task, std::string taskDesc, QDate startDate, QTime startTime, QDate endDate, QTime endTime){
	//Updates desc if field is not empty
	setDesc(task, taskDesc);
	//Only desc to change
	if(startDate.isNull() && startTime.isNull() && endDate.isNull() && endTime.isNull()){
		return;
	}
	//Only start date/time
	if(startDate.isValid() && startTime.isValid() && endDate.isNull() && endTime.isNull()){
		upgradeToDeadline(task, startDate, startTime);
		return;
	}
	//Only end date/time
	if(startDate.isNull() && startTime.isNull() && endDate.isValid() && endTime.isValid()){
		upgradeToDeadline(task, endDate, endTime);
		return;
	}
	//Both start date/time and end date/time
	if(startDate.isValid() && startTime.isValid() && endDate.isValid() && endTime.isValid()){
		upgradeToTimed(task, startDate, startTime, endDate, endTime);
		return;
	}
	assert(false);
	return;
}

void TaskEditor::editDeadline(Task* &task, std::string taskDesc, QDate startDate, QTime startTime, QDate endDate, QTime endTime){
	//Updates desc if field is not empty
	setDesc(task, taskDesc);
	//Only desc to change
	if(startDate.isNull() && startTime.isNull() && endDate.isNull() && endTime.isNull()){
		return;
	}
	//Only date to change
	if(startDate.isValid() && startTime.isNull() && endDate.isNull() && endTime.isNull()){
		setEndDate(task, startDate);
		return;
	}
	if(startDate.isNull() && startTime.isNull() && endDate.isValid() && endTime.isNull()){
		setEndDate(task, endDate);
		return;
	}
	//Only time to change
	if(startDate.isNull() && startTime.isValid() && endDate.isNull() && endTime.isNull()){
		setEndTime(task, startTime);
		return;
	}
	if(startDate.isNull() && startTime.isNull() && endDate.isNull() && endTime.isValid()){
		setEndTime(task, endTime);
		return;
	}
	//Both date/time to change
	if(startDate.isValid() && startTime.isValid() && endDate.isNull() && endTime.isNull()){
		setEndDate(task, startDate);
		setEndTime(task, startTime);
		return;
	}
	if(startDate.isNull() && startTime.isNull() && endDate.isValid() && endTime.isValid()){
		setEndDate(task, endDate);
		setEndTime(task, endTime);
		return;
	}
	//Both start date/time and end date/time (upgrade to timed task)
	if(startDate.isValid() && startTime.isValid() && endDate.isValid() && endTime.isValid()){
		upgradeToTimed(task, startDate, startTime, endDate, endTime);
		return;
	}
	assert(false);
	return;
}

void TaskEditor::editTimed(Task* task, std::string taskDesc, QDate startDate, QTime startTime, QDate endDate, QTime endTime){
	//Updates desc if field is not empty
	setDesc(task, taskDesc);
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

void TaskEditor::setDesc(Task* task, std::string taskDesc){
	QString desc(taskDesc.c_str());
	//updates desc only if field is not empty
	if(!desc.trimmed().isEmpty()){
		task->setTaskDesc(desc.trimmed().toStdString());
	}
	return;
}

void TaskEditor::setStartDate(Task* task, QDate startDate){
	DateTime start(task->getStartDate());
	start.setDate(startDate);
	task->setStartDate(start);
	return;
}

void TaskEditor::setStartTime(Task* task, QTime startTime){
	DateTime start(task->getStartDate());
	start.setTime(startTime);
	task->setStartDate(start);
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

void TaskEditor::upgradeToDeadline(Task* &task, QDate date, QTime time){
	DateTime deadline(date, time);
	std::string desc = task->getTaskDesc();
	bool status = task->getCompleteStatus();
	delete task;
	task = new TaskDeadline;
	task->setTask(status,desc,deadline);
	return;
}

void TaskEditor::upgradeToTimed(Task* &task, QDate startDate, QTime startTime, QDate endDate, QTime endTime){
	DateTime start(startDate, startTime);
	DateTime deadline(endDate, endTime);
	std::string desc = task->getTaskDesc();
	bool status = task->getCompleteStatus();
	delete task;
	task = new TaskTimed;
	task->setTask(status,desc,start,deadline);
	return;
}