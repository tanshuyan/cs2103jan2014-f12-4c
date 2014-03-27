// TaskFilter.cpp
// v1.0
#include "TaskFilter.h"

const std::string TASK_FLOAT = "FLOAT";
const std::string TASK_TIMED = "TIMED";
const std::string TASK_DEADLINE = "DEADLINE";

TaskFilter::TaskFilter(){
}
	
bool TaskFilter::search(std::vector<Task*> &taskList, std::vector<Task*> &displayList, std::vector<std::vector<Task*>::iterator> &displayIndexList, bool status){
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

	return true;
}

bool TaskFilter::search(std::vector<Task*> &taskList, std::vector<Task*> &displayList, std::vector<std::vector<Task*>::iterator> &displayIndexList, std::string taskDesc){
	displayList.clear();
	displayIndexList.clear();

	for(std::vector<Task*>::iterator iter = taskList.begin(); iter != taskList.end(); iter++){
		if ((*iter)->getTaskDesc().find(taskDesc) != std::string::npos){
			displayList.push_back(*iter);
			displayIndexList.push_back(iter);
		}
	}
		
	if (displayList.empty()){
		return false;
	}

	return true;
}

bool TaskFilter::search(std::vector<Task*> &taskList, std::vector<Task*> &displayList, std::vector<std::vector<Task*>::iterator> &displayIndexList){
	displayList.clear();
	displayIndexList.clear();

	for(std::vector<Task*>::iterator iter = taskList.begin(); iter != taskList.end(); iter++){
			displayList.push_back(*iter);
			displayIndexList.push_back(iter);
	}
		
	if (displayList.empty()){
		return false;
	}

	return true;
}

bool TaskFilter::search(std::vector<Task*> &taskList, std::vector<Task*> &displayList, std::vector<std::vector<Task*>::iterator> &displayIndexList, QDate currentDate){
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

	return true;
}