// TaskFilter.cpp
// v1.2
// added search float == display float tasks also
// added marking functions
#include "TaskFilter.h"
#include <algorithm>
#include <assert.h>

const std::string TASK_FLOAT = "FLOAT";
const std::string TASK_TIMED = "TIMED";
const std::string TASK_DEADLINE = "DEADLINE";
const std::string STATUS_OVERDUE = "overdue"; // incomplete and date overdue
const std::string STATUS_ONGOING = "ongoing"; // incomplete and scheduled for today
const std::string STATUS_COMPLETE = "complete"; // completed
const std::string STATUS_INCOMPLETE = "incomplete"; // incompleted

TaskFilter::TaskFilter(){
}


std::string TaskFilter::markTask(const Task* taskToBeMarked, DateTime currentDateTime) {
	if(taskToBeMarked->getCompleteStatus() == true) {
		return STATUS_COMPLETE;
	}

	if(taskToBeMarked->getTaskType() == TASK_FLOAT) {
		return STATUS_INCOMPLETE;
	}

	if(taskToBeMarked->getTaskType() == TASK_DEADLINE) {
		if(taskToBeMarked->getDeadline() < currentDateTime) {
			return STATUS_OVERDUE;
		}

		if( (taskToBeMarked->getDeadline().getDate() == currentDateTime.getDate()) && (taskToBeMarked->getDeadline().getTime() > currentDateTime.getTime()) ) {
			return STATUS_ONGOING;
		}
		return STATUS_INCOMPLETE;
	}

	if(taskToBeMarked->getTaskType() == TASK_TIMED) {
		if(taskToBeMarked->getDeadline() < currentDateTime) {
			return STATUS_OVERDUE;
		}
		// enddatetime is larger than current date time
		if(taskToBeMarked->getStartDate() < currentDateTime) {
			return STATUS_ONGOING;
		}
		return STATUS_INCOMPLETE;
	}

	assert(false);
}

void TaskFilter::markDisplayList(std::vector<Task*> &displayList, std::vector<std::string> &displayListStatus) {
	std::vector<Task*>::iterator iter;
	DateTime currentDateTime;
	currentDateTime.setCurrDateTime();
	//marks all the tasks in the display list
	for(iter = displayList.begin(); iter!=displayList.end(); iter++) {
		displayListStatus.push_back(markTask(*iter, currentDateTime));
	}
}

std::string TaskFilter::toUpper(std::string string) {
	for(int i = 0; i < (int) string.size(); i++) {
		string[i] = toupper(string[i]);
	}
	return string;
}

bool TaskFilter::isTaskType(std::string searchTerm) {
	searchTerm = toUpper(searchTerm);
	if(searchTerm == TASK_FLOAT || searchTerm == TASK_DEADLINE || searchTerm == TASK_TIMED) {
		return true;
	} else {
		return false;
	}
}

bool TaskFilter::search(std::vector<Task*> &taskList, std::vector<Task*> &displayList, std::vector<std::vector<Task*>::iterator> &displayIndexList, bool status, std::vector<std::string> &displayListStatus){
	displayList.clear();
	displayIndexList.clear();
	
	for(std::vector<Task*>::iterator iter = taskList.begin(); iter != taskList.end(); iter++){
		if ((*iter)->getCompleteStatus() == status && iter != taskList.end()){
			displayList.push_back(*iter);
			displayIndexList.push_back(iter);
		}
	}
	
	if (displayList.empty()){
		return false;
	}
	markDisplayList(displayList, displayListStatus);
	return true;
}

bool TaskFilter::search(std::vector<Task*> &taskList, std::vector<Task*> &displayList, std::vector<std::vector<Task*>::iterator> &displayIndexList, std::string taskDesc, std::vector<std::string> &displayListStatus){
	displayList.clear();
	displayIndexList.clear();
	std::string upperCaseTaskDesc;
	if(isTaskType(taskDesc)) {
		upperCaseTaskDesc = toUpper(taskDesc);
		for(std::vector<Task*>::iterator iter = taskList.begin(); iter != taskList.end(); iter++){
			if (((*iter)->getTaskDesc().find(taskDesc) != std::string::npos) || ((*iter)->getTaskType() == upperCaseTaskDesc)) { // either finds the search term or the same type of task
				displayList.push_back(*iter);
				displayIndexList.push_back(iter);
			}
		}
	} else {
		for(std::vector<Task*>::iterator iter = taskList.begin(); iter != taskList.end(); iter++){
			if ((*iter)->getTaskDesc().find(taskDesc) != std::string::npos) { 
				displayList.push_back(*iter);
				displayIndexList.push_back(iter);
			}
		}
	}

	if (displayList.empty()){
		return false;
	}
	markDisplayList(displayList, displayListStatus);
	return true;
}

bool TaskFilter::search(std::vector<Task*> &taskList, std::vector<Task*> &displayList, std::vector<std::vector<Task*>::iterator> &displayIndexList, std::vector<std::string> &displayListStatus) {
	displayList.clear();
	displayIndexList.clear();

	for(std::vector<Task*>::iterator iter = taskList.begin(); iter != taskList.end(); iter++){
			displayList.push_back(*iter);
			displayIndexList.push_back(iter);
	}
		
	if (displayList.empty()){
		return false;
	}
	markDisplayList(displayList, displayListStatus);
	return true;
}

bool TaskFilter::search(std::vector<Task*> &taskList, std::vector<Task*> &displayList, std::vector<std::vector<Task*>::iterator> &displayIndexList, QDate currentDate, std::vector<std::string> &displayListStatus){
	displayList.clear();
	displayIndexList.clear();

	for(std::vector<Task*>::iterator iter = taskList.begin(); iter != taskList.end(); iter++){
		// for deadline tasks, display those with deadline = today's date
		if((*iter)->getTaskType() == TASK_DEADLINE) {
			if((*iter)->getDeadline().getDate().operator==(currentDate)) {
				displayList.push_back(*iter);
				displayIndexList.push_back(iter);
			}
		}
		// for timed tasks, display those that are ongoing 	
		if((*iter)->getTaskType() == TASK_TIMED) {
			if((*iter)->getStartDate().getDate().operator<=(currentDate) && (*iter)->getDeadline().getDate().operator>=(currentDate)) {
				displayList.push_back(*iter);
				displayIndexList.push_back(iter);
			}
		}
	}

	if (displayList.empty()){
		return false;
	}
	markDisplayList(displayList, displayListStatus);
	return true;
}