// TaskFilter.cpp
// v1.2
// added search float == display float tasks also
// added marking functions
#include "TaskFilter.h"

TaskFilter::TaskFilter(){
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
		if((*iter)->getTaskType() == TaskDeadline::TASK_DEADLINE) {
			if((*iter)->getDeadline().getDate().operator==(currentDate)) {
				displayList.push_back(*iter);
				displayIndexList.push_back(iter);
			}
		}
		// for timed tasks, display those that are ongoing 	
		if((*iter)->getTaskType() == TaskTimed::TASK_TIMED) {
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

bool TaskFilter::isTaskType(std::string searchTerm) {
	searchTerm = toUpper(searchTerm);
	if(searchTerm == TaskFloat::TASK_FLOAT || searchTerm == TaskDeadline::TASK_DEADLINE || searchTerm == TaskTimed::TASK_TIMED) {
		return true;
	} else {
		return false;
	}
}

std::string TaskFilter::toUpper(std::string string) {
	for(int i = 0; i < (int) string.size(); i++) {
		string[i] = toupper(string[i]);
	}
	return string;
}

std::string TaskFilter::markTask(const Task* taskToBeMarked, DateTime currentDateTime) {
	if(taskToBeMarked->getCompleteStatus() == true) {
		return DisplayOutput::STATUS_COMPLETE;
	}

	if(taskToBeMarked->getTaskType() == TaskFloat::TASK_FLOAT) {
		return DisplayOutput::STATUS_INCOMPLETE;
	}

	if(taskToBeMarked->getTaskType() == TaskDeadline::TASK_DEADLINE) {
		if(taskToBeMarked->getDeadline() < currentDateTime) {
			return DisplayOutput::STATUS_OVERDUE;
		}

		if( (taskToBeMarked->getDeadline().getDate() == currentDateTime.getDate()) && (taskToBeMarked->getDeadline().getTime() > currentDateTime.getTime()) ) {
			return DisplayOutput::STATUS_ONGOING;
		}
		return DisplayOutput::STATUS_INCOMPLETE;
	}

	if(taskToBeMarked->getTaskType() == TaskTimed::TASK_TIMED) {
		if(taskToBeMarked->getDeadline() < currentDateTime) {
			return DisplayOutput::STATUS_OVERDUE;
		}
		if(taskToBeMarked->getStartDate() < currentDateTime) {
			return DisplayOutput::STATUS_ONGOING;
		}
		return DisplayOutput::STATUS_INCOMPLETE;
	}
	assert(false);
	return DisplayOutput::STATUS_INCOMPLETE;
}

void TaskFilter::markDisplayList(const std::vector<Task*> &displayList, std::vector<std::string> &displayListStatus) {
	std::vector<Task*>::const_iterator iter;
	DateTime currentDateTime;
	currentDateTime.setCurrDateTime();
	for(iter = displayList.begin(); iter!=displayList.end(); iter++) {
		displayListStatus.push_back(markTask(*iter, currentDateTime));
	}
}
