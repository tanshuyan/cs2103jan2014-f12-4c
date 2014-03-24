// TaskFilter.cpp
// v1.0
#include "TaskFilter.h"

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